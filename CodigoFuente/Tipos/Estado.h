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
    de la licencia como para cualquier versión posterior (según su
    elección).

    GoM se distribuye con la esperanza de ser útil, pero SIN NINGUNA
    GARANTÍA, incluso sin garantía MERCANTIL implícita o CONVENIENCIA
    PARA UN PROPÓSITO PARTICULAR. Vea la GNU General Public License
    para más detalles.

    Debió recibir una copia de la GNU General Public License
    junto a GoM. Si no es así, visite <http://www.gnu.org/licenses/>.

*/

/*! \file Estado.h
 *  \brief Fichero de definición de la clase \c Estado.
 *
 *  Es la clase encargada de hacer de mediadora entre todas las clases
 *  involucradas en el transcurso de una batalla. No contiene toda la
 *  información necesaria para especificar el estado de una batalla
 *  (hay cierta información que se guarda en otras clases de control
 *  de reglas), pero sí toda la necesaria para intercomunicar a las
 *  distintas clases relacionadas con el juego, tanto de interfaz como
 *  de reglas.
 *
 *  \sa GestorReglas
 *  \sa GestorInterfaz
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#ifndef _GoM_ESTADO_
#define _GoM_ESTADO_

#include <vector>
#include "Accion.h"
#include "Matematicas.h"
#include "Ejercito/Unidad.h"

struct Resultado
{
	Resultado ()
	{
		for (unsigned i = 0; i < 2; ++i)
			for (unsigned j = 0; j < 4; ++j)
				cuad[i][j] = 0;

		totalU[0] = totalU[1] = total = 0;
	}

	std::map<Unidad*, unsigned> puntos;
	int totalU[2];
	int cuad[2][4];
	int total;
	Victoria v;
};

/*! \class Estado
 *  \brief Clase estado.
 *
 *  El estado mantiene la siguiente información:
 *  \li Turno actual.
 *  \li Jugador en turno actual,
 *  \li Fase actual del jugador en turno.
 *  \li Subfase actual del jugador en turno.
 *  \li Tareas disponibles en el transcurso de la partida.
 *  \li Tareas disponibles actualmente.
 *  \li Tareas activas actualmente.
 *  \li Acciones necesarias para ejecutar las tareas del juego.
 *  \li Ejércitos involucrados.
 *  \li Unidad actual.
 *
 *  \sa GestorReglas
 *  \sa GestorInterfaz
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class Estado
{
 public:
	/*! \fn Estado (Ejercito *_pe, Ejercito *_pf, Ejercito *_gaia)
	 *  \brief Constructor de la clase Estado.
	 *
	 *  \param _pe Puntero al primer ejército.
	 *  \param _pf Puntero al segundo ejército.
	 *  \param _gaia Puntero al ejército GAIA.
	 *
	 *  \pre \c _pe, \c _pf y \c _gaia son punteros a ejércitos válidos
	 *  (construidos).
	 *
	 *  \post Crea el estado inicial del juego:
	 *    \li Turno actual sin especificar.
	 *    \li Jugador actual sin especificar.
	 *    \li Fase actual del jugador en turno sin especificar.
	 *    \li Subfase actual del jugador en turno sin especificar.
	 *    \li Tareas disponibles en el transcurso de la partida sin
	 *    especificadar.
	 *    \li Acciones necesarias para ejecutar las tareas disponibles
	 *    sin especificar.
	 *    \li Tareas disponibles actualmente sin especificar.
	 *    \li Ejércitos involucrados especificados.
	 *    \li Unidad actual sin especificar.
	 *
	 *  \sa Ejer
	 *  \sa Fase
	 *  \sa Subfase
	 *  \sa Tarea
	 *  \sa Acción
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	Estado (Ejercito *_pe, Ejercito *_pf, Ejercito *_gaia);

	/*! \fn Ejer enumEjer (Ejercito *_e) const
	 *  \brief Devuelve si un ejército es el primero o el segundo.
	 *
	 *  \param _e Ejército de referencia.
	 *
	 *  \return Si el ejercito apuntado por \c _e es uno de los que
	 *          configuran la batalla codificada por el \c Estado,
	 *          devuelve \c ePRIM si es el primero, y \c eSEG si es el
	 *          segundo ejército. Si el ejército apuntado por \c _e no
	 *          es válido o no se reconoce en la batalla actual,
	 *          devuelve \c eNULO.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	Ejer enumEjer (Ejercito *_e) const;

	/*! \fn Accion* LeerAccion (Tarea t) const
	 *  \brief Devuelve la acción asociada a una tarea.
	 *
	 *  \param t Tarea de referencia.
	 *
	 *  \pre El estado debe haber sido inicializado y la batalla debe
	 *  haber comenzado.
	 *
	 *  \return Si la tarea \c t es una tarea válida en la batalla
	 *          actual, devuelve un puntero a su acción
	 *          asociada. Devuelve \c NULL en caso contrario.
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c Inicializacion
	 *  \sa \c Batalla
	 *  \sa \c Accion
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	Accion* LeerAccion (Tarea t) const;

	/*! \fn bool Testear (Fase _f, SubFase _sf) const
	 *  \brief Comprueba la fase/subfase actual de juego.
	 *
	 *  \param _f Fase de referencia.
	 *  \param _sf Subfase de referencia.
	 *
	 *  \pre El estado debe haber sido inicializado y la batalla debe
	 *  haber comenzado.
	 *
	 *  \return Devuelve \c true si la fase actual es \c _f y si la
	 *          subfase actual es \c _sf. Devuelve \c false en caso
	 *          contrario.
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c Inicializacion
	 *  \sa \c Batalla
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	bool Testear (Fase _f, SubFase _sf) const;

	/*! \fn unsigned Turno() const
	 *  \brief Turno de juego actual.
	 *
	 *  \pre El estado debe haber sido inicializado y la batalla debe
	 *  haber comenzado.
	 *
	 *  \return Devuelve el número de turno actual.
	 *
	 *  \note El turno actual no distingue los turnos propios de cada
	 *        jugador, es decir, para el turno 3 del primer jugador, y
	 *        el turno 3 del segundo jugador, devolverá 3.
	 *
	 *  \note Un valor 0 significa que la batalla ha comenzado, pero no
	 *  se ha comenzado ningún turno.
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c Inicializacion
	 *  \sa \c Batalla
	 *  \sa \c EjercitoActual
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	unsigned Turno() const;

	/*! \fn Ejer EjercitoActual() const
	 *  \brief Jugador en curso.
	 *
	 *  \pre El estado debe haber sido inicializado y la batalla debe
	 *  haber comenzado.
	 *
	 *  \return Devuelve \c ePRIM si el jugador actual es el primero, y
	 *          \c eSEG si es el segundo. Si no hay ningun jugador
	 *          actual en curso devuelve \c eNULO.
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c Inicializacion
	 *  \sa \c Batalla
	 *  \sa \c Turno
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	Ejer EjercitoActual() const;

	/*! \fn Fase F() const
	 *  \brief Fase actual.
	 *
	 *  \pre El estado debe haber sido inicializado y la batalla debe
	 *  haber comenzado.
	 *
	 *  \return Devuelve la fase en curso del jugador actual. Si no hay
	 *          ninguna fase en curso devuelve \c fNULO.
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c Inicializacion
	 *  \sa \c Batalla
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	Fase F() const;

	/*! \fn SubFase SF() const
	 *  \brief Subfase actual.
	 *
	 *  \pre El estado debe haber sido inicializado y la batalla debe
	 *  haber comenzado.
	 *
	 *  \return Devuelve la subfase en curso del jugador actual. Si no
	 *          hay ninguna subfase en curso, devuelve \c sfNULO.
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c Inicializacion
	 *  \sa \c Batalla
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	SubFase SF() const;

	/*! \fn Unidad* UnidadActual() const
	 *  \brief Unidad actual.
	 *
	 *  \pre El estado debe haber sido inicializado y la batalla debe
	 *  haber comenzado.
	 *
	 *  \return Devuelve la unidad actual. Si no hay ninguna unidad
	 *  actual en curso devuelve \c NULL.
	 *
	 *  \note La unidad actual es aquella sobre la que se realizará la
	 *  siguiente tarea, si ésta es aplicable.
	 *
	 *  \note Para poder elegir una unidad actual, previamente hay que
	 *        indicarlo con la tarea \c tELEGIRUNIDAD a \c GestorReglas,
	 *        mediante su acción \c acElegirUnidad asociada.
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c Inicializacion
	 *  \sa \c Batalla
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	Unidad* UnidadActual() const;

	/*! \fn Ejercito* pEjer (Ejer _e) const
	 *  \brief Ejercito referido.
	 *
	 *  \param _e Referencia de ejército.
	 *
	 *  \pre El estado debe haber sido inicializado y la batalla debe
	 *  haber comenzado.
	 *
	 *  \return Devuelve el puntero al ejército que indique \c _e. Si \c
	 *  _e es \c eNULO, devolverá \c NULL.
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c Inicializacion
	 *  \sa \c Batalla
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	Ejercito* pEjer (Ejer _e) const;

	/*! \fn bool LeerTarea (Tarea t, bool tipo) const
	 *  \brief Disponibilidad actual o activación de una tarea.
	 *
	 *  \param t Tarea de referencia.
	 *  \param tipo Tipo de lectura.
	 *
	 *  \pre El estado debe haber sido inicializado y la batalla debe
	 *  haber comenzado.
	 *
	 *  \return Si \c tipo es \c true, la lectura será referida al
	 *  estado de activación de la tarea \c t. Si es \c false, será
	 *  referida a su disponibilidad. La función devolvera \c true o \c
	 *  false según esté o no \c t activo o disponible (dependiendo del
	 *  tipo de lectura).
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c Inicializacion
	 *  \sa \c Batalla
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	bool LeerTarea (Tarea t, bool tipo) const;

	/*! \fn Tarea UltimaTarea() const
	 *  \brief Última tarea ejecutada.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	Tarea UltimaTarea() const;

  /*! \fn void Inicializacion()
	 *  \brief Inicialización de la batalla.
	 *
	 *  \pre El estado debe haber sido creado, pero no inicializado.
	 *
	 *  \post Prepara al estado para comenzar la inicialización de la
	 *  batalla.
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c Batalla
	 *  \sa \c GestorReglas
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	void Inicializacion();

	/*! \fn void Batalla()
	 *  \brief Indicar al estado que la batalla ha comenzado.
	 *
	 *  \pre La batalla debe haber sido creada e inicializada, pero ésta
	 *       función no debe haber sido llamada ninguna vez.
	 *
	 *  \post Se establece el estado inicial de una batalla:
	 *        \li Turno actual 0 (indicador de despligue).
	 *        \li Jugador en turno sin especificar.
	 *        \li Fase actual del jugador en turno sin especificar.
	 *        \li Subfase actual del jugador en turno sin especificar.
	 *        \li Tareas disponibles en el transcurso de la partida
	 *        especificadas.
	 *        \li Acciones necesarias para ejecutar las tareas
	 *        disponibles especificadas.
	 *        \li Tareas disponibles actualmente especificadas (tareas
	 *        de estado inicial).
	 *        \li Ejércitos involucrados especificados.
	 *        \li Unidad actual sin especificar.
	 *
	 *  \note Una batalla creada e inicializada no solo involucra a la
	 *        creación e inicialización del estado, sino a la creación
	 *        he inicialización de todas las clases involucradas en la
	 *        gestión de reglas.
	 *
	 *  \note Las tareas y acciones no son especificadas por ésta
	 *        función, sino que han sido debidamente inicializadas
	 *        en el proceso de inicialización global del gestor de
	 *        reglas.
	 *
	 *  \note Aunque existan valores sin especificar, están controlados,
	 *        y puede acudirse a sus funciones lectoras
	 *        asociadas (se cumplicarán las precondiciones de cada una
	 *        de ellas). No se especifican porque no tiene
	 *        sentido especificarlas cuando ningún turno ha dado
	 *        comienzo.
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c Batalla
	 *  \sa \c GestorReglas
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	void Batalla();

	/*! \fn void NuevaAccion (Accion* ac)
	 *  \brief Incluye una nueva acción.
	 *
	 *  \param ac Puntero a la acción de referencia.
	 *
	 *  \pre El estado debe haber sido creado e inicializado, pero la
	 *  batalla no debe haber comenzado.
	 *
	 *  \post Incluye a la tarea asociada a la accion \c ac, como tarea
	 *  disponible para la batalla.
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c Batalla
	 *  \sa \c GestorReglas
	 *  \sa \c Accion
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	void NuevaAccion (Accion* ac);

	/*! \fn void NuevoTurno()
	 *  \brief Incrementa el turno.
	 *
	 *  \pre La batalla debe haber comenzado.
	 *
	 *  \post El estado se posiciona en el siguiente turno de juego.
	 *
	 *  \note El incremento de turno se hace indiscriminadamente
	 *        respecto al jugador actual, lo que provocaría que un mismo
	 *        jugador juege dos turnos consecutivos, si ésta función no
	 *        se usa conjuntamente a \c NuevoEjercito.
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *        responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c NuevoEjercito
	 *  \sa \c Batalla
	 *  \sa \c GestorReglas
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	void NuevoTurno();

	/*! \fn void NuevoEjercito (Ejer _e)
	 *  \brief Establece al ejército actual.
	 *
	 *  \param _e Ejercito de referencia.
	 *
	 *  \pre La batalla debe haber comenzado.
	 *
	 *  \post El estado se posiciona en el turno del jugador \c _e.
	 *
	 *  \note Se usa esta función en conjunción con \c NuevoTurno para
	 *        que cada jugador juege su turno en el orden
	 *        adecuado.
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *        responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c NuevoTurno
	 *  \sa \c Batalla
	 *  \sa \c GestorReglas
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	void NuevoEjercito (Ejer _e);

	/*! \fn void NuevaFase (Fase _f)
	 *  \brief Establece la fase actual
	 *
	 *  \pre La batalla debe haber comenzado.
	 *
	 *  \post El estado se posiciona en la fase \c _f, para el jugador y
	 *  turno actual.
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c NuevoTurno
	 *  \sa \c Batalla
	 *  \sa \c GestorReglas
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	void NuevaFase (Fase _f);

	/*! \fn void NuevaSubFase (SubFase _sf)
	 *  \brief Establece la fase actual
	 *
	 *  \param _sf Subfase de referencia.
	 *
	 *  \pre La batalla debe haber comenzado.
	 *
	 *  \post El estado se posiciona en la subfase \c _sf, para el
	 *  jugador y turno actual.
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c Batalla
	 *  \sa \c GestorReglas
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	void NuevaSubFase (SubFase _sf);

	/*! \fn void NuevaUnidadActual (Unidad *_u)
	 *  \brief Establece una nueva unidad actual.
	 *
	 *  \param _u Puntero a la unidad de referencia.
	 *
	 *  \pre La batalla debe haber comenzado.
	 *
	 *  \post \c _u pasará a ser la siguiente unidad sustenta a acciones
	 *  (si son aplicables).
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *  \sa \c Batalla
	 *  \sa \c GestorReglas
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	void NuevaUnidadActual (Unidad *_u);

	/*! \fn void IncluirUltimaTarea (Tarea t)
	 *  \brief Establece una nueva 'ultima tarea'.
	 *
	 *  \param t Última tarea ejecutada.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	void IncluirUltimaTarea (Tarea t);

	/*! \fn void ModificarTarea (Tarea t, bool tipo, bool valor)
	 *  \brief Modifica la disponibilidad o estado de activación de una
	 *  tarea.
	 *
	 *  \param t Tarea de referencia.
	 *  \param tipo Tipo de modificación.
	 *  \param valor Nueva disponibilidad.
	 *
	 *  \pre La batalla debe haber comenzado.
	 *
	 *  \post Si \c tipo es \c true, se modificará el estado de
	 *        activación de \c t. Si es \c false, su disponibilidad. El
	 *        nuevo estado de activación o disponibilidad será el
	 *        indicado por \c valor.
	 *
	 *  \note Si las precondiciones no se cumplen, la función no se
	 *  responsabiliza de las consecuencias de su ejecución.
	 *
	 *
	 *  \note Al modificar el estado de activación de una tarea,
	 *  siempre se modifica su disponibilidad; si se activa, por
	 *  defecto se pone disponible; y si se desactiva, se anula su
	 *  disponibilidad.
	 *
	 *  \sa \c Batalla
	 *  \sa \c GestorReglas
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	void ModificarTarea (Tarea t, bool tipo, bool valor);

 private:
	/*! \var unsigned turno
	 *  \brief Turno actual.
	 *
	 *  \note 0 indica despliegue.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	unsigned turno;

	/*! \var Ejer e
	 *  \brief Ejercito en curso.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	Ejer e;

	/*! \var Fase f
	 *  \brief Fase actual.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	Fase f;

	/*! \var SubFase sf
	 *  \brief Subfase actual.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	SubFase sf;

	/*! \var Unidad *u
	 *  \brief Puntero a la unidad actual.
	 *
	 *  \note Atributo mutable por si se detecta en una lectura (que es
	 *        una función constante) que una unidad ya no esté activa
	 *        (por ejemplo, que haya sido eliminada), para evitar
	 *        devolver una unidad actualmente no disponible. En tal caso
	 *        habría que eliminar la referencia, asignando al puntero un
	 *        valor \c NULL.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	mutable Unidad *u;

	/*! \var Ejercito *pe
	 *  \brief Puntero al primer ejército.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	Ejercito *pe;

	/*! \var Ejercito *pf
	 *  \brief Puntero al segundo ejército.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	Ejercito *pf;

	/*! \var Ejercito *gaia
	 *  \brief Puntero al ejército GAIA.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	Ejercito *gaia;

	/*! \var Accion* acciones[nTareas]
	 *  \brief Vector de acciones.
	 *
	 *  \c acciones[t] contiene la acción asociada a la tarea \c t. Si
	 *     la tarea \c t no es una tarea posible para la batalla actual,
	 *     \c acciones[t] será \c NULL.
	 *
	 *  \sa \c Accion
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	Accion* acciones[nTareas];

	/*! \var bool activacion[nTareas]
	 *  \brief Vector de activación de tareas.
	 *
	 *  \c activacion[t] contiene el estado de activacion actual de la
	 *  tarea \c t. Un valor \c true indica que está activo, y \c false,
	 *  paralelamente, que no lo está.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	bool activacion[nTareas];

	/*! \var bool disponibilidad[nTareas]
	 *  \brief Vector de disponibilidad de tareas.
	 *
	 *  \c disponibilidad[t] contiene la disponibilidad actual de la
	 *  tarea \c t. Un valor \c true indica disponibilidad actual, y \c
	 *  false, paralelamente, una no disponibilidad.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	bool disponibilidad[nTareas];

	/*! \var ultimaT
	 *  \brief Última tarea ejecutada.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2010
	 *  \version 1
	 *  \since 1
	 */
	Tarea ultimaT;
};

#endif
