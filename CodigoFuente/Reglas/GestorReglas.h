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

/*! \file GestorReglas.h
 *  \brief Fichero que define la clase \c GestorReglas y las acciones que caen
 *         bajo su directa responsibilidad.
 *
 *  El gestor de reglas es la entidad encargada de gestionar todas las tareas en el transcurso de
 *  la partida. Se encarga principalmente de permitir toda la jugabilidad dada por el reglamento
 *  de \c GoM. Éste fichero define es la clase principal del gestor de reglas.
 *
 *  También define las acciones asociadas a las tareas que caen bajo la directa responsabilidad de
 *  \c GestorReglas. Éstas acciones son:
 *         \li \c acTurno
 *         \li \c acMovimiento
 *         \li \c acCombate
 *         \li \c acDisparo
 *         \li \c acElegirUnidad
 *         \li \c acFinalizarBatalla
 *         \li \c acNulo
 *
 *  \sa \c Accion
 *  \sa \c GestorMovimiento
 *  \sa \c GestorCombate
 *  \sa \c GestorDisparo
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */

#ifndef _GoM_GESTOR_REGLAS_
#define _GoM_GESTOR_REGLAS_

#include "GestorFases/GestorMovimiento.h"
#include "GestorFases/GestorDisparo.h"

/*! \class GestorReglas
 *  \brief Clase principal del gestor de reglas.
 *
 *  Esta clase es la clase principal del gestor de reglas. Se encarga principalmente de gestionar
 *  las tareas recibidas de corte más general, y de transmitir otro tipo de tareas a otros
 *  gestores más concretos (movimiento o combate).
 *
 *  Las tareas que son responsabilidad directa de \c GestorReglas son:
 *         \li \c tTURNO
 *         \li \c tMOVIMIENTO
 *         \li \c tCOMBATE
 *         \li \c tDISPARO
 *         \li \c tELEGIRUNIDAD
 *         \li \c tFINALIZARBATALLA
 *         \li \c tNULO
 *
 *  El gestor de reglas, despues de la construcción de todas sus clases y antes de comenzar la batalla,
 *  debe pasar por un proceso de inicialización que coordina adecuadamente todas las clases, y configura
 *  un estado previo adecuado para comenzar la batalla.
 *
 *  \sa \c Accion
 *  \sa \c Tarea
 *  \sa \c Estado
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class GestorReglas
{
 public:
  /*! \fn GestorReglas (Ejercito *e, Ejercito *f, Ejercito *gaia)
	 *
   *  \brief Contructor de \c GestorReglas.
   *
   *  \param e Puntero al primer ejército.
   *  \param f Puntero al segundo ejército.
	 *  \param gaia Puntero al ejército GAIA.
   *
   *  \pre \c e, \c f y \c gaia son punteros a ejércitos válidos (construidos).
   *  \post Construye al \c GestorReglas para desenvolverse en una batalla cuyos ejércitos
   *        son \c *e y \c *f respectivamente.
   *
   *  \note Hay que distinguir entre el gestor de reglas y \c GestorReglas. El primero es el conjunto de
   *        todas las clases involucradas en la gestión de reglas. El segundo es, en concreto, esta clase.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	GestorReglas (Ejercito *e, Ejercito *f, Ejercito *gaia);

  /*! \fn ~GestorReglas()
   *  \brief Destructor de \c GestorReglas.
   *
   *  \post Destruye a \c GestorReglas, destruyendo sucesivamente todos los tipos involucrados
   *        hasta destruir definitivamente todo el gestor de reglas.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	~GestorReglas();

  /*! \fn const Estado& EstadoBatalla() const
   *  \brief Destructor de \c GestorReglas.
   *
   *  \post Devuelve el estado actual de la batalla.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	const Estado& EstadoBatalla() const;

  /*! \fn const GestorEscenario& Escenario() const
   *  \brief Gestor del escenario.
   *
   *  \return Devuelve una referencia al gestor de escenarios vigente.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	const GestorEscenario& Escenario() const;

	Resultado ResultadoCombate();

  /* Modificadoras */
	void Inicializar();

	void ComenzarBatalla();

	bool EjecutarAccion (const Accion *a);

 private:
	Estado E;
	unsigned estado;

	GestorFase *pf;
	GestorMovimiento *gMov;
	GestorCombate *gCom;
	GestorDisparo *gDis;
	GestorEscenario *esc;

  /* Funciones privadas */
	void EjecutarAFD (unsigned id);

	void HuidaInicial();
};

