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

/*! \file Icono.h
 *  \brief Fichero de definición de la clase \c Icono.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#ifndef _GoM_ICONO_
#define _GoM_ICONO_

#include "SDL/SDL.h"
#include <string>
#include "../../Tipos.h"

/*! \class Icono
 *  \brief Clase icono.
 *
 *  \sa GestorIconos
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class Icono
{
 public:
  /* Constructor */
  Icono (Tarea _t, std::string c, double fw, double fh);

	/* Destructor */
	~Icono();

  /* Consultoras */
  Tarea T() const;

  SDL_Surface* Imagen() const;

  bool operator<< (const Punto& _p) const;

  bool Seleccionado() const;

	Rectangulo Posicion() const;

  /* Modificadoras */
  // Ambas funciones cambian la posición del icono.
  void NuevaPosicion(const Punto& _p);

  void NuevaPosicion(const SDL_Rect& _p);

  void EliminarPosicion();

  void Seleccionar();
  // Selecciona al icono.

  void Deseleccionar();
  // Deselecciona al icono.

 private:
  Tarea t;	// Tarea correspondiente al icono.
  SDL_Surface *s; // imagen del icono 's'.
  Punto p; // Coordenada superior izquierda del icono. Las dimensiones del icono vendrán dadas por 's'.
  bool sel; // Si el icono está seleccionado.
  bool act; // Si el icono tiene asignada posición.
};

#endif
