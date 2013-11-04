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

/*! \file GestorInterfaz.h
 *  \brief Fichero que define al gestor de interfaz.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#ifndef _GoM_GESTOR_INTERFAZ_
#define _GoM_GESTOR_INTERFAZ_

#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "Icono/GestorIconos.h"
#include "GestorEjercitos/GestorEjercitos.h"
#include "../Reglas/GestorReglas.h"

struct ParejaImg
{
  ParejaImg (SDL_Surface *_img, SDL_Rect _r) : img(_img), r(_r) {}

  SDL_Surface *img;
  SDL_Rect r;
};

typedef vector<ParejaImg>::iterator imgI;

typedef pair<SDL_Surface*, unsigned> pCont;

struct CompI
{
  bool operator()(const pCont& i, const pCont& j) const
  {
    return (i.second > j.second);
  }};

/*! \class GestorInterfaz
 *  \brief Clase del gestor de interfaz.
 *
 *  \sa GestorReglas
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class GestorInterfaz
{
 public:
  /* Constructor */
  GestorInterfaz();

  /* Destructor */
  ~GestorInterfaz();

  /* Modificadoras */
  void Inicializar (const Estado& E);
  // Inicializa todas las estructuras necesarias del gestor.

  unsigned Menu();
  // Lanza el menú del juego.

  void ElegirEjercitos(Ejercito **e, Ejercito **f) const;

  void NuevoEjercito() const;

  void EditarEjercito() const;

  Accion* NuevoEvento (const Estado& E, const GestorEscenario& esc);
  // Devuelve la siguiente acción indicada por el usuario.

	void ResultadoCombate(const Estado& E, Resultado r);

 private:
  SDL_Surface *marco, *fondo;   // 'marco' es la pantalla, 'fondo' la imagen base que la ocupa.
  // 'pixelArea' es el pixel de reyeno de áreas de selección, y pixelUnidad el de posición provisional de unidades.
  SDL_Surface *pixelArea, *pixelUnidad, *pixelUnidadCargaSel;
  SDL_Surface *pixelUnidadP, *pixelUnidadS;
  SDL_Surface *marcos;
	SDL_Surface *resultado;
  SDL_Surface *selector;
	SDL_Surface *subrayador;
  SDL_Surface *marca;

	Unidad *ultimaUnidad;
	Tarea ultimaTarea;
	bool bimprimir;

  SDL_Color color;

  double fw, fh;

  GestorIconos *gi;
  GestorEjercitos *ge;
  // 'fuenteN' es la fuente básica (normal o común), la 'fuenteT' es la que indica un cambio de turno,
  //   y la 'fuenteE' la propia para los errores.
  TTF_Font *fuenteN, *fuenteT,
		*fuenteE, *fuenteG;

  // vector de todas las impresiones pendientes.
  vector<ParejaImg> imgs;
  vector<pCont> errores;

  /* Funciones privadas */
	void MejorPantalla ();

  Accion* ObtenerAtributos (Accion *a, Unidad *u, const Estado& E, const GestorEscenario& esc);
  // Obtiene los atributos de una acción dada, y la devuelve.

  Unidad* ElegirUnidadCarga (const Estado& E, const GestorEscenario& esc, bool com = true);
  // Elige la unidad entre todas las que la unidad actual puede declarar carga.


  double ElegirDespl (const Estado& E, const GestorEscenario& esc);
  // Elige el desplazamiento (dentro de su límite máximo permitido) de la unidad actual.

  double ElegirAngIzq (const Estado& E, const GestorEscenario& esc);
  // Elige el pivotaje izquierdo (dentro de su límite máximo permitido) de la unidad actual.

  double ElegirAngDer (const Estado& E, const GestorEscenario& esc);
  // Elige el pivotaje derecho (dentro de su límite máximo permitido) de la unidad actual.

  void ElegirAtaques (const Estado& E, EfPendientes *efP);
  // Elige todos los ataques no asignados de efP.

  void Imprimir (const Estado& E, Unidad *u);
  // Imprime todo el escenario del juego.

  void ImprimirDescripcion (Unidad *u, const Estado& E);
  // Imprime la descripción de una unidad.

  void ImprimirEjercito (const Ejercito *e, const Estado& E);
  // Imprime todas las unidades del ejército 'e'.

  void ImprimirError (const Estado& E, short i);
  // Imprime el error i-ésimo de la lista de errores posibles.

  void ErrorTarea (const Estado& E, Tarea t);

  template<typename T> void RellenarArea (const T& fig, SDL_Surface *pix, bool dir = false);
};

#endif
