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
 *  \brief Fichero que implementa al gestor de disparo.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#include "GestorDisparo.h"

using namespace std;

const unsigned AFD[4][4] = { {1, 3, 3, 3}, {3, 1, 2, 3}, {3, 3, 3, 2}, {3, 3, 3, 3} };

// GestorDisparo::GestorDisparo
/*************************************/
GestorDisparo::GestorDisparo() : GestorFase(fDISPARO)
{}

// GestorDisparo::Inicializar
/*************************************/
void GestorDisparo::Inicializar (Estado& E)
{
// Se añaden todas las acciones disponibles que sean responsabilidad del gestor de combate.
	E.NuevaAccion (new acDisDisparar());
}

// GestorDisparo::IniciarFase
/*************************************/
void GestorDisparo::IniciarFase (Estado& E)
{
	GestorFase::IniciarFase (E);

	// Se modifican las tareas disponibles.
	E.ModificarTarea (tDISPARO, true, false);
	E.ModificarTarea (tdisDISPARAR, true, true);
}

// GestorCombate::EjecutarAccion
/*************************************/
void GestorDisparo::EjecutarAccion(Estado& E, const Accion *a, const GestorEscenario& esc)
{
	if (a->T() == tdisDISPARAR)
		{
			Unidad *u = ((acDisDisparar*)a)->UnidadAtacante();
			Unidad *v = ((acDisDisparar*)a)->UnidadAtacada();

			unsigned Nv = v->N();

			if (u->Activo() && !u->Huyendo() && !u->Desmoralizado() && !u->Combatiendo())
				{
					const Atrib& a = u->Atributos();
					const Atrib& b = v->Atributos();

					for (unsigned i = 0; v->Activo() && i < u->N(); ++i)
						{
							unsigned hp = a.hp;
							unsigned fa = a.fa;

							float dist = esc.DistanciaUnidades(u, v, i);

							if (Mayor(a.aa, dist))
								{
									if (Mayor(dist, a.aa / 2.0))
										{
											hp -= 1;
											fa -= 1;
										}
									else if (Menor(dist, a.aa / 4.0))
										{
											hp += 1;
											fa += 1;
										}

									if (u->Marchando())
										hp -= 1;

									bool ac = false;

									if (esc.Chequeo(hp) && esc.Chequeo(fa, b.r))
										{
											if (fa > 4)
												ac = !esc.Chequeo (b.sa - (a.f - 5));
											else
												ac = !esc.Chequeo (b.sa);
										}

									if (ac)
										{
											v->ModificarHeridas(-1);

											if (!v->N())
												v->Eliminar();
										}
								}

							u->Disparar(true);
						}

					if (v->Activo() && (4 * v->N() < 3 * Nv))
						{
							/*
							 *  Le añadimos la bonificación mágica.
							 */
							unsigned prob = rand() % 4;
					
							if (prob > 1)
								prob -= 1;
					
							u->ModificarAtributo(rand() % 12, prob);

							if (!esc.Chequeo(v->Atributos().l))
								{
									E.IncluirUltimaTarea(tcomSIGHUIDA);

									v->Huir(true);

									vector<Unidad*> unidadDispara;

									unidadDispara.push_back(u);

									esc.Huida(E, v, &unidadDispara);
								}
						}
				}
		}
}

// GestorDisparo::FinalizarFase
/*************************************/
void GestorDisparo::FinalizarFase (Estado& E)
{
	GestorFase::FinalizarFase (E);

	E.ModificarTarea (tDISPARO, true, false);
	E.ModificarTarea (tdisDISPARAR, true, false);
}

// GestorDisparo::Destruir
/*************************************/
void GestorDisparo::Destruir (Estado& E)
{
	delete E.LeerAccion (tdisDISPARAR);
}
		
// GestorDisparto::~GestorDisparo
/*************************************/
GestorDisparo::~GestorDisparo()
{}
