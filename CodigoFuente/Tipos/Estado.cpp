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

#include "Estado.h"
#include <iostream>

using namespace std;

// Estado::Estado
/*************************************/
Estado::Estado (Ejercito *_pe, Ejercito *_pf, Ejercito *_gaia)
{
	pe = _pe;
	pf = _pf;
	gaia = _gaia;
}

// Estado::enumEjer
/*************************************/
Ejer Estado::enumEjer (Ejercito *_e) const
{
	if (_e == pe)
		return (ePRIM);
	else if (_e == pf)
		return (eSEG);
	else
		return (eNULO);
}

// Estado::Inicializacion
/*************************************/
void Estado::Inicializacion()
{
	for (unsigned t = 0; t < nTareas; ++t)
		acciones[t] = 0;

	ultimaT = tNULO;
}

// Estado::LeerAccion
/*************************************/
Accion* Estado::LeerAccion (Tarea t) const
{
	return (acciones[t]);
}

// Estado::NuevaAccion
/*************************************/
void Estado::NuevaAccion (Accion *ac)
{
	acciones[ac->T()] = ac;
}

// Estado:Batalla
/*************************************/
void Estado::Batalla()
{
	turno = 0;
	u = 0;
	e = eNULO;
	f = fNULO;
	sf = sfNULO;

	for (unsigned t = 0; t < nTareas; ++t)
		ModificarTarea((Tarea)t, true, false);
}

// Estado::Testear
/*************************************/
bool Estado::Testear (Fase _f, SubFase _sf) const
{
	return (_f == f && _sf == sf);
}

// Estado:Turno
/*************************************/
unsigned Estado::Turno() const
{
	return (turno);
}

// Estado:EjercitoActual
/*************************************/
Ejer Estado::EjercitoActual() const
{
	return (e);
}

// Estado:F
/*************************************/
Fase Estado::F() const
{
	return (f);
}

// Estado:SF
/*************************************/
SubFase Estado::SF() const
{
	return (sf);
}

// Estado:UnidadActual
/*************************************/
Unidad* Estado::UnidadActual() const
{
	if (u && !u->Activo())
		u = 0;

	return (u);
}

// Estado::pEjer
/*************************************/
Ejercito* Estado::pEjer (Ejer _e) const
{
	if (_e == ePRIM)
		return (pe);
	else if (_e == eSEG)
		return (pf);
	else if (_e == eGAIA)
		return (gaia);
	else
		return (NULL);
}

// Estado::LeerTarea
/*************************************/
bool Estado::LeerTarea (Tarea t, bool tipo) const
{
	if (tipo)
		return (activacion[t]);
	else
		return (disponibilidad[t]);
}

// Estado::UltimaTarea
/*************************************/
Tarea Estado::UltimaTarea () const
{
	return (ultimaT);
}

// Estado::NuevoTurno
/*************************************/
void Estado::NuevoTurno()
{
	++turno;
}

// Estado::NuevoEjercito
/*************************************/
void Estado::NuevoEjercito (Ejer _e)
{
	e = _e;
}

// Estado::NuevaFase
/*************************************/
void Estado::NuevaFase (Fase _f)
{
	f = _f;
}

// Estado::NuevaSubFase
/*************************************/
void Estado::NuevaSubFase (SubFase _sf)
{
	sf = _sf;
}

// Estado::NuevaUnidadActual
/*************************************/
void Estado::NuevaUnidadActual (Unidad *_u)
{
	u = _u;
}

// Estado::IncluirUltimaTarea
/*************************************/
void Estado::IncluirUltimaTarea (Tarea t)
{
	ultimaT = t;
}


// Estado::ModificarTarea
/*************************************/
void Estado::ModificarTarea (Tarea t, bool tipo, bool valor)
{
	if (tipo)
		disponibilidad[t] = activacion[t] = valor;
	else
		disponibilidad[t] = valor;
}
