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

/*! \file GoM.cpp
 *  \brief Implementación de la clase principal del juego.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#include <iostream>
#include <fstream>
#include <string>
#include "GoM.h"

using namespace std;

// Juego::LanzarGoM
/*************************************/
void Juego::LanzarGoM()
{
	srand (time(0));

  GestorInterfaz i;

  while (1)
    switch(i.Menu())
      {
      case 0:
				Ejercito *e, *f, *gaia;

				i.ElegirEjercitos(&e, &f);

				if (e && f)
					{
						gaia = new GAIA(eGAIA);

						GestorReglas r(e, f, gaia);

						// Inicializa el gestor de reglas y de interfaz.
						r.Inicializar();
						i.Inicializar(r.EstadoBatalla());

						r.ComenzarBatalla();

						// Bucle principal del juego. 'r' (reglas) ejecuta las acciones indicadas por 'i' (interfaz).
						while (r.EjecutarAccion (i.NuevoEvento(r.EstadoBatalla(), r.Escenario())));

						i.ResultadoCombate(r.EstadoBatalla(), r.ResultadoCombate());
					}

				break;
      case 1:
				i.NuevoEjercito();
				break;
      case 2:
				i.EditarEjercito();
				break;
      case 3:
				return;
      default:
				break;
      }
}
