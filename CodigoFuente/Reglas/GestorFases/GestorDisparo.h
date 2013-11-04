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

/*! \file GestorDisparo.h
 *  \brief Fichero que define al gestor de disparo.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#ifndef _GoM_GESTOR_DISPARO_
#define _GoM_GESTOR_DISPARO_

#include "GestorFase.h"

/*! \class GestorDisparo
 *  \brief Clase de la fase de disparo.
 *
 *  \sa GestorFase
 *  \sa GestorReglas
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class GestorDisparo : public GestorFase
{
 public:
  /* Modificadoras. Inicialización. */
  void Inicializar(Estado& E);

  /* Modificadoras. Batalla. */
  void IniciarFase (Estado& E);

  void EjecutarAccion (Estado& E, const Accion *a, const GestorEscenario& esc);

  void FinalizarFase (Estado& E);

  /* Modificadoras. Destrucción. */
  void Destruir (Estado& E);

  /* Clases amigas */
  friend class GestorReglas;

 protected:
  /* Constructor */
  GestorDisparo();

  /* Destructor */
  ~GestorDisparo();
};

class acDisDisparar : public Accion
{
 public:
	/* Consultoras */
  Unidad* UnidadAtacante()	{	return (u);	}

  Unidad* UnidadAtacada()	{	return (v);	}

	/* Modificadoras */
  void DeclararDisparo (Unidad *_u, Unidad *_v) {	u = _u;	v = _v;	}

  /* Funcion abstracta */
  void Abstracta() {}

  /* Clases amigas */
  friend class GestorDisparo;

 private:
  Unidad *u, *v;

  /* Constructor */
 acDisDisparar() : Accion (tdisDISPARAR, fDISPARO, sfNULO, 0),
		u(NULL), v(NULL) {}

  /* Destructor */
  ~acDisDisparar() {}
};

#endif
