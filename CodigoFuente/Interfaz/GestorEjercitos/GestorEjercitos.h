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

/*! \file GestorEjercitos.h
 *  \brief Fichero que define al gestor de ejércitos.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#ifndef _GESTOR_EJERCITOS_
#define _GESTOR_EJERCITOS_

#include <map>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "../../Tipos.h"
#include "ListaTexto/ListaTexto.h"

class RefEjercito;

class RefUnidad
{
 public:
  /* Constructor */
  RefUnidad();

  RefUnidad(std::string _unidad, Ejercito *e, double fw, double fh);

  /* Lectoras */
  Unidad* unidad() const;

  std::string Nombre() const;

  unsigned X() const;

  unsigned Y() const;

  unsigned N() const;

  unsigned F() const;

  unsigned Puntos() const;

  /* Modificadoras */
  void NuevoX(unsigned x);

  void NuevoY(unsigned y);

  void NuevoN(unsigned n);

  void NuevoF(unsigned f);

  /* Clases amigas */
  friend class RefEjercito;

 private:
  Unidad *u;

  std::string nombreUnidad;
};

class RefEjercito
{
 public:
  /* Constructor */
  RefEjercito();

  RefEjercito(std::string raza, Ejer _e);

  /* Destructor */
  ~RefEjercito();

  /* Lectoras */
  unsigned Puntos() const;

  std::string Raza() const;

  RefUnidad& unidad(int iUnidad);

  RefUnidad& unidad(unsigned iUnidad);

  unsigned N() const;

  std::vector<int> Verificar() const;

  Ejercito* ejercito() const;

  /* Modificadoras */
  RefUnidad& NuevaUnidad(int iUnidad, std::string unidad, double fw, double fh);

  void EliminarUnidad(int iUnidad);

 private:
  mutable bool ejercitoLeido;
  std::string raza;
  Ejercito *e;
  std::map<int, RefUnidad> vUnidades;
};

/*! \class GestorEjercitos
 *  \brief Clase del gestor de ejércitos.
 *
 *  \sa GestorFase
 *  \sa GestorReglas
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class GestorEjercitos
{
 public:
  /* Constructor */
  GestorEjercitos(SDL_Surface *screen, double _fw, double _fh);

  /* Destructor */
  ~GestorEjercitos();

  /* Modificadoras */
  void ElegirEjercitos(Ejercito **e, Ejercito **f);

  void NuevoEjercito();

  void EditarEjercito();

 private:
  TTF_Font *fuenteN;
  TTF_Font *fuenteP;

  SDL_Color color;
  SDL_Surface *screen;

  SDL_Surface *pElegirEjercitos;
  SDL_Surface *pCrearEjercito;
  SDL_Surface *pElegirFichero;
  SDL_Surface *pCrearFichero;

  SDL_Surface *subrayador;
  SDL_Surface *selector, *marcador;
  SDL_Surface *punto, *puntoSel;
  SDL_Surface *marca;

  SDL_Surface *cajaTexto;

  double fw;
  double fh;

  /* Modificadoras */
  RefEjercito* ConstruirEjercito(std::string nom, Ejer e);

  void EliminarEjercito(std::string nom);

  void ActualizarTexto(ListaTexto *texto, int i, Uint16 unicode, bool numerico, int max);

  std::string SeleccionarEjercito();

  bool Guardar(RefEjercito& r, std::string nombreActual = "");

  bool ModificarEjercito(std::string ejercito);

  void CrearSumario(ListaTexto& sumario, RefEjercito *r);

  void ModificarSumario(ListaTexto& sumario, int i, const RefUnidad& u);
};

#endif
