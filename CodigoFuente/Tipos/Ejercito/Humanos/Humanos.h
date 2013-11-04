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

/*! \file Humanos.h
 *  \brief Fichero que define a la clase \c Humanos.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#ifndef _GoM_HUMANOS_
#define _GoM_HUMANOS_

#include <string>
#include "../Ejercito.h"
#include "Legion.h"
#include "Arcabuceros.h"
#include "Ballesteros.h"
#include "Escuderos.h"
#include "Equites.h"
#include "Unicornios.h"
#include "Pegasos.h"
#include "Manticora.h"
#include "Dragon.h"

/*! \class Humanos
 *  \brief Clase humanos.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class Humanos : public Ejercito
{
 public:
  /* Constructor */
  Humanos(Ejer _e);

  /* Destructor */
  ~Humanos();

  /* Modificadoras */
  Unidad* NuevaUnidad (std::string nombre, double fw, double fh);

 private:
  Ejer e;
};

#endif
