/*
    This file is part of GoM.

    GoM is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published
    by the Free Software Foundation, either version 3 of the License,
    or (at your option) any later version.

    GoM is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GoM.  If not, see <http://www.gnu.org/licenses/>.

--

    Este fichero forma parte de GoM.

    GoM es sotware libre: podrá redistribuirlo y/o modificarlo
    bajo los términos de la GNU General Public License según es
    publicada por la Free Software Fundation, tanto para la versión 3
    de la licencia como para cualquier versión posterior (según su elección).

    GoM se distribuye con la esperanza de ser útil, pero SIN NINGUNA
    GARANTÍA, incluso sin garantía MERCANTIL implícita o CONVENIENCIA
    PARA UN PROPÓSITO PARTICULAR. Vea la GNU General Public License
    para más detalles.

    Debió recibir una copia de la GNU General Public License
    junto a GoM. Si no es así, visite <http://www.gnu.org/licenses/>.

*/

/*! \file Unidad.h
 *  \brief Fichero que define a la clase \c Unidad.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#ifndef _GoM_UNIDAD_
#define _GoM_UNIDAD_

#include <string>
#include <vector>
#include <map>
#include "SDL/SDL.h"
#include "../Matematicas.h"
#include "../Clases.h"
#include "../Enumeraciones.h"
#include "../Excepciones.h"

struct Atrib
{
  std::string nombre;
  float m;
  unsigned ha;
	unsigned hp;
  unsigned f;
  unsigned r;
  unsigned a;
  unsigned h;
  unsigned i;
  unsigned l;
  unsigned p;
  unsigned sa;
	unsigned fa;
	float aa;
  Punto ro;
  unsigned puntos;
};

typedef std::vector<unsigned> RangoEf;

/*! \class Unidad
 *  \brief Clase unidad.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
class Unidad
{
 public:
  /* Constructor */
  Unidad (Atrib _a, std::string dir, Ejercito *_e, unsigned min,
					unsigned max, double _fw, double _fh, std::string nomUnidad);

  /* Destructor */
  virtual ~Unidad();

  /* Consultoras. */
	std::string NombreUnidad() const;

  bool Activo() const;
  // Devuelve si la unidad está activa.
	bool Actualizar() const;
	// Devuelve si la unidad se ha modificado en posición o forma desde
	// la última vez que se obtuvo su imágen.
	bool bMarchar() const;
	// Devuelve si la unidad puede marchar.
  const Atrib& Atributos() const;
  // Devuelve los atributos de la unidad.
  float Ang() const;
  // Devuelve el ángulo que forma la cara frontal con el eje x (en radianes).
  unsigned MinEfecs() const;
  // Devuelve el número de efectivos mínimo posible de la unidad al
  // comienzo de la batalla.			
	unsigned MaxEfecs() const;
  unsigned N() const;
  // Devuelve el número de efectivos actual de la unidad.
	unsigned NO() const;
	// Devuelve el número de efectivos original de la unidad.
  unsigned Frente() const;
  // Devuelve el número de miniaturas de la primera fila.
  unsigned Filas() const;
  // Devuelve el número de filas de la unidad.
  unsigned P() const;
  // Devuelve la potencia total de la unidad.
  unsigned Puntos() const;
  // Devuelve el coste total en puntos de la unidad.
  float MovMax () const;
  // Devuelve el movimiento máximo que puede realizar la unidad actualmente.
  float AngMax () const;
  // Devuelve el ángulo máximo en grados que puede realizar la unidad actualmente.
  const Punto& Psi() const;
  // Devuelve las coordenadas del pivote superior izquierdo de la unidad.
  const Punto& Psd() const;
  // Devuelve las coordenadas del pivote superior derecho de la unidad.
  const Punto& Pii() const;
  // Devuelve las coordenadas del pivote inferior izquierdo de la unidad.
  const Punto& Pid() const;
  // Devuelve las coordenadas del pivote inferior derecho de la unidad.
  Segmento Lado (Dir d, bool prec) const;
  unsigned Efecs (Dir d) const;

  Rectangulo Efec (unsigned _n) const;
  // Devuelve el Rectangulo de la n-ésima miniatura de la unidad.
  const Rectangulo& R() const;

  bool Cargando() const;

	bool Marchado() const;

  bool Marchando() const;

  bool Combatiendo() const;

  bool Desmoralizado() const;

  bool Huyendo() const;

  bool Seleccionado() const;

	bool Disparado() const;

	unsigned Heridas() const;

  unsigned Contacto (const Segmento& s, Dir d) const;

  RangoEf Contacto (Unidad *u, Dir d, Dir f) const;

  Ejercito* uEjercito() const;

	Ejer eEjercito() const;

  virtual Unidad* UnidadVirtual() = 0;

  bool operator<< (const Punto& p) const;
  // Devuelve true si p está en la unidad (sin contar la fila
  // incompleta), false en caso contrario.

	SDL_Surface* ImgSeleccionado() const;
	SDL_Surface* ImgMarcado() const;

	Punto puntoImpr() const;

  /* Modificadoras */
	void Inicializar();

	void ModificarAtributo(unsigned i, int cantidad);

  SDL_Surface* ImgActual ();
  // Devuelve la imagen que corresponde a la orientación actual de
  // cada uno de los efectivos de la unidad.

  void Seleccionar();

  void Deseleccionar();

  void Reiniciar();
  // Añade una nueva fase de movimiento a la unidad (reinicia el contador de movimiento posible).
  void NuevaPO (const Punto& p, float ang);
  // Añade una nueva posición a la unidad.
  void Marchar (bool m);
  // Si m = true hace que la unidad marche, o detiene la marcha (o no hace nada si no marchaba) en caso contrario.
  void MasEfectivos(unsigned _n);

  void MenosEfectivos(unsigned _n);

  void Desplazar(float k);

  void Girar();

  void PivotarIzq (float ang);

  void PivotarDer (float ang);

  void Trasladar (const Segmento& s);

  void NuevoFrente (unsigned _frente);

  void Cargar (bool c);

  void Combatir (bool c, bool ataque);

  void Desmoralizar (bool d);

  void Huir (bool h);

	void Disparar (bool d);

	void ModificarHeridas (int numHeridas);

  void Eliminar();

 protected:
  Atrib a;                    		// Atributos de la unidad.
  Ejercito *e;                    // Ejército al que pertenece la
																	// unidad.
  Rectangulo r;										// Rectángulo de la unidad (considerándo a la última fila).
  unsigned n, frente;             // Número de efectivos totales y en
																	// la primera fila.
	unsigned no;                    // Número de efectivos al comenzar
																	// la batalla.
	unsigned heridas;
  unsigned nmin;                  // Número mínimo de efectivos.
	unsigned nmax;                  // Número máximo de efectivos.
  unsigned ufila;                 // Número de "huecos" libres delante del primer efectivo de la última fila.

  float movmax;                   // Cantidad de movimiento restante (total - consumido).
  bool marcha;                    // Marcha = true si la unidad está marchando, Marcha = false si no está marchando.

	bool marchar;                   // True si la unidad puede marchar
																	// en el turno actual.
	bool marchado;                  // True si la unidad ha marchado en
																	// el turno actual.
  bool sel;
  bool carga;                     // True si la unidad ha declarado carga, false en caso contrario.
  bool comb;                      // True si la unidad está trabada con otras unidades, false en caso contrario.
  bool desmo; 										// True si la unidad está desmoralizada, false en caso contrario.
  bool huida;                     // True si la unidad está huyendo,
																	// false en caso contrario.
	bool disp;                      // True si la unidad ha disparado
																	// este turno. False en caso contrario.

	bool actualizar;                // True si la unidad ha cambiado
																	// desde la última vez que se imprimió.
  bool vir;                       // True si la unidad es virtual, false en caso contrario.
  bool act;                       // True si la unidad está activa (si
																	// existe en el juego), false en
																	// caso contrario.

	std::string nomUnidad;

	std::map<unsigned, SDL_Surface*> imagenes;
	SDL_Surface *imgSeleccionado, *selOr;
	SDL_Surface *imgMarcado, *marcOr;

	Punto posImpr;
	double fw;
	double fh;

  void ActualizarRect (unsigned _n, unsigned _frente);

	void ActualizarImgSelMarc();
};

#endif