// Accion de la tarea tTURNO
class acTurno : public Accion
{
 public:
  /* Función abstracta */
	void Abstracta() {}

  /* Clases amigas */
	friend class GestorReglas;

 private:
  /* Constructores */
 acTurno() : Accion (tTURNO, fNULO, sfNULO, 0) {}

  /* Destructores */
	~acTurno() {}
};

// Accion de la tarea tMOVIMIENTO
class acMovimiento : public Accion
{
 public:
  /* Función abstracta */
	void Abstracta() {}

  /* Clases amigas */
	friend class GestorReglas;

 private:
  /* Constructores */
 acMovimiento() : Accion (tMOVIMIENTO, fNULO, sfNULO, 1) {}

  /* Destructores */
	~acMovimiento() {}
};

// Accion de la tarea tCOMBATE
class acCombate : public Accion
{
 public:
  /* Función abstracta */
	void Abstracta() {}

  /* Clases amigas */
	friend class GestorReglas;

 private:
  /* Constructores */
 acCombate() : Accion (tCOMBATE, fNULO, sfNULO, 2) {}

  /* Destructores */
	~acCombate() {}
};

// Accion de la tarea tDISPARO
class acDisparo : public Accion
{
 public:
  /* Función abstracta */
	void Abstracta() {}

  /* Clases amigas */
	friend class GestorReglas;

 private:
  /* Constructores */
 acDisparo() : Accion (tDISPARO, fNULO, sfNULO, 3) {}

  /* Destructores */
	~acDisparo() {}
};

// Accion de la tarea tELEGIRUNIDAD
class acElegirUnidad : public Accion
{
 public:
  /* Consultoras */
	Unidad* uActual() const { return (u); }

  /* Modificadoras */
	void NuevaUnidad (Unidad *_u) { u = _u; }

  /* Función abstracta */
	void Abstracta() {}

  /* Clases amigas */
	friend class GestorReglas;

 private:
	Unidad *u;

  /* Constructores */
 acElegirUnidad() : Accion (tELEGIRUNIDAD, fNULO, sfNULO, 4) { u = 0; }

  /* Destructores */
	~acElegirUnidad() {}
};

// Accion de la tarea tFINALIZARBATALLA
class acFinalizarBatalla : public Accion
{
 public:
  /* Función abstracta */
	void Abstracta() {}

  /* Clases amigas */
	friend class GestorReglas;

 private:
  /* Constructores */
 acFinalizarBatalla() : Accion (tFINALIZARBATALLA, fNULO, sfNULO, 5) {}

  /* Destructores */
	~acFinalizarBatalla() {}
};

// Accion de la tarea tNULO
class acNulo : public Accion
{
 public:
  /* Función abstracta */
	void Abstracta() {}

  /* Clases amigas */
	friend class GestorReglas;

 private:
  /* Constructores */
 acNulo() : Accion (tNULO, fNULO, sfNULO, 6) {}

  /* Destructores */
	~acNulo() {}
};

#endif

/*!
 * \class GestorReglas
 * \brief Principal gestor del control de las reglas del juego.
 *
 * Esta clase implementa el control más general de las fases del juego. Controla el buen
 * transcurso de la partida a nivel de fases, hace la gestión de las tareas generales
 * (las que no pertenecen a ninguna clase), redirige las tareas más concretar a su gestor
 * correspondiente, y asegura que no se sobrepase el número de turnos del juego.
 *
 * Debido a que hay ciertos tipos y valores que no pueden crearse completamente en el
 * constructor del gestor, este gestor no podrá realizar función alguna hasta que no se
 * haya inicializado usando la función propuesta para elo, para asegurar un correcto
 * funcionamiento de la gestión de reglas. En caso de intentar invocar a alguna función
 * sin haberse inicializado usando la función propuesta para ello, dicha función
 * no realizará operación ninguna.
 */

/*!
 * \fn GestorReglas()
 * \brief Constructor de la clase.
 *
 * Manda la orden para que recursivamente se inicialicen todos los gestores dedicados
 * al control de reglas. Marca como no inicializada a la función. Para inicializarla hay
 * que invocar a la función \c GoM_Inicializar ().
 *
 * \sa
 * const GoM_pAcciones& GoM_GestorReglas::GoM_Inicializar()
 */
