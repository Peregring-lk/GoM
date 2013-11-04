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

/*! \file GestorCombate.cpp
 *  \brief Fichero que implementa al gestor de combate.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#include <algorithm>
#include "GestorMovimiento.h"

using namespace std;

const unsigned AFD[4][4] = { {1, 3, 3, 3}, {3, 1, 2, 3}, {3, 3, 3, 2}, {3, 3, 3, 3} };

// GoM::AtPendientes
/*************************************/
unsigned AtPendientes (EfPendientes *efP, Unidad *u, unsigned ef)
{
	if (efP && u)
		return ((*efP)[u].v[ef].n);
	else
		return (0);
}

// GoM::AsignarAt
/*************************************/
void AsignarAt (EfPendientes *efP, Unidad *u, unsigned ef, Unidad *v, unsigned n)
{
	if (efP && u && v)
	{
		unsigned aux = (*efP)[u].v[ef].n;

		if (aux)
		{
			aux = (unsigned)Min(n, aux);

			(*efP)[u].nTotal -= aux;
			(*efP)[u].v[ef].v[v] += aux;
			(*efP)[u].v[ef].n -= aux;
		}
	}
}

// GestorCombate::GestorCombate
/*************************************/
GestorCombate::GestorCombate() : GestorFase(fCOMBATE)
{}

// GestorCombate::Inicializar
/*************************************/
void GestorCombate::Inicializar (Estado& E)
{
// Se añaden todas las acciones disponibles que sean responsabilidad del gestor de combate.
	E.NuevaAccion (new acComResolucionCombates());
	E.NuevaAccion (new acComSigCombate());
	E.NuevaAccion (new acComEfectoCombates());
	E.NuevaAccion (new acComSigEfectoCombate());
}

// GestorCombate::NuevoCombate
/*************************************/
void GestorCombate::NuevoCombate (Estado& E, Carga c, const GestorEscenario& esc)
{
	if (c.v->Huyendo())
		c.v->Eliminar();
	else
		{
			c.u->Combatir(true, true);
			c.v->Combatir(true, false);

			int i = combates.size();

			while (i-- && combates[i].unids.find(c.v) == combates[i].unids.end());

			if (i == -1)
				{
					combates.push_back(Combate());
					i = combates.size() - 1;
					combates[i].orden.push_back(c.v);
					combates[i].unids[c.v].b = Bajas();
				}

			combates[i].orden.insert(combates[i].orden.begin(), c.u);
			combates[i].unids[c.u].v[c.v] = Ataque(FRE, c.d);
			combates[i].unids[c.v].v[c.u] = Ataque(c.d, FRE);
			combates[i].unids[c.u].b = Bajas();
			combates[i].perdedor = eNULO;
		}
}

// GestorCombate::CombatesPendientes
/*************************************/
bool GestorCombate::CombatesPendientes (Estado& E)
{
	return (!combates.empty());
}

// GestorCombate::IniciarFase
/*************************************/
void GestorCombate::IniciarFase (Estado& E)
{
	GestorFase::IniciarFase (E);

	estado = 0;
	combActual = 0;
	numEfectos = 0;
	efecActual = 0;

// Se modifican las tareas disponibles.
	E.ModificarTarea (tCOMBATE, true, false);

	if (combates.size())
	{
		E.ModificarTarea (tTURNO, false, false);
		E.ModificarTarea (tDISPARO, false, false);
		E.ModificarTarea (tcomRESOLUCIONCOMBATES, true, true);
		((acComSigCombate*)E.LeerAccion(tcomSIGCOMBATE))->Reiniciar();
		PrepararCombate (E, combates[0]);
	}
}

// GestorCombate::EjecutarAccion
/*************************************/
void GestorCombate::EjecutarAccion(Estado& E, const Accion *a, const GestorEscenario& esc)
{
 	estado = AFD[estado][a->ID()];

	switch (estado)
	{
		case 1:
			E.NuevaSubFase (sfcomRESOLUCIONCOMBATES);
			E.ModificarTarea (tcomRESOLUCIONCOMBATES, true, false);
			E.ModificarTarea (tcomSIGCOMBATE, true, true);
			ResolverAccion (E, a, esc);
			break;
		case 2:
			E.NuevaSubFase (sfcomEFECTOCOMBATES);
			E.ModificarTarea (tcomHUIDAS, true, false);
			E.ModificarTarea (tcomSIGHUIDA, true, true);
			ResolverAccion (E, a, esc);
			break;
		default:
			break;
}}

