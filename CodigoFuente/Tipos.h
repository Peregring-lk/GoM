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
    de la licencia como para cualquier versión posterior (según su elección).

    GoM se distribuye con la esperanza de ser útil, pero SIN NINGUNA
    GARANTÍA, incluso sin garantía MERCANTIL implícita o CONVENIENCIA
    PARA UN PROPÓSITO PARTICULAR. Vea la GNU General Public License
    para más detalles.

    Debió recibir una copia de la GNU General Public License
    junto a GoM. Si no es así, visite <http://www.gnu.org/licenses/>.

*/

/*! \file Tipos.h
 *  \brief Fichero que agrupa a todos los tipos auxiliares.
 *
 *  Estos tipos auxiliares son:
 *  \li Clase \c Estado
 *  \li Clase \c Accion
 *  \li Clase \c GestorEscenarios
 *  \li Clase \c Ejercito
 *  \li Clase \c Unidad
 *  \li Cada una de las clases de ejército (\c Humanos, \c Orcos y \c
 *  GAIA) del juego.
 *  \li Cada una de las clases de unidades de cada ejército del
 *  juego.
 *
 *  \note Los ficheros se incluyen recursivamente. Por ejemplo, el
 *  fichero \c GestorEscenario.h incluye a \c Estado.h.
 *
 *  \note Este fichero ahorra incluir repetidas veces y uno a uno
 *  todos los ficheros de las clases usadas mas recurrentemente.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#ifndef _GoM_TIPOS_
#define _GoM_TIPOS_

#include "Tipos/GestorEscenario.h"
#include "Tipos/Ejercito/Humanos/Humanos.h"
#include "Tipos/Ejercito/Orcos/Orcos.h"
#include "Tipos/Ejercito/GAIA/GAIA.h"

#endif
