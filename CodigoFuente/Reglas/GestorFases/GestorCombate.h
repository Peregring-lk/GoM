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

/*! \file GestorCombate.h
 *  \brief Fichero que define al gestor de combate.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#ifndef _GoM_GESTOR_COMBATE_
#define _GoM_GESTOR_COMBATE_

#include <set>
#include "GestorFase.h"

typedef std::map<Unidad*, unsigned> ListaAt;

struct ListaAtaques
{
  unsigned n;  // Cantidad de ataques del efectivo que aun deben asignarse.
  ListaAt v;	 // Unidad y ataques asignados.
};

typedef std::map<unsigned, ListaAtaques> ListaEf;

struct EfecPendientes
{
EfecPendientes() : nTotal(0) {}

  unsigned nTotal; // Total de ataques por asignar restantes de la unidad.
  ListaEf v; // Efectivo y ataques asignados a cada unidad.
};

typedef std::map<Unidad*, EfecPendientes> EfPendientes;

unsigned AtPendientes (EfPendientes *efP, Unidad *u, unsigned ef);

void AsignarAt (EfPendientes *efP, Unidad *u, unsigned ef, Unidad *v, unsigned n);

struct Bajas
{
Bajas() : frente(0), flancoder(0), ret(0), flancoizq(0), filasOr(0), pOr(0), elim(false)
  { bFRE = bIZQ = bDER = bRET = 0; }

  /* Consultoras */
  unsigned actBajas (Dir d)
  {
    if (d == FRE)
      return (bFRE);
    else if (d == IZQ)
      return (bIZQ);
    else if (d == DER)
      return (bDER);
    else
      return (bRET);
  }

  /* Modificadoras */
  void Reiniciar(unsigned f, unsigned p)
  { 
    bFRE = bIZQ = bDER = bRET = 0;
    filasOr = f;
    pOr = p;
    frente = flancoizq = flancoder = ret = 0;
  }

  void NuevasBajas (Dir d, unsigned n)
  {
    if (d == FRE)
      bFRE += n;
    else if (d == IZQ)
      bIZQ += n;
    else if (d == DER)
      bDER += n;
    else
      bRET += n;
  }

  unsigned bFRE, bIZQ, bDER, bRET;
  unsigned frente;
  unsigned flancoder;
  unsigned ret;
  unsigned flancoizq;
  unsigned filasOr;
  unsigned pOr;
  bool elim;
};

struct Ataque
{
Ataque() : nAtaques(0) {}
Ataque(Dir d, Dir f) : d(d), f(f), nAtaques(0) {}

  Dir d, f;
  int nAtaques;
};

struct Participacion
{
  std::map<Unidad*, Ataque> v;
  Bajas b;
};

typedef map<Unidad*, Participacion>::iterator I;
typedef map<Unidad*, Ataque>::iterator J;

struct Combate
{
  std::map<Unidad*, Participacion> unids;
  std::vector<Unidad*> orden;
  std::vector<I> perds;
  Ejer perdedor;
};

struct CompUnids
{
  bool operator() (Unidad *u, Unidad *v)
  {
    return (u->Atributos().i > v->Atributos().i);
  }
};

/*! \class GestorCombate
 *  \brief Clase de la fase de combate.
 *
 *  \sa GestorFase
 *  \sa GestorReglas
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class GestorCombate : public GestorFase
{
 public:
  /* Modificadoras. Inicialización. */
  void Inicializar(Estado& E);

  /* Modificadoras. Batalla. */
  void NuevoCombate (Estado& E, Carga c, const GestorEscenario& esc);

  bool CombatesPendientes (Estado& E);

  void IniciarFase (Estado& E);

  void EjecutarAccion (Estado& E, const Accion *a, const GestorEscenario& esc);

  void FinalizarFase (Estado& E);

  /* Modificadoras. Destrucción. */
  void Destruir (Estado& E);

  /* Clases amigas */
  friend class GestorReglas;

 protected:
  /* Constructor */
  GestorCombate();

  /* Destructor */
  ~GestorCombate();

 private:
  unsigned estado;
  unsigned combActual;
  unsigned numEfectos;
  unsigned efecActual;

  std::vector<Combate> combates;

  /* Modificadoras. Batalla. */
  void ResolverAccion (Estado& E, const Accion *a, const GestorEscenario& esc);

  void PrepararCombate (const Estado& E, Combate& c);

  void ResolverCombate (const Estado& E, Combate& c, const GestorEscenario& esc);

  template<typename I, typename J> J SigIter (I& cont, J act, bool elim);

  void LimpiarUnids (Combate& c, I i, J j);
};

class acComResolucionCombates : public Accion
{
 public:
  /* Funcion abstracta */
  void Abstracta() {}

  /* Clases amigas */
  friend class GestorCombate;

 private:
  /* Constructor */
 acComResolucionCombates() : Accion (tcomRESOLUCIONCOMBATES, fCOMBATE, sfNULO, 0) {}

  /* Destructor */
  ~acComResolucionCombates() {}
};

class acComSigCombate : public Accion
{
 public:
  /* Funcion abstracta */
  void Abstracta() {}

  /* Consultoras */
  EfPendientes* Pendientes() const { return (efP); }

  /* Modificadoras */
  void Reiniciar ()
  {
    if (efP)
      delete efP;

    efP = new EfPendientes();
  }

  void Destruir()
  {
    if (efP)
      {
	delete efP;
	efP = 0;
      }}

  /* Clases amigas */
  friend class GestorCombate;

 private:
  EfPendientes *efP;

  /* Constructor */
 acComSigCombate() : Accion (tcomSIGCOMBATE, fCOMBATE, sfcomRESOLUCIONCOMBATES, 1), efP(0) {}

  /* Destructor */
  ~acComSigCombate()
    {
      if (efP)
	delete efP;
    }
};

class acComEfectoCombates : public Accion
{
 public:
  /* Funcion abstracta */
  void Abstracta() {}

  /* Clases amigas */
  friend class GestorCombate;

 private:
  /* Constructor */
 acComEfectoCombates() : Accion (tcomHUIDAS, fCOMBATE, sfNULO, 2) {}

  /* Destructor */
  ~acComEfectoCombates() {}
};

class acComSigEfectoCombate : public Accion
{
 public:
  /* Funcion abstracta */
  void Abstracta() {}

  /* Clases amigas */
  friend class GestorCombate;

 private:
  /* Constructor */
 acComSigEfectoCombate() : Accion (tcomSIGHUIDA, fCOMBATE, sfcomEFECTOCOMBATES, 3) {}

  /* Destructor */
  ~acComSigEfectoCombate() {}
};

#endif