// GestorCombate::ResolverAccion
/*************************************/
void GestorCombate::ResolverAccion (Estado& E, const Accion *a, const GestorEscenario& esc)
{
	if (a->T() == tcomSIGCOMBATE)
	{
		ResolverCombate(E, combates[combActual], esc);

		if (++combActual == combates.size())
		{
			E.ModificarTarea (tcomSIGCOMBATE, true, false);

			if (numEfectos)
				E.ModificarTarea (tcomHUIDAS, true, true);
			else
				{
					E.ModificarTarea (tTURNO, false, true);
					E.ModificarTarea (tDISPARO, false, true);
				}
		}
		else
			PrepararCombate(E, combates[combActual]);
	}
	else if (a->T() == tcomSIGHUIDA)
	{
		for ( ; combates[efecActual].perds.empty() && efecActual < combates.size(); ++efecActual);

		for (unsigned i = 0; i < combates[efecActual].perds.size(); ++i)
		{
			I j = combates[efecActual].perds[i];
			vector<Unidad*> unidsComb;

			for (J k = j->second.v.begin(); k != j->second.v.end(); ++k)
				unidsComb.push_back(k->first);

			E.IncluirUltimaTarea(tcomSIGHUIDA);
			esc.Huida(E, j->first, &unidsComb);
		}

		++efecActual;
		--numEfectos;

		if (!numEfectos)
		{
			E.ModificarTarea (tcomSIGHUIDA, true, false);
			E.ModificarTarea (tTURNO, false, true);
			E.ModificarTarea (tDISPARO, false, true);
}}}

// GestorCombate::PrepararCombate
/*************************************/
void GestorCombate::PrepararCombate (const Estado& E, Combate& c)
{
	EfPendientes *efP = ((acComSigCombate*)E.LeerAccion(tcomSIGCOMBATE))->Pendientes();

	for (I i = c.unids.begin(); i != c.unids.end(); ++i)
	{
		Unidad *u = i->first;
		Atrib a = u->Atributos();
		RangoEf inter(u->N(), unsigned());

		i->second.b.filasOr = u->Filas();

		for (J j = i->second.v.begin(); j != i->second.v.end(); ++j)
		{
			Unidad *v = j->first;

			RangoEf r1(u->Contacto(v, j->second.d, j->second.f));

			j->second.nAtaques += r1.size() * a.a;

			if (j->second.f == FRE)
				++c.unids[v].b.frente;
			else if (j->second.f == DER)
				++c.unids[v].b.flancoder;
			else if (j->second.f == RET)
				++c.unids[v].b.ret;
			else
				++c.unids[v].b.flancoizq;

			for (J k = j; ++k != i->second.v.end(); )
			{
				Unidad *w = k->first;

				RangoEf r2 = u->Contacto(w, k->second.d, k->second.f);
				RangoEf::iterator IT = set_intersection(r1.begin(), r1.end(), r2.begin(), r2.end(), inter.begin());

				// Si existen "efectivos" en común, se guardan en el vector de
				// efectivos pendientes. '*IT' es el efectivo actual.
				while (IT-- != inter.begin())
					{
						(*efP)[u].v[*IT].n = a.a;
						(*efP)[u].nTotal += a.a;

						(*efP)[u].v[*IT].v[v] = 0;
						(*efP)[u].v[*IT].v[w] = 0;

						--(j->second.nAtaques);
						--(i->second.v[w].nAtaques);
					}
			}
		}
	}
}

