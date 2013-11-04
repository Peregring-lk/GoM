/*
    This file is part of GoM.

    GoM is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published
    by the Free Software Foundation, either version 3 of the License,
    or (at your option) any later version.

    GoM is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GoM.  If not, see <http://www.gnu.org/licenses/>.

--

    Este fichero forma parte de GoM.

    GoM es sotware libre: podrá redistribuirlo y/o modificarlo
    bajo los términos de la GNU General Public License según es
    publicada por la Free Software Fundation, tanto para la versión 3
    de la licencia como para cualquier versión posterior (según su
    elección).

    GoM se distribuye con la esperanza de ser útil, pero SIN NINGUNA
    GARANTÍA, incluso sin garantía MERCANTIL implícita o CONVENIENCIA
    PARA UN PROPÓSITO PARTICULAR. Vea la GNU General Public License
    para más detalles.

    Debió recibir una copia de la GNU General Public License
    junto a GoM. Si no es así, visite <http://www.gnu.org/licenses/>.

*/

/*! \file GestorInterfaz.cpp
 *  \brief Fichero que implementa al gestor de interfaz.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "GestorInterfaz.h"
#include <cmath>
#include "SDL/SDL_rotozoom.h"

using namespace std;

vector<Mix_Music*> canciones;
vector<Mix_Chunk*> sonidos;

// CargarCanciones
/*************************************/
void CargarCanciones()
{
	/*
	 *  Canciones
	 */
	Mix_Music *aux;

	if (!(aux = Mix_LoadMUS("Sonido/Canciones/HeavyInterlude.ogg")))
		cerr << SDL_GetError() << endl;

	canciones.push_back(aux);

	if (!(aux = Mix_LoadMUS("Sonido/Canciones/Night of the Owl.ogg")))
		cerr << SDL_GetError() << endl;

	canciones.push_back(aux);

	if (!(aux = Mix_LoadMUS("Sonido/Canciones/One of Them.ogg")))
		cerr << SDL_GetError() << endl;

	canciones.push_back(aux);

	if (!(aux = Mix_LoadMUS("Sonido/Canciones/Darkness is Coming.ogg")))
		cerr << SDL_GetError() << endl;

	canciones.push_back(aux);

	if (!(aux = Mix_LoadMUS("Sonido/Canciones/Achaidh Cheide.ogg")))
		cerr << SDL_GetError() << endl;

	canciones.push_back(aux);

	if (!(aux = Mix_LoadMUS("Sonido/Canciones/Rising Game.ogg")))
		cerr << SDL_GetError() << endl;

	canciones.push_back(aux);

	if (!(aux = Mix_LoadMUS("Sonido/Canciones/Truth of the Legend.ogg")))
		cerr << SDL_GetError() << endl;

	canciones.push_back(aux);

	if (!(aux = Mix_LoadMUS("Sonido/Canciones/Desert City.ogg")))
		cerr << SDL_GetError() << endl;

	canciones.push_back(aux);

	Mix_VolumeMusic(100);

	/*
	 *  Chunks
	 */
	Mix_Chunk *c;

	if (!(c = Mix_LoadWAV("Sonido/408__TicTacShutUp__light_1.aiff")))
		cerr << SDL_GetError() << endl;

	Mix_VolumeChunk(c, 128);

	sonidos.push_back(c);

	if (!(c = Mix_LoadWAV("Sonido/9432__thanvannispen__male_Thijs_loud_scream.aiff")))
		cerr << SDL_GetError() << endl;

	Mix_VolumeChunk(c, 128);

	sonidos.push_back(c);

	if (!(c = Mix_LoadWAV("Sonido/20567__roryistea__cryforharmony.aiff")))
		cerr << SDL_GetError() << endl;

	Mix_VolumeChunk(c, 128);

	sonidos.push_back(c);

	if (!(c = Mix_LoadWAV("Sonido/15446__pitx__15399_fragmento.aiff")))
		cerr << SDL_GetError() << endl;

	Mix_VolumeChunk(c, 128);

	sonidos.push_back(c);

	if (!(c = Mix_LoadWAV("Sonido/37596__hello_flowers__Sword.aiff")))
		cerr << SDL_GetError() << endl;

	Mix_VolumeChunk(c, 128);

	sonidos.push_back(c);

	if (!(c = Mix_LoadWAV("Sonido/45137__DJ_Chronos__Dark_church_bell.aiff")))
		cerr << SDL_GetError() << endl;

	Mix_VolumeChunk(c, 128);

	sonidos.push_back(c);
}

// SiguienteCancion
/*************************************/
void SiguienteCancion()
{
	unsigned azar = NumAzar((unsigned)0, canciones.size() - 1);

	Mix_Music* sig = canciones[azar];

	if (!(Mix_PlayMusic(sig, 0)) == -1)
		cerr << SDL_GetError() << endl;
}

