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

/*! \file GestorEscenario.h
 *  \brief Fichero de la clase \c GestorEscenario y otras
 *  clases auxiliares.
 *
 *  En este fichero se define a la clase \c GestorEscenario, y además,
 *  se definen otras clases que sirven de auxilio a los problemas que
 *  resuelve el gestor.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */

#ifndef _GoM_GESTOR_ESCENARIO_
#define _GoM_GESTOR_ESCENARIO_

#include <vector>
#include <map>
#include "Estado.h"
#include "Matematicas.h"
#include "Ejercito/Ejercito.h"

// Carga de una unidad 'u', a una unidad objetivo 'v'. 'd' es la dirección de carga: FRENTE, FLANCO IZQ/DER, o RETAGUARDIA.
struct Carga
{
  Carga() : u(0), v(0) {}
  Carga (Unidad *_u, Unidad *_v) : u(_u), v(_v) {}

  Unidad *u, *v;
	Dir d;
};

struct MovCarga
{
  MovCarga();
  MovCarga(const Carga& _C, const Segmento& _s);

  Carga C;
  bool efec;
  float despl;	 // Indica cuanto desplazamiento tiene que realizar para completar la carga o la carga fállida.

  Segmento s;
  unsigned nEfec;
};

/*! \class GestorEscenario
 *  \brief Clase gestor de escenario.
 *
 *  \sa Unidad
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class GestorEscenario
{
 public:
  /* Constructor */
  GestorEscenario (const Punto& DimEsc);

  /* Lectoras */
  const Punto& DimEscenario() const;

  bool Chequeo (unsigned a) const;

  bool Chequeo (unsigned a, unsigned b) const;

  float DesplMax (const Estado& E, Unidad *uAct,
									Carga *c = NULL, Unidad **prim = NULL) const;
  // Devuelve el desplazamiento máximo posible de la unidad actual. Si
  //  _u != NULL, se ignorará a la unidad _u para efectuar el cálculo
  //  del desplazamiento máximo.

  float PivotMaxIzq (const Estado& E, Unidad *uAct) const;
  // Devuelve el pivotaje máximo posible (pivotaje izquierdo) de la unidad actual. Si _u != NULL,
  //  se ignorará a la unidad _u para efectuar el cálculo del desplazamiento máximo.

  float PivotMaxDer (const Estado& E, Unidad *uAct) const;
  // Devuelve el pivotaje máximo posible (pivotaje derecho) de la unidad actual. Si _u != NULL,
  //  se ignorará a la unidad _u para efectuar el cálculo del desplazamiento máximo.

  bool Visible (const Estado& E, Unidad *u) const;
  // Devuelve si la unidad actual ve o no a 'u'.

  MovCarga MovimientoCarga (const Estado& E, const Carga& c) const;
  // Devuelve el movimiento de carga óptimo.

  void Huida (const Estado& E, Unidad *u, std::vector<Unidad*> *v = NULL) const;
  // Genera y ejecuta el movimiento de huida de la unidad u (que debe estar huyendo) suponiendo que en v están
  //  todas las unidades con las que se encontraba trabado.
	//  void Huida (const Estado& E, Unidad *u) const;
  // Genera y ejecuta el movimiento de huida de la unidad u, esquivando a las unidades enemigas
  //  que se encuentre por el camino y pasando a través de las unidades amigas que se encuentre por el mismo
  //  (la unidad que recibe el traspaso recibe un

	float DistanciaUnidades (Unidad *u, Unidad *v, int i = -1, int j = -1) const;

	Resultado ResultadoCombate (const Estado& E) const;

  /* Clases amigas */
  friend class GestorReglas;

 private:
  Punto esc[4];
  const float inf;

  /* Funciones privadas */
	std::pair<Dir, Dir> SegVision (const Estado& E, Unidad *u, Unidad *v) const;

  Semidisco AnguloVision (const Estado& E, Unidad *u) const;

  MovCarga MovSeg (const Carga& c, const Segmento& _s, Dir d) const;

  bool MejorarMov (const Estado& E, MovCarga c, MovCarga& C) const;

  float SigEmplazamiento (const Segmento& _s, Unidad *u, bool sig) const;
  // Tomando como referencia la posición del segmento s, se devuelve el desplazamiento en la misma dirección que deberá
  //  realizar el segmento _s para colocarse detrás de la unidad u
  //  (respetando la distancia de seguridad).
	// Si 'sig' es false, se busca, en vez del sigueinte emplazamiento,
  //  el anterior.

  bool FueraCampo (Unidad *u) const;
  // Devuelve true o false según la unidad u salga o permanezca en el
  // campo.

	MovCarga CargaFallida (const Estado& E, MovCarga C) const;
	// Supone que la carga almacena en C ha sido fállida, y calcula la
	// posición final de carga fállida.
};

#endif
