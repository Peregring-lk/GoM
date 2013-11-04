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

/*! \file Humanos.cpp
 *  \brief Fichero que implementa a la clase \c Ejercito.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#include "Humanos.h"

using namespace std;

// Humanos::Humanos
/*************************************/
Humanos::Humanos (Ejer _e) : Ejercito("Humanos", _e), e(_e)
{}

// Humanos::~Humanos
/*************************************/
Humanos::~Humanos()
{}

// Humanos::NuevaUnidad
/*************************************/
Unidad* Humanos::NuevaUnidad (string nombre, double fw, double fh)
{
	bool guardar = true;
	string dir = "Imagenes/Peanas/Humanos/" + nombre;

	if (e == ePRIM)
		dir += "P";
	else if (e == eSEG)
		dir += "S";
	else
		guardar = false;

	dir += ".png";

	if (nombre == "Legión")
		Ejercito::NuevaUnidad (new Legion (dir.c_str(), this, fw, fh));
	else if (nombre == "Arcabuceros")
		Ejercito::NuevaUnidad (new Arcabuceros (dir.c_str(), this, fw, fh));
	else if (nombre == "Ballesteros")
		Ejercito::NuevaUnidad (new Ballesteros (dir.c_str(), this, fw, fh));
	else if (nombre == "Escuderos")
		Ejercito::NuevaUnidad (new Escuderos(dir.c_str(), this, fw, fh));
	else if (nombre == "Equites")
		Ejercito::NuevaUnidad (new Equites (dir.c_str(), this, fw, fh));
	else if (nombre == "Unicornios")
		Ejercito::NuevaUnidad (new Unicornios (dir.c_str(), this, fw, fh));
	else if (nombre == "Pegasos")
		Ejercito::NuevaUnidad (new Pegasos (dir.c_str(), this, fw, fh));
	else if (nombre == "Mantícora")
		Ejercito::NuevaUnidad (new Manticora (dir.c_str(), this, fw, fh));
	else if (nombre == "Dragón")
		Ejercito::NuevaUnidad (new Dragon (dir.c_str(), this, fw, fh));
	else
		guardar = false;

	if (guardar)
		return ((*this)[this->nUnidades() - 1]);
	else
		return (NULL);
}
