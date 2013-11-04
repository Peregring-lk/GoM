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

/*! \file Equites.cpp
 *  \brief Fichero que implementa a la clase \c Equites.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#include "Equites.h"

using namespace std;

const Atrib Equites::a = { "Equites", 125, 5, 0, 6, 4, 3, 1, 7, 8, 2, 6,
													0, 0, Punto(10, 20), 65 };

// Equites::Equites
/*************************************/
Equites::Equites (string dir, Humanos *h, double fw, double fh)
	: Unidad(Equites::a, dir, (Ejercito*)h, 5, 20, fw, fh, "Equites")
{}

// Equites::UnidadVirtual
/*************************************/
Unidad* Equites::UnidadVirtual()
{
	Equites *l = new Equites(*this);

	l->vir = true;
	return (l);
}
