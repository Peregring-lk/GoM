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

/*! \file GestorFase.h
 *  \brief Fichero que implementa a la clase \c GestorFase.
 *
 *  Dado que todas las clases que se dedican a gestionar las fases reaccionan a partir
 *  de una acción recibida, y que cada acción es gestionada por una clase en concreto,
 *  y que existe un agente (\c GestorReglas) que se dedica a redirigir dicha acción
 *  correctamente, se hacen a todas estas clases heredadas de una clase común (la presente
 *  en este fichero) y así se le puede dar un comportamiento
 *  polimórfico a este hecho.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#ifndef _GoM_GESTOR_FASE_
#define _GoM_GESTOR_FASE_

#include <iostream>
#include "../../Tipos.h"

using namespace std;

/*! \class GestorFase
 *  \brief Clase base de todos los gestores de las distintas fases del
 *  juego.
 *
 *  La función principal de esta clase es \c EjercutarAccion. Sin
 *  esta, no tendría sentido la construcción de esta clase ni el
 *  comportamiento polimórfico que se le desea dar a la gestión de las
 *  acciones. Cada gestor de fase concreto gestiona una serie de
 *  acciones que le son propias y solo sabe como manejarlas él. El
 *  gestor de reglas contiene un puntero de tipo puntero a \c
 *  GestorFase, que, según el estado de la partida actual,
 *  apuntará al gestor correspondiente, y le pasará automáticamente
 *  cualquier acción recibida que el propio \c GestorFase no pueda
 *  manejar, mediante la función "polimórfica" \c EjecutarAccion.
 *
 *  Además se incluye la función \c Inicializar, también para darle un
 *  uso polimórfico, que continúa y completa el propósito de la función
 *  del mismo nombre de la clase \c GestorReglas.
 *
 *  \sa GestorMovimiento
 *  \sa GestorCombate
 *  \sa GestorDisparo
 *  \sa GestorInterfaz
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class GestorFase
{
 public:
  /* Constructores */
  GestorFase (Fase _f) : f(_f), turno(false) {}

  /* Destructores */
  virtual ~GestorFase()	{}

  /* Modificadoras */
  virtual void Destruir (Estado& E) = 0;

  virtual void Inicializar (Estado& E) = 0;

  virtual void IniciarFase (Estado& E)
  {
    E.NuevaFase (f);
    turno = true;
  }

  virtual void EjecutarAccion (Estado& E, const Accion *a, const GestorEscenario& esc) = 0;

  virtual void FinalizarFase (Estado& E)
  {
    E.NuevaFase (fNULO);
    E.NuevaSubFase (sfNULO);
    turno = false;
  }

 private:
  const Fase f;
  bool turno;
};

#endif
