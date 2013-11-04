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

/*! \file Accion.h
 *  \brief Fichero de definición de la clase abstracta \c Accion.
 *
 *  Es la clase base de todas las acciones del juego.
 *
 *  \sa GestorReglas
 *  \sa GestorInterfaz
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#ifndef _GoM_ACCION_
#define _GoM_ACCION_

#include "Enumeraciones.h"
#include "Clases.h"

/*! \class Accion
 *  \brief Clase acción
 *
 *  La clase acción es la clase base de todas las acciones del
 *  juego. Mantiene la información común a todas las acciones del
 *  juego:
 *  \li Tarea a la que corresponde la acción.
 *  \li Fase a la que corresponde la acción.
 *  \li Subfase a la que corresponde la acción.
 *  \li Identificador usado por el gestor responsable de la acción.
 *
 *  \sa \c GestorReglas
 *  \sa \c GestorInterfaz
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class Accion
{
 public:
	/*! \fn Accion (Tarea _t, Fase _f, SubFase _sf, unsigned _id)
	 *  \brief Constructor de la clase Acción.
	 *
	 *  \param _t Tarea correspondiente a la acción a construir.
	 *  \param _f Fase a la que pertenece la acción a construir.
	 *  \param _sf Subfase a la que pertenece la acción a construir.
	 *  \param _id Identificador usado por la clase responsable de dicha
	 *  acción para su manejo y control.
	 *
	 *  \note La clase acción es una clase abstracta.
	 *
	 *  \sa \c Fase
	 *  \sa \c Subfase
	 *  \sa \c Tarea
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
  Accion (Tarea _t, Fase _f, SubFase _sf, unsigned _id);

	/*! \fn virtual ~Accion()
	 *  \brief Destructor de la clase acción.
	 *
	 *  \note La clase acción no debe destruir ninguna otra clase
	 *  contenida en ella. Se implementa ya que es necesario tener un
	 *  destructor virtual si queremos destruir objetos heredados
	 *  apuntando a su clase base.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
  virtual ~Accion();

	/*! \fn Tarea T() const
	 *  \brief Devuelve la tarea correspondiente a la acción.
	 *
	 *  \sa \c Tarea
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
  Tarea T() const;

	/*! \fn Fase F() const
	 *  \brief Devuelve la fase a la que pertenece la acción.
	 *
	 *  \sa \c Fase
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
  Fase F() const;

	/*! \fn Fase SF() const
	 *  \brief Devuelve la subfase a la que pertenece la acción.
	 *
	 *  \sa \c Subfase
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
  SubFase SF() const;

	/*! \fn unsigned ID() const
	 *  \brief Devuelve el identificador de la acción.
	 *
	 *  Cada acción es gestionada por una clase. Este identificador
	 *  sirve para agilizar el trato de dicha clase para la acción. Por
	 *  ejemplo, para indexarla usando un autómata.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
  unsigned ID() const;

	/*! \fn virtual void Abstracta()
	 *  \brief Función que hace que la clase \c Accion sea abstracta.
	 *
	 *  \note Las clases heredadas no tienen que implementar esta
	 *  función con ningún comportamiento específico. Con implementarla
	 *  sin sentencias (void Abstracta() {}) ya hace que la clase deje
	 *  de ser abstracta.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
  virtual void Abstracta() = 0;

 private:
	/*! \var const Tarea t
	 *  \brief Tarea correspondiente a la acción.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
  const Tarea t;

	/*! \var const Fase f
	 *  \brief Fase correspondiente a la acción.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
  const Fase f;

	/*! \var const SubFase sf
	 *  \brief Subfase correspondiente a la acción.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
  const SubFase sf;

	/*! \var const unsigned id
	 *  \brief Identificador correspondiente a la acción.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
  const unsigned id;
};

#endif
