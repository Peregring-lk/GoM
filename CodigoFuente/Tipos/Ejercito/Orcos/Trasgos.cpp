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

#include "Trasgos.h"

using namespace std;

const Atrib Trasgos::a = { "Trasgos", 60, 3, 0, 3, 3, 1, 1, 2, 5, 1, 1,
													 0, 0, Punto(8, 8), 5 };

// Trasgos::Trasgos
/*************************************/
Trasgos::Trasgos (string dir, Orcos *h, double fw, double fh)
	: Unidad (Trasgos::a, dir, (Ejercito*)h, 20, 100, fw, fh, "Trasgos")
{}

// Trasgos::UnidadVirtual
/*************************************/
Unidad* Trasgos::UnidadVirtual ()
{
	Trasgos *l = new Trasgos(*this);

	l->vir = true;
	return (l);
}
