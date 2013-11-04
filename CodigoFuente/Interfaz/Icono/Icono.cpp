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

/*! \file Icono.cpp
 *  \brief Fichero de implementación de la clase \c Icono.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#include <iostream>
#include "Icono.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"

using namespace std;

// Icono::Icono
/*************************************/
Icono::Icono (Tarea _t, string c, double fw, double fh) : t(_t)
{
  SDL_Surface *sOr;

  if (!(sOr = IMG_Load (c.c_str())))
    cerr << SDL_GetError() << endl << flush;

  if (!(s = zoomSurface(sOr, fw, fh, 0)))
    cerr << SDL_GetError() << endl << flush;

  sel = false;
  act = false;

	delete sOr;
}

// Icono:T
/**************************************/
Tarea Icono::T() const
{
  return (t);
}

// Icono:Imagen
/**************************************/
SDL_Surface* Icono::Imagen() const
{
  return (s);
}

// Icono::operator<<
/*************************************/
bool Icono::operator<< (const Punto& _p) const
{
  // Comprueba que las coordenadas del punto estén inmersas en las
  // coordenadas del cuadro del icono.

  if (act)
    return (_p.x > p.x && _p.x < (p.x + s->w) && _p.y > p.y && _p.y < (p.y + s->h));
  else
    return (false);
}

// Icono::Seleccionado
/*************************************/
bool Icono::Seleccionado() const
{
  return (sel);
}

// Icono::Posicion
/*************************************/
Rectangulo Icono::Posicion() const
{
  return (Rectangulo(p, s->w, s->h, 0));
}

// Icono::NuevaPosicion
/*************************************/
void Icono::NuevaPosicion (const Punto& _p)
{
  act = true;

  p = _p;
}

// Icono::NuevaPosicion
/*************************************/
void Icono::NuevaPosicion (const SDL_Rect& _p)
{
  act = true;

  p = Punto (_p.x, _p.y);
}

// Icono::EliminarPosicion
/*************************************/
void Icono::EliminarPosicion()
{
  act = false;
}

// Icono::Seleccionar
/*************************************/
void Icono::Seleccionar()
{
  sel = true;
}

// Icono::Deseleccionar
/*************************************/
void Icono::Deseleccionar()
{
  sel = false;
}

// Icono::~Icono
/*************************************/
Icono::~Icono()
{
  if (s)
		delete s;
}
