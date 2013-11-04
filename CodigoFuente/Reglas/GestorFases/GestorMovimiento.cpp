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

/*! \file GestorMovimiento.cpp
 *  \brief Fichero que implementa al gestor de movimiento.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#include <iostream>
#include "GestorMovimiento.h"

using namespace std;

const unsigned AFD[10][11] = { { 1, 7, 7, 7, 5, 7, 7, 7, 7, 7, 7 },
                               { 7, 2, 7, 7, 5, 7, 7, 7, 7, 7, 7 },
															 { 7, 2, 3, 7, 7, 7, 7, 7, 7, 7, 7 },
															 { 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7 },
															 { 7, 7, 7, 4, 5, 7, 7, 7, 7, 7, 7 },
															 { 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6 },
															 { 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6 },
															 { 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6 },
															 { 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6 },
															 { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 } };

// GestorMovimiento::GestorMovimiento
/*************************************/
GestorMovimiento::GestorMovimiento (GestorCombate *_gc, GestorEscenario *_ge)
	: GestorFase(fMOVIMIENTO), gc(_gc), ge(_ge)
{}

// GestorMovimiento::Inicializar
/*************************************/
void GestorMovimiento::Inicializar (Estado& E)
{
// Se añaden todas las acciones disponibles que sean responsabilidad del gestor de movimiento.
	E.NuevaAccion (new acMovDeclaracionCargas());
	E.NuevaAccion (new acMovDeclararCarga());
	E.NuevaAccion (new acMovMovimientoCargas());
	E.NuevaAccion (new acMovCargar());
	E.NuevaAccion (new acMovRestoMovimientos());
	E.NuevaAccion (new acMovMarchar());
	E.NuevaAccion (new acMovMover());
	E.NuevaAccion (new acMovPivotarIzq());
	E.NuevaAccion (new acMovPivotarDer());
	E.NuevaAccion (new acMovGirar());
}

// GestorMovimiento::IniciarFase
/*************************************/
void GestorMovimiento::IniciarFase (Estado& E)
{
	GestorFase::IniciarFase (E);

	estado = 0;

	// Se modifican las tareas disponibles.
	E.ModificarTarea (tMOVIMIENTO, true, false);
	E.ModificarTarea (tmovDECLARACIONCARGAS, true, true);
	E.ModificarTarea (tmovRESTOMOVIMIENTOS, true, true);
}

// GestorMovimiento::EjecutarAccion
/*************************************/
void GestorMovimiento::EjecutarAccion (Estado& E, const Accion *a, const GestorEscenario& esc)
{
 	estado = AFD[estado][a->ID()];

	switch (estado)
	{
		case 1:
			E.NuevaSubFase (sfmovDECLARACIONCARGAS);
			E.ModificarTarea (tmovDECLARACIONCARGAS, true, false);
			E.ModificarTarea (tmovDECLARARCARGA, true, true);
			break;
		case 3:
			E.NuevaSubFase (sfmovMOVIMIENTOCARGAS);
			E.ModificarTarea (tmovMOVIMIENTOCARGAS, true, false);
			E.ModificarTarea (tmovDECLARARCARGA, true, false);
			E.ModificarTarea (tmovCARGAR, true, true);
			break;
		case 5:
			E.NuevaSubFase (sfmovRESTOMOVIMIENTOS);
			E.ModificarTarea (tmovRESTOMOVIMIENTOS, true, false);
			E.ModificarTarea (tmovDECLARACIONCARGAS, true, false);
			E.ModificarTarea (tmovDECLARARCARGA, true, false);
			E.ModificarTarea (tmovCARGAR, true, false);
			E.ModificarTarea (tmovMARCHAR, true, true);
			E.ModificarTarea (tmovMOVER, true, true);
			E.ModificarTarea (tmovPIVOTARIZQ, true, true);
			E.ModificarTarea (tmovPIVOTARDER, true, true);
			E.ModificarTarea (tmovGIRAR, true, true);
			break;
		case 2:
		case 4:
		case 6:
			ResolverAccion (E, a, *ge);
		default:
			break;
}}

