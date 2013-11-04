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

/*! \file GestorReglas.cpp
 *  \brief Implementación del gestor de reglas.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#include <iostream>
#include "GestorReglas.h"

using namespace std;

const unsigned nTurnos = 6;
const unsigned AFD [10][4] = { {1, 9, 9, 9}, {2, 3, 5, 7}, {1, 4, 6, 8},
															 {2, 9, 5, 7}, {1, 9, 6, 8},
															 {2, 9, 9, 7}, {1, 9, 9, 8},
															 {2, 9, 9, 9}, {1, 9, 9, 9},
															 {9, 9, 9, 9} };

// GestorReglas::GestorReglas
/*************************************/
GestorReglas::GestorReglas (Ejercito *e, Ejercito *f, Ejercito *gaia)
	: E(e, f, gaia)
{
	gCom = new GestorCombate();
	esc = new GestorEscenario (Punto(1280, 600));
	gMov = new GestorMovimiento (gCom, esc);
	gDis = new GestorDisparo();

	/*
	 *  Invertimos las posiciones de despliegue del segundo ejército
	 *
	 *  *NOTA: El despliegue se define en la primera parte del campo,
	 pero el segundo ejército se despliega en la segunda (el
	 encaramiento gira 180 grados).
	*/
	for (unsigned i = 0; i < f->nUnidades(); ++i)
		{
			Unidad *u = (*f)[i];

			u->NuevaPO(Punto(1280, 600) - u->Psi(), AngGR(180));
		}
}

// GestorReglas::EstadoBatalla
/*************************************/
const Estado& GestorReglas::EstadoBatalla() const
{
	return (E);
}

// GestorReglas::Escenario
/*************************************/
const GestorEscenario& GestorReglas::Escenario() const
{
	return (*esc);
}

// GestorReglas::Inicializar
/*************************************/
void GestorReglas::Inicializar()
{
	E.Inicializacion();

	E.pEjer(ePRIM)->Inicializar();
	E.pEjer(eSEG)->Inicializar();

	// Se añaden todas las acciones responsabilidad del gestor de reglas.
	E.NuevaAccion (new acTurno());
	E.NuevaAccion (new acMovimiento());
	E.NuevaAccion (new acCombate());
	E.NuevaAccion (new acDisparo());
	E.NuevaAccion (new acElegirUnidad());
	E.NuevaAccion (new acFinalizarBatalla());
	E.NuevaAccion (new acNulo());

	// Para cada gestor de fase, se le envía la señal de inicialización.
	gMov->Inicializar(E);
	gCom->Inicializar(E);
	gDis->Inicializar(E);
}

// GestorReglas::ComenzarBatalla
/*************************************/
void GestorReglas::ComenzarBatalla()
{
	E.Batalla();

	// Se incluyen las tareas disponibles/activas iniciales.
	E.ModificarTarea (tTURNO, true, true);
	E.ModificarTarea (tELEGIRUNIDAD, true, true);
	E.ModificarTarea (tFINALIZARBATALLA, true, true);

	estado = 0;

	// pf es un puntero a la fase actual. Al comenzar, no apunta a ninguna.
	pf = 0;
}

// GestorReglas::EjecutarAccion
/*************************************/
bool GestorReglas::EjecutarAccion (const Accion *a)
{
	E.IncluirUltimaTarea(tNULO);

	// Aunque estemos dentro de una fase actual, siempre hay acciones que puede requerir el control del gestor de reglas.
	if (a->F() == fNULO)
		{
			if (a->T() == tELEGIRUNIDAD)
				E.NuevaUnidadActual (((acElegirUnidad*)a)->uActual());
			else if (a->T() == tFINALIZARBATALLA)
				return (false);
			else if (a->T() != tNULO)
				EjecutarAFD (a->ID());
		}
	// Para cualquier acción de una fase concreta, se le da el control a su dueño.
	else if (pf != 0)
		pf->EjecutarAccion (E, a, *esc);

	// Fin de partida.
	if (E.Turno() > nTurnos)
		return (false);

	return (true);
}

