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

/*! \file GestorMovimiento.h
 *  \brief Fichero que define al gestor de movimiento.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#ifndef _GoM_GESTOR_MOVIMIENTO_
#define _GoM_GESTOR_MOVIMIENTO_

#include "GestorCombate.h"
#include <vector>

/*! \class GestorMovimiento
 *  \brief Clase de la fase de movimiento.
 *
 *  \sa GestorFase
 *  \sa GestorReglas
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class GestorMovimiento : public GestorFase
{
 public:
  /* Modificadoras. Inicialización. */
  void Inicializar (Estado& E);

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
  GestorMovimiento (GestorCombate *_gc, GestorEscenario *_ge);

  /* Destructor */
  ~GestorMovimiento();

 private:
  int estado;

  GestorCombate *gc;
	GestorEscenario *ge;
			
  vector<Carga> v;

  /* Modificadoras. Batalla. */
  void ResolverAccion (Estado& E, const Accion *a, const GestorEscenario& esc);

  void IncluirMovimientosCargas (Estado& E, const GestorEscenario& esc);
};

class acMovDeclaracionCargas : public Accion
{
 public:
  /* Funcion abstracta */
  void Abstracta() {}

  /* Clases amigas */
  friend class GestorMovimiento;

 private:
  /* Constructor */
 acMovDeclaracionCargas() : Accion (tmovDECLARACIONCARGAS, fMOVIMIENTO, sfNULO, 0) {}

  /* Destructor */
  ~acMovDeclaracionCargas() {}
};

class acMovDeclararCarga : public Accion
{
 public:
  /* Consultoras */
  Unidad* UnidadAtacante()	{	return (u);	}

  Unidad* UnidadAtacada()	{	return (v);	}

  /* Modificadoras */
  void DeclararCarga (Unidad *_u, Unidad *_v) {	u = _u;	v = _v;	}

  /* Funcion abstracta */
  void Abstracta() {}

  /* Clases amigas */
  friend class GestorMovimiento;

 private:
  Unidad *u, *v;

  /* Constructor */
 acMovDeclararCarga() : Accion (tmovDECLARARCARGA, fMOVIMIENTO, sfmovDECLARACIONCARGAS, 1), u(0), v(0) {}

  /* Destructor */
  ~acMovDeclararCarga() {}
};

class acMovMovimientoCargas : public Accion
{
 public:
  /* Funcion abstracta */
  void Abstracta() {}

  /* Clases amigas */
  friend class GestorMovimiento;

 private:
  /* Constructor */
 acMovMovimientoCargas() : Accion (tmovMOVIMIENTOCARGAS, fMOVIMIENTO, sfNULO, 2) {}

  /* Destructor */
  ~acMovMovimientoCargas() {}
};

class acMovCargar : public Accion
{
 public:
  /* Funcion abstracta */
  void Abstracta() {}

  /* Clases amigas */
  friend class GestorMovimiento;

 private:
  /* Constructor */
 acMovCargar() : Accion (tmovCARGAR, fMOVIMIENTO, sfmovMOVIMIENTOCARGAS, 3) {}

  /* Destructor */
  ~acMovCargar() {}
};

class acMovRestoMovimientos : public Accion
{
 public:
  /* Funcion abstracta */
  void Abstracta() {}

  /* Clases amigas */
  friend class GestorMovimiento;

 private:
  /* Constructor */
 acMovRestoMovimientos() : Accion (tmovRESTOMOVIMIENTOS, fMOVIMIENTO, sfNULO, 4) {}

  /* Destructor */
  ~acMovRestoMovimientos() {}
};

class acMovMarchar : public Accion
{
 public:
  /* Función abstracta */
  void Abstracta() {}

  /* Clases amigas */
  friend class GestorMovimiento;

 private:

  /* Constructores */
 acMovMarchar() : Accion (tmovMARCHAR, fMOVIMIENTO, sfmovRESTOMOVIMIENTOS, 5) { }

  /* Destructores */
  ~acMovMarchar() {}
};

class acMovMover : public Accion
{
 public:
  /* Consultoras */
  double D() const { return (d); }

  /* Modificadoras */
  void NuevaDistancia (double _d) { d = _d; }

  /* Funcion abstracta */
  void Abstracta() {}

  /* Clases amigas */
  friend class GestorMovimiento;

 private:
  double d;

  /* Constructores */
 acMovMover() : Accion (tmovMOVER, fMOVIMIENTO, sfmovRESTOMOVIMIENTOS, 6) { d = 0;	}

  /* Destructores */
  ~acMovMover() {}
};

class acMovPivotarIzq : public Accion
{
 public:
  /* Consultoras */
  double Ang() const { return (ang); }

  /* Modificadoras */
  void NuevoAng (double _ang) { ang = _ang; }

  /* Función abstracta */
  void Abstracta() {}

  /* Clases amigas */
  friend class GestorMovimiento;

 private:
  double ang;

  /* Constructores */
 acMovPivotarIzq() : Accion (tmovPIVOTARIZQ, fMOVIMIENTO, sfmovRESTOMOVIMIENTOS, 7) { ang = 0; }

  /* Destructores */
  ~acMovPivotarIzq() {}
};

class acMovPivotarDer : public Accion
{
 public:
  /* Consultoras */
  double Ang() const { return (ang); }

  /* Modificadoras */
  void NuevoAng (double _ang) { ang = _ang; }

  /* Función abstracta */
  void Abstracta() {}

  /* Clases amigas */
  friend class GestorMovimiento;

 private:
  double ang;

  /* Constructores */
 acMovPivotarDer() : Accion (tmovPIVOTARDER, fMOVIMIENTO, sfmovRESTOMOVIMIENTOS, 8) { ang = 0; }

  /* Destructores */
  ~acMovPivotarDer() {}
};

class acMovGirar : public Accion
{
 public:
  /* Función abstracta */
  void Abstracta() {}

  /* Clases amigas */
  friend class GestorMovimiento;

 private:
  /* Constructores */
 acMovGirar() : Accion (tmovGIRAR, fMOVIMIENTO, sfmovRESTOMOVIMIENTOS, 9) {}

  /* Destructores */
  ~acMovGirar() {}
};


#endif
