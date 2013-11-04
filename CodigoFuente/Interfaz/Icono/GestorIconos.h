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

/*! \file GestorIconos.h
 *  \brief Fichero que define al gestor de iconos.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#ifndef _GoM_GESTOR_ICONOS_
#define _GoM_GESTOR_ICONOS_

#include <iostream>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "Icono.h"

/*! \class GestorIconos
 *  \brief Clase del gestor de iconos.
 *
 *  \sa GestorIntefaz
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class GestorIconos
{
 public:
  /* Constructor */
  GestorIconos(double _fw, double _fh);

	/* Destructor */
	~GestorIconos();

  /* Consultoras */
  Tarea EncuentraTarea (const Estado& E, const Punto& p);
  // Encuentra la tarea correspondiente al icono indicado por el punto
  // 'p'.

	Tarea Seleccionado();

  /* Modificadoras */
  void Inicializar (const Estado& E);
  // Inicializa toda la estructura interna necesaria del gestor de iconos.

  void ImprimirIconos (const Estado& E, SDL_Surface *s, TTF_Font *f, SDL_Color c, SDL_Rect msj);
  // Imprime todos los iconos disponibles actualmente. Si un icono está seleccionado
  // (solo podrá estarlo uno a la vez) se imprimirá en 'msj' con fuente y color 'f'+'c', 
  // el mensaje explicativo de la tarea del icono.

	void DeseleccionarIcono(Tarea t);

 private:
  Icono* ic[nTareas];

	Tarea seleccionado;

  double fw, fh;

  // Se crea un icono, que coincide en tamaño y posición con el escenario, que corresponde a la acción Elegir unidad.
  // Este punto indica la esquina superior derecha de dicho icono.
  Punto marcoElegirUnidad;
  SDL_Rect marcoElegirUnidadImpr;

	SDL_Surface *selector;

	std::string Desc[nTareas];

  std::string DirImagen (Tarea t);
  // Devuelve una cadena con la dirección de la imagen base
  // correspondiente a la tarea t.

	void InicializarDescripciones();
};

#endif