// GestorReglas::ResultadoCombate
/*************************************/
Resultado GestorReglas::ResultadoCombate()
{
	return (esc->ResultadoCombate(E));
}

// GestorReglas::~GestorReglas
/*************************************/
GestorReglas::~GestorReglas()
{
	delete E.LeerAccion (tTURNO);
	delete E.LeerAccion (tMOVIMIENTO);
	delete E.LeerAccion (tCOMBATE);
	delete E.LeerAccion (tDISPARO);
	delete E.LeerAccion (tELEGIRUNIDAD);
	delete E.LeerAccion (tFINALIZARBATALLA);
	delete E.LeerAccion (tNULO);

	delete gMov;
	delete gCom;
	delete esc;
	delete gDis;
}

// GestorReglas::EjecutarAFD
/*************************************/
void GestorReglas::EjecutarAFD (unsigned id)
{
	// Autómata de estado más general.
	estado = AFD[estado][id];

	switch (estado)
		{
		case 1:
			E.NuevoEjercito (ePRIM);
			E.NuevoTurno();
			E.pEjer(ePRIM)->Reiniciar();
			E.pEjer(eSEG)->Reiniciar();
			if (pf)
				{
					pf->FinalizarFase (E);
					pf = 0;
				}
			E.ModificarTarea (tMOVIMIENTO, true, true);
			E.ModificarTarea (tDISPARO, true, true);
			if (gCom->CombatesPendientes(E))
				{
					E.ModificarTarea (tCOMBATE, true, true);
					E.ModificarTarea (tTURNO, false, false);
					E.ModificarTarea (tDISPARO, false, false);
				}

			HuidaInicial();

			break;
		case 2:
			E.NuevoEjercito (eSEG);
			E.pEjer(ePRIM)->Reiniciar();
			E.pEjer(eSEG)->Reiniciar();
			if (pf)
				{
					pf->FinalizarFase (E);
					pf = 0;
				}
			E.ModificarTarea (tMOVIMIENTO, true, true);
			E.ModificarTarea (tDISPARO, true, true);
			if (gCom->CombatesPendientes(E))
				{
					E.ModificarTarea (tCOMBATE, true, true);
					E.ModificarTarea (tTURNO, false, false);
					E.ModificarTarea (tDISPARO, false, false);
				}

			HuidaInicial();

			break;
		case 3:
		case 4:
			if (pf)
				pf->FinalizarFase (E);
			pf = gMov;
			pf->IniciarFase (E);
			break;
		case 5:
		case 6:
			if (pf)
				pf->FinalizarFase (E);

			pf = gCom;
			pf->IniciarFase (E);
			E.ModificarTarea (tMOVIMIENTO, true, false);
			break;
		case 7:
		case 8:
			if (pf)
				pf->FinalizarFase (E);

			pf = gDis;
			pf->IniciarFase(E);
			E.ModificarTarea(tMOVIMIENTO, true, false);
			E.ModificarTarea(tCOMBATE, true, false);
			break;
		default:
			break;
		}
}

// GestorReglas::HuidaInicial
/*************************************/
void GestorReglas::HuidaInicial()
{
	/*
	 *  Añadimos el control de huida de principio de turno.
	 */
	const Ejercito *e = E.pEjer (E.EjercitoActual());

	for (unsigned j = 0; j < e->nUnidades(); ++j)
		{
			Unidad *v = (*e)[j];

			if (v->Huyendo())
				{
					bool reagrupar = esc->Chequeo(v->Atributos().l);

					if (reagrupar && v->P() > 4)
						v->Huir(false);
					else
						{
							E.IncluirUltimaTarea(tcomSIGHUIDA);
							esc->Huida(E, v); 
						}
				}
		}
}
