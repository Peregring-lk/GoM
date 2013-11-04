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

/*! \file GestorIconos.cpp
 *  \brief Fichero que implementa al gestor de iconos.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#include "GestorIconos.h"
#include "SDL/SDL_rotozoom.h"

using namespace std;

// GestorIconos::GestorIconos
/************************************/
GestorIconos::GestorIconos(double _fw, double _fh) : fw(_fw), fh(_fh)
{
  // Se crea un icono, que coincide en tamaño y posición con el
  // escenario, que corresponde a la acción Elegir unidad.
  // Este punto indica la esquina superior derecha de dicho icono.
  marcoElegirUnidad = Punto(0, 105 * fh);

  marcoElegirUnidadImpr.x = 0;
  marcoElegirUnidadImpr.y = 100 * fh;
  marcoElegirUnidadImpr.w = 0;
  marcoElegirUnidadImpr.y = 0;

	InicializarDescripciones();

	SDL_Surface *sOr;

	if (!(sOr = IMG_Load("Imagenes/Especiales/selectorIconos.png")))
		cerr << SDL_GetError() << endl;

	if (!(selector = zoomSurface(sOr, fw, fh, 0)))
		cerr << SDL_GetError() << endl;

	delete sOr;

	seleccionado = tNULO;
}

// GestorIconos::Inicializar
/************************************/
void GestorIconos::Inicializar (const Estado& E)
{
  // Se crean iconos para cada una de las acciones permitidas durante la partida.
  for (unsigned t = 0; t < nTareas; ++t)
    {
      Accion *ac = E.LeerAccion ((Tarea)t);

      if (!ac || ac->T() == tNULO)
				ic[t] = 0;
      else
				ic[t] = new Icono((Tarea)t, DirImagen ((Tarea)t), fw, fh);
    }

  ic[tELEGIRUNIDAD]->NuevaPosicion(marcoElegirUnidad);
}

// GestorIconos::EncuentraTarea
/************************************/
Tarea GestorIconos::EncuentraTarea (const Estado& E, const Punto& p)
{
	for (unsigned t = 0; t + 1 < nTareas; ++t)
		if (E.LeerAccion ((Tarea)t) && ic[t] && (*ic[t] << p))
			{
				// Se selecciona automáticamente la tarea encontrada.
				ic[t]->Seleccionar();
				seleccionado = (Tarea)t;
						
				return ((Tarea)t);
			}

  return (tNULO);
}

// GestorIconos::Seleccionado
/************************************/
Tarea GestorIconos::Seleccionado()
{
	return (seleccionado);
}
 
// GestorIconos::ImprimirIconos
/************************************/
void GestorIconos::ImprimirIconos (const Estado& E, SDL_Surface *s, TTF_Font *f, SDL_Color c, SDL_Rect msj)
{
	const unsigned anchoIcono = 40 * fw;
	SDL_Rect activo = { 745 * fw, 56 * fh, 0, 0 };

	vector<Tarea> vDisponibles;

	/*
	 *  Entre todos los iconos sustentos a impresión (activos no
	 *  disponibles y activos disponibles), solo se imprimen en este
	 *  primer bucle los activos no disponibles. Los activos disponibles
	 *  se guardan en un vector, y se imprimen en el bucle siguiente.
	 */
  for (unsigned t = 0; t < nTareas; ++t)
    if (ic[t])
      {
				if ((Tarea)t == tELEGIRUNIDAD)
					SDL_BlitSurface (ic[t]->Imagen(), 0, s, &marcoElegirUnidadImpr);
				else
					{
						if (E.LeerTarea((Tarea)t, false))
							vDisponibles.push_back((Tarea)t);
						else if (E.LeerTarea((Tarea)t, true))
							{
								ic[t]->NuevaPosicion(activo);
								SDL_BlitSurface(ic[t]->Imagen(), NULL, s, &activo);

								activo.x += anchoIcono;
							}
						else
							ic[t]->EliminarPosicion();
					}
      }

	// Si está seleccionado se imprime el mensaje descriptivo del icono.
	if (seleccionado != tNULO)
		{
			if (seleccionado != tELEGIRUNIDAD)
				{
					SDL_Surface *texto = TTF_RenderUTF8_Solid(f, Desc[seleccionado].c_str(), c);
					SDL_Rect aux = { msj.x + (msj.w - texto->w) / 2, msj.y, 0, 0 };
					SDL_BlitSurface (texto, NULL, s, &aux);
				}

			Rectangulo R(ic[seleccionado]->Posicion());
			unsigned diferencia = (selector->w - R.w) / 2;

			// Asumimos que tanto iconos como el selector son
			// cuadrados (cuatro lados iguales).
			SDL_Rect selIcono = { R.a.x - diferencia, R.a.y - diferencia,
														selector->w, selector->h };
			SDL_BlitSurface(selector, NULL, s, &selIcono);

			ic[seleccionado]->Deseleccionar();
		}

	/*
	 *  Una vez conocidos el número de iconos disponibles, se imprimen
	 *  de modo que queden centrados en su sección de la zona de iconos.
	 */
	unsigned iDisponibles = vDisponibles.size();
	unsigned anchoSeccionDisponibles = 360 * fw;
	unsigned anchoIconosDisponibles = anchoIcono * iDisponibles;
	SDL_Rect disponible = { 370 * fw + (anchoSeccionDisponibles - anchoIconosDisponibles) / 2, 
													56 * fh, 0, 0 };
	for (unsigned i = 0; i < vDisponibles.size(); ++i)
		{
			Icono* icono = ic[vDisponibles[i]];

			icono->NuevaPosicion(disponible);
			SDL_BlitSurface(icono->Imagen(), NULL, s, &disponible);

			disponible.x += anchoIcono;
		}
}

