/*
    This file is part of GoM.

    GoM is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GoM is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GoM.  If not, see <http://www.gnu.org/licenses/>.

--

    Este fichero forma parte de GoM.

    GoM es sotware libre: podrá redistribuirlo y/o modificarlo
    bajo los términos de la GNU General Public License según es publicada
    por la Free Software Fundation, tanto para la versión 3 de la
    licencia como para cualquier versión posterior (según su elección).

    GoM se distribuye con la esperanza de ser útil, pero SIN NINGUNA
    GARANTÍA, incluso sin garantía MERCANTIL implícita o CONVENIENCIA
    PARA UN PROPÓSITO PARTICULAR. Vea la GNU General Public License
    para más detalles.

    Debió recibir una copia de la GNU General Public License
    junto a GoM. Si no es así, visite <http://www.gnu.org/licenses/>.

*/

/*! \file GestorEjercitos.cpp
 *  \brief Fichero que implementa al gestor de ejércitos.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <set>
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_rotozoom.h"
#include "GestorEjercitos.h"

using namespace std;

const string dir = "Ejercitos/";
const string dirlist = "CodigoFuente/Interfaz/GestorEjercitos/";

// RefUnidad::RefUnidad
/*************************************/
RefUnidad::RefUnidad()
{
  u = 0;
}

// RefUnidad::RefUnidad
/*************************************/
RefUnidad::RefUnidad(string _unidad, Ejercito *e, double fw, double fh) : nombreUnidad(_unidad)
{
  u = e->NuevaUnidad(nombreUnidad, fw, fh);

  u->NuevaPO(Punto(0, 150), 0);
}

// RefUnidad::Nombre
/*************************************/
Unidad* RefUnidad::unidad() const
{
  return (u);
}

// RefUnidad::Nombre
/*************************************/
string RefUnidad::Nombre() const
{
  return (nombreUnidad);
}

// RefUnidad::X
/*************************************/
unsigned RefUnidad::X() const
{
  return ((unsigned)u->Psi().x);
}

// RefUnidad::Y
/*************************************/
unsigned RefUnidad::Y() const
{
  return ((unsigned)u->Psi().y);
}

// RefUnidad::N
/*************************************/
unsigned RefUnidad::N() const
{
  return (u->N());
}

// RefUnidad::F
/*************************************/
unsigned RefUnidad::F() const
{
  return (u->Frente());
}

// RefUnidad::Puntos
/*************************************/
unsigned RefUnidad::Puntos() const
{
  return (u->Puntos());
}

// RefUnidad::NuevoX
/*************************************/
void RefUnidad::NuevoX(unsigned x)
{
  u->NuevaPO(Punto(x, u->Psi().y), 0);
}

// RefUnidad::NuevoY
/*************************************/
void RefUnidad::NuevoY(unsigned y)
{
  u->NuevaPO(Punto(u->Psi().x, y), 0);
}

// RefUnidad::NuevoN
/*************************************/
void RefUnidad::NuevoN(unsigned n)
{
	if (n > u->MaxEfecs())
		n = u->MaxEfecs();

  if (n > u->MinEfecs())
    {
      if (u->N() > n)
				u->MenosEfectivos(u->N() - n);
      else
				u->MasEfectivos(n - u->N());
    }
}

// RefUnidad::NuevoF
/*************************************/
void RefUnidad::NuevoF(unsigned f)
{
  if (f > 4)
    u->NuevoFrente(f);
}

// RefEjercito::RefEjercito
/*************************************/
RefEjercito::RefEjercito()
{
  raza = "";
  e = 0;
}

// RefEjercito::RefEjercito
/*************************************/
RefEjercito::RefEjercito(string _raza, Ejer _e) : raza(_raza)
{
  ejercitoLeido = false;

  if (raza == "Humanos")
    e = new Humanos(_e);
  else if (raza == "Orcos")
    e = new Orcos(_e);
  else
    e = 0;
}

// RefEjercito::~RefEjercito
/*************************************/
RefEjercito::~RefEjercito()
{
  if (e && !ejercitoLeido)
    delete e;
}

// RefEjercito::Puntos
/*************************************/
unsigned RefEjercito::Puntos() const
{
  unsigned puntos = 0;

  for (map<int, RefUnidad>::const_iterator i = vUnidades.begin(); i != vUnidades.end(); ++i)
    puntos += i->second.Puntos();

  return (puntos);
}

// RefEjercito::Raza
/*************************************/
string RefEjercito::Raza() const
{
  return (raza);
}

// RefEjercito::Unidad
/*************************************/
RefUnidad& RefEjercito::unidad(int iUnidad)
{
  return (vUnidades[iUnidad]);
}

// RefEjercito::Unidad
/*************************************/
RefUnidad& RefEjercito::unidad(unsigned iUnidad)
{
  if (iUnidad >= vUnidades.size())
    iUnidad = vUnidades.size() - 1;

	map<int, RefUnidad>::iterator i = vUnidades.begin();
			
	while (iUnidad--)
		++i;
	
	return (i->second);
}

// RefEjercito::N
/*************************************/
unsigned RefEjercito::N() const
{
  return (vUnidades.size());
}

// RefEjercito::Verificar
/*************************************/
vector<int> RefEjercito::Verificar() const
{
  vector<int> vUnids;

  typedef map<int, RefUnidad>::const_iterator I;

  Rectangulo despliege(Punto(0, 150), 1280, 150, 0);

  for (I i = vUnidades.begin(); i != vUnidades.end(); ++i)
    {
      bool eliminar = false;

      Rectangulo R(i->second.unidad()->R());

      if (!(despliege << R))
				eliminar = true;

			R = R.Ensanchar(15 * sqrt(2));

      I k = i;
      for (I j = ++k; j != vUnidades.end(); ++j)
				if (R * j->second.unidad()->R())
					{
						vUnids.push_back(j->first);
						eliminar = true;
					}

      if (eliminar)
				vUnids.push_back(i->first);
    }

  return (vUnids);
}