// GestorInterfaz::GestorInterfaz
/*************************************/
GestorInterfaz::GestorInterfaz()
{
  SDL_Surface *fondoOr;
  SDL_Surface *marcosOr;
	SDL_Surface *resultadoOr;
  SDL_Surface *subrayadorOr;
	SDL_Surface *marcaOr;

  // Iniciamos el sistema de video
  if (SDL_Init (SDL_INIT_VIDEO|SDL_INIT_AUDIO) == -1)
    cerr << SDL_GetError() << endl;

  if (TTF_Init() == -1)
    cerr << SDL_GetError() << endl;

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1)
		cerr << SDL_GetError() << endl;

	MejorPantalla();

	CargarCanciones();
	SiguienteCancion();

	Mix_AllocateChannels(3);

	Mix_HookMusicFinished(SiguienteCancion);

  // Se inicializan todas las fuentes.
  if (!(fuenteN = TTF_OpenFont ("Imagenes/Fuentes/FreeSansOblique.ttf", 12)))
    cerr << SDL_GetError() << endl;

  TTF_SetFontStyle (fuenteN, TTF_STYLE_BOLD);

  if (!(fuenteT = TTF_OpenFont ("Imagenes/Fuentes/circulat.ttf", 32)))
    cerr << SDL_GetError() << endl;
  TTF_SetFontStyle (fuenteT, TTF_STYLE_BOLD|TTF_STYLE_ITALIC);

  if (!(fuenteG = TTF_OpenFont ("Imagenes/Fuentes/FreeSansOblique.ttf", 20)))
    cerr << SDL_GetError() << endl;
  TTF_SetFontStyle (fuenteG, TTF_STYLE_ITALIC|TTF_STYLE_BOLD);

  if (!(fuenteE = TTF_OpenFont ("Imagenes/Fuentes/FreeSansOblique.ttf", 16)))
    cerr << SDL_GetError() << endl;
  TTF_SetFontStyle (fuenteE, TTF_STYLE_ITALIC|TTF_STYLE_BOLD);

  if (!(fondoOr = IMG_Load ("Imagenes/fondo.png")))
    cerr << SDL_GetError() << endl;

	fw = (double)marco->w / fondoOr->w;
  fh = (double)marco->h / fondoOr->h;

  gi = new GestorIconos(fw, fh);
  ge = new GestorEjercitos(marco, fw, fh);

  if (!(pixelArea = IMG_Load ("Imagenes/Especiales/PixelArea.png")))
    cerr << SDL_GetError() << endl;
  if (!(pixelUnidad = IMG_Load ("Imagenes/Especiales/PixelUnidad.png")))
    cerr << SDL_GetError() << endl;
  if (!(pixelUnidadCargaSel = IMG_Load ("Imagenes/Especiales/PixelUnidadCargaSel.png")))
    cerr << SDL_GetError() << endl;
  if (!(pixelUnidadP = IMG_Load ("Imagenes/Especiales/PixelUnidadActualP.png")))
    cerr << SDL_GetError() << endl;
  if (!(pixelUnidadS = IMG_Load ("Imagenes/Especiales/PixelUnidadActualS.png")))
    cerr << SDL_GetError() << endl;

  if (!(marcosOr = IMG_Load ("Imagenes/marcos.png")))
    cerr << SDL_GetError() << endl;
	if (!(resultadoOr = IMG_Load ("Imagenes/Menu/Resultado.png")))
		cerr << SDL_GetError() << endl;
  if (!(subrayadorOr = IMG_Load ("Imagenes/Especiales/Subrayador.png")))
    cerr << SDL_GetError() << endl;
	if (!(marcaOr = IMG_Load ("Imagenes/Especiales/tick.png")))
		cerr << SDL_GetError() << endl;

  if (!(fondo = zoomSurface(fondoOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;
  if (!(marcos = zoomSurface(marcosOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;
	if (!(resultado = zoomSurface(resultadoOr, fw, fh, 0)))
		cerr << SDL_GetError() << endl;
  if (!(subrayador = zoomSurface (subrayadorOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;
	if (!(marca = zoomSurface (marcaOr, fw, fh, 0)))
		cerr << SDL_GetError() << endl;

  delete fondoOr;
  delete marcosOr;
	delete resultadoOr;
	delete subrayadorOr;

  SDL_EnableUNICODE(1);

  color.r = 0;
  color.g = 0;
  color.b = 0;
}

// GestorInterfaz::MejorPantalla
/*************************************/
void GestorInterfaz::MejorPantalla ()
{	
	const SDL_VideoInfo *info = SDL_GetVideoInfo();
	Uint32 flags = SDL_FULLSCREEN;

	if (info->hw_available)
		flags = flags | SDL_HWSURFACE | SDL_DOUBLEBUF;
	else
		flags = flags | SDL_SWSURFACE;

	SDL_Rect **resoluciones = SDL_ListModes(info->vfmt, flags);

	if (!(marco = SDL_SetVideoMode(resoluciones[0]->x, resoluciones[0]->y, info->vfmt->BitsPerPixel, flags)))
    cerr << SDL_GetError() << endl;
}

// GestorInterfaz::Inicializar
/*************************************/
void GestorInterfaz::Inicializar (const Estado& E)
{
	SDL_Surface *fondoOr;

	if (fondo)
		delete fondo;

  if (!(fondoOr = IMG_Load ("Imagenes/fondo.png")))
    cerr << SDL_GetError() << endl;

  if (!(fondo = zoomSurface (fondoOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;

	delete fondoOr;
	
  gi->Inicializar (E);

	GAIA* g = (GAIA*)E.pEjer(eGAIA);
	g->InicializarGAIA(fw, fh, fondo);

	ultimaUnidad = NULL;
	ultimaTarea = tNULO;
	bimprimir = true;
}

// GestorInterfaz::Menu
/*************************************/
unsigned GestorInterfaz::Menu()
{
  string vOpciones[4] = { "Nueva batalla", "Crear ejercito", "Editar ejercito", "Salir" };
  SDL_Event evento;
  SDL_Surface *ImgMenu, *ImgMenuOr;

  SDL_Rect marcomenu = { (Sint16)(100 * fw), (Sint16)(100 * fh), (Sint16)(400 * fw), (Sint16)(400 * fh) };
  SDL_Color colormenu = { 255, 0, 0 };
  SDL_Color coloreleg = { 255, 255, 0 };
  TTF_Font *fmenu;

  int iopciones = iNULO;

  if (!(ImgMenuOr = IMG_Load ("Imagenes/Menu/menu.png")))
    cerr << SDL_GetError() << endl;
  if (!(fmenu = TTF_OpenFont ("Imagenes/Fuentes/mima4x4o.ttf", 40)))
    cerr << SDL_GetError() << endl;

  if (!(ImgMenu = zoomSurface (ImgMenuOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl;

  delete ImgMenuOr;
 
  ListaTexto opciones(fmenu, colormenu, marcomenu, NULL, NULL, NULL);

  for (unsigned i = 0; i < 4; ++i)
    opciones.NuevoTexto(vOpciones[i].c_str());

	bool bimprimir = true;

  while (1)
    {
      SDL_Delay(40);

			if (bimprimir)
				{
					SDL_BlitSurface(ImgMenu, NULL, marco, NULL);
					opciones.Imprimir(marco);

					SDL_Flip(marco);

					bimprimir = false;
				}

			if (!SDL_PollEvent(&evento))  // Si no quedaban eventos, duermo el sistema
				SDL_WaitEvent(&evento);     // hasta que los haya.

			do
				{
					if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT)
						{
							int iopciones = opciones.Evento(evento.button.x, evento.button.y, true);

							string opcionActual = opciones.LeerTexto(iopciones);

							for (unsigned i = 0; i < 4; ++i)
								if (vOpciones[i] == opcionActual)
									return (i);
						}
					else if (evento.type == SDL_MOUSEMOTION)
						{
							int iauxopciones = opciones.Evento(evento.button.x, evento.button.y, false);

							if (iauxopciones != iopciones)
								{
									opciones.CambiarColor(iopciones, colormenu);
									opciones.CambiarColor(iauxopciones, coloreleg);
									iopciones = iauxopciones;
									bimprimir = true;
								}
						}
				} while (SDL_PollEvent(&evento));
		}
}  // Fin Menu

// GestorInterfaz::ElegirEjercitos
/*************************************/
void GestorInterfaz::ElegirEjercitos (Ejercito **e, Ejercito **f) const
{
  ge->ElegirEjercitos(e, f);
}

// GestorInterfaz::NuevoEjercito
/*************************************/
void GestorInterfaz::NuevoEjercito() const
{
  ge->NuevoEjercito();
}

// GestorInterfaz::EditarEjercito
/*************************************/
void GestorInterfaz::EditarEjercito() const
{
  ge->EditarEjercito();
}

// GestorInterfaz::NuevoEvento
/*************************************/
Accion* GestorInterfaz::NuevoEvento (const Estado& E, const GestorEscenario& esc)
{
  SDL_Event click;
  int a, b;

	if (E.UltimaTarea() == tcomSIGHUIDA)
		Mix_PlayChannel(3, sonidos[1], 0);
		
  while (1)
    {
			if (bimprimir)
				{
					Imprimir(E, ultimaUnidad);
					bimprimir = false;
				}

      SDL_Delay (40);

			/*
			 *  Obtenemos el siguiente evento.
			 */
			if (!SDL_PollEvent(&click))  // Si no quedaban eventos, duermo el sistema
				SDL_WaitEvent(&click);     // hasta que los haya.

      SDL_GetMouseState (&a, &b);

			/*
			 *  Busqueda de la acción pedida por el usuario.
			 */
      Punto c(a, b);

			Tarea antg = gi->Seleccionado();
			Tarea taux = gi->EncuentraTarea(E,c);
      Accion *ac = E.LeerAccion(taux);

			if (antg != tNULO)
				{
					if (taux != antg)
						{
							gi->DeseleccionarIcono(antg);
							bimprimir = true;
						}

					if (antg == tELEGIRUNIDAD && ultimaUnidad != NULL)
						{
							ultimaUnidad->Deseleccionar();

							ultimaUnidad = NULL;
							bimprimir = true;
						}
				}

			/*
			 *  Procesamos el evento buscando cambios.
			 */
			if (ac != NULL && ac->T() != tNULO)
				{
					Unidad *u = NULL;
					bool bcambiounidad = false;
					ultimaTarea = ac->T();

					if (ac->T() == tELEGIRUNIDAD)
						{
							/*
							 *  Unidad apuntada por el ratón.
							 */
							Punto p(c.x / fw, 700 - c.y / fh);

							u = (*E.pEjer (ePRIM) << p);
							if (u == NULL)
								u = (*E.pEjer (eSEG) << p);

							if (u != ultimaUnidad)
								{
									bcambiounidad = true;

									if (ultimaUnidad != NULL)
										ultimaUnidad->Deseleccionar();

									if (u != NULL)
										u->Seleccionar();

									ultimaUnidad = u;
									bimprimir = true;
								}
						}
					else
						{
							if (ultimaUnidad != NULL)
								ultimaUnidad->Deseleccionar();

							ultimaUnidad = NULL;
							bimprimir = true;
						}

					do
						{
							// Si se pulsa el botón derecho del ratón.
							if (click.type == SDL_MOUSEBUTTONDOWN && click.button.button == SDL_BUTTON_LEFT)
								{
									if (!bcambiounidad && ultimaUnidad != E.UnidadActual())
										bimprimir = true;

									if (!E.LeerTarea(ac->T(), false)) 
										{
											ErrorTarea(E, ac->T());
											ac = 0;
										}
									else
										return (ObtenerAtributos (ac, u, E, esc));
								}
						} while (SDL_PollEvent (&click));
				} // if (ac != NULL && ac->T() != tNULO)
			else if (ultimaTarea != ac->T())
				{
					ultimaTarea = ac->T();
					bimprimir = true;
				}
		} //while(1)
}

// GestorInterfaz::ObtenerAtributos
/*************************************/
Accion* GestorInterfaz::ObtenerAtributos (Accion *ac, Unidad *u,
																					const Estado& E,
																					const GestorEscenario& esc)
{
	/*
	 *  Reproducción de sonidos.
	 */
	if (ac->T() == tELEGIRUNIDAD)
		{
			if (((acElegirUnidad*)ac)->uActual() != NULL)
				Mix_PlayChannel(1, sonidos[0], 0);
		}
	else if (ac->T() == tTURNO)
		Mix_PlayChannel(2, sonidos[2], 0);
	else if (ac->T() == tFINALIZARBATALLA)
		{
			Mix_PlayChannel(1, sonidos[5], 0);
			SDL_Delay (1500);
		}
	else if (ac->T() != tNULO)
		Mix_PlayChannel(1, sonidos[4], 0);

	/*
	 *  Acciones
	 */
  if (ac->T() == tELEGIRUNIDAD)
    ((acElegirUnidad*)ac)->NuevaUnidad (u);
  else if (ac->T() == tmovDECLARARCARGA)
    {
      Unidad *v = E.UnidadActual();
      if (!v || E.enumEjer (v->uEjercito()) != E.EjercitoActual())
				{
					ImprimirError (E, 0);
					ac = E.LeerAccion (tNULO);
				}
      else if (v->Cargando())
				{
					ImprimirError (E, 2);
					ac = E.LeerAccion (tNULO);
				}
      else if (v->Combatiendo())
				{
					ImprimirError (E, 3);
					ac = E.LeerAccion (tNULO);
				}
      else if (v->Marchando())
				{
					ImprimirError (E, 15);
					ac = E.LeerAccion (tNULO);
				}
			else if (v->Huyendo())
				{
					ImprimirError (E, 11);
					ac = E.LeerAccion (tNULO);
				}
      else
				{
					Unidad *w = ElegirUnidadCarga (E, esc);

					if (w != NULL)
						((acMovDeclararCarga*)ac)->DeclararCarga (v, w);
					else
						ac = E.LeerAccion (tNULO);
				}}
  else if (ac->T() == tmovMARCHAR)
    {
      Unidad *v = E.UnidadActual();

      // Solo puede ejecutarse la acción sobre una unidad del ejército
      // actual.
      if (!v || E.enumEjer (v->uEjercito()) != E.EjercitoActual())
				{
					ImprimirError (E, 0);
					ac = E.LeerAccion (tNULO);
				}
			else if (!v->bMarchar())
				{
					ImprimirError (E, 15);
					ac = E.LeerAccion(tNULO);
				}
      else if (v->Cargando())
				{
					ImprimirError (E, 2);
					ac = E.LeerAccion (tNULO);
				}
      else if (v->Combatiendo())
				{
					ImprimirError (E, 3);
					ac = E.LeerAccion (tNULO);
				}
			else if (v->Huyendo())
				{
					ImprimirError (E, 11);
					ac = E.LeerAccion (tNULO);
				}
      else if (Comp(v->MovMax(), 0))
				{
					ImprimirError (E, 5);
					ac = E.LeerAccion (tNULO);
				}}
  else if (ac->T() == tmovMOVER)
    {
      Unidad *v = E.UnidadActual();
      // Solo puede ejecutarse la acción sobre una unidad del ejército
      // actual.
      if (!v || E.enumEjer (v->uEjercito()) != E.EjercitoActual())
				{
					ImprimirError (E, 0);
					ac = E.LeerAccion (tNULO);
				}
      else if (v->Cargando())
				{
					ImprimirError (E, 2);
					ac = E.LeerAccion (tNULO);
				}
      else if (v->Combatiendo())
				{
					ImprimirError (E, 3);
					ac = E.LeerAccion (tNULO);
				}
			else if (v->Huyendo())
				{
					ImprimirError (E, 11);
					ac = E.LeerAccion (tNULO);
				}
      else if (Comp(v->MovMax(), 0))
				{
					ImprimirError (E, 5);
					ac = E.LeerAccion (tNULO);
				}
      else
				((acMovMover*)ac)->NuevaDistancia (ElegirDespl (E, esc));
    }
  else if (ac->T() == tmovPIVOTARIZQ)
    {
      Unidad *v = E.UnidadActual();
      // Solo puede ejecutarse la acción sobre una unidad del ejército
      // actual.
      if (!v || E.enumEjer (v->uEjercito()) != E.EjercitoActual())
				{
					ImprimirError (E, 0);
					ac = E.LeerAccion (tNULO);
				}
      else if (v->Cargando())
				{
					ImprimirError (E, 2);
					ac = E.LeerAccion (tNULO);
				}
      else if (v->Combatiendo())
				{
					ImprimirError (E, 3);
					ac = E.LeerAccion (tNULO);
				}
			else if (v->Huyendo())
				{
					ImprimirError (E, 11);
					ac = E.LeerAccion (tNULO);
				}
      else if (Comp(v->MovMax(), 0))
				{
					ImprimirError (E, 5);
					ac = E.LeerAccion (tNULO);
				}
      else
				{
					double ang = 5 * (unsigned)(.5 + AngRG(ElegirAngIzq(E,esc)) / 5);
					((acMovPivotarIzq*)ac)->NuevoAng (AngGR(ang));
				}
    }
  else if (ac->T() == tmovPIVOTARDER)
    {
      Unidad *v = E.UnidadActual();
      // Solo puede ejecutarse la acción sobre una unidad del ejército
      // actual.
      if (!v || E.enumEjer (v->uEjercito()) != E.EjercitoActual())
				{
					ImprimirError (E, 0);
					ac = E.LeerAccion (tNULO);
				}
      else if (v->Cargando())
				{
					ImprimirError (E, 2);
					ac = E.LeerAccion (tNULO);
				}
      else if (v->Combatiendo())
				{
					ImprimirError (E, 3);
					ac = E.LeerAccion (tNULO);
				}
			else if (v->Huyendo())
				{
					ImprimirError (E, 11);
					ac = E.LeerAccion (tNULO);
				}
      else if (Comp(v->MovMax(), 0))
				{
					ImprimirError (E, 5);
					ac = E.LeerAccion (tNULO);
				}
      else
				((acMovPivotarDer*)ac)->NuevoAng (ElegirAngDer (E, esc));
    }
  else if (ac->T() == tcomSIGCOMBATE)
    {
      EfPendientes *efP = ((acComSigCombate*)ac)->Pendientes();
      ElegirAtaques (E, efP);
    }
	else if (ac->T() == tmovGIRAR)
		{
      Unidad *v = E.UnidadActual();

      if (!v || E.enumEjer (v->uEjercito()) != E.EjercitoActual())
				{
					ImprimirError (E, 0);
					ac = E.LeerAccion (tNULO);
				}
			else if (v->Huyendo())
				{
					ImprimirError(E, 11);
					ac = E.LeerAccion (tNULO);
				}
      else if (v->Cargando())
				{
					ImprimirError (E, 2);
					ac = E.LeerAccion (tNULO);
				}
      else if (v->Combatiendo())
				{
					ImprimirError (E, 3);
					ac = E.LeerAccion (tNULO);
				}
			else if (v->Marchando())
				{
					ImprimirError(E, 13);
					ac = E.LeerAccion (tNULO);
				}
			else if (v->Marchado())
				{
					ImprimirError(E, 13);
					ac = E.LeerAccion (tNULO);
				}
			else if (!Mayor(v->MovMax(), v->Atributos().m / 4))
				{
					ImprimirError(E, 14);
					ac = E.LeerAccion (tNULO);
				}
		}
	else if (ac->T() == tdisDISPARAR)
		{
      Unidad *v = E.UnidadActual();
      // Solo puede ejecutarse la acción sobre una unidad del ejército
      // actual.
      if (!v || E.enumEjer (v->uEjercito()) != E.EjercitoActual())
				{
					ImprimirError (E, 0);
					ac = E.LeerAccion (tNULO);
				}
      else if (v->Combatiendo())
				{
					ImprimirError (E, 3);
					ac = E.LeerAccion (tNULO);
				}
			else if (v->Huyendo())
				{
					ImprimirError (E, 11);
					ac = E.LeerAccion (tNULO);
				}
			else if (v->Disparado())
				{
					ImprimirError (E, 16);
					ac = E.LeerAccion (tNULO);
				}
			else if (v->Atributos().hp == 0)
				{
					ImprimirError(E,19);
					ac = E.LeerAccion(tNULO);
				}
			else if (v->Atributos().fa == 0)
				{
					ImprimirError(E,18);
					ac = E.LeerAccion(tNULO);
				}
      else
				{
					Unidad *w = ElegirUnidadCarga(E, esc, false);

					if (w != NULL)
						((acDisDisparar*)ac)->DeclararDisparo (v, w);
					else
						ac = E.LeerAccion(tNULO);
				}
		}

  return (ac);
}

// GestorIntefaz::ElegirUnidadCarga
/*************************************/
Unidad* GestorInterfaz::ElegirUnidadCarga (const Estado& E, const GestorEscenario& esc, bool com)
{
  vector<Unidad*> vu;
  Unidad *sel; // Guarda cual fué la última unidad apuntada por el ratón.
  bool selAct; // Guarda si hay alguna unidad seleccionada actualmente.

  // Consigo a todas las unidades visibles.
  for (unsigned i = 0; i < 2; ++i)
    {
      const Ejercito *e = E.pEjer ((Ejer)i);
      Unidad *u = E.UnidadActual();

      for (unsigned j = 0; j < e->nUnidades(); ++j)
				{
					Unidad *w = (*e)[j];

					if (w->Activo() && u != w && w->uEjercito() != u->uEjercito() && esc.Visible (E, w))
						if (com || !w->Combatiendo())
							vu.push_back (w);
				}
		}

  if (!vu.size())
    {
      ImprimirError(E, 1);
      return (0);
    }

  while (1)
    {
      sel = 0;
      selAct = false;

      // Consigo la unidad a la que está apuntando el ratón, y la marco como apuntada.
      int x, y;
      SDL_GetMouseState (&x, &y);
      Punto p(x / fw, 700 - y / fh);

      unsigned i = 0;
      while (i < vu.size() && !(*vu[i] << p))
				++i;

      if (i < vu.size())
				{
					sel = vu[i];
					selAct = true;
				}
      else
				selAct = false;

      // Imprimo todas las unidades visibles.
      for (unsigned i = 0; i < vu.size(); ++i)
				{
					SDL_Surface *aux = pixelUnidad;

					if (selAct && vu[i] == sel)
						aux = pixelUnidadCargaSel;

					RellenarArea(vu[i]->R(), aux);
				}

      Imprimir (E, 0);
      SDL_Delay (40);

      // Miro si se ha elegido.
      SDL_Event click;
      while (SDL_PollEvent (&click))    // Si se pulsa el botón derecho del ratón.
				if (click.type == SDL_MOUSEBUTTONDOWN && click.button.button == SDL_BUTTON_LEFT && sel)
					return (sel);
				else if (click.type == SDL_KEYDOWN && click.key.keysym.sym == SDLK_ESCAPE)
					return (0);
    }
}		

// GestorIntefaz::ElegirDespl
/*************************************/
double GestorInterfaz::ElegirDespl (const Estado& E, const GestorEscenario& esc)
{
  Unidad *u = E.UnidadActual();

  if (u)
    {
      Atrib a = u->Atributos();
      Rectangulo o(u->R());
      Rectangulo r(o);
      // Se obtiene un rectangulo con el area de desplazamiento posible.
      Rectangulo s(o.b, o.w, esc.DesplMax (E, u), AngGR (180) + o.ang);

      while (1)
				{
					// La posición provisional de la unidad será modificada
					// según donde situe el usuario el ratón (dentro del área).
					int x, y;
					SDL_GetMouseState (&x, &y);
					Punto p(x / fw, 700 - y / fh);

					if (s << p)
						{
							r = o;
							r += Recta (s.a, s.b).Distancia (p);
						}

					RellenarArea(s, pixelArea);
					RellenarArea(r, pixelUnidad);

					Imprimir (E, 0);
					SDL_Delay (40);

					// Si se hace click dentro del area, se devuelve el
					// desplazamiento efectuado.
					SDL_Event click;
					while (SDL_PollEvent (&click))    // Si se pulsa el botón derecho del ratón.
						if (click.type == SDL_MOUSEBUTTONDOWN && click.button.button == SDL_BUTTON_LEFT && s << p)
							return (Recta (o.a, o.b).Distancia (p) - 1);
						else if (click.type == SDL_KEYDOWN && click.key.keysym.sym == SDLK_ESCAPE)
							return (0);
				}
		}

  return (0);
}

// GestorIntefaz::ElegirAngIzq
/*************************************/
double GestorInterfaz::ElegirAngIzq (const Estado& E, const GestorEscenario& esc)
{
  Unidad *u = E.UnidadActual();

  if (u)
    {
      Atrib a = u->Atributos();
      Rectangulo o(u->R());
      Rectangulo r(o);
      // Semidisco que indica el area de pivotaje posible. El resto
      //  del código sigue un comportamiento análogo al de DesplMax.
      Semidisco s(o.a, o.ang, AngC (o.ang + esc.PivotMaxIzq (E, u)), o.w);

      while (1)
				{
					int x, y;
					SDL_GetMouseState (&x, &y);
					Punto p(x / fw, 700 - y / fh);

					if (s << p)
						{
							r = o;
							r &= Recta (o.a, o.b) ^ Recta (o.a, p);
						}

					RellenarArea(s, pixelArea);
					RellenarArea(r, pixelUnidad);

					Imprimir (E, 0);
					SDL_Delay (40);

					SDL_Event click;
					while (SDL_PollEvent (&click))    // Si se pulsa el botón derecho del ratón.
						if (click.type == SDL_MOUSEBUTTONDOWN && click.button.button == SDL_BUTTON_LEFT && s << p)
							return (Recta (o.a, o.b) ^ Recta (o.a, p));
						else if (click.type == SDL_KEYDOWN && click.key.keysym.sym == SDLK_ESCAPE)
							return (0);
				}
		}

  return (0);
}

// GestorIntefaz::ElegirAngDer
/*************************************/
double GestorInterfaz::ElegirAngDer (const Estado& E, const GestorEscenario& esc)
{
  Unidad *u = E.UnidadActual();

  if (u)
    {
      Atrib a = u->Atributos();
      Rectangulo o(u->R());
      Rectangulo r(o);
      // Semidisco que indica el area de pivotaje posible. El resto
      //  del código sigue un comportamiento análogo al de DesplMax.
      Semidisco s(o.b, AngC (AngGR (180) + o.ang - esc.PivotMaxDer (E, u)), AngC (AngGR (180) + o.ang), o.w);

      while (1)
				{
					int x, y;
					SDL_GetMouseState (&x, &y);
					Punto p(x / fw, 700 - y / fh);

					if (s << p)
						{
							Recta w(o.b, p);
							r = Rectangulo (w.ExtremoSegmento (o.b, o.w), o.w, o.h, AngGR (360) + o.ang - (w ^ Recta (o.b, o.a)));
						}

					RellenarArea(s, pixelArea);
					RellenarArea(r, pixelUnidad);

					Imprimir (E, 0);
					SDL_Delay (40);

					SDL_Event click;
					while (SDL_PollEvent (&click))    // Si se pulsa el bot�n derecho del rat�n.
						if (click.type == SDL_MOUSEBUTTONDOWN && click.button.button == SDL_BUTTON_LEFT && s << p)
							return (Recta(o.b, p) ^ Recta(o.b, o.a));
						else if (click.type == SDL_KEYDOWN && click.key.keysym.sym == SDLK_ESCAPE)
							return (0);
				}
		}

  return (0);
}

// GestorInterfaz::ElegirAtaques
/*************************************/
void GestorInterfaz::ElegirAtaques (const Estado& E, EfPendientes *efP)
{
  typedef multimap<Unidad*, unsigned> ListEfecs;
  ListEfecs aux;

  for (EfPendientes::iterator i = efP->begin(); i != efP->end(); ++i)
    for (ListaEf::iterator j = i->second.v.begin(); j != i->second.v.end(); ++j)
      if (j->second.n)
				aux.insert(pair<Unidad*, unsigned>(i->first, j->first));

  ListEfecs::iterator pulsado = aux.end(); // Si hay algún efectivo pulsado.
  ListEfecs::iterator sel = aux.end(); // Si hay algún efectivo seleccionado.
  Unidad *uSel = 0; // Si hay una unidad seleccionada.

  while (!aux.empty())
    {
      int x, y;
      SDL_GetMouseState (&x, &y);
      Punto p(x / fw, 700 - y / fh);

      for (ListEfecs::iterator i = aux.begin(); i != aux.end(); ++i)
				{
					SDL_Surface *pAux;
					Unidad *u = i->first;
					Punto ro = u->Atributos().ro;
					Rectangulo r(u->Efec(i->second));
					Rectangulo s(r.Envoltura());

					bool selBucle = false;

					if (pulsado == i)
						{
							pAux = pixelUnidad;
							SDL_Surface *qAux;

							ListaAt *J = &((*efP)[u].v[i->second].v);
							bool uBucle = false;
							for (ListaAt::iterator j = J->begin(); j != J->end(); ++j)
								{
									Unidad *v = j->first;

									Rectangulo t(v->R());
									Rectangulo x(t.Envoltura());

									if (t << p)
										{
											qAux = pixelUnidad;
											uSel = v;
											uBucle = true;
										}
									else
										{
											qAux = pixelUnidadCargaSel;

											if (!uBucle)
												uSel = 0;
										}

									RellenarArea(t, qAux);
								}}
					else if (pulsado != aux.end())
						pAux = pixelArea;
					else if (r << p)
						{
							pAux = pixelUnidad;
							sel = i;
							selBucle = true;
						}
					else
						{
							pAux = pixelUnidadCargaSel;

							if (!selBucle)
								sel = aux.end();
						}

					RellenarArea(r, pAux);
				}

      Imprimir(E, 0);
      SDL_Delay (40);

      SDL_Event click;
      while (SDL_PollEvent(&click))    // Si se pulsa el botón derecho del ratón.
				if (click.type == SDL_MOUSEBUTTONDOWN && click.button.button == SDL_BUTTON_LEFT)
					{
						if (pulsado == aux.end())
							{
								if (sel != aux.end())
									{
										pulsado = sel;
										sel = aux.end();
									}}
						else if (uSel != 0)
							{
								AsignarAt (efP, pulsado->first, pulsado->second, uSel, 1);
								uSel = 0;

								if (!AtPendientes(efP, pulsado->first, pulsado->second))
									{
										aux.erase(pulsado);
										pulsado = aux.end();
									}}}
				else if (click.type == SDL_KEYDOWN && click.key.keysym.sym == SDLK_ESCAPE)
					{
						if (pulsado != aux.end())
							pulsado = aux.end();
						else
							exit(EXIT_FAILURE);
					}
		}
}

// GestorInterfaz::Imprimir
/*************************************/
void GestorInterfaz::Imprimir (const Estado& E, Unidad *u)
{
  SDL_Rect msjdesc = { 70 * fw, 740 * fh, 500 * fw, 0 };
  SDL_Rect mtitulo = { 0, 10 * fh, 1280 * fw, 50 * fw };
  SDL_Rect marco1 = { 70 * fw, 700 * fh, 500 * fw, 100 * fh };
  SDL_Rect marco2 = { 710 * fw, 700 * fh, 500 * fw, 100 * fh };

  SDL_BlitSurface (fondo, 0, marco, 0);

  SDL_BlitSurface (marcos, 0, marco, &marco1);
  SDL_BlitSurface (marcos, 0, marco, &marco2);

  gi->ImprimirIconos (E, marco, fuenteN, color, msjdesc);

  if (!errores.empty())
    {
      SDL_Rect x = marco2;
			x.y += 19;

      sort(errores.begin(), errores.end(), CompI());

      vector<vector<pCont>::iterator> pContelim;
      for (vector<pCont>::iterator i = errores.begin(); i != errores.end(); ++i)
				{
					if (i->second % 40)
						{
							++(i->second);

							x.x += (x.w - i->first->w) / 2;

							SDL_BlitSurface (i->first, NULL, marco, &x);

							x.x = marco2.x;

							// Ojo: BlitSurface modifica a 'x', entonces, modifica
							// su ancho.
							x.w = marco2.w;
							x.y += i->first->h;
						}
					else
						pContelim.push_back(i);
				}

      for (unsigned i = 0; i < pContelim.size(); ++i)
				errores.erase(pContelim[i]);
    }

  if (u)
    ImprimirDescripcion (u, E);

  ImprimirEjercito (E.pEjer (ePRIM), E);
  ImprimirEjercito (E.pEjer (eSEG), E);

  for (unsigned i = 0; i < imgs.size(); ++i)
    SDL_BlitSurface (imgs[i].img, 0, marco, &imgs[i].r);

  ostringstream o;

  if (!E.Turno())
    o << "EJERCITOS DESPLEGADOS";
  else
    {
      o << "TURNO " << E.Turno() << "   ";

      if (E.EjercitoActual() == ePRIM)
				o << "Primer ejercito";
      else
				o << "Segundo ejercito";
    }

	SDL_Color colorT = { 255, 255, 0 };
  SDL_Surface *aux = TTF_RenderUTF8_Solid (fuenteT, o.str().c_str(), colorT);
  SDL_Rect raux = { (mtitulo.w - aux->w) / 2, 8 * fh, 0, 0 };
  SDL_BlitSurface (aux, 0, marco, &raux);
  delete aux;

  SDL_Flip (marco);
  
  imgs.clear();
} // Fin de la función

// GestorIntefaz::ImprimirEjercito
/*************************************/
void GestorInterfaz::ImprimirEjercito (const Ejercito *e, const Estado& E)
{
  for (unsigned i = e->nUnidades(); i--; )
    {
      Unidad *u = (*e)[i];                         // i-ésima unidad del ejército actual.

      if (u->Activo())
				{
					Atrib a = u->Atributos();

					Rectangulo r(Punto(), a.ro.x, a.ro.y, u->Ang());
					Punto x, y;

					double ang = AngRG (u->Ang());

					// Cada imagen tiene de resolución la envoltura de la peana
					//  pivotada. 'x' será entonces el desplazamiento que existe
					//  desde el pivote superior izquierdo de la pena al pivote
					//  superior izquierdo de su envoltura (imágen).
					if (Intervalo (0, 90, ang))
						x = Punto(0, Abs (r.b.y - r.a.y));
					else if (Intervalo (90, 180, ang))
						x = Punto(Abs (r.a.x - r.b.x), Abs (r.c.y - r.a.y));
					else if (Intervalo (180, 270, ang))
						x = Punto(Abs (r.a.x - r.c.x), Abs (r.d.y - r.a.y));
					else if (Intervalo (270, 360, ang))
						x = Punto(Abs (r.a.x - r.d.x), 0);

					unsigned j = u->N() + 1;

					while (--j)      // Se imprimen todos los efectivos.
						{
							SDL_Rect po;
							y = u->Efec(j).a;
							y.x = (unsigned)(y.x + .5);
							y.y = (unsigned)(y.y + .5);

							po.x = (int)(.5 + (y.x - x.x) * fw);

							// Se transforma la coordenada 'y' por que el gestor de
							// reglas considera las dimensiones del juego según las
							// coordenadas cartesianas clásicas, pero SDL considera
							// la coordenada 'y' en sentido inverso.
							po.y = (int)(.5 + (700 - (y.y + x.y)) * fh);
							imgs.insert(imgs.begin(), ParejaImg(u->ImgActual(), po));
						}

					SDL_Rect po;
					Punto p(u->puntoImpr());

					po.x = p.x * fw + .5;
					po.y = (700 - p.y) * fh + .5;

					if (u == E.UnidadActual())
						imgs.insert(imgs.end() - 1, ParejaImg(u->ImgMarcado(), po));
					else if (u->Seleccionado())
						imgs.insert(imgs.end() - 1, ParejaImg(u->ImgSeleccionado(), po));
				}
		}
}

// GestorIntefaz::ImprimirDescripcion
/*************************************/
void GestorInterfaz::ImprimirDescripcion (Unidad *u, const Estado& E)
{
  Atrib a = u->Atributos();
  SDL_Rect msj = { 160 * fw, 720 * fh, 0, 0 };
  ostringstream o, p, q, r;

  string tipo = "Unidad: " + a.nombre + ", Ejército: ";

  if (E.enumEjer (u->uEjercito()) == ePRIM)
    tipo += "Primero";
  else if (E.enumEjer (u->uEjercito()) == eSEG)
    tipo += "Segundo";

  o << "M" << a.m << " HA" << a.ha << " HP" << a.hp << " F" << a.f << " R" << a.r
    << " A" << a.a << " H" << a.h << " I" << a.i << " L" << a.l << " FA" << a.fa
		<< " AA" << a.aa;
  p << "Movimiento restante: " << u->MovMax();
  q << "Número de efectivos: " << u->N() << " (" << (unsigned)(100 * (float)u->N() / u->NO()) << "%)";

  if (u->Cargando())
    r << "Cargando";
  else if (u->Marchando())
    r << "Marchando";
  else if (u->Huyendo())
    r << "Huyendo";
  else if (u->Combatiendo())
    r << "Combatiendo";
  else if (u->Desmoralizado())
    r << "Desmoralizados";

  imgs.push_back (ParejaImg (TTF_RenderUTF8_Solid (fuenteN, tipo.c_str(), color), msj));
  msj.y += 13 * fh;
  imgs.push_back (ParejaImg (TTF_RenderUTF8_Solid (fuenteN, o.str().c_str(), color), msj));
  msj.y += 13 * fh;
  imgs.push_back (ParejaImg (TTF_RenderUTF8_Solid (fuenteN, p.str().c_str(), color), msj));
  msj.y += 13 * fh;
  imgs.push_back (ParejaImg (TTF_RenderUTF8_Solid (fuenteN, q.str().c_str(), color), msj));
  msj.y += 13 * fh;
  imgs.push_back (ParejaImg (TTF_RenderUTF8_Solid (fuenteN, r.str().c_str(), color), msj));
}

// GestorIntefaz::ImprimirError
/*************************************/
void GestorInterfaz::ImprimirError (const Estado& E, short i)
{
  ostringstream o;

	Mix_PlayChannel(1, sonidos[3], 0);

  switch (i)
    {
    case 0:
      o << "Elija una unidad del";
      if (E.EjercitoActual() == ePRIM)
				o << " primer ";
      else if (E.EjercitoActual() == eSEG)
				o << " segundo ";
      o << "ejército";
      break;
    case 1:
      o << "No hay ninguna unidad visible";
      break;
    case 2:
      o << "La unidad ha declarado carga.";
      break;
    case 3:
      o << "La unidad está combatiendo.";
      break;
    case 4:
      o << "La unidad está marchando.";
      break;
    case 5:
      o << "La unidad ha consumido su movimiento.";
      break;
    case 6:
      o << "No se puede iniciar turno";
      break;
    case 7:
      o << "Aún no se puede iniciar la fase movimiento";
      break;
    case 8:
      o << "Aún no se puede iniciar la fase de combate";
      break;
    case 9:
      o << "No existen cargas que resolver";
      break;
    case 10:
      o << "Aún no ha comenzado la batalla";
			break;
		case 11:
			o << "La unidad está huyendo";
			break;
		case 12:
			o << "Aún no se puede efectuar ningún movimiento libre";
			break;
		case 13:
			o << "No se puede girar, la unidad ha marchando";
			break;
		case 14:
			o << "No se dispone de movimiento suficiente para girar";
			break;
		case 15:
			o << "Actualmente la unidad no puede marchar";
			break;
		case 16:
			o << "La unidad ya ha disparado este turno";
			break;
		case 17:
			o << "Aún no se puede efectuar ningún disparo";
			break;
		case 18:
			o << "Esta unidad no posee armas de proyectiles";
			break;
		case 19:
			o << "Esta unidad no sabe disparar";
			break;
    default:
      break;
    }

  if (errores.size() > 4)
    errores.erase(errores.begin());

  errores.push_back(make_pair(TTF_RenderUTF8_Solid (fuenteN, o.str().c_str(), color), 1));
}

// GestorIntefaz::ErrorTarea
/*************************************/
void GestorInterfaz::ErrorTarea (const Estado& E, Tarea t)
{
  switch (t)
		{
    case tTURNO:
      ImprimirError(E, 6);
      break;
    case tMOVIMIENTO:
      if (!E.Turno())
				ImprimirError(E, 10);
      else
				ImprimirError(E, 7);
      break;
    case tCOMBATE:
      if (!E.Turno())
				ImprimirError(E, 10);
      else
				ImprimirError(E, 8);
      break;
    case tmovMOVIMIENTOCARGAS:
      ImprimirError(E, 9);
			break;
		case tmovRESTOMOVIMIENTOS:
			ImprimirError(E, 12);
			break;
		case tDISPARO:
			ImprimirError(E,17);
			break;
    default:
      break;
    }
}

// GestorIntefaz::RellenarArea
/*************************************/
template<typename T> void GestorInterfaz::RellenarArea (const T& fig, SDL_Surface *pix, bool dir)
{
  Rectangulo w(fig.Envoltura());

  SDL_Rect auxs = { (Sint16)(w.a.x * fw),
										(Sint16)((700 - w.a.y) * fh),
										(Sint16)(w.w * fw), (Sint16)(w.h * fh)};

  for (int i = auxs.x; i <= auxs.x + auxs.w; ++i)
    for (int j = auxs.y; j <= auxs.y + auxs.h; ++j)
      if (fig << Punto (i / fw, 700 - j / fh))
				{
					SDL_Rect x = { i, j, 0, 0 };

					if (dir)
						imgs.insert(imgs.begin(), ParejaImg(pix, x));
					else
						imgs.push_back(ParejaImg (pix, x));
				}
}

// GestorIntefaz::ResultadoCombate
/*************************************/
void GestorInterfaz::ResultadoCombate(const Estado& E, Resultado r)
{
	SDL_Event evento;
	bool dentro = true;

	SDL_Rect rejercito1 = { 0, 160 * fh, 500 * fw, 480 * fh };
	SDL_Rect rejercito2 = { 775 * fw, 160 * fh, 500 * fw, 480 * fh };
	SDL_Rect rcuad1 = { 30 * fw, 580 * fh, 450 * fw, 100 * fh };
	SDL_Rect rcuad2 = { 805 * fw, 580 * fh, 450 * fw, 100 * fh };
  SDL_Rect flechaVolver = { 540 * fw, 675 * fh, 200 * fw, 92 * fh };
  SDL_Rect subflechaVolver = { 615 * fw, 735 * fh, 40 * fw, 8 * fh };
	SDL_Rect rpuntosej1 = { 550 * fw, 250 * fh, 250 * fw, 100 * fh };
	SDL_Rect rpuntosej2 = { 550 * fw, 380 * fh, 250 * fw, 100 * fh };
	SDL_Rect rganador = { 500 * fw, 580 * fh, 300 * fw, 100 * fh };
	SDL_Rect rtVictoria = { 500 * fw, 630 * fh, 300 * fw, 100 * fh };

	SDL_Surface *puntosej1;
	SDL_Surface *puntosej2;
	SDL_Surface *ganador;
	SDL_Surface *tVictoria;

	ListaTexto ejercito1(fuenteN, color, rejercito1, NULL, NULL);
	ListaTexto ejercito2(fuenteN, color, rejercito2, NULL, NULL);
	ListaTexto cuadrante1(fuenteN, color, rcuad1, NULL, NULL);
	ListaTexto cuadrante2(fuenteN, color, rcuad2, NULL, NULL);

	bool bflechaVolver = false;

	// Añadimos los puntos de cada unidad.
	typedef map<Unidad*, unsigned>::iterator I;
	for (I i = r.puntos.begin(); i != r.puntos.end(); ++i)
		{
			ostringstream os;

			Unidad *u = i->first;

			os << u->Atributos().nombre << ": " << i->second;

			if (E.enumEjer(u->uEjercito()) == ePRIM)
				ejercito1.NuevoTexto(os.str().c_str());
			else
				ejercito2.NuevoTexto(os.str().c_str());
		}

	// Cuadrantes del primer ejército.
	cuadrante1.NuevoTexto("Primer cuadrante: ");
	cuadrante1.NuevoTexto("Segundo cuadrante: ");
	cuadrante1.NuevoTexto("Tercer cuadrante: ");
	cuadrante1.NuevoTexto("Cuarto cuadrante: ");

	for (unsigned i = 0; i < 4; ++i)
		if (r.cuad[0][i])
			cuadrante1.NuevaEtiqueta(i, marca);

	// Cuadrantes del segundo ejército.
	cuadrante2.NuevoTexto("Primer cuadrante: ");
	cuadrante2.NuevoTexto("Segundo cuadrante: ");
	cuadrante2.NuevoTexto("Tercer cuadrante: ");
	cuadrante2.NuevoTexto("Cuarto cuadrante: ");

	for (unsigned i = 0; i < 4; ++i)
		if (r.cuad[1][i])
			cuadrante2.NuevaEtiqueta(i, marca);

	// Puntuaciones totales/ejercito
	ostringstream os1, os2;

	os1 << r.totalU[0];
	os2 << r.totalU[1];

	if (!(puntosej1 = TTF_RenderUTF8_Solid(fuenteG, os1.str().c_str(), color)))
		cerr << SDL_GetError() << endl;

	if (!(puntosej2 = TTF_RenderUTF8_Solid(fuenteG, os2.str().c_str(), color)))
		cerr << SDL_GetError() << endl;

	SDL_Color colorR = { 255, 255, 255 };

	if (r.v != Empate)
		{
			ostringstream os;

			if (r.total > 0)
				os << "Primer ejército: +" << r.total;
			else if (r.total < 0)
				os << "Segundo ejército: +" << -r.total;

			if (!(ganador = TTF_RenderUTF8_Solid(fuenteG, os.str().c_str(), colorR)))
				cerr << SDL_GetError() << endl;
		}

	ostringstream osnuevo;

	if (r.v == Empate)
		osnuevo << "Empate";
	else if (r.v == VictoriaMarginal)
		osnuevo << "Victoria marginal";
	else if (r.v == VictoriaDecisiva)
		osnuevo << "Victoria decisiva";
	else if (r.v == Masacre)
		osnuevo << "Masacre";
	
	if (!(tVictoria = TTF_RenderUTF8_Solid(fuenteG, osnuevo.str().c_str(), colorR)))
		cerr << SDL_GetError() << endl;

	/*
	 *  Centramos el mensaje de victoria
	 */
	rtVictoria.x += (rtVictoria.w - tVictoria->w) / 2;

	bool bimprimir = true;
  while (dentro)
    {
      SDL_Delay(40);

			if (bimprimir)
				{
					bimprimir = false;

					SDL_BlitSurface(resultado, NULL, marco, NULL);

					ejercito1.Imprimir(marco);
					ejercito2.Imprimir(marco);
					cuadrante1.Imprimir(marco);
					cuadrante2.Imprimir(marco);

					SDL_BlitSurface(puntosej1, NULL, marco, &rpuntosej1);
					SDL_BlitSurface(puntosej2, NULL, marco, &rpuntosej2);
					SDL_BlitSurface(tVictoria, NULL, marco, &rtVictoria);

					if (r.v != Empate)
						{
							rganador.x += (rganador.w - ganador->w) / 2;
							SDL_BlitSurface(ganador, NULL, marco, &rganador);
						}

					if (bflechaVolver)
						SDL_BlitSurface(subrayador, NULL, marco, &subflechaVolver);

					SDL_Flip(marco);
				}

			if (!SDL_PollEvent(&evento))  // Si no quedaban eventos, duermo el sistema
				SDL_WaitEvent(&evento);     // hasta que los haya.

			do
				{
					if (evento.type == SDL_MOUSEMOTION)
						{
							if (InRect(flechaVolver, evento.button.x, evento.button.y))
								{
									bimprimir = true;
									bflechaVolver = true;
								}
							else
								bflechaVolver = false;
						}
					else if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT && bflechaVolver)
							dentro = false;
				} while (SDL_PollEvent(&evento));
		}
}

// GestorIntefaz::~GestorInterfaz
/*************************************/
GestorInterfaz::~GestorInterfaz()
{
  SDL_EnableUNICODE(0);

	for (unsigned i = 0; i < canciones.size(); ++i)
		Mix_FreeMusic(canciones[i]);

	Mix_CloseAudio();

  delete pixelArea;
  delete pixelUnidad;
  delete pixelUnidadCargaSel;
  delete pixelUnidadP;
  delete pixelUnidadS;
  delete marcos;
	delete subrayador;
	delete marca;

  TTF_CloseFont(fuenteT);
  TTF_CloseFont(fuenteE);
  TTF_CloseFont(fuenteN);

  delete ge;

  TTF_Quit();
  SDL_Quit();
}