// GestorIconos::DeseleccionarIcono
/************************************/
void GestorIconos::DeseleccionarIcono(Tarea t)
{
	if (ic[t])
		ic[t]->Deseleccionar();

	seleccionado = tNULO;
}

// GestorIconos::DirImagen
/************************************/
string GestorIconos::DirImagen(Tarea t)
{
  switch (t)
    {
    case tTURNO:
      return ("Imagenes/Iconos/IconoTURNO.png");
    case tMOVIMIENTO:
      return ("Imagenes/Iconos/IconoMOVIMIENTO.png");
    case tmovDECLARACIONCARGAS:
			return ("Imagenes/Iconos/IconoDECLARACIONCARGAS.png");
    case tmovDECLARARCARGA:
      return ("Imagenes/Iconos/IconoDECLARARCARGA.png");
    case tmovMOVIMIENTOCARGAS:
      return ("Imagenes/Iconos/IconoMOVIMIENTOCARGAS.png");
    case tmovCARGAR:
      return ("Imagenes/Iconos/IconoCARGAR.png");
    case tmovRESTOMOVIMIENTOS:
      return ("Imagenes/Iconos/IconoRESTOMOVIMIENTOS.png");
    case tELEGIRUNIDAD:
      return ("Imagenes/Iconos/1280600.png");
    case tmovMARCHAR:
      return ("Imagenes/Iconos/IconoMARCHAR.png");
    case tmovMOVER:
      return ("Imagenes/Iconos/IconoMOVER.png");
    case tmovPIVOTARIZQ:
      return ("Imagenes/Iconos/IconoPIVOTARIZQ.png");
    case tmovPIVOTARDER:
      return ("Imagenes/Iconos/IconoPIVOTARDER.png");
    case tmovGIRAR:
      return ("Imagenes/Iconos/IconoGIRAR.png");
    case tCOMBATE:
      return ("Imagenes/Iconos/IconoCOMBATE.png");
    case tcomRESOLUCIONCOMBATES:
      return ("Imagenes/Iconos/IconoRESOLUCIONCOMBATES.png");
    case tcomSIGCOMBATE:
      return ("Imagenes/Iconos/IconoSIGCOMBATE.png");
    case tcomHUIDAS:
      return ("Imagenes/Iconos/IconoHUIDAS.png");
    case tcomSIGHUIDA:
      return ("Imagenes/Iconos/IconoSIGHUIDA.png");
		case tDISPARO:
			return ("Imagenes/Iconos/IconoDISPARO.png");
		case tdisDISPARAR:
			return ("Imagenes/Iconos/IconoDISPARAR.png");
    case tFINALIZARBATALLA:
      return ("Imagenes/Iconos/IconoFINALIZARBATALLA.png");
    default:
      return ("Imagenes/Iconos/IconoNULO.png");
    }
}

// GestorIconos::InicializarDescripciones
/************************************/
void GestorIconos::InicializarDescripciones()
{
	for (unsigned t = 0; t < nTareas; ++t)
		{
			string texto;

			if ((Tarea)t == tTURNO)
				texto = "Siguiente turno";
			else if ((Tarea)t == tMOVIMIENTO)
				texto = "Fase de movimiento";
			else if ((Tarea)t == tELEGIRUNIDAD)
				texto = "Selecciona a una unidad";
			else if ((Tarea)t == tmovDECLARACIONCARGAS)
				texto = "Subfase de declaración de cargas";
			else if ((Tarea)t == tmovDECLARARCARGA)
				texto = "Declara una nueva carga";
			else if ((Tarea)t == tmovMOVIMIENTOCARGAS)
				texto = "Subfase de movimiento de cargas";
			else if ((Tarea)t == tmovCARGAR)
				texto = "Mueve la siguiente carga";
			else if ((Tarea)t == tmovRESTOMOVIMIENTOS)
				texto = "Subfase de resto de movimientos";
			else if ((Tarea)t == tmovMARCHAR)
				texto = "Marchando / Andando";
			else if ((Tarea)t == tmovMOVER)
				texto = "Desplaza a una unidad";
			else if ((Tarea)t == tmovPIVOTARIZQ)
				texto = "Pivota la unidad a la izquierda";
			else if ((Tarea)t == tmovPIVOTARDER)
				texto = "Pivota a la unidad a la derecha";
			else if ((Tarea)t == tmovGIRAR)
				texto = "Gira la unidad a su retaguardia";
			else if ((Tarea)t == tCOMBATE)
				texto = "Fase de combate";
			else if ((Tarea)t == tcomRESOLUCIONCOMBATES)
				texto = "Subfase de resolución de combates";
			else if ((Tarea)t == tcomSIGCOMBATE)
				texto = "Resuelve el siguiente combate";
			else if ((Tarea)t == tcomHUIDAS)
				texto = "Subfase de huidas";
			else if ((Tarea)t == tcomSIGHUIDA)
				texto = "Siguiente huida";
			else if ((Tarea)t == tDISPARO)
				texto = "Fase de disparo";
			else if ((Tarea)t == tdisDISPARAR)
				texto = "Elegir disparo";
			else if ((Tarea)t == tFINALIZARBATALLA)
				texto = "Finaliza la batalla";
			else
				texto = "¿?";

			Desc[t] = texto;
		}
}

// GestorIconos::~GestorIconos
/************************************/
GestorIconos::~GestorIconos()
{
	if (selector)
		delete selector;
}