// GestorCombate::ResolverCombate
/*************************************/
void GestorCombate::ResolverCombate (const Estado& E, Combate& c, const GestorEscenario& esc)
{
	acComSigCombate *ac = (acComSigCombate*)E.LeerAccion (tcomSIGCOMBATE);

	// Se reyenan los efectivos pendientes.
	EfPendientes *efP = ac->Pendientes();
	for (EfPendientes::iterator i = efP->begin(); i != efP->end(); ++i)
		for (ListaEf::iterator j = i->second.v.begin(); j != i->second.v.end(); ++j)
			for (ListaAt::iterator k = j->second.v.begin(); k != j->second.v.end(); ++k)
				c.unids[i->first].v[k->first].nAtaques += k->second;

	ac->Reiniciar();

// Se resuelven los ataques.
	for (unsigned i = 0; i < c.orden.size(); ++i)
	{
		Unidad *u = c.orden[i];

		if (!c.unids[u].b.elim)
		{
			Atrib a = u->Atributos();

			Participacion& p = c.unids[u];
			Bajas *pb = 0;
			Unidad *v = 0;

			for (J j = p.v.begin(); j != p.v.end(); j = SigIter(p.v, j, pb->elim))
			{
				v = j->first;
				pb = &(c.unids[v].b);

				Atrib b = v->Atributos();

				for (unsigned n = (unsigned)Max (j->second.nAtaques - p.b.actBajas(j->second.d), 0); n--; )
				{
					bool ac = false;

					if (esc.Chequeo(a.ha, b.ha) && esc.Chequeo(a.f, b.r))
					{
						if (a.f > 4)
							ac = !esc.Chequeo (b.sa - (a.f - 5));
						else
							ac = !esc.Chequeo (b.sa);
					}

					if (ac)
					{
						if (v->Activo())
						{
							v->ModificarHeridas(-1);

							if (!v->N())
							{
								v->Eliminar();
								pb->elim = true;
						}}

						pb->NuevasBajas(j->second.f, 1);
				}}

				j->second.nAtaques = 0;
	}}}

	for (I i = c.unids.begin(); i != c.unids.end(); ++i)
	{
		Unidad *u = i->first;

		if (!c.unids[u].b.elim)
			for (J j = i->second.v.begin(); j != i->second.v.end(); ++j)
			{
				Unidad *v = j->first;

				if (j->second.f == RET)
				{
					unsigned aux = c.unids[v].b.filasOr - v->Filas();

					if (aux && v->N() && i->second.v.size() == 1)
						u->Desplazar (v->Atributos().ro.y * aux);
	}}}

// Se calcula el resultado del combate.
	unsigned ej1 = 0, ej2 = 0, pej1 = 0, pej2 = 0;

	for (I i = c.unids.begin(); i != c.unids.end(); ++i)
	{
		Unidad *u = i->first;
		unsigned *aux1, *aux2, *paux1;

		if (E.enumEjer(u->uEjercito()) == ePRIM)
		{
			aux1 = &ej1;
			aux2 = &ej2;
			paux1 = &pej1;
		}
		else
		{
			aux1 = &ej2;
			aux2 = &ej1;
			paux1 = &pej2;
		}

		*aux1 += i->second.b.filasOr;
		*paux1 += i->second.b.pOr;
		*aux2 += i->second.b.bFRE + i->second.b.bDER + i->second.b.bRET + i->second.b.bDER;
		*aux2 += i->second.b.flancoizq + i->second.b.flancoder + 2 * i->second.b.ret;
	}

	if (pej1 > pej2)
		++ej1;
	else if (pej1 != pej2)
		++ej2;

	if (ej1 > ej2)
		c.perdedor = eSEG;
	else if (ej1 != ej2)
		c.perdedor = ePRIM;
	else
		c.perdedor = eNULO;

	for (I i = c.unids.begin(); i != c.unids.end(); ++i)
	{
		Unidad *u = i->first;

		if (u->Activo() && u->uEjercito() == E.pEjer(c.perdedor) && !esc.Chequeo(u->Atributos().l))
		{
			u->Desmoralizar(true);
			c.unids[u].b.elim = true;
			c.perds.push_back(i);
	}}

	if (c.perds.size())
		++numEfectos;

	/*
	 *  Cambiamos el atributo de las unidades ganadoras (magia).
	 */
	if (c.perdedor != eNULO)
		for (unsigned i = 0; i < c.orden.size(); ++i)
			{
				Unidad *u = c.orden[i];
				
				if (c.perdedor != u->eEjercito())
					{
						unsigned prob = rand() % 4;

						if (prob > 1)
							prob -= 1;
						
						u->ModificarAtributo(rand() % 12, prob);
					}
			}
}

// GestorCombate::FinalizarFase
/*************************************/
void GestorCombate::FinalizarFase (Estado& E)
{
	GestorFase::FinalizarFase (E);

	((acComSigCombate*)E.LeerAccion(tcomSIGCOMBATE))->Destruir();

	for (int i = combates.size(); i--; )
	{
		Combate& c = combates[i];

		c.perds.clear();
		c.perdedor = eNULO;

		for (I j = c.unids.begin(); j != c.unids.end(); ++j)
			if (!j->second.b.elim)
			{
				for (J k = j->second.v.begin(); k != j->second.v.end(); k = SigIter(j->second.v, k, c.unids[k->first].b.elim));

				if (j->second.v.empty())
					j->second.b.elim = true;
		}

		for (I j = c.unids.begin(); j != c.unids.end(); j = SigIter(c.unids, j, j->second.b.elim))
			if (j->second.b.elim)
			{
				if (j->first->Activo())
						j->first->Combatir(false, false);
				c.orden.erase (find (c.orden.begin(), c.orden.end(), j->first));
			}

		if (c.orden.empty())
			combates.erase(combates.begin() + i);
		else
		{
			stable_sort (c.orden.begin(), c.orden.end(), CompUnids());

			for (I j = c.unids.begin(); j != c.unids.end(); ++j)
				j->second.b.Reiniciar(j->first->Filas(), j->first->P());
	}}

	E.ModificarTarea (tCOMBATE, true, false);
	E.ModificarTarea (tcomRESOLUCIONCOMBATES, true, false);
	E.ModificarTarea (tcomSIGCOMBATE, true, false);
	E.ModificarTarea (tcomHUIDAS, true, false);
	E.ModificarTarea (tcomSIGHUIDA, true, false);
}

// GestorCombate::EliminarIter
/*************************************/
template<typename I, typename J> J GestorCombate::SigIter (I& cont, J act, bool elim)
{
	if (act != cont.end())
		if (elim)
		{
			J k;
			bool prim = false;

			if (act == cont.begin())
				prim = true;
			else
			{
				k = act;
				--k;
			}

			cont.erase(act);

			if (prim)
				return (cont.begin());
			else
				return (++k);
		}
		else
			return (++act);
	else
		return (act);
}

// GestorCombate::Destruir
/*************************************/
void GestorCombate::Destruir (Estado& E)
{
	delete E.LeerAccion (tcomRESOLUCIONCOMBATES);
	delete E.LeerAccion (tcomSIGCOMBATE);
	delete E.LeerAccion (tcomHUIDAS);
	delete E.LeerAccion (tcomSIGHUIDA);
}
		
// GestorCombate::~GestorCombate
/*************************************/
GestorCombate::~GestorCombate()
{}
