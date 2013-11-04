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

/*! \file GoM.h
 *  \brief Clase principal del juego.
 *
 *  \par Detalles de implementación:
 *  El comentido de esta clase es, en realidad, bastante triste por un lado, pero por
 *  otro lado necesaria. Su misión principal es simplemente servir de clase puente entre
 *  las clases con más peso \c GoM_GestorReglas y \c GestorInterfaz: es la clase de hacer
 *  posible el paso de mensajes de una a otra. Aunque por su posición, es la
 *  responsable de ejecutar el bucle principal del juego, como ya se describió en la
 *  página principal.
 *
 *  \par
 *  La otra "gran" misión de la clase \c GoM es la de retransmitir la orden de
 *  creación e inicialización de los tipos del juego al crearse un objeto tipo \c GoM
 *  desde la clase principal (\c main). Esto se logra creando e inicializando, en el
 *  constructor, un objeto tipo \c GestorReglas y otro tipo \c GestorInterfaz, que a su
 *  vez se encargarán de crear e inicializar a otras clases
 *  colaboradoras de ambas.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#ifndef _GoM_JUEGO_
#define _GoM_JUEGO_

#include <string>
#include "Interfaz/GestorInterfaz.h"

/*! \class Juego
 *  \brief Clase juego.
 *
 *  Esta clase es la clase que contiene las funciones principales del
 *  juego, y lanza y comunica a los gestores de reglas y de interfaz.
 *
 *  \sa GestorReglas
 *  \sa GestorInterfaz
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class Juego
{
 public:
  /*! \fn void LanzarGoM()
	 *  \brief Función principal del juego.
	 *
	 *  Crea al gestor de interfaz y lanza al menú principal del
	 *  juego, gestionando las peticiones del usuario y comunicando al
	 *  gestor de reglas con el gestor de interfaz (lo que constituye el
	 *  bucle principal del juego) en caso de que el usuario desee
	 *  comenzar una batalla.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
  void LanzarGoM();
};

#endif
