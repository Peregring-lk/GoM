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

/*! \file Ejercito.cpp
 *  \brief Fichero que implementa a la clase \c Ejercito.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#include <vector>
#include "Ejercito.h"
#include "Unidad.h"

using namespace std;

// Ejercito::Ejercito
/*************************************/
Ejercito::Ejercito(string nomEjercito, Ejer e) : nomEjercito(nomEjercito), e(e)
{}

// Ejercito::~Ejercito
/*************************************/
Ejercito::~Ejercito()
{
	for (unsigned i = unidades.size (); i--; )
		delete (unidades[i]);                         // Liberamos todas y cada una de las unidades del ejército.		
}

// Ejercito::eEjercito
/*************************************/
Ejer Ejercito::eEjercito() const
{
	return (e);
}

// Ejercito::NombreEjercito
/*************************************/
string Ejercito::NombreEjercito() const
{
	return (nomEjercito);
}

// Ejercito::nUnidades
/*************************************/
unsigned Ejercito::nUnidades() const
{
	return (unidades.size());
}

// Ejercito::operator[]
/*************************************/
Unidad* Ejercito::operator[] (unsigned n) const
{
	if (n > unidades.size())
		return (NULL);

	return (unidades[n]);
}

// Ejercito::operator<<
/*************************************/
Unidad* Ejercito::operator<< (const Punto& p) const
{
	for (unsigned i = 0; i < unidades.size (); ++i)
		if (unidades[i]->Activo() && *unidades[i] << p)
			return (unidades[i]);

	return (0);
}

// Ejercito::Puntos
/**************************************/
unsigned Ejercito::Puntos() const
{
	unsigned puntos = 0;

	for (unsigned i = 0; i < unidades.size (); ++i)
		puntos += unidades[i]->Puntos();

	return (puntos);
}

// Ejercito::Inicializar
/**************************************/
void Ejercito::Inicializar()
{
	for (unsigned i = 0; i < unidades.size(); ++i)
		unidades[i]->Inicializar();
}

// Ejercito::Reiniciar
/**************************************/
void Ejercito::Reiniciar()
{
	for (unsigned i = 0; i < unidades.size (); ++i)
		unidades[i]->Reiniciar();
}

// Ejercito::NuevaUnidad
/*************************************/
void Ejercito::NuevaUnidad (Unidad *u)
{
	bool guardar = true;

	if (u->uEjercito() != this)
		guardar = false;

	for (unsigned i = 0; guardar && i < unidades.size(); ++i)
		if (u == unidades[i])
			guardar = false;

	if (guardar)
		unidades.push_back (u);
}

// Ejercito::EliminarUnidad
/*************************************/
void Ejercito::EliminarUnidad(unsigned n)
{
	delete unidades[n];

	unidades.erase(unidades.begin() + n);
}
