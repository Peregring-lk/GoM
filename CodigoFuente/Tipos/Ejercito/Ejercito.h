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

/*! \file Ejercito.h
 *  \brief Fichero que define a la clase \c Ejercito.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#ifndef _EJERCITO_
#define _EJERCITO_

#include <vector>
#include <string>
#include "Unidad.h"
#include "../Clases.h"
#include "../Excepciones.h"

/*! \class Ejercito
 *  \brief Clase ejército.
 *
 *  \sa Unidad
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class Ejercito
{
 public:
	/* Constructor */
	Ejercito(std::string nomEjercito, Ejer ejer = eNULO);

  /* Destructor */
  virtual ~Ejercito();

  /* Consultoras. */
	Ejer eEjercito() const;

	std::string NombreEjercito() const;

  unsigned nUnidades() const;

  Unidad* operator[] (unsigned n) const;
  // Devuelve la n-ésima unidad del ejército.

  Unidad* operator<< (const Punto& p) const;

	unsigned Puntos() const;

  /* Modificadoras */
	void Inicializar();

  void Reiniciar();

  virtual Unidad* NuevaUnidad (std::string nombre, double fw, double fh) = 0;

  void EliminarUnidad(unsigned n);

 protected:
  /* Modificadoras */
  void NuevaUnidad (Unidad *u);

 private:
	std::string nomEjercito;
	Ejer e;       // Ejercito primero o segundo.

  std::vector<Unidad*> unidades;
};

#endif
