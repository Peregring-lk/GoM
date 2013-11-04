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

/*! \file Pegasos.cpp
 *  \brief Fichero que implementa a la clase \c Pegasos.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#include "Pegasos.h"

using namespace std;

const Atrib Pegasos::a = { "Pegasos", 200, 6, 0, 7, 5, 4, 2, 7, 8, 2, 7,
													0, 0, Punto(20, 20), 90 };

// Pegasos::Pegasos
/*************************************/
Pegasos::Pegasos (string dir, Humanos *h, double fw, double fh)
	: Unidad(Pegasos::a, dir, (Ejercito*)h, 3, 10, fw, fh, "Pegasos")
{}

// Pegasos::UnidadVirtual
/*************************************/
Unidad* Pegasos::UnidadVirtual()
{
	Pegasos *l = new Pegasos(*this);

	l->vir = true;
	return (l);
}