// GestorMovimiento::ResolverAccion
/*************************************/
void GestorMovimiento::ResolverAccion (Estado& E, const Accion *a, const GestorEscenario& esc)
{
	if (a->T() == tmovDECLARARCARGA)
	{
		Unidad *u = ((acMovDeclararCarga*)a)->UnidadAtacante();
		Unidad *w = ((acMovDeclararCarga*)a)->UnidadAtacada();

		if (u && w)
		{
			v.push_back (Carga (u, w));
			u->Cargar (true);
		}

		E.ModificarTarea (tmovMOVIMIENTOCARGAS, true, true);
		E.ModificarTarea (tTURNO, false, false);
		E.ModificarTarea (tmovRESTOMOVIMIENTOS, false, false);
		E.ModificarTarea (tCOMBATE, false, false);
		E.ModificarTarea (tDISPARO, false, false);
	}
	else if (a->T() == tmovCARGAR)
	{
		MovCarga m = esc.MovimientoCarga (E, v[0]);

		m.C.u->Trasladar(m.s);
		m.C.u->Cargar(false);

		if (m.efec)
			gc->NuevoCombate (E, m.C, esc);

		v.erase(v.begin());
		if (!v.size())
		{
			E.ModificarTarea (tmovCARGAR, true, false);
			E.ModificarTarea (tmovRESTOMOVIMIENTOS, false, true);

			if (gc->CombatesPendientes (E))
			{
				E.ModificarTarea (tCOMBATE, true, true);
				E.ModificarTarea (tDISPARO, false, false);
				E.ModificarTarea (tTURNO, false, false);
			}
			else
				{
					E.ModificarTarea (tTURNO, false, true);
					E.ModificarTarea (tDISPARO, false, true);
				}
		}
	}
	else if (a->T() == tmovMARCHAR)
	{
		Unidad *u = E.UnidadActual();

		if (u)
			u->Marchar(!u->Marchando());
	}
	else if (a->T() == tmovMOVER)
	{
		Unidad *u = E.UnidadActual();

		if (u && u->uEjercito() == E.pEjer (E.EjercitoActual()))
			u->Desplazar (((acMovMover*)a)->D());
	}
	else if (a->T() == tmovPIVOTARIZQ)
	{
		Unidad *u = E.UnidadActual();

		if (u && u->uEjercito() == E.pEjer (E.EjercitoActual()))
			u->PivotarIzq (((acMovPivotarIzq*)a)->Ang());
	}
	else if (a->T() == tmovPIVOTARDER)
	{
		Unidad *u = E.UnidadActual();

		if (u && u->uEjercito() == E.pEjer (E.EjercitoActual()))
			u->PivotarDer (((acMovPivotarDer*)a)->Ang());
	}
	else if (a->T() == tmovGIRAR)
	{
		Unidad *u = E.UnidadActual();

		if (u && u->uEjercito() == E.pEjer (E.EjercitoActual()))
			u->Girar();
	}
}

// GestorMovimiento::FinalizarFase
/*************************************/
void GestorMovimiento::FinalizarFase (Estado& E)
{
	GestorFase::FinalizarFase (E);

	E.ModificarTarea (tMOVIMIENTO, true, false);
	E.ModificarTarea (tmovDECLARACIONCARGAS, true, false);
	E.ModificarTarea (tmovDECLARARCARGA, true, false);
	E.ModificarTarea (tmovMOVIMIENTOCARGAS, true, false);
	E.ModificarTarea (tmovCARGAR, true, false);
	E.ModificarTarea (tmovRESTOMOVIMIENTOS, true, false);
	E.ModificarTarea (tmovMARCHAR, true, false);
	E.ModificarTarea (tmovMOVER, true, false);
	E.ModificarTarea (tmovPIVOTARIZQ, true, false);
	E.ModificarTarea (tmovPIVOTARDER, true, false);
	E.ModificarTarea (tmovGIRAR, true, false);
}

// GestorMovimiento::Destruir
/*************************************/
void GestorMovimiento::Destruir (Estado& E)
{
	delete E.LeerAccion (tmovDECLARACIONCARGAS);
	delete E.LeerAccion (tmovDECLARARCARGA);
	delete E.LeerAccion (tmovMOVIMIENTOCARGAS);
	delete E.LeerAccion (tmovCARGAR);
	delete E.LeerAccion (tmovRESTOMOVIMIENTOS);
	delete E.LeerAccion (tmovMOVER);
	delete E.LeerAccion (tmovPIVOTARIZQ);
	delete E.LeerAccion (tmovPIVOTARDER);
	delete E.LeerAccion (tmovGIRAR);
}

// GestorMovimiento::~GestorMovimiento
/*************************************/
GestorMovimiento::~GestorMovimiento()
{}