// RefEjercito::Ejercito
/*************************************/
Ejercito* RefEjercito::ejercito() const
{
  ejercitoLeido = true;

  return (e);
}

// RefEjercito::NuevaUnidad
/*************************************/
RefUnidad& RefEjercito::NuevaUnidad(int iUnidad, string unidad, double fw, double fh)
{
  vUnidades[iUnidad] = RefUnidad(unidad, e, fw, fh);

  return (vUnidades[iUnidad]);
}

// RefEjercito::EliminarUnidad
/*************************************/
void RefEjercito::EliminarUnidad(int iUnidad)
{
  typedef map<int, RefUnidad>::iterator I;

	map<int, RefUnidad> aux;

  I i = vUnidades.find(iUnidad);

  if (i != vUnidades.end())
    {
      unsigned j = 0;

      for (I k = vUnidades.begin(); k != i; ++k)
				{
					aux[k->first] = k->second;
					++j;
				}

      e->EliminarUnidad(j);

			for (I k = ++i; k != vUnidades.end(); ++k)
				aux[k->first - 1] = k->second;

      vUnidades = aux;
    }}

// GestorEjercitos::GestorEjercitos
/*************************************/
GestorEjercitos::GestorEjercitos(SDL_Surface *screen, double _fw, double _fh) : screen(screen), fw(_fw), fh(_fh)
{
  SDL_Surface *pElegirEjercitosOr, *pCrearEjercitoOr, *pElegirFicheroOr, *pCrearFicheroOr;
  SDL_Surface *selectorOr, *marcadorOr, *subrayadorOr, *puntoOr, *puntoSelOr, *marcaOr;
  SDL_Surface *cajaTextoOr;
 
  if (!(pElegirEjercitosOr = IMG_Load ("Imagenes/Menu/ElegirEjercitos.png")))
    cerr << SDL_GetError() << endl;
  if (!(pCrearEjercitoOr = IMG_Load ("Imagenes/Menu/CrearEjercito.png")))
    cerr << SDL_GetError() << endl;
  if (!(pElegirFicheroOr = IMG_Load ("Imagenes/Menu/ElegirFichero.png")))
    cerr << SDL_GetError() << endl;
  if (!(pCrearFicheroOr = IMG_Load ("Imagenes/Menu/CrearFichero.png")))
    cerr << SDL_GetError() << endl;

  if (!(selectorOr = IMG_Load ("Imagenes/Especiales/Selector.png")))
    cerr << SDL_GetError() << endl;
  if (!(marcadorOr = IMG_Load ("Imagenes/Especiales/Seleccionado.png")))
    cerr << SDL_GetError() << endl;
  if (!(subrayadorOr = IMG_Load ("Imagenes/Especiales/Subrayador.png")))
    cerr << SDL_GetError() << endl;

  if (!(puntoOr = IMG_Load ("Imagenes/Especiales/Punto.png")))
    cerr << SDL_GetError() << endl;
  if (!(puntoSelOr = IMG_Load ("Imagenes/Especiales/PuntoSel.png")))
    cerr << SDL_GetError() << endl;
  if (!(marcaOr = IMG_Load ("Imagenes/Especiales/Marca.png")))
    cerr << SDL_GetError() << endl;

  if (!(cajaTextoOr = IMG_Load ("Imagenes/Especiales/CuadroEj.png")))
    cerr << SDL_GetError() << endl;
  if (!(fuenteN = TTF_OpenFont ("Imagenes/Fuentes/FreeSansOblique.ttf", 12)))
    cerr << SDL_GetError() << endl;
  if (!(fuenteP = TTF_OpenFont ("Imagenes/Fuentes/FreeSansOblique.ttf", 20)))
    cerr << SDL_GetError() << endl;

  TTF_SetFontStyle (fuenteN, TTF_STYLE_BOLD);
  TTF_SetFontStyle (fuenteP, TTF_STYLE_BOLD);

  if (!(pElegirEjercitos = zoomSurface (pElegirEjercitosOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;
  if (!(pCrearEjercito = zoomSurface (pCrearEjercitoOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;
  if (!(pElegirFichero = zoomSurface (pElegirFicheroOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;
  if (!(pCrearFichero = zoomSurface (pCrearFicheroOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;
  if (!(selector = zoomSurface (selectorOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;
  if (!(marcador = zoomSurface (marcadorOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;
  if (!(subrayador = zoomSurface (subrayadorOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;
  if (!(punto = zoomSurface (puntoOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;
  if (!(puntoSel = zoomSurface (puntoSelOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;
  if (!(marca = zoomSurface (marcaOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;
  if (!(cajaTexto = zoomSurface (cajaTextoOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;

  color.r = 0;
  color.g = 0;
  color.b = 0;

  delete pElegirEjercitosOr;
  delete pCrearEjercitoOr;
  delete pElegirFicheroOr;
  delete pCrearFicheroOr;
  delete selectorOr;
  delete marcadorOr;
  delete subrayadorOr;
  delete puntoOr;
  delete puntoSelOr;
  delete marcaOr;
  delete cajaTextoOr;
}

// GestorEjercitos::ElegirEjercitos
/*************************************/
void GestorEjercitos::ElegirEjercitos(Ejercito **e, Ejercito **f)
{
  string ejercitoleido;
  SDL_Event evento;

  SDL_Rect rlistaEjercitos = { 130 * fw, 275 * fh, 266 * fw, 250 * fh };
  SDL_Rect rejercito1 = { 630 * fw, 273 * fh, 400 * fw, 16 };
  SDL_Rect rejercito2 = { 630 * fw, 337 * fh, 400 * fw, 16 };
  SDL_Rect flechaEjercito1 = { 515 * fw, 260 * fh, 85 * fw, 40 * fh };
  SDL_Rect flechaEjercito2 = { 515 * fw, 325 * fh, 85 * fw, 40 * fh };
  SDL_Rect flechaVolver = { 747 * fw, 525 * fh, 200 * fw, 92 * fh };
  SDL_Rect flechaAceptar = { 955 * fw, 525 * fh, 200 * fw, 92 * fh };
  SDL_Rect subflechaEjercito1 = { 520 * fw, 305 * fh, 40 * fw, 8 * fh };
  SDL_Rect subflechaEjercito2 = { 520 * fw, 370 * fh, 40 * fw, 8 * fh };
  SDL_Rect subflechaVolver = { 843 * fw, 590 * fh, 40 * fw, 8 * fh };
  SDL_Rect subflechaAceptar = { 1020 * fw, 590 * fh, 40 * fw, 8 * fh };

  ListaTexto ficheros(fuenteN, color, rlistaEjercitos, selector, marcador);
  ListaTexto ejercito1(fuenteN, color, rejercito1, NULL, NULL);
  ListaTexto ejercito2(fuenteN, color, rejercito2, NULL, NULL);

  int iejercito1 = ejercito1.SiguienteId();
  int iejercito2 = ejercito2.SiguienteId();

  bool bflechaEjercito1 = false;
  bool bflechaEjercito2 = false;
  bool bflechaVolver = false;
  bool bflechaAceptar = false;

  *e = NULL;
  *f = NULL;

  ifstream i((dirlist + "Ejercitos.txt").c_str());

  if (!i)
    {
      cerr << "GestorEjercitos::ElegirEjercitos: No se pudo abrir el fichero de ejércitos disponibles" << endl;
      exit(EXIT_FAILURE);
    }

  while (getline(i, ejercitoleido))
    ficheros.NuevoTexto(ejercitoleido);

  i.close();

  bool bucle = true;
	bool comprobar = false;
  bool bejercito1 = false;
  bool bejercito2 = false;
	bool bimprimir = true;
  while (bucle)
    {
      SDL_Delay (40);

			if (bimprimir)
				{
					bimprimir = false;

					SDL_BlitSurface(pElegirEjercitos, NULL, screen, NULL);

					ficheros.Imprimir(screen);
					ejercito1.Imprimir(screen);
					ejercito2.Imprimir(screen);

					if (bflechaEjercito1)
						SDL_BlitSurface (subrayador, NULL, screen, &subflechaEjercito1);
					else if (bflechaEjercito2)
						SDL_BlitSurface (subrayador, NULL, screen, &subflechaEjercito2);
					else if (bflechaVolver)
						SDL_BlitSurface (subrayador, NULL, screen, &subflechaVolver);
					else if (bflechaAceptar)
						SDL_BlitSurface (subrayador, NULL, screen, &subflechaAceptar);

					SDL_Flip(screen);
				}

			if (!SDL_PollEvent(&evento))  // Si no quedaban eventos, duermo el sistema
				SDL_WaitEvent(&evento);     // hasta que los haya.

			do
				{
					if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT)
						{
							if (InRect(flechaVolver, evento.button.x, evento.button.y))
								bucle = false;
							else if (InRect(flechaAceptar, evento.button.x, evento.button.y) && bejercito1 && bejercito2)
								comprobar = true;
							else if (InRect(flechaEjercito1, evento.button.x, evento.button.y))
								{
									int ifich = ficheros.Marcado();
		  
									if (ifich != iNULO)
										{
											bimprimir = true;
											ejercito1.ModificarTexto(iejercito1, ficheros.LeerTexto(ifich));
											bejercito1 = true;
										}
								}
							else if (InRect(flechaEjercito2, evento.button.x, evento.button.y))
								{
									int ifich = ficheros.Marcado();

									if (ifich != iNULO)
										{
											bimprimir = true;
											ejercito2.ModificarTexto(iejercito2, ficheros.LeerTexto(ifich));
											bejercito2 = true;
										}
								}
							else
								{
									bimprimir = true;
									ficheros.Evento (evento.button.x, evento.button.y, true);
								}
						}
					else if (evento.type == SDL_MOUSEMOTION)
						{
							if (InRect(flechaVolver, evento.button.x, evento.button.y))
								{
									bimprimir = true;
									bflechaVolver = true;
									bflechaAceptar = false;
									bflechaEjercito1 = false;
									bflechaEjercito2 = false;
								}
							else if (InRect(flechaAceptar, evento.button.x, evento.button.y))
								{
									bimprimir = true;
									bflechaVolver = false;
									bflechaAceptar = true;
									bflechaEjercito1 = false;
									bflechaEjercito2 = false;
								}
							else if (InRect(flechaEjercito1, evento.button.x, evento.button.y))
								{
									bimprimir = true;
									bflechaVolver = false;
									bflechaAceptar = false;
									bflechaEjercito1 = true;
									bflechaEjercito2 = false;
								}
							else if (InRect(flechaEjercito2, evento.button.x, evento.button.y))
								{
									bimprimir = true;
									bflechaVolver = false;
									bflechaAceptar = false;
									bflechaEjercito1 = false;
									bflechaEjercito2 = true;
								}
							else
								{
									bimprimir = true;
									bflechaVolver = false;
									bflechaAceptar = false;
									bflechaEjercito1 = false;
									bflechaEjercito2 = false;

									ficheros.Evento(evento.button.x, evento.button.y, false);
								}
						}
				} while (SDL_PollEvent(&evento));

			if (comprobar)
				{
					*e = ConstruirEjercito(ejercito1.LeerTexto(iejercito1), ePRIM)->ejercito();
					*f = ConstruirEjercito(ejercito2.LeerTexto(iejercito2), eSEG)->ejercito();

					bucle = false;
					comprobar = false;
				}
		} //while (bucle)
}

// GestorEjercitos::NuevoEjercito
/*************************************/
void GestorEjercitos::NuevoEjercito()
{
  ModificarEjercito("");
}

// GestorEjercitos::EditarEjercito
/*************************************/
void GestorEjercitos::EditarEjercito()
{
  string s = SeleccionarEjercito();

  if (s != "" && !ModificarEjercito(s))
    EditarEjercito();
}

// GestorEjercitos::EliminarEjercito
/*************************************/
void GestorEjercitos::EliminarEjercito(string nom)
{
  if (nom != "")
    {
      string ejercitoLeido;

      rename((dirlist + "Ejercitos.txt").c_str(), (dirlist + "Temp").c_str());

      ifstream i((dirlist + "Temp").c_str(), ios_base::in);
      ofstream o((dirlist + "Ejercitos.txt").c_str(), ios_base::trunc);

      while (getline(i, ejercitoLeido))
				if (ejercitoLeido != nom)
					o << ejercitoLeido << endl;

      i.close();
      o.close();

      remove((dir + nom.c_str() + ".txt").c_str());
      remove ((dirlist + "Temp").c_str());
    }}

// GestorEjercitos::ConstruirEjercito
/*************************************/
RefEjercito* GestorEjercitos::ConstruirEjercito(string nom, Ejer e)
{
  RefEjercito *refEjercito;
  unsigned n, m, a, b;
  string ej, basura;

  if (nom == "")
    return (new RefEjercito());

  ifstream i((dir + nom + ".txt").c_str(), ios_base::in);

  i >> ej;

  refEjercito = new RefEjercito(ej, e);

  i >> basura;

  // Lee del fichero todas las unidades del ejército para la partida.
  unsigned ii = 0;
  while (i >> ej >> basura >> n >> m >> a >> b)
    {
      RefUnidad& u = refEjercito->NuevaUnidad (ii, ej, fw, fh);
      u.NuevoN(n);
      u.NuevoF(m);
      u.unidad()->NuevaPO(Punto(a, b), 0);
      ++ii;
    }

  return (refEjercito);
}

// GestorEjercitos::ActualizarTexto
/*************************************/
void GestorEjercitos::ActualizarTexto(ListaTexto *texto, int i, Uint16 unicode, bool numerico, int max)
{
  string tex = texto->LeerTexto(i);

  if (unicode == 8 && tex.length())
    tex.erase(tex.length() - 1);
  else if (max < 0 || tex.length() < (unsigned)max)
    {
      if (numerico)
				{
					if (unicode > 47 && unicode < 58)
						tex += (char)unicode;
				}
      else if (unicode > 31 && unicode < 127)		
				tex += (char)unicode;
    }

  texto->ModificarTexto(i, tex);
}

// GestorEjercitos::SeleccionarEjercito
/*************************************/
string GestorEjercitos::SeleccionarEjercito()
{
  SDL_Event evento;

  SDL_Rect rficheros = { 390 * fw, 250 * fh, 500 * fw, 300 * fh };
  SDL_Rect eliminar = { 921 * fw, 358 * fh, 50 * fw, 50 * fh };
  SDL_Rect flechaVolver = { 723 *fw, 674 * fh, 200 * fw, 92 * fh };
  SDL_Rect flechaAceptar = { 910 * fw, 675 * fh, 200 * fw, 92 * fh };
  SDL_Rect subflechaVolver = { 810 * fw, 730 * fh, 40 * fw, 8 * fh };
  SDL_Rect subflechaAceptar = { 980 * fw, 730 * fh, 40 * fw, 8 * fh };
  SDL_Rect subeliminar = { 921 * fw, 440 * fh, 40 * fw, 8 * fh };

  ListaTexto ficheros(fuenteN, color, rficheros, selector, marcador);
  int iActual = iNULO;
  string ejercitoleido;

  ifstream i((dirlist + "Ejercitos.txt").c_str());

  if (!i)
    {
      cerr << "GestorEjercitos::EditarEjercito: No se pudo abrir el fichero de ejércitos disponibles" << endl;
      exit(EXIT_FAILURE);
    }

  while (getline(i, ejercitoleido))
    ficheros.NuevoTexto(ejercitoleido);

  i.close();

  bool bucle = true;
  bool bflechaVolver = false;
  bool bflechaAceptar = false;
  bool beliminar = false;
	bool bimprimir = true;
  while (bucle)
    {
      SDL_Delay (40);

			if (bimprimir)
				{
					bimprimir = false;

					SDL_BlitSurface(pElegirFichero, NULL, screen, NULL);

					if (bflechaVolver)
						SDL_BlitSurface(subrayador, NULL, screen, &subflechaVolver);
					else if (bflechaAceptar)
						SDL_BlitSurface(subrayador, NULL, screen, &subflechaAceptar);
					else if (beliminar)
						SDL_BlitSurface(subrayador, NULL, screen, &subeliminar);

					ficheros.Imprimir(screen);
					SDL_Flip(screen);
				}

			if (!SDL_PollEvent(&evento))  // Si no quedaban eventos, duermo el sistema
				SDL_WaitEvent(&evento);     // hasta que los haya.

			do
				{
					if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT)
						{
							if (InRect(flechaVolver, evento.button.x, evento.button.y))
								{
									bucle = false;
									iActual = iNULO;
								}
							else if (InRect(flechaAceptar, evento.button.x, evento.button.y))
								{
									if (iActual != iNULO)
										bucle = false;
								}
							else if (iActual != iNULO && InRect(eliminar, evento.button.x, evento.button.y))
								{
									bimprimir = true;

									EliminarEjercito(ficheros.LeerTexto(iActual));
									ficheros.EliminarTexto(iActual);
									iActual = ficheros.Marcado();
								}
							else
								{
									iActual = ficheros.Evento(evento.button.x, evento.button.y, true);

									if (iActual != iNULO)
										bimprimir = true;
								}
						}
					else if (evento.type == SDL_MOUSEMOTION)
						{
							if (InRect(flechaVolver, evento.button.x, evento.button.y))
								{
									bimprimir = true;
									bflechaVolver = true;
									bflechaAceptar = false;
									beliminar = false;
								}
							else if (InRect(flechaAceptar, evento.button.x, evento.button.y))
								{
									bimprimir = true;
									bflechaVolver = false;
									bflechaAceptar = true;
									beliminar = false;
								}
							else if (InRect(eliminar, evento.button.x, evento.button.y))
								{
									bimprimir = true;
									bflechaVolver = false;
									bflechaAceptar = false;
									beliminar = true;
								}
							else
								{
									bimprimir = true;
									bflechaVolver = bflechaAceptar = beliminar = false;
									ficheros.Evento(evento.button.x, evento.button.y, false);
								}
						}
				} while (SDL_PollEvent(&evento));
		} //while(bucle) ...

  return (ficheros.LeerTexto(iActual));
}

// GestorEjercitos::Guardar
/*************************************/
bool GestorEjercitos::Guardar (RefEjercito& r, string nombreActual)
{
  SDL_Event evento;

  bool guardar = false;
  bool bflechaVolver = false;
  bool bflechaAceptar = false;

  SDL_Rect rtexto = { 600 * fw, 392 * fh, 200 * fw, 16 };
  SDL_Rect flechaVolver = { 723 * fw, 674 * fh, 200 * fw, 92 * fh };
  SDL_Rect flechaAceptar = { 910 * fw, 675 * fh, 200 * fw, 92 * fh };
  SDL_Rect subflechaVolver = { 810 * fw, 730 * fh, 40 * fw, 8 * fh };
  SDL_Rect subflechaAceptar = { 980 * fw, 730 * fh, 40 * fh, 8 * fh };

  ListaTexto texto(fuenteN, color, rtexto, NULL, NULL);

  int itexto = texto.NuevoTexto(nombreActual);

	bool bimprimir = true;
  while (!guardar)
    {
      SDL_Delay (40);

			if (bimprimir)
				{
					bimprimir = false;

					SDL_BlitSurface(pCrearFichero, NULL, screen, NULL);
					texto.Imprimir(screen);

					if (bflechaVolver)
						SDL_BlitSurface(subrayador, NULL, screen, &subflechaVolver);
					else if (bflechaAceptar)
						SDL_BlitSurface(subrayador, NULL, screen, &subflechaAceptar);

					SDL_Flip(screen);
				}

			if (!SDL_PollEvent(&evento))  // Si no quedaban eventos, duermo el sistema
				SDL_WaitEvent(&evento);     // hasta que los haya.

			do
				{
					if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT)
						{
							if (InRect (flechaVolver, evento.button.x, evento.button.y))
								return (false);
							else if (InRect (flechaAceptar, evento.button.x, evento.button.y))
								{
									if (texto.LeerTexto(itexto).size())
										guardar = true;
								}
							else if (InRect (rtexto, evento.button.x, evento.button.y))
								{
									bimprimir = true;
									texto.ModificarTexto (itexto, "");
								}
						}
					else if (evento.type == SDL_MOUSEMOTION)
						{
							if (InRect(flechaAceptar, evento.button.x, evento.button.y))
								{
									bimprimir = true;
									bflechaAceptar = true;
									bflechaVolver = false;
								}
							else if (InRect(flechaVolver, evento.button.x, evento.button.y))
								{
									bimprimir = true;
									bflechaAceptar = false;
									bflechaVolver = true;
								}
							else
								{
									bimprimir = true;
									bflechaAceptar = false;
									bflechaVolver = false;
								}
						}
					else if (evento.type == SDL_KEYDOWN)
						{
							bimprimir = true;
							ActualizarTexto (&texto, itexto, evento.key.keysym.unicode, false, 25);
						}
				} while (SDL_PollEvent(&evento));
		}

  set<string> ficheros;
  string ejercitoLeido, nomFich = texto.LeerTexto(itexto);
  ifstream i((dirlist + "Ejercitos.txt").c_str(), ios_base::in);

  while (getline(i, ejercitoLeido))
    if (ejercitoLeido != nombreActual)
      ficheros.insert(ejercitoLeido);

  if (nombreActual != nomFich && ficheros.find(nomFich) != ficheros.end())
    guardar = false;

  i.close();

  if (guardar)
    {
      ofstream o((dirlist + "Ejercitos.txt").c_str(), ios_base::trunc);

      ficheros.insert(nomFich);

      if (nombreActual != "")
				{
					string nomFichaux = dir + nomFich + ".txt";
					rename((dir + nombreActual + ".txt").c_str(), nomFichaux.c_str());
				}

      for (set<string>::iterator i = ficheros.begin(); i != ficheros.end(); ++i)
				o << *i << endl;

      o.close();

      o.open((dir + nomFich.c_str() + ".txt").c_str(), ios_base::trunc);

      o << r.Raza() << " " << r.Puntos() << endl;

      for (unsigned i = 0; i < r.N(); ++i)
				{
					RefUnidad& u = r.unidad(i);

					o << u.Nombre() << " " << u.Puntos() << endl;
					o << u.N() << " " << u.F() << " " << u.X() << " " << u.Y() << endl;
				}

      o.close();

      return (true);
    }
  else
    return (Guardar(r, ""));
}

// GestorEjercitos::ModificarEjercito
/*************************************/
bool GestorEjercitos::ModificarEjercito(string ejercito)
{
  SDL_Event evento;
  RefEjercito *refEjercito = ConstruirEjercito(ejercito, ePRIM);

  vector<string> vURazas[4];

  vURazas[0].push_back(string("Legión"));
  vURazas[0].push_back(string("Arcabuceros"));
  vURazas[0].push_back(string("Ballesteros"));
  vURazas[0].push_back(string("Escuderos"));
  vURazas[0].push_back(string("Equites"));
  vURazas[0].push_back(string("Unicornios"));
  vURazas[0].push_back(string("Pegasos"));
  vURazas[0].push_back(string("Mantícora"));
  vURazas[0].push_back(string("Dragón"));

  vURazas[1].push_back("Guerreros");
  vURazas[1].push_back("Trasgos");
  vURazas[1].push_back("Wargos");
	vURazas[1].push_back("Onis");
	vURazas[1].push_back("Garms");
	vURazas[1].push_back("Jabalíes");
	vURazas[1].push_back("Abominación");
	vURazas[1].push_back("Gigante");
	vURazas[1].push_back("Trolls");
  vURazas[2].push_back("");

  SDL_Rect flechaUnidad = { 581 * fw, 126 * fh, 85 * fw, 40 * fh };
  SDL_Rect flechaVolver = { 723 * fw, 674 * fh, 200 * fw, 92 * fh };
  SDL_Rect flechaAceptar = { 910 * fw, 675 * fh, 200 * fw, 92 * fh };
  SDL_Rect eliminar = { 810 * fw, 256 * fh, 40 * fw, 40 * fh };
  SDL_Rect traza = { 69 * fw, 88 * fh, 400 * fw, 16 };
  SDL_Rect tpuntuacion = { 825 * fw, 609 * fh, 200 * fw, 30 };
  SDL_Rect tunidadActual = { 701 * fw, 137 * fh, 400 * fw, 16 };
  SDL_Rect tefectivos = { 557 * fw, 238 * fh, 261 * fw, 16 };
  SDL_Rect tfrente = { 833 * fw, 236 * fh, 261 * fw, 16 };
  SDL_Rect tcoordX = { 557 * fw, 320 * fh, 261 * fw, 16 };
  SDL_Rect tcoordY = { 833 * fw, 320 * fh, 261 * fw, 16 };
  SDL_Rect marcoRazas = { 69 * fw, 111 * fh, 400 * fw, 0 };
  SDL_Rect marcoUnidades = { 10 * fw, 230 * fh, 522 * fw, 435 * fh };
  SDL_Rect marcoSumario = { 575 * fw, 410 * fh, 500 * fw, 130 * fh };
  SDL_Rect subflechaUnidad = { 590 * fw, 167 * fh, 40 * fw, 8 * fh };
  SDL_Rect subflechaVolver = { 810 * fw, 730 * fh, 40 * fw, 8 * fh };
  SDL_Rect subflechaAceptar = { 980 * fw, 730 * fh, 40 * fw, 8 * fh };
  SDL_Rect subeliminar = { 810 * fw, 296 * fh, 40 * fw, 8 * fh };

  ListaTexto raza(fuenteN, color, traza, NULL, NULL, NULL);
  ListaTexto razas(fuenteN, color, marcoRazas, selector, marcador, cajaTexto);
  ListaTexto unidades(fuenteN, color, marcoUnidades, selector, marcador, NULL);
  ListaTexto sumario(fuenteN, color, marcoSumario, selector, marcador, NULL);
  ListaTexto unidadActual(fuenteN, color, tunidadActual, NULL, NULL, NULL);
  ListaTexto efectivos(fuenteN, color, tefectivos, NULL, NULL, NULL);
  ListaTexto frente(fuenteN, color, tfrente, NULL, NULL, NULL);
  ListaTexto coordX(fuenteN, color, tcoordX, NULL, NULL, NULL);
  ListaTexto coordY(fuenteN, color, tcoordY, NULL, NULL, NULL);
  ListaTexto puntuacion(fuenteP, color, tpuntuacion, NULL, NULL, NULL);

  razas.NuevoTexto("Humanos");
  razas.NuevoTexto("Orcos");

  int itraza;
  int ipuntuacion;
  int iefectivos = efectivos.SiguienteId();
  int iunidadActual = unidadActual.SiguienteId();
  int ifrente = frente.SiguienteId();
  int icoordX = coordX.SiguienteId();
  int icoordY = coordY.SiguienteId();
  int iunidadElegida = iNULO;
  int iraza = iNULO;

  if (ejercito != "")
    {
      itraza = raza.NuevoTexto(refEjercito->Raza());

      ostringstream o;

      o << refEjercito->ejercito()->Puntos();

      ipuntuacion = puntuacion.NuevoTexto(o.str());
    }
  else
    {
      itraza = raza.NuevoTexto("Elija una raza");
      ipuntuacion = puntuacion.NuevoTexto("0");
    }

  bool elegirRaza = false;
  bool bflechaUnidad = false;
  bool bflechaVolver = false;
  bool bflechaAceptar = false;
  bool beliminar = false;

  ListaTexto *ltescritura = 0;
  int iescritura = 0;
  bool escritura = false;

  CrearSumario(sumario, refEjercito);

  unsigned irazaActual;
  if (refEjercito->Raza() == "Humanos")
    irazaActual = 0;
  else if (refEjercito->Raza() == "Orcos")
    irazaActual = 1;
  else
    irazaActual = 2;

  vector<string>& vURaza = vURazas[irazaActual];

  for (unsigned i = 0; i < vURaza.size(); ++i)
    unidades.NuevoTexto(vURaza[i]);

  raza.NuevaEtiqueta (itraza, punto);

	bool bimprimir = true;
  while (1)
    {
      SDL_Delay (40);

			if (bimprimir)
				{
					bimprimir = false;

					SDL_BlitSurface(pCrearEjercito, NULL, screen, NULL);

					raza.Imprimir(screen);
					unidades.Imprimir(screen);

					if (elegirRaza)
						razas.Imprimir(screen);

					if (!escritura && iunidadElegida != iNULO)
						{
							RefUnidad& u = refEjercito->unidad(iunidadElegida);
							stringstream s;
							string t;

							s << u.N() << " " << u.F() << " " << u.X() << " " << u.Y() << endl;

							s >> t;
							efectivos.ModificarTexto(iefectivos, t);
							s >> t;
							frente.ModificarTexto(ifrente, t);
							s >> t;
							coordX.ModificarTexto(icoordX, t);
							s >> t;
							coordY.ModificarTexto(icoordY, t);
						}

					sumario.Imprimir(screen);
					puntuacion.Imprimir(screen);
					unidadActual.Imprimir(screen);
					efectivos.Imprimir(screen);
					frente.Imprimir(screen);
					coordX.Imprimir(screen);
					coordY.Imprimir(screen);

					if (bflechaUnidad)
						SDL_BlitSurface(subrayador, NULL, screen, &subflechaUnidad);
					else if (bflechaVolver)
						SDL_BlitSurface(subrayador, NULL, screen, &subflechaVolver);
					else if (bflechaAceptar)
						SDL_BlitSurface(subrayador, NULL, screen, &subflechaAceptar);
					else if (beliminar)
						SDL_BlitSurface(subrayador, NULL, screen, &subeliminar);

					SDL_Flip(screen);
				} // if (bimprimir) ...

			if (!SDL_PollEvent(&evento))  // Si no quedaban eventos, duermo el sistema
				SDL_WaitEvent(&evento);     // hasta que los haya.

			do
				{
					if (escritura)
						{
							if (evento.type == SDL_KEYDOWN)
								{
									bimprimir = true;

									if (evento.key.keysym.sym == SDLK_RETURN)
										{
											stringstream s1, s2;
											unsigned n;
											RefUnidad& u = refEjercito->unidad(iunidadElegida);

											s1 << ltescritura->LeerTexto(iescritura);

											if (s1.str() == "")
												n = 0;
											else
												s1 >> n;

											if (ltescritura == &efectivos)
												u.NuevoN(n);

											else if (ltescritura == &frente)
												u.NuevoF(n);
											else if (ltescritura == &coordX)
												u.NuevoX(n);
											else if (ltescritura == &coordY)
												u.NuevoY(n);

											escritura = false;

											ltescritura->EliminarEtiqueta(iescritura);

											ModificarSumario(sumario, iunidadElegida, u);

											s2 << refEjercito->Puntos();
											puntuacion.ModificarTexto(ipuntuacion, s2.str());
										}
									else
										ActualizarTexto(ltescritura, iescritura, evento.key.keysym.unicode, true, 4);
								}
						} // fin if (escritura)
					else if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT)
						{
							if (InRect (flechaVolver, evento.button.x, evento.button.y))
								return (false);
							else if (InRect (flechaAceptar, evento.button.x, evento.button.y) && refEjercito->Puntos())
								{
									bimprimir = true;

									sumario.LimpiarEtiquetas();

									vector<int> v = refEjercito->Verificar();

									if (v.size())
										for (unsigned i = 0; i < v.size(); ++i)
											sumario.NuevaEtiqueta(v[i], marca);
									else if (refEjercito->Raza() != "" && Guardar(*refEjercito, ejercito))
										return (true);
								}
							else if (iunidadElegida != iNULO && InRect(eliminar, evento.button.x, evento.button.y))
								{
									bimprimir = true;

									ostringstream os;

									sumario.EliminarTexto(iunidadElegida);
									refEjercito->EliminarUnidad(iunidadElegida);

									efectivos.ModificarTexto(iefectivos, "");
									frente.ModificarTexto(ifrente, "");
									coordX.ModificarTexto(icoordX, "");
									coordY.ModificarTexto(icoordY, "");
									unidadActual.ModificarTexto(iunidadActual, "");

									os << refEjercito->Puntos();
									puntuacion.ModificarTexto(ipuntuacion, os.str());

									iunidadElegida = sumario.Marcado();
								}
							else if (!elegirRaza)
								{
									bimprimir = true;

									if (itraza == raza.Evento(evento.button.x, evento.button.y, true))
										{
											elegirRaza = true;

											raza.NuevaEtiqueta(itraza, puntoSel);
										}
									else if (refEjercito->Raza() != "")
										{
											bool bnuevaUnidad = false;
											int iunidadLista = unidades.Marcado();

											int iunidadSumario = sumario.Evento(evento.button.x, evento.button.y, true);
										
											if (iunidadSumario != iNULO)
                        bnuevaUnidad = true;
											else if (iunidadLista != iNULO && InRect(flechaUnidad, evento.button.x, evento.button.y))
												{
													bnuevaUnidad = true;
													ostringstream os1, os2;

													os1 << unidades.LeerTexto(iunidadLista);
													iunidadSumario = sumario.SiguienteId();

													const RefUnidad& u = refEjercito->NuevaUnidad(iunidadSumario, os1.str(), fw, fh);

													os2 << refEjercito->Puntos();
													puntuacion.ModificarTexto(ipuntuacion, os2.str());

													ModificarSumario(sumario, iunidadSumario, u);
												}

                      if (unidades.Evento(evento.button.x, evento.button.y, true) == iNULO)
                        unidades.Marcar(iunidadLista);

											if (bnuevaUnidad)
												{
													const RefUnidad& u = refEjercito->unidad(iunidadSumario);

													ostringstream efecs, frent, x, y;
							
													unidadActual.ModificarTexto(iunidadActual, u.Nombre());

													iunidadElegida = iunidadSumario;

													efecs << u.N();
													efectivos.ModificarTexto(iefectivos, efecs.str());

													frent << u.F();
													frente.ModificarTexto(ifrente, frent.str());

													x << u.X();
													coordX.ModificarTexto(icoordX, x.str());

													y << u.Y();
													coordY.ModificarTexto(icoordY, y.str());
												}

											if (!escritura)
												{
													if (InRect (tefectivos, evento.button.x, evento.button.y))
														{
															escritura = true;
															iescritura = iefectivos;
															ltescritura = &efectivos;
														}
													else if (InRect (tfrente, evento.button.x, evento.button.y))
														{
															escritura = true;
															iescritura = ifrente;
															ltescritura = &frente;
														}
													else if (InRect (tcoordX, evento.button.x, evento.button.y))
														{
															escritura = true;
															iescritura = icoordX;
															ltescritura = &coordX;
														}
													else if (InRect (tcoordY, evento.button.x, evento.button.y))
														{
															escritura = true;
															iescritura = icoordY;
															ltescritura = &coordY;
														}

													if (escritura)
														{
															ltescritura->ModificarTexto(iescritura, "");
															ltescritura->NuevaEtiqueta(iescritura, punto);
														}
												}
										} // else if (refEjercito->Raza() != "") ... {
								} // else if (elegirRaza)
							else if ((iraza = razas.Evento(evento.button.x, evento.button.y, true)) != iNULO)
								{
									unsigned irazaActual;
									string razaActual = razas.LeerTexto(iraza);

									bimprimir = true;

									raza.ModificarTexto(itraza, razaActual);

									unidades.Vaciar();
									sumario.Vaciar();

									unidadActual.ModificarTexto (iunidadActual, "");
									efectivos.ModificarTexto (iefectivos, "");
									frente.ModificarTexto (ifrente, "");
									coordX.ModificarTexto (icoordX, "");
									coordY.ModificarTexto (icoordY, "");
									puntuacion.ModificarTexto (ipuntuacion, "0");

									delete refEjercito;
									refEjercito = new RefEjercito(razaActual, ePRIM);

									iunidadElegida = iNULO;

									if (razaActual == "Humanos")
										irazaActual = 0;
									else if (razaActual == "Orcos")
										irazaActual = 1;
									else
										irazaActual = 2;

									vector<string>& vURaza = vURazas[irazaActual];

									for (unsigned i = 0; i < vURaza.size(); ++i)
										unidades.NuevoTexto(vURaza[i]);

									elegirRaza = false;

									raza.NuevaEtiqueta(itraza, punto);
									razas.Reiniciar();
								}
							else
								{
									elegirRaza = false;
									bimprimir = true;
								}
						}
					else if (evento.type == SDL_MOUSEMOTION)
						{
							bimprimir = true;

							if (elegirRaza)
								razas.Evento(evento.button.x, evento.button.y, false);

							unidades.Evento(evento.button.x, evento.button.y, false);
							sumario.Evento(evento.button.x, evento.button.y, false);

							if (raza.Evento(evento.button.x, evento.button.y, false) != iNULO)
								raza.NuevaEtiqueta(itraza, puntoSel);
							else if (!elegirRaza)
								raza.NuevaEtiqueta(itraza, punto);

							if (InRect (flechaUnidad, evento.button.x, evento.button.y))
								{
									bflechaUnidad = true;
									bflechaVolver = false;
									bflechaAceptar = false;
									beliminar = false;
								}
							else if (InRect (flechaVolver, evento.button.x, evento.button.y))
								{
									bflechaUnidad = false;
									bflechaVolver = true;
									bflechaAceptar = false;
									beliminar = false;
								}
							else if (InRect (flechaAceptar, evento.button.x, evento.button.y))
								{
									bflechaUnidad = false;
									bflechaVolver = false;
									bflechaAceptar = true;
									beliminar = false;
								}
							else if (InRect (eliminar, evento.button.x, evento.button.y))
								{
									bflechaUnidad = false;
									bflechaVolver = false;
									bflechaAceptar = false;
									beliminar = true;
								}
							else
								{
									bflechaUnidad = false;
									bflechaVolver = false;
									bflechaAceptar = false;
									beliminar = false;
								}
						}
				} while (SDL_PollEvent(&evento));
		}
} // Fin función.

// GestorEjercitos::CrearSumario
/*************************************/
void GestorEjercitos::CrearSumario(ListaTexto& sumario, RefEjercito *r)
{
  for (unsigned i = 0; i < r->N(); ++i)
    {
      Unidad *u = r->unidad(i).unidad();
			Punto psi(u->Psi());

      ostringstream os;

      os << u->NombreUnidad() << " - (" << psi.x << ", " << psi.y << "), "
				 << u->N() << "/" << u->Frente() << " -";

      sumario.NuevoTexto(os.str());	
    }
}

// GestorEjercitos::ModificarSumario
/*************************************/
void GestorEjercitos::ModificarSumario(ListaTexto& sumario, int i, const RefUnidad& u)
{
  ostringstream os;

  os << u.Nombre() << " - (" << u.X() << ", " << u.Y() << "), " << u.N() << "/" << u.F() << " -";

  sumario.ModificarTexto(i, os.str());
  sumario.Marcar(i);
}

// GestorEjercitos::~GestorEjercitos
/*************************************/
GestorEjercitos::~GestorEjercitos()
{
  TTF_CloseFont(fuenteN);
  TTF_CloseFont(fuenteP);

  delete pElegirEjercitos;
  delete pCrearEjercito;
  delete pElegirFichero;
  delete pCrearFichero;

  delete subrayador;
  delete selector;
  delete marcador;
  delete punto;
  delete puntoSel;
  delete marca;

  delete cajaTexto;
}
