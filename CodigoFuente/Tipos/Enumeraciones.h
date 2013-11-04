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

/*! \file Enumeraciones.h
 *  \brief Clase que implementa una serie de enumeraciones necesarias
 *  en el transcurso del juego.
 *
 *  \note Este fichero debe usarse para realizar declaraciones
 *  adelantadas para clases conflictivas.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#ifndef _GoM_ENUMERACIONES_
#define _GoM_ENUMERACIONES_

/*! \enum Ejer
 *  \brief Enumeración de los ejércitos en una partida.
 *
 *  En una partida existen tres ejércitos: los dos ejércitos
 *  combatientes y el ejército GAIA. \c ePRIM y \c eSEG identifican a
 *  los ejércitos combatientes, eGAIA al ejército GAIA y eNULO como
 *  valor nulo de la enumeración.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
enum Ejer { ePRIM, eSEG, eGAIA, eNULO };

/*! \enum Ejer
 *  \brief Enumeración de los tipos de victoria.
 *
 *  El resultado de la partida puede ser de cuatro tipos:
 *  \li Empate
 *  \li Victoria marginal
 *  \li Victoria decisiva
 *  \li Masacre
 *
 *  Cada uno de estos tipos de victoria tiene su correspondiente valor
 *  en la enumeración.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
enum Victoria { Empate, VictoriaMarginal, VictoriaDecisiva, Masacre };

/*! \enum Fase
 *  \brief Enumeración de las distintas fases del juego.
 *
 *  Existen tres fases de juego:
 *  \li Fase de movimiento
 *  \li Fase de combate
 *  \li Fase de disparo
 *
 *  Cada una de estos fases tiene su correspondiente valor
 *  en la enumeración.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
enum Fase { fMOVIMIENTO, fCOMBATE, fDISPARO, fNULO };

/*! \enum SubFase
 *  \brief Enumeración de las distintas subfases del juego.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
enum SubFase { sfmovDECLARACIONCARGAS, sfmovMOVIMIENTOCARGAS,
							 sfmovRESTOMOVIMIENTOS, sfcomRESOLUCIONCOMBATES,
							 sfcomEFECTOCOMBATES, sfNULO };

/*! \enum Tarea
 *  \brief Enumeración de las distintas tareas del juego.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
enum Tarea { tMOVIMIENTO = 0, tmovDECLARACIONCARGAS, tmovDECLARARCARGA,
						 tmovMOVIMIENTOCARGAS, tmovCARGAR, tmovRESTOMOVIMIENTOS,
						 tmovMARCHAR, tmovMOVER, tmovPIVOTARIZQ, tmovPIVOTARDER,
						 tmovGIRAR, tCOMBATE, tcomRESOLUCIONCOMBATES,
						 tcomSIGCOMBATE, tcomHUIDAS, tcomSIGHUIDA, tDISPARO, tdisDISPARAR, 
						 tTURNO, tELEGIRUNIDAD, tFINALIZARBATALLA, tNULO };

/*! \enum Dir
 *  \brief Enumeración de las distintas direcciones de una unidad.
 *
 *  Estas direcciones son usadas para indicar a qué flanco de una
 *  unidad enemiga me dirigo, aunque también pueden servir para
 *  hacer referencia a un flanco de la propia unidad.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
enum Dir { FRE, DER, RET, IZQ };

/*! \var nTareas
 *  \brief Número de tareas en el juego.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
const unsigned nTareas = tNULO + 1;

#endif
