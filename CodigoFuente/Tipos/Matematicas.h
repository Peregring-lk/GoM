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

/*! \file Matematicas.h
 *  \brief Fichero de declaración de clases y funciones tanto geométricas como de corte general.
 *
 *  Permite trabajar con los siguientes tipos geométricos:
 *   \li \c Punto
 *   \li \c Recta
 *   \li \c Segmento
 *   \li \c Rectangulo
 *   \li \c Cuadrilatero
 *   \li \c Circunferencia
 *   \li \c Semidisco
 *
 *  Además de poseer diversas funciones matemáticas habituales.
 *
 *  \note Todas las clases y funciones aquí implementadas suponen
 *        un plano cartesiano con un eje \a x dirigido en direccion
 *        O-E y un eje \a y dirigido en direccion S-N.
 *
 *  \note Todos los parámetros o variables usadas como ángulos, si no se indica lo contrario, se tomarán
 *        como radianes. Además, el ángulo siempre se tomará respecto al eje \c x.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */

#ifndef _GoM_MATEMATICAS_
#define _GoM_MATEMATICAS_

#include <cmath>
#include "Excepciones.h"

/*! \struct Punto
 *  \brief Tipo punto.
 *
 *  Las funciones adjuntas a la estructura permiten trabajar con el punto en el
 *  plano.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
struct Punto
{
	/*! \fn Punto()
	 *  \brief Constructor por defecto de un punto.
	 *
	 *  \post Construye el punto (\a 0, \a 0).
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto();

	/*! \fn Punto(float x, float y)
	 *  \brief Constructor general de un punto.
	 *
	 *  \param x Coordenada \a x del punto.
	 *  \param y Coordenada \a y del punto.
	 *
	 *  \post Construye el punto (\a x, \a y).
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto (float x, float y);

	/*! \fn Punto operator+ (const Punto& p) const
	 *  \brief Devuelve la suma de dos puntos.
	 *
	 *  \param p El punto adición.
	 *
	 *  \post Si el punto actual es \f$(x,y)\f$, devuelve el punto
   *        \f$(x + p.x, y + p.y)\f$.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto operator+ (const Punto& p) const;

	/*! \fn Punto operator+ (float k) const
	 *  \brief Devuelve la suma de un punto y un escalar.
	 *
	 *  \param k El escalar adición.
	 *
	 *  \return Si el punto actual es \f$(x, y)\f$, devuelve el punto
   *          \f$(x + k, y + k)\f$.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto operator+ (float k) const;

	/*! \fn Punto operator- (const Punto& p) const
	 *  \brief Devuelve la resta de dos puntos.
	 *
	 *  \param p El punto sustraendo.
	 *
	 *  \return Si el punto actual es \f$(x, y)\f$, devuelve el punto
   *          \f$(x - p.x, y - p.y)\f$.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto operator- (const Punto& p) const;

	/*! \fn Punto operator- (float k) const
	 *  \brief Devuelve la resta de un punto y un escalar.
	 *
	 *  \param k El escalar sustraendo.
	 *
	 *  \return Si el punto actual es \f$(x, y)\f$, devuelve el punto
   *          \f$(x - k, y - k)\f$.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto operator- (float k) const;

	/*! \fn Punto operator* (float k) const
	 *  \brief Devuelve el producto de un punto y un escalar.
	 *
	 *  \param k El escalar multiplicador.
	 *
	 *  \return Si el punto actual es \f$(x, y)\f$, devuelve el punto
   *          \f$(kx, ky)\f$.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto operator* (float k) const;

	/*! \fn float operator* (const Punto& p) const
	 *  \brief Devuelve el producto escalar de dos puntos.
	 *
	 *  \param p El punto proyección.
	 *
	 *  \return Si el punto actual es \f$(x, y)\f$, devuelve el escalar
	 *          \f$x \cdot p.x + y \cdot p.y\f$
	 *
	 *  \note Una interpretación de producto escalar (la usada aquí) es que el producto escalar
	 *        \f$ p_a \cdot p_b \f$ es el producto de \f$ |p_a| \f$ con el módulo del vector
	 *        proyección \f$ p_b \f$ sobre \f$ p_a \f$: \f[ p_a \cdot p_b = |p_a| \cdot |proy((p_a)_{p_b})| \f]
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float operator* (const Punto& p) const;

	/*! \fn bool operator== (const Punto& p) const
	 *  \brief Comprueba que dos puntos sean el mismo.
	 *
	 *  \param p El punto a comparar.
	 *
	 *  \return Devuelve \c true si el punto a comparar y el actual son el mismo punto.
	 *          Devuelve \c false en caso contrario.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	bool operator== (const Punto& p) const;

	/*! \fn bool operator!= (const Punto& p) const
	 *  \brief Comprueba que dos puntos no sean el mismo.
	 *
	 *  \param p El punto a comparar.
	 *
	 *  \return Devuelve \c true si el punto a comparar y el actual no son el mismo punto.
	 *          Devuelve \c false en caso contrario.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	bool operator!= (const Punto& p) const;

	/*! \fn bool Sentido (const Punto& p, const Punto& q) const
	 *  \brief Comprueba que tres puntos no estén orientados positivamente.
	 *
	 *  \param p El segundo punto en la sucesión.
	 *  \param q El tercer punto en la sucesión
	 *
	 *  \return Devuelve \c true si los puntos \c *this, \c p y \c q no están orientados positivamente.
	 *          Devuelve \c false en caso contrario.
	 *
	 *  \note Tres puntos \f$ p_a, p_b, p_c \f$ están orientados positivamente si la lectura \f$ p_a \rightarrow
	 *        p_b \rightarrow p_c \f$ tiene sentido antihorario. Si tiene sentido horario, se dice que están
	 *        orientados positivamente. Si son colineales (si están en un mismo segmento), su orientación será nula.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	bool Sentido (const Punto& p, const Punto& q) const;

	/*! \fn Punto& operator+= (const Punto& p)
	 *  \brief Desplaza un punto según su suma con otro.
	 *
	 *  \param p El punto adición.
	 *
	 *  \post Si el punto actual es \f$(x, y)\f$, pasará a ser
   *        \f$(x + p.x, y + p.y)\f$.
	 *
	 *  \return Devuelve por referencia el punto desplazado.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto& operator+= (const Punto& p);

	/*! \fn Punto& operator+= (float k)
	 *  \brief Desplaza un punto según su suma con un escalar.
	 *
	 *  \param k El escalar adición.
	 *
	 *  \post Si el punto actual es \f$(x, y)\f$, pasará a ser
   *        \f$(x + k, y + k)\f$.
	 *
	 *  \return Devuelve por referencia el punto desplazado.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto& operator+= (float k);

	/*! \fn Punto& operator-= (const Punto& p)
	 *  \brief Desplaza un punto según su resta con otro.
	 *
	 *  \param p El punto adición.
	 *
	 *  \post Si el punto actual es \f$(x, y)\f$, pasará a ser
   *        \f$(x - p.x, y - p.y)\f$.
	 *
	 *  \return Devuelve por referencia el punto desplazado.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto& operator-= (const Punto& p);

	/*! \fn Punto& operator-= (float k)
	 *  \brief Desplaza un punto según su resta con un escalar.
	 *
	 *  \param k El escalar sustrendo.
	 *
	 *  \post Si el punto actual es \f$(x, y)\f$, pasará a ser
   *        \f$(x - k, y - k)\f$.
	 *
	 *  \return Devuelve por referencia el punto desplazado.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto& operator-= (float k);

	/*! \fn Punto& operator*= (float k)
	 *  \brief Desplaza un punto según su producto con un escalar.
	 *
	 *  \param k El escalar multiplicador.
	 *
	 *  \post Si el punto actual es \f$(x, y)\f$, pasará a ser
   *        \f$(kx, ky)\f$.
	 *
	 *  \return Devuelve por referencia el punto desplazado.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto& operator*= (float k);

	/*! \var float x
	 *  \brief Coordenada \a x.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float x;

	/*! \var float y
	 *  \brief Coordenada \c y.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
   */
	float y;

	/*! \var float mod
	 *  \brief El módulo del punto.
	 *
	 *  \note Aunque estrictamente un punto no sea un vector, \c mod guarda el valor del módulo
	 *        del punto tratado como vector.
	 *
	 *  \note Es equivalente a la longitud del segmento \f$\overline{OP}\f$, siendo \f$O=(0,0)\f$,
	 *        y \f$P=(x, y)\f$.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float mod;
};


/*! \struct Recta
 *  \brief Tipo recta.
 *
 *  Las funciones adjuntas a la estructura permiten trabajar con la recta en el
 *  plano.
 *
 *  \note Debido a las limitaciones naturales que posee la recta tratada como una función (\f$ y = ax+b \f$),
 *        que no permite construir a la recta \f$x = 0\f$, el concepto elegido para representarla es el de
 *        hiperplano en \f$\mathbf{R}^2\f$, es decir, la ecuación de la forma \f$ax+by=c\f$.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
struct Recta
{
	/*! \fn Recta()
	 *  \brief Constructor por defecto de una recta.
	 *
   *  \post Construye la recta \f$ y = 0 \f$.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Recta();

	/*! \fn Recta (const Punto& p, const Punto& q)
	 *  \brief Constructor general (1) de una recta.
	 *
	 *  \param p Primer punto de referencia.
	 *  \param q Segundo punto de referencia.
	 *
	 *  \post Construye la única recta que contiene a la vez a \c p y a \c q.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Recta (const Punto& p, const Punto& q);

	/*! \fn Recta (const Punto& p, float _ang)
	 *  \brief Constructor general (2) de una recta.
	 *
	 *  \param p Punto de referencia.
	 *  \param _ang Ángulo respecto al eje \a x.
	 *
	 *  \post Construye la única recta que contiene a \c p y dista \c _ang radianes del eje \a x.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Recta (const Punto& p, float _ang);

	/*! \fn Recta operator+ (float k) const
	 *  \brief Devuelve una recta desplazada positivamente sobre el eje \f$ y \f$.
	 *
	 *  \param k Desplazamiento positivo sobre el eje \a y.
	 *
	 *  \return Si la recta actual es \f$ r_0 \equiv ax+by=c \f$, devuelve la recta \f$ ax+b(y-k)=c \f$,
	 *          que dista una distancia \f$k\f$ sobre \f$r_0\f$ por el eje \f$y\f$.
	 *
	 *  \note La recta devuelta será paralela a la original.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Recta operator+ (float k) const;

	/*! \fn Recta operator- (float k) const
	 *  \brief Devuelve una recta desplazada negativamente sobre el eje \f$ y \f$.
	 *
	 *  \param k Desplazamiento negativo sobre el eje \a y.
	 *
	 *  \return Si la recta actual es \f$ r_0 \equiv ax+by=c \f$, devuelve la recta \f$ ax+b(y+k)=c \f$,
	 *          que dista una distancia \f$k\f$ bajo \f$r_0\f$ por el eje \f$y\f$.
	 *
	 *  \note La recta devuelta será paralela a la original.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Recta operator- (float k) const;

	/*! \fn Recta operator> (float k) const
	 *  \brief Devuelve una recta desplazada positivamente sobre el eje \a x.
	 *
	 *  \param k Desplazamiento positivo sobre el eje \a x.
	 *
	 *  \return Si la recta actual es \f$ r_0 \equiv ax+by=c \f$, devuelve la recta \f$ a(x-k)+by=c \f$,
	 *          que dista una distancia \c k sobre \f$r_0\f$ por el eje \a x.
	 *
	 *  \note La recta devuelta será paralela a la original.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Recta operator> (float k) const;

	/*! \fn Recta operator< (float k) const
	 *  \brief Devuelve una recta desplazada negativamente sobre el eje \a x.
	 *
	 *  \param k Desplazamiento negativo sobre el eje \a x.
	 *
	 *  \return Si la recta actual es \f$ r_0 \equiv ax+by=c \f$, devuelve la recta \f$ a(x+k)+by=c \f$,
	 *          que dista una distancia \c k bajo \f$r_0\f$ por el eje \a x.
	 *
	 *  \note La recta devuelta será paralela a la original.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Recta operator< (float k) const;

	/*! \fn Recta operator>> (const Punto& p) const
	 *  \brief Devuelve una recta desplazada de modo que contenga a \c p.
	 *
	 *  \param p Punto de referencia de desplazamiento.
	 *
	 *  \return Si la recta actual es \f$ r_0 \equiv ax+by=c_a \f$, devuelve la recta \f$ r_1 \equiv ax+by=c_b \f$,
	 *          consiguiendo \f$c_b\f$ de modo que \f$r_1\f$ contenga al punto \c p.
	 *
	 *  \note La recta devuelta será paralela a la original.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Recta operator>> (const Punto& p) const;

	/*! \fn Punto operator* (const Recta& r) const
	 *  \brief Calcula la intersección de dos rectas.
	 *
	 *  \param r Recta de intersección.
	 *
	 *  \return Si las rectas no son paralelas entre sí, devuelve la intersección de ambas.
	 *
	 *  \throw xPnulo Lanzado cuando las rectas son paralelas pero no iguales, indicando que
	 *                no existe intersección alguna.
	 *
	 *  \throw xRiguales Lanzado si las dos rectas coinciden, indicando que existen infinitas
	 *                   intersecciones (tantas como puntos tenga cada recta).
	 *
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto operator* (const Recta& r) const throw (xPnulo, xRiguales);

	/*! \fn Punto operator<< (const Punto& r) const
	 *  \brief Comprueba que un punto pertenezca a una recta.
	 *
	 *  \param p Punto de referencia.
	 *
	 *  \return Si \c p es un punto de la recta, devuelve \c true. Devuelve \c false en caso contrario.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	bool operator<< (const Punto& p) const;

	/*! \fn bool operator== (const Recta& r) const
	 *  \brief Comprueba que dos rectas sean la misma.
	 *
	 *  \param r La recta a comparar.
	 *
	 *  \return Devuelve \c true si la recta a comparar y la actual son la misma recta.
	 *          Devuelve \c false en caso contrario.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	bool operator== (const Recta& r) const;

	/*! \fn bool operator!= (const Recta& r) const
	 *  \brief Comprueba que dos rectas no sean la misma.
	 *
	 *  \param r La recta a comparar.
	 *
	 *  \return Devuelve \c true si la recta a comparar y la actual no son la misma recta.
	 *          Devuelve \c false en caso contrario.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	bool operator!= (const Recta& r) const;

	/*! \fn bool operator|| (const Recta& r) const
	 *  \brief Comprueba que dos rectas sean paralelas.
	 *
	 *  \param r La recta a comparar.
	 *
	 *  \return Devuelve \c true si la recta a comparar y la actual son paralelas.
	 *          Devuelve \c false en caso contrario.
	 *
	 *  \note Dos rectas coincidentes también son paralelas.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	bool operator|| (const Recta& r) const;

	/*! \fn float operator^ (const Recta& r) const
	 *  \brief Devuelve el ángulo entre dos rectas.
	 *
	 *  \param r La recta a comparar.
	 *
	 *  \return Devuelve el ángulo en radianes que existe desde la recta actual hasta la recta \c r.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float operator^ (const Recta& r) const;

	/*! \fn float AngMin (const Recta& r) const
	 *  \brief Devuelve el mínimo ángulo entre dos rectas.
	 *
	 *  \param r La recta a comparar.
	 *
	 *  \return Devuelve \f$ min(\widehat{r_0r_1}, \widehat{r_1r_0}) \f$.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float AngMin (const Recta& r) const;

	/*! \fn Punto ExtremoSegmento (const Punto& p, float l) const
	 *  \brief Devuelve el extremo opuesto de un segmento a partir de uno de sus puntos y su longitud.
	 *
	 *  \param p Primer punto del segmento.
	 *  \param l Longitud del segmento.
	 *
	 *  \pre El punto \c p debe pertenecer a la recta.
	 *
	 *  \return Si el punto \c p es un extremo de un segmento de longitud \c l de la recta actual,
	 *          devuelve el extremo opuesto de dicho segmento.
	 *
	 *  \throw xPnulo Lanzado si \c p no pertenece a la recta.
	 *
	 *  \note Se tomará siempre como referencia la dirección de la recta actual. Si \f$ l > 0\f$ significará
	 *        que el segmento se dirige a favor de la recta (tendrán el mismo ángulo). Si \f$ l < 0 \f$,
   *        significa que el segmento se dirige en dirección contraria (diferiran \f$\frac{\pi}{2}rad\f$).
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto ExtremoSegmento (const Punto& p, float l) const throw (xPnulo);

	/*! \fn float Distancia (const Punto& p) const
	 *  \brief Devuelve la distancia de la recta a un punto.
	 *
	 *  \param p El punto de referencia.
	 *
	 *  \return Devuelve la distancia existente entre el punto \c p y la recta actual.
	 *
	 *  \note Es equivalente a la longitud del segmento \f$\overline{ip}\f$, siendo \f$i\f$ el punto
	 *        intersección entre la recta actual y la única perpendicular a ella que contiene a \c p.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float Distancia (const Punto& p) const;

	/*! \fn Recta& operator+= (float k)
	 *  \brief Desplaza la recta positivamente sobre el eje \a y.
	 *
	 *  \param k Desplazamiento positivo sobre el eje \a y.
	 *
	 *  \post Si la recta actual es \f$ r_0 \equiv ax+by=c \f$, pasará a ser \f$ ax+b(y-k)=c \f$,
	 *          que dista una distancia \c k sobre \f$r_0\f$ por el eje \a y.
	 *
   *  \return Devuelve por referencia la recta desplazada.
	 *
	 *  \note La nueva recta será paralela a la original.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Recta& operator+= (float k);

	/*! \fn Recta& operator-= (float k)
	 *  \brief Desplaza la recta negativamente sobre el eje \a y.
	 *
	 *  \param k Desplazamiento negativo sobre el eje \a y.
	 *
	 *  \post Si la recta actual es \f$ r_0 \equiv ax+by=c \f$, pasará a ser \f$ ax+b(y+k)=c \f$,
	 *          que dista una distancia \c k bajo \f$r_0\f$ por el eje \a y.
	 *
   *  \return Devuelve por referencia la recta desplazada.
	 *
	 *  \note La nueva recta será paralela a la original.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Recta& operator-= (float k);

	/*! \fn Recta& operator>= (float k)
	 *  \brief Desplaza la recta positivamente sobre el eje \a x.
	 *
	 *  \param k Desplazamiento positivo sobre el eje \a x.
	 *
	 *  \post Si la recta actual es \f$ r_0 \equiv ax+by=c \f$, pasará a ser \f$ a(x-k)+b=c \f$,
	 *          que dista una distancia \c k sobre \f$r_0\f$ por el eje \a x.
	 *
   *  \return Devuelve por referencia la recta desplazada.
	 *
	 *  \note La nueva recta será paralela a la original.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Recta& operator>= (float k);

	/*! \fn Recta& operator<= (float k)
	 *  \brief Desplaza la recta negativamente sobre el eje \a x.
	 *
	 *  \param k Desplazamiento negativo sobre el eje \a x.
	 *
	 *  \post Si la recta actual es \f$ r_0 \equiv ax+by=c \f$, pasará a ser \f$ a(x+k)+b=c \f$,
	 *          que dista una distancia \c k bajo \f$r_0\f$ por el eje \a x.
	 *
   *  \return Devuelve por referencia la recta desplazada.
	 *
	 *  \note La nueva recta será paralela a la original.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Recta& operator<= (float k);

	/*! \fn Recta& operator>>= (const Punto& p) const
	 *  \brief Desplaza la recta de modo que contenga a \c p.
	 *
	 *  \param p Punto de referencia de desplazamiento.
	 *
	 *  \post Si la recta actual es \f$ r_0 \equiv ax+by=c_a \f$, pasará a ser la recta \f$ r_1 \equiv ax+by=c_b \f$,
	 *          consiguiendo \f$c_b\f$ de modo que \f$r_1\f$ contenga al punto \c p.
	 *
	 *  \return Devuelve por referencia la recta desplazada.
	 *
	 *  \note La recta devuelta será paralela a la original.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Recta& operator>>= (const Punto& p);

	/*! \var float a
	 *  \brief Coeficiente de la variable \a x de la recta.
	 *
	 *  \note Aunque no afecte al contenido funcional de la estructura \c Recta, por comodidad,
	 *        éste coeficiente siempre valdrá 0 ó 1.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float a;

	/*! \var float b
	 *  \brief Coeficiente de la variable \a y de la recta.
	 *
	 *  \note Aunque no afecte al contenido funcional de la estructura \c Recta, por comodidad,
	 *        éste coeficiente valdrá 1 cuando el coeficiente \c a sea 0.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float b;

	/*! \var float c
	 *  \brief Término independiente de la recta.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float c;

	/*! \var float ang
	 *  \brief Ángulo de la recta respecto al eje \a x.
	 *
	 *  \note Aunque para una recta es indistiguible tener \f$x\f$ ó \f$x+\frac{\pi}{2}\f$ radianes como ángulo
	 *        puesto que la ecuación de la recta no posee noción alguna de dirección, esta variable si contemplará
	 *        dicha distinción para potenciar la funcionalidad del tipo \c Recta.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float ang;
};


/*! \struct Segmento
 *  \brief Tipo segmento.
 *
 *  Las funciones adjuntas a la estructura permiten trabajar con el segmento
 *  en el plano.
 *
 *  \note Un segmento viene delimitado por dos puntos \a a y \a b. Si la dirección del segmento es
 *        \a a \f$\rightarrow\f$ \a b, \a a será el punto o límite inferior, y b el punto o límite superior.
 *
 *  \note Llamaremos deslizar al hecho de mover un segmento (o un punto) sobre una recta (es decir, sin salirnos de ella).
 *
 *  \note Llamaremos desplazamiento recto al alejamiento perpendicular de un segmento (o un punto) sobre una recta u otro
 *        segmento. Si se aleja "por encima" del segmento/recta de referencia (según su dirección), el desplazamiento recto
 *        será positivo, y si se aleja "por debajo" del segmento/recta de referencia (según su dirección), el desplazamiento
 *        recto será negativo.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
struct Segmento
{
	/*! \fn Segmento()
	 *  \brief Constructor por defecto de un segmento.
	 *
	 *  \post Construye el segmento \f$ \overline{AB} \f$, siendo \f$ A \f$ el punto \f$(0,0)\f$, y
	 *        \f$B\f$ el punto \f$(1,0) \f$.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento();

	/*! \fn Segmento (const Punto& p, const Punto& q)
	 *  \brief Constructor general(1) de un segmento.
	 *
	 *  \param p Primer punto delimitador del segmento.
	 *  \param q Segundo punto delimitador del segmento.
   *
	 *  \post Construye el segmento \f$\overline{pq}\f$.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento (const Punto& p, const Punto& q);

	/*! \fn Segmento (const Punto& p, float ang, float _l)
	 *  \brief Constructor general(2) de un segmento.
	 *
	 *  \param p Punto delimitador del segmento.
	 *  \param ang Ángulo del segmento respecto al eje x.
	 *  \param _l Longitud del segmento.
   *
	 *  \post Construye el segmento que comienza en \c p y se prolonga una longitud \c _l
	 *        con un ángulo de \c ang radianes respecto al eje x.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento (const Punto& p, float ang, float _l);

	/*! \fn Segmento (float _l, const Punto& p, float ang)
	 *  \brief Constructor general(3) de un segmento.
	 *
	 *  \param _l Longitud del segmento.
	 *  \param p Mediatriz del segmento.
	 *  \param ang Ángulo del segmento respecto al eje \c x.
   *
	 *  \post Construye el segmento de longitud \c _l y mediatriz \c p
	 *        con un ángulo de \c ang radianes respecto al eje \c x.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento (float _l, const Punto& p, float ang);

	/*! \fn Segmento operator+ (const Punto& p) const
	 *  \brief Devuelve un segmento desplazado positivamente por un punto.
	 *
	 *  \param p Punto desplazador.
	 *
	 *  \return Si el segmento actual es \f$ \overline{ab} \f$, devuelve el segmento \f$ \overline{(a+p)(b+p)} \f$.
	 *
	 *  \note El segmento devuelto será paralelo al original, ya que se desplazan ambos extremos del segmento por igual.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento operator+ (const Punto& p) const;

  /*! \fn Segmento operator+ (float k) const
	 *  \brief Devuelve un segmento desplazado perpendicularmente de forma positiva respecto a otro.
	 *
	 *  \param k Escalar desplazador.
	 *
	 *  \return Si el segmento actual es \f$ s_a = \overline{ab} \f$, devuelve el segmento \f$ s_b = \overline{(a+p)(b+p)} \f$,
	 *          siendo \f$ \overline{a(a+p)} \f$ y \f$ \overline{b(b+p)}\f$ segmentos perpendiculares a \f$s_a\f$, de tal forma
	 *          que \f$s_b\f$ se encuentre alejado una distancia \c k sobre \f$s_a\f$.
	 *
	 *  \note El segmento devuelto será paralelo al original ya que se desplazan los dos puntos por igual.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento operator+ (float k) const;

		/*! \fn Segmento operator- (const Punto& p) const
	 *  \brief Devuelve un segmento desplazado negativamente por un punto.
	 *
	 *  \param p Punto desplazador.
	 *
	 *  \return Si el segmento actual es \f$ \overline{ab} \f$, devuelve el segmento \f$ \overline{(a-p)(b-p)} \f$.
	 *
	 *  \note El segmento devuelto será paralelo al original, ya que se desplazan ambos extremos del segmento por igual.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento operator- (const Punto& p) const;

  /*! \fn Segmento operator- (float k) const
	 *  \brief Devuelve un segmento desplazado perpendicularmente de forma negativa respecto a otro.
	 *
	 *  \param k Escalar desplazador.
	 *
	 *  \return Si el segmento actual es \f$ s_a = \overline{ab} \f$, devuelve el segmento \f$ s_b = \overline{(a-p)(b-p)} \f$,
	 *          siendo \f$ \overline{a(a+p)} \f$ y \f$ \overline{b(b+p)}\f$ segmentos perpendiculares a \f$s\f$, de tal forma
	 *          que \f$s_b\f$ se encuentre alejado una distancia \f$k\f$ bajo \f$s_a\f$.
	 *
	 *  \note El segmento devuelto será paralelo al original ya que se desplazan los dos puntos por igual.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento operator- (float k) const;

	/*! \fn Segmento operator- () const
	 *  \brief Devuelve el segmento inverso.
	 *
	 *  \return Si el segmento actual es \f$ \overline{ab} \f$, devuelve el segmento \f$ \overline{ba} \f$.
	 *
	 *  \note El segmento devuelto estará en la misma recta que el original ya que solo se invierte la dirección del segmento.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento operator- () const;

  /*! \fn Segmento operator> (float k) const
	 *  \brief Devuelve un segmento deslizado positivamente.
	 *
	 *  \param k Escalar deslizador.
	 *
	 *  \return Si el segmento actual es \f$ s_a = \overline{ab} \f$, devuelve el segmento \f$ s_b = \overline{cd} \f$,
	 *          tal que las longitudes de \f$\overline{ac}\f$ y \f$\overline{bd}\f$ sean \f$k\f$, y \f$s_b\f$ se sitúe
	 *          en la misma recta que \f$s_a\f$.
	 *
	 *  \note Se usará el término deslizar para indicar todo movimiento realizado dentro de la misma recta en la
	 *        que se sitúa un segmento. Para un movimiento a favor de la dirección de la recta se hablará de
	 *        deslizamiento positivo, y en la dirección contraria, deslizamiento negativo.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento operator> (float k) const;

  /*! \fn Segmento operator< (float k) const
	 *  \brief Devuelve un segmento deslizado negativamente.
	 *
	 *  \param k Escalar deslizador.
	 *
	 *  \return Si el segmento actual es \f$ s_a = \overline{ab} \f$, devuelve el segmento \f$ s_b = \overline{cd} \f$,
	 *          tal que las longitudes de \f$\overline{ac}\f$ y \f$\overline{bd}\f$ sean \f$-k\f$, y \f$s_b\f$ se sitúe
	 *          en la misma recta que \f$s_a\f$.
	 *
	 *  \note Se usará el término deslizar para indicar todo movimiento realizado dentro de la misma recta en la
	 *        que se sitúa un segmento. Para un movimiento a favor de la dirección de la recta se hablará de
	 *        deslizamiento positivo, y en la dirección contraria, deslizamiento negativo.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento operator< (float k) const;

  /*! \fn Segmento operator>> (const Punto& p) const
	 *  \brief Devuelve un segmento colocado sobre un punto.
	 *
	 *  \param p Punto de referencia..
	 *
	 *  \return Si el segmento actual es \f$ s_a = \overline{ab} \f$, devuelve el segmento \f$ s_b = \overline{pq} \f$,
	 *          siendo \f$q\f$ el equivalente a \f$b\f$ si colocaramos al segmento \f$s_a\f$ con \f$a\f$ en \f$p\f$.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento operator>> (const Punto& p) const;

	  /*! \fn bool operator<< (const Punto& p) const
	 *  \brief Comprueba que un punto pertenezca a un segmento.
	 *
	 *  \param p Punto de referencia..
	 *
	 *  \return Si el punto \c p pertenece al segmento, devuelve \c true. Devuelve \c false en caso contrario.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	bool operator<< (const Punto& p) const;

  /*! \fn bool operator<< (const Segmento& s) const
	 *  \brief Comprueba que un segmento pertenezca a otro.
	 *
	 *  \param s Segmento de referencia.
	 *
	 *  \return Si el segmento \c s pertenece al segmento actual, devuelve \c true.
	 *          Devuelve \c false en caso contrario.
	 *
	 *  \note Un segmento pertenece a otro solo si está completamente contenido. En caso de que
	 *        solo una porción de un segmento esté dentro de otro, no se dirá que está contenido.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	bool operator<< (const Segmento& s) const;

  /*! \fn bool operator== (const Segmento& s) const
	 *  \brief Comprueba que dos segmentos sean el mismo.
	 *
	 *  \param s Segmento de referencia.
	 *
	 *  \return Si el segmento \c s es el mismo que el actual, devuelve \c true. Devuelve
	 *          \c false en caso contrario.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	bool operator== (const Segmento& s) const;

  /*! \fn bool operator!= (const Segmento& s) const
	 *  \brief Comprueba que dos segmentos no sean el mismo.
	 *
	 *  \param s Segmento de referencia.
	 *
	 *  \return Si el segmento \c s no es el mismo que el actual, devuelve \c true. Devuelve
	 *          \c false en caso contrario.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	bool operator!= (const Segmento& s) const;

  /*! \fn bool operator|| (const Segmento& s) const
	 *  \brief Comprueba que un segmento sea paralelo a otro.
	 *
	 *  \param s Segmento de referencia.
	 *
	 *  \return Si el segmento \c s es paralelo al segmento actual, devuelve \c true.
	 *          Devuelve \c false en caso contrario.
	 *
	 *  \note Dos segmentos son paralelos síí las rectas donde están contenidas son paralelas.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	bool operator|| (const Segmento& s) const;

	/*! \fn bool operator|| (const Recta& _r) const
	 *  \brief Comprueba que un segmento sea paralelo a una recta.
	 *
	 *  \param _r Recta de referencia.
	 *
	 *  \return Si la recta \c _r es paralela al segmento actual, devuelve \c true.
	 *          Devuelve \c false en caso contrario.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	bool operator|| (const Recta& _r) const;

  /*! \fn bool operator^ (const Segmento& s) const
	 *  \brief Devuelve el ángulo entre dos segmentos.
	 *
	 *  \param s Segmento de referencia.
	 *
	 *  \return Devuelve el ángulo en radianes desde el segmento actual a \c s.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float operator^ (const Segmento& s) const;

	/*! \fn bool operator^ (const Recta& _r) const
	 *  \brief Devuelve el ángulo entre un segmento y una rectas.
	 *
	 *  \param _r Recta de referencia.
	 *
	 *  \return Devuelve el ángulo en radianes desde el segmento actual a \c _r.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float operator^ (const Recta& _r) const;

  /*! \fn Punto operator* (const Segmento& s) const
	 *  \brief Devuelve el punto intersección entre dos segmentos.
	 *
	 *  \param s Segmento de referencia.
	 *
	 *  \return Devuelve el punto intersección (si existe y es único) entre el segmento actual y \f$s\f$.
	 *
	 *  \throw xPnulo Lanzado cuando los dos segmentos no intersecan.
	 *  \throw xScoincidentes Lanzado cuando \c s se solapa al segmento actual total o parcialmente,
	 *         indicando que existen infinitos puntos de intersección, tantos como contenga el segmento
	 *         intersección de ambos.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto operator* (const Segmento& s) const throw (xPnulo, xScoincidentes);

  /*! \fn bool ExisteInter (const Recta& _r) const
	 *  \brief Comprueba que exista intersección entre un segmento y una recta.
	 *
	 *  \param _r Recta de referencia.
	 *
	 *  \return Devuelve \c true si existe intersección entre el segmento actual y la recta.
	 *          Devuelve \c false en caso contrario.
	 *
	 *  \throw xPnulo Lanzado cuando los dos segmentos no intersecan.
	 *  \throw xScoincidentes Lanzado cuando \c s se solapa al segmento actual total o parcialmente,
	 *         indicando que existen infinitos puntos de intersección, tantos como contenga el segmento
	 *         intersección de ambos.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	bool ExisteInter (const Recta& _r) const;

	/*! \fn Segmento SegCoincidente (const Segmento& s)
	 *  \brief Devuelve el segmento coincidente entre dos segmentos superpuesto total o parcialmente.
	 *
	 *  \param s Segmento de referencia.
	 *
	 *  \return Devuelve el segmento intersección entre el segmento actual y \c s.
	 *
	 *  \throw xPnulo Lanzado cuando los dos segmentos no tienen ningún punto en común.
	 *
	 *  \note Si los dos segmentos no están superpuestos, pero intersecan (es decir, que exista un único punto
	 *        en común), devuelve el segmento de longitud 0 \f$\overline{pp}\f$, siendo \f$p\f$ el punto
	 *        intersección entre ambos.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento SegCoincidente (const Segmento& s) throw (xPnulo);

	/*! \fn Punto operator* (const Recta& _r) const
	 *  \brief Devuelve el punto intersección entre un segmento y una recta.
	 *
	 *  \param _r Recta de referencia.
	 *
	 *  \return Devuelve el punto intersección entre el segmento actual y la recta \c _r.
	 *
	 *  \throw xPnulo Lanzado cuando no existe interesección.
	 *  \throw xScoincidentes Lanzado cuando el segmento pertenece a la recta, indicando que existen
	 *         infinitos puntos de intersección, tantos como tenga el segmento.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto operator* (const Recta& _r) const throw (xPnulo, xScoincidentes);

	/*! \fn Segmento operator& (float ang) const
	 *  \brief Devuelve un segmento girado.
	 *
	 *  \param ang Ángulo de giro.
	 *
	 *  \return Devuelve el segmento resultado de girar al segmento actual \c ang radianes.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento operator& (float ang) const;

  /*! \fn Punto Mediatriz() const
	 *  \brief Devuelve la mediatriz de un segmento.
	 *
	 *  \return Devuelve el punto mediatriz del segmento actual.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto Mediatriz() const;

  /*! \fn float DistanciaRect (const Segmento& s) const
	 *  \brief Calcula la distancia recta entre dos segmentos.
	 *
	 *  \return Devuelve la distancia del segmento perpendicular al segmento actual más corto posible, con extremos
	 *          en el segmento actual y \c s respectivamente. Si no existe tal segmento (porque no exista recta
	 *          perpendicular que corte a \c s), devuelve -1.
	 *
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float DistanciaRect (const Segmento& s) const;

  /*! \fn Segmento& operator+= (const Punto& p)
	 *  \brief Desplaza positivamente un segmento según su suma con un punto.
	 *
	 *  \param p Punto desplazador.
	 *
	 *  \post Si el segmento actual es \f$ \overline{ab} \f$, pasará a ser \f$ \overline{(a+p)(b+p)} \f$.
	 *
	 *  \return Devuelve por referencia al segmento actual desplazado.
	 *
	 *  \note El segmento devuelto será paralelo al original, ya que se desplazan ambos extremos del segmento por igual.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento& operator+= (const Punto& p);

  /*! \fn Segmento$ operator+= (float k)
	 *  \brief Desplaza un segmento  perpendicularmente de forma positiva respecto a otro.
	 *
	 *  \param k Escalar desplazador.
	 *
	 *  \post Si el segmento actual es \f$ s_a = \overline{ab} \f$, pasará a ser \f$ s_b = \overline{(a+p)(b+p)} \f$,
	 *          siendo \f$ \overline{a(a+p)} \f$ y \f$ \overline{b(b+p)}\f$ segmentos perpendiculares a \f$s\f$, de tal forma
	 *          que \f$s_b\f$ se encuentre alejado una distancia \f$k\f$ sobre \f$s_a\f$.
	 *
	 *  \return Devuelve por referencia al segmento actual desplazado.
	 *
	 *  \note El segmento devuelto será paralelo al original ya que se desplazan los dos puntos por igual.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento& operator+= (float k);

	/*! \fn Segmento& operator-= (const Punto& p)
	 *  \brief Desplaza negativamente un segmento según su suma con un punto.
	 *
	 *  \param p Punto desplazador.
	 *
	 *  \post Si el segmento actual es \f$ \overline{ab} \f$, pasará a ser \f$ \overline{(a-p)(b-p)} \f$.
	 *
	 *  \return Devuelve por referencia al segmento actual desplazado.
	 *
	 *  \note El segmento devuelto será paralelo al original, ya que se desplazan ambos extremos del segmento por igual.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento& operator-= (const Punto& p);

	/*! \fn Segmento$ operator-= (float k)
	 *  \brief Desplaza un segmento perpendicularmente de forma negativa respecto a otro.
	 *
	 *  \param k Escalar desplazador.
	 *
	 *  \post Si el segmento actual es \f$ s_a = \overline{ab} \f$, pasará a ser \f$ s_b = \overline{(a-p)(b-p)} \f$,
	 *          siendo \f$ \overline{a(a+p)} \f$ y \f$ \overline{b(b+p)}\f$ segmentos perpendiculares a \f$s\f$, de tal forma
	 *          que \f$s_b\f$ se encuentre alejado una distancia \f$k\f$ bajo \f$s_a\f$.
	 *
	 *  \return Devuelve por referencia al segmento actual desplazado.
	 *
	 *  \note El segmento devuelto será paralelo al original ya que se desplazan los dos puntos por igual.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento& operator-= (float k);

  /*! \fn Segmento& operator>= (float k)
	 *  \brief Desliza positivamente un segmento.
	 *
	 *  \param k Escalar deslizador.
	 *
	 *  \post Si el segmento actual es \f$ s_a = \overline{ab} \f$, pasará a ser \f$ s_b = \overline{cd} \f$,
	 *          tal que las longitudes de \f$\overline{ac}\f$ y \f$\overline{bd}\f$ sean \f$k\f$, y \f$s_b\f$ se sitúe
	 *          en la misma recta que \f$s_a\f$.
	 *
	 *  \return Devuelve por referencia al segmento actual deslizado.
	 *
	 *  \note Se usará el término deslizar para indicar todo movimiento realizado dentro de la misma recta en la
	 *        que se sitúa un segmento. Para un movimiento a favor de la dirección de la recta se hablará de
	 *        deslizamiento positivo, y en la dirección contraria, deslizamiento negativo.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento& operator>= (float k);

	/*! \fn Segmento& operator<= (float k)
	 *  \brief Desliza negativamente un segmento.
	 *
	 *  \param k Escalar deslizador.
	 *
	 *  \post Si el segmento actual es \f$ s_a = \overline{ab} \f$, pasará a ser \f$ s_b = \overline{cd} \f$,
	 *          tal que las longitudes de \f$\overline{ac}\f$ y \f$\overline{bd}\f$ sean \f$-k\f$, y \f$s_b\f$ se sitúe
	 *          en la misma recta que \f$s_a\f$.
	 *
	 *  \return Devuelve por referencia al segmento actual deslizado.
	 *
	 *  \note Se usará el término deslizar para indicar todo movimiento realizado dentro de la misma recta en la
	 *        que se sitúa un segmento. Para un movimiento a favor de la dirección de la recta se hablará de
	 *        deslizamiento positivo, y en la dirección contraria, deslizamiento negativo.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento& operator<= (float k);

	/*! \fn Segmento& operator>>= (const Punto& p)
	 *  \brief Coloca a un segmento sobre un punto.
	 *
	 *  \param p Punto de referencia..
	 *
	 *  \post Si el segmento actual es \f$ s_a = \overline{ab} \f$, pasará a ser \f$ s_b = \overline{pq} \f$,
	 *          siendo \f$q\f$ el equivalente a \f$b\f$ al colocar al segmento \f$s_a\f$ con \f$a\f$ en \f$p\f$.
	 *
	 *  \return Devuelve por referencia al segmento actual trasladado.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento& operator>>= (const Punto& p);

	/*! \fn Segmento& operator&= (float ang)
	 *  \brief Gira un segmento.
	 *
	 *  \param ang Ángulo de giro.
	 *
	 *  \post Gira el segmento ractual \c ang radianes.
	 *
	 *  \return Devuelve por referencia al segmento actual girado.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Segmento& operator&= (float ang);

	/*! \var Punto a
	 *  \brief Extremo inferior del segmento.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto a;

  /*! \var Punto b
	 *  \brief Extremo superior del segmento.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto b;

  /*! \var float l
	 *  \brief Longitud del segmento.
	 *
	 *  \note Equivalente a \f$\mid (b-a)\mid\f$.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float l;

  /*! \var Recta r
	 *  \brief Recta que contiene al segmento \f$\overline{ab}\f$.
	 *
	 *  \note El ángulo del segmento viene determinado por el ángulo de \c r.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Recta r;
};


/*! \struct Rectangulo
 *  \brief Tipo rectangulo.
 *
 *  Las funciones adjuntas a la estructura permiten trabajar con el rectangulo
 *  en el plano.
 *
 *  \note Un rectángulo es la figura geométrica de cuatro vértices, que emparejadas forman cuatro aristas,
 *        de modo que las aristas sean paralelas dos a dos, y todos los ángulos interiores sean rectos.
 *
 *  \note Un rectángulo siempre tendrá un vértice de referencia u orientación (al que llamaremos VR).
 *        Por consiguiente, ese vértice será el vértice superior izquierdo del rectángulo. A partir de ese vértice,
 *        y leyendo en sentido horario, aparecerán los vértices superior derecho, inferior derecho e inferior izquierdo.
 *
 *  \note Un rectángulo tendrá como arista de referencia (al que llamaremos AR) al formado por el segmento de
 *        límite inferior VR y de límite superior a su vértice superior derecho. El ángulo o inclinación del
 *        rectángulo será el ángulo de AR.
 *
 *  \note AR también será llamado frente del rectángulo. Al lado opuesto a AR se le llamará base del rectángulo.
 *        A la arista formada desde el vértice superior derecho jasta el inferior derecho será el lado derecho
 *        del rectángulo; y la arista formada desde vértice inferior izquierdo hasta el vértice superior izquierdo
 *        será el vértice izquierdo del rectángulo.
 *
 *  \note El ancho del rectángulo es la longitud de AR, y la altura del rectángulo es la longitud del lado
 *        izquierdo, que es igual al del lado derecho, e igual a la distancia entre la base y el frente.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
struct Rectangulo
{
  /*! \fn Rectangulo()
   *  \brief Constructor predeterminado de un rectángulo.
   *
   *  \post Construye un rectangulo de altura y ancho 1, de VR (0, 1) y ángulo 0.
   *
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Rectangulo();

  /*! \fn Rectangulo (const Punto& p, float _w, float _h, float _ang)
   *  \brief Constructor general(1) de un rectángulo.
   *
   *  \param p VR.
   *  \param _w Ancho del rectángulo
   *  \param _h Altura del rectángulo.
   *  \param _ang Ángulo del rectángulo.
   *
   *  \post Construye al rectángulo de VR \c p, ancho \c _w, algura \c _h, y ángulo \c _ang.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Rectangulo (const Punto& p, float _w, float _h, float _ang);

  /*! \fn Rectangulo operator+ (float k) const
   *  \brief Devuelve un rectángulo desplazado positivamente y de forma recta respecto a otro.
   *
   *  \param k Escalar desplazador.
   *
   *  \return Devuelve el rectángulo resultado de desplazar positivamente al rectángulo actual una distancia \c k.
   *
   *  \note Desplazar un rectángulo es equivalente a desplazar su AR, trayéndose consigo
   *        al resto del rectángulo; es decir, que ni el ancho, ni el alto, ni el ángulo
   *        del rectángulo cambia, solo la posición global del mismo.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Rectangulo operator+ (float k) const;

  /*! \fn Rectangulo operator& (float _ang) const
   *  \brief Devuelve un rectángulo girado(1) respecto a otro.
   *
   *  \param _ang Ángulo de giro.
   *
   *  \return Devuelve al rectángulo resultado de girar el rectángulo \c _ang radianes.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Rectangulo operator& (float _ang) const;

  /*! \fn Rectangulo operator^ (float _ang) const
   *  \brief Devuelve un rectángulo girado(2) respecto a otro.
   *
   *  \param _ang Ángulo de giro.
   *
   *  \return Devuelve al rectángulo resultado de girar el rectángulo \c _ang radianes, pero considerando
   *          al vértice superior derecho como eje del giro.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Rectangulo operator^ (float _ang) const;

  /*! \fn Rectangulo operator~ () const
   *  \brief Devuelve un rectángulo girado.
   *
   *  \return Devuelve al rectángulo resultado de girar al rectangulo actual sobre sí mismo \f$\frac{\pi}{2}\f$
   *          radianes en sentido horario, es decir, que el frente del rectángulo de salida es el lado derecho
   *          del rectángulo original.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Rectangulo operator~ () const;

  /*! \fn bool operator<< (const Punto& p) const
   *  \brief Comprueba que un punto pertenezca a un rectángulo.
   *
   *  \param p Punto de referencia.
   *
   *  \return Devuelve \c true si \c p está dentro del rectángulo actual. Devuelve \c false en caso contrario.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	bool operator<< (const Punto& p) const;

  /*! \fn bool operator<< (const Rectangulo& R) const
   *  \brief Comprueba que un rectangulo pertenezca a otro rectángulo.
   *
   *  \param R Rectángulo de referencia.
   *
   *  \return Devuelve \c true si \c R está dentro del rectángulo actual. Devuelve \c false en caso contrario.
   *
   *  \note Un rectángulo \a A está dentro de otro \a B síí \a A está \e completamente \e incluido en \a B,
   *        es decir, que los cuatro vértices de \a B estén en el área formada por los cuatro vértices de \a A.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	bool operator<< (const Rectangulo& R) const;

  /*! \fn bool operator* (const Rectangulo& R) const
   *  \brief Comprueba si dos rectángulos tienen aristas que intersecan.
   *
   *  \param R Rectángulo de referencia.
   *
   *  \return Devuelve \c true si alguna arista de \c R interseca con alguna arista del rectángulo actual.
   *          Devuelve \c false en caso contrario.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	bool operator* (const Rectangulo& R) const;

  /*! \fn Rectangulo Envoltura() const
   *  \brief Devuelve el rectángulo envoltura.
   *
   *  \return Devuelve el rectángulo envoltura del rectángulo actual.
   *
   *  \note Se define rectángulo envoltura al rectángulo con AR paralelo al eje \c
   *        de área mínima que contiene al objeto actual.
   *
   *  \note Evidentemente, el rectángulo envoltura tendrá 0 radianes de inclinación.
   *
   *  \sa Cuadrilatero
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Rectangulo Envoltura() const;

	/*! \fn Rectangulo Ensanchar(float ens) const
	 *  \brief Devuelve el rectángulo ensanche.
	 *
	 *  \param ens Distancia de ensanche del rectángulo.
	 *
	 *  \return Devuelve un rectángulo ensanchado 'ens' cantidad.
	 *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Rectangulo Ensanchar(float ens) const;

  /*! \fn Rectangulo Centro() const
   *  \brief Devuelve el centro del rectángulo.
   *
   *  \return Devuelve el centro del rectángulo actual.
   *
   *  \sa Cuadrilatero
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Punto Centro() const;

  /*! \fn Rectangulo& operator+= (float k)
   *  \brief Desplaza positivamente y de forma recta un rectángulo.
   *
   *  \param k Escalar desplazador.
   *
   *  \post Desplaza positivamente al rectángulo actual una distancia \c k.
   *
   *  \return Devuelve por referencia el rectángulo desplazado actual.
   *
   *  \note Desplazar un rectángulo es equivalente a desplazar su AR, trayéndose consigo
   *        al resto del rectángulo; es decir, que ni el ancho, ni el alto, ni el ángulo
   *        del rectángulo cambia, solo la posición global del mismo.
   *
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Rectangulo& operator+= (float k);

	/*! \fn Rectangulo& operator&= (float _ang)
   *  \brief Gira(1) un rectángulo.
   *
   *  \param _ang Ángulo de giro.
   *
   *  \post Gira al rectángulo \c _ang radianes.
   *
   *  \return Devuelve por referencia el rectángulo girado actual.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Rectangulo& operator&= (float _ang);

	/*! \fn Rectangulo operator^= (float _ang)
   *  \brief Gira(2) un rectángulo.
   *
   *  \param _ang Ángulo de giro.
   *
   *  \post Girar al rectángulo ángulo actual \c _ang radianes, pero considerando
   *          al vértice superior derecho como eje del giro.
   *
   *  \return Devuelve por referencia al rectángulo girado actual.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Rectangulo& operator^= (float _ang);

	/*! \fn Rectangulo& operator>>= (const Punto& p)
   *  \brief Reposiciona un rectángulo a un nuevo punto.
   *
   *  \param p Punto de referencia..
   *
   *  \post Traslada al rectángulo a una nueva posición de modo que \c p sea su nuevo VR.
   *
   *  \return Devuelve por referencia al rectángulo trasladado actual.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Rectangulo& operator>>= (const Punto& p);

  /*! \var Punto a
	 *  \brief Esquina superior izquierda del rectángulo.
	 *
	 *  \note Éste punto es el vértice de referencia (VR) del rectángulo.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto a;

	/*! \var Punto b
	 *  \brief Esquina superior derecha del rectángulo.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
  Punto b;

  /*! \var Punto c
	 *  \brief Esquina inferior derecha del rectángulo.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
  Punto c;

  /*! \var Punto d
	 *  \brief Esquina inferior izquierda del rectángulo.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
  Punto d;

  /*! \var float w
	 *  \brief Ancho del rectángulo
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float w;

	/*! \var float h
	 *  \brief Altura del rectángulo
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float h;

	/*! \var float ang
	 *  \brief Ángulo del rectángulo.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float ang;
};


/*! \struct Cuadrilatero
 *  \brief Tipo rectangulo
 *
 *  Las funciones adjuntas a la estructura permiten trabajar con el cuadrilatero
 *  (cualquier espacio con cuatro vértices) en el plano.
 *
 *  \note A diferencia del rectángulo, un cuadrilatero tiene cuatro vértices libres, ésto es,
 *        que no hay restricciones sobre la medida de los ángulos internos ni la relación entre
 *        aristas.
 *
 *  \note El vocabulario usado para nombrar las partes del rectángulo será aplicable para los cuadrilateros.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
struct Cuadrilatero
{
  /*! \fn Cuadrilatero()
   *  \brief Constructor predeterminado de un cuadrilatero.
   *
   *  \post Construye un cuadrilatero de altura y ancho 1, de VR (0, 1) y ángulo 0.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Cuadrilatero();

  /*! \fn Cuadrilatero (const Punto& _a, const Punto& _b, const Punto& _c, const Punto& _d)
   *  \brief Constructor general de un cuadrilatero.
   *
   *  \param _a Esquina superior izquierda (VR y extremo inferior de AR).
   *  \param _b Esquina superior derecha (extremo superior de AR).
   *  \param _c Esquina inferior derecha.
   *  \param _d Esquina inferior izquierda.
   *
   *  \post Construye un cuadrilatero de vértices \c _a, \c _b, \c _c, \c _d. El vértice \c _a será VR, y
   *        la arista \f$\overline{\_a\_b}\f$ será AR.
   *
   *  \throw xCDnulo Lanzado si los cuatro puntos no forman un cuadrilatero válido.
   *
   *  \note Cuatro puntos \f$a,b,c,d\f$ forman un cuadrilatero válido síí las aristas \f$\overline{ab}, \overline{bc},
   *        \overline{cd}, \overline{da}\f$ intersecan de la siguiente forma:
   *        \li \f$\overline{ab}, \overline{bc}\f$ intersecan únicamente en el punto \c b.
   *        \li \f$\overline{bc}, \overline{cd}\f$ intersecan únicamente en el punto \c c.
   *        \li \f$\overline{cd}, \overline{da}\f$ intersecan únicamente en el punto \c d.
   *        \li \f$\overline{da}, \overline{ab}\f$ intersecan únicamente en el punto \c a.
   *        Si existe alguna otra intersección entre éstas cuatro aristas, el cuadrilatero no será válido.
   *
   *  \note Si dos vértices son iguales, por ejemplo \f$a=b\f$, la arista \f$overline{da}\f$ intersecará con la arista
   *        \f$\overline{bc}\f$, en el punto \f$a=b\f$, lo cual rompe la definición de cuadrilatero válido. Por tanto,
   *        una condición consecuente es que los cuatro vértices sean distintos entre sí.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Cuadrilatero (const Punto& _a, const Punto& _b, const Punto& _c, const Punto& _d) throw (xCDnulo);

  /*! \fn bool operator<< (const Punto& p) const
   *  \brief Comprueba que un punto pertenezca a un cuadrilatero.
   *
   *  \param p Punto de referencia.
   *
   *  \return Devuelve \c true si \c p se encuentra dentro del área que delimita el cuadrilatero
   *          actual. Devuelve \c false en caso contrario.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	bool operator<< (const Punto& p) const;

  /*! \var Punto a
	 *  \brief Esquina superior izquierda (VR y extremo inferior de AR) del cuadrilatero.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto a;

	/*! \var Punto b
	 *  \brief Esquina superior derecha (extremo superior de AR) del cuadrilatero.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto b;

	/*! \var Punto c
	 *  \brief Esquina inferior derecha del cuadrilatero.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto c;

	/*! \var Punto d
	 *  \brief Esquina inferior izquierda del cuadrilatero.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto d;
};


/*! \struct Circunferencia
 *  \brief Tipo circunferencia.
 *
 *  Las funciones adjuntas a la estructura permiten trabajar con la circunferencia
 *  en el plano.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
struct Circunferencia
{
  /*! \fn Circunferencia()
   *  \brief Constructor predeterminado de una circunferencia.
   *
   *  \post Construye una circunferencia de origen (0,0) y radio 1.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Circunferencia();

  /*! \fn Circunferencia (const Punto _o, float _r)
   *  \brief Constructor general de una circunferencia.
   *
   *  \param _o Origen de la circunferencia.
   *  \param _r Radio de la circunferencia.
   *
   *  \post Construye una circunferencia de origen \c _o y radio \c _r.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Circunferencia (const Punto _o, float _r);

  /*! \fn Segmento operator* (const Recta& s) const
   *  \brief Intersección de una circunferencia con una recta.
   *
   *  \param s Recta de referencia.
   *
   *  \return Devuelve el segmento intersección de la recta \c s con la circunferencia actual.
   *
   *  \throw xPnulo Lanzado si no existe intersección entre la recta y la circunferencia.
   *
   *  \note Aunque la intersección entre una circunferencia y una recta sean dos puntos individuales (o uno
   *        si la recta es tangente), se devolverá el segmento formado por ambos puntos como extremos.
   *
   *  \note Si la recta es tangente, el segmento devuelto será el segmento de longitud 0 \f$\overline{xx}\f$,
   *        siendo \c x el punto intersección.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Segmento operator* (const Recta& s) const throw (xPnulo);

  /*! \fn Segmento operator* (const Segmento& s) const
   *  \brief Intersección de una circunferencia con un segmento.
   *
   *  \param s Segmento de referencia.
   *
   *  \return Devuelve el segmento intersección del segmento \c s con la circunferencia actual.
   *
   *  \throw xPnulo Lanzado si no existe intersección entre el segmento y la circunferencia.
   *
   *  \note Aunque la intersección entre una circunferencia y un segmento sean uno o dos puntos
   *        individuales, se devolverá el segmento formado por ambos puntos como extremos.
   *
   *  \note Si el segmento es tangente, el segmento devuelto será el segmento de longitud 0 \f$\overline{xx}\f$,
   *        siendo \c x el punto intersección.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Segmento operator* (const Segmento& s) const throw (xPnulo);

  /*! \fn Segmento operator* (const Circunferencia& c) const
   *  \brief Intersección de dos circunferencias.
   *
   *  \param c Circunferencia de referencia.
   *
   *  \return Devuelve el segmento intersección de la circunferencia \c c con la circunferencia actual.
   *
   *  \throw xSnulo Lanzado si no existe intersección entre ambas circunferencias.
   *
   *  \note Aunque la intersección entre dos circunferencias sean dos puntos individuales (o uno
   *        si las circunferencias son tangentes), se devolverá el segmento formado por ambos puntos como extremos.
   *
   *  \note Si la circunferencia es tangente, el segmento devuelto será el segmento de longitud 0 \f$\overline{xx}\f$,
   *        siendo \c x el punto intersección.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Segmento operator* (const Circunferencia& c) const throw (xSnulo);

  /*! \fn bool operator<< (const Punto& p) const
   *  \brief Comprueba que un punto pertenezca a una circunferencia.
   *
   *  \param p Punto de referencia.
   *
   *  \return Devuelve \c true si el punto pertenece al área delimitada por la circunferencia.
   *          Devuelve \c false en caso contrario.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	bool operator<< (const Punto& p) const;

	/*! \fn bool operator<< (const Segmento& s) const
   *  \brief Comprueba que un segmento pertenezca a una circunferencia.
   *
   *  \param s Segmento de referencia.
   *
   *  \return Devuelve \c true si el segmento pertenece a laa circunferencia actual.
   *          Devuelve \c false en caso contrario.
   *
   *  \note Un segmento pertenecerá a una circunferencia síí está \e completamente \e incluida en el área
   *        que ésta delimita. Si solo está parcialmente incluida (es decir, que exista intersección),
   *        devolverá \c false.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	bool operator<< (const Segmento& s) const;

  /*! \var Punto o
	 *  \brief Origen de la circunferencia.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto o;

	/*! \var float r
	 *  \brief Radio de la circunferencia.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float r;
};


/*! \struct Semidisco
 *  \brief Tipo semidisco.
 *
 *  Las funciones adjuntas a la estructura permiten trabajar con el semidisco
 *  (semicircunferencia) en el plano.
 *
 *  \note Un semidisco posee dos ángulos, el inferior y el superior, y dos segmentos, el inferior y el superior:
 *        \li Ambos segmentos tendrán a su punto inferior en común, y una misma longitud.
 *        \li El punto inferior en común de ambos segmentos será el origen del semidisco.
 *        \li La longitud en común de ambos segmentos será el radio del semidisco.
 *        \li El ángulo inferior (ai) es el ángulo del segmento inferior.
 *        \li El ángulo superior (as) es el ángulo del segmento superior.
 *        \li El ángulo de un semidisco es el ángulo interior formado por ambos segmentos (as-ai).
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
struct Semidisco
{
  /*! \fn Semidisco()
   *  \brief Constructor predeterminado de un semidisco.
   *
   *  \post Construye un semidisco de origen (0,0), radio 1 y ángulo \f$\frac{\pi}{2}\f$
   *        (el ángulo inferior será 0).
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Semidisco();

  /*! \fn Semidisco (const Punto& _o, float _ang1, float _ang2, float _r)
   *  \brief Constructor general de un semidisco.
   *
   *  \param _o Origen del semidisco.
   *  \param _ang1 Ángulo inferior del semidisco.
   *  \param _ang2 Ángulo superior del semidisco.
   *  \param _r Radio del semidisco.
   *
   *  \pre \f$ {}_{}r \geq 0.\f$
   *  \post Construye el semidisco de origen \c _o, radio _r y ángulo \f$_ang2 - ang1\f$
   *        (el ángulo inferior será \c _ang1).
   *
   *  \throw xSCilegal Lanzado si \c _r < 0.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Semidisco (const Punto& _o, float _ang1, float _ang2, float _r) throw (xSCilegal);

	/*! \fn bool operator<< (const Punto& p) const
   *  \brief Comprueba que un punto pertenezca a una semidisco.
   *
   *  \param p Punto de referencia.
   *
   *  \return Devuelve \c true si \c p está en el área delimitada por el semidisco actual.
   *          Devuelve \c false en caso contrario.
   *
   *  \throw xSCilegal Lanzado si \c _r < 0.
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	bool operator<< (const Punto& p) const;

	/*! \fn Rectangulo Envoltura() const
   *  \brief Devuelve el rectángulo envoltura.
   *
   *  \return Devuelve el rectángulo envoltura del semidisco actual.
   *
   *  \note Se define rectángulo envoltura al rectángulo con AR paralelo al eje \c
   *        de área mínima que contiene al objeto actual.
   *
   *  \note Evidentemente, el rectángulo envoltura tendrá 0 radianes de inclinación.
   *
   *  \sa Cuadrilatero
   *
   *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
   *  \date 11/2009
   *  \version 1
   *  \since 1
   */
	Rectangulo Envoltura() const;

  /*! \var Punto o
	 *  \brief Origen del semidisco.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	Punto o;

	/*! \var float ang1
	 *  \brief Ángulo inferior del semidisco.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float ang1;

	/*! \var float ang2
	 *  \brief Ángulo superior del semidisco.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
  float ang2;

  /*! \var float r
	 *  \brief Radio del semidisco.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 11/2009
	 *  \version 1
	 *  \since 1
	 */
	float r;
};


/*! \fn unsigned NumAzar (unsigned a, unsigned b)
 *  \brief Devuelve un número al azar (1).
 *
 *  \param a Primer delimitador del intervalo.
 *  \param b Segundo delimitador del intervalo.
 *
 *  \return Devuelve un número pseudoaleatorio en el intervalo \f$[a,b] \subset N \f$.
 *
 *  \note Si b < a, [a,b] será equivalente a [b,a].
 *  \note Se calcularán números pseudoaleatorios con la semilla predeterminada de cstdlib, a no ser
 *        que el usuario la cambie por los métodos tradicionales.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
unsigned NumAzar (unsigned a, unsigned b);


/*! \fn unsigned NumAzar (float a, float b)
 *  \brief Devuelve un número al azar (1).
 *
 *  \param a Primer delimitador del intervalo.
 *  \param b Segundo delimitador del intervalo.
 *
 *  \return Devuelve un número pseudoaleatorio en el intervalo \f$[a,b] \subset R \f$.
 *
 *  \note Si b < a, [a,b] será equivalente a [b,a].
 *  \note Se calcularán números pseudoaleatorios con la semilla predeterminada de cstdlib, a no ser
 *        que el usuario la cambie por los métodos tradicionales.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
unsigned NumAzar (float a, float b);


/*! \fn float Abs (float x)
 *  \brief Devuelve el valor absoluto de un número.
 *
 *  \param x Real de referencia.
 *
 *  \return Devuelve el valor absoluto de \c x.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
float Abs (float x);


/*! \fn float Min (float a, float b)
 *  \brief Devuelve el mínimo de dos números reales.
 *
 *  \param a Primer real de referencia.
 *  \param b Segundo real de referencia.
 *
 *  \return Devuelve el mínimo (con un redondeo máximo de 3 cifras decimales) de \c a y \c b.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
float Min (float a, float b);


/*! \fn float Max (float a, float b)
 *  \brief Devuelve el máximo de dos números reales.
 *
 *  \param a Primer real de referencia.
 *  \param b Segundo real de referencia.
 *
 *  \return Devuelve el máximo (con un redondeo máximo de 3 cifras decimales) de \c a y \c b.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
float Max (float a, float b);


/*! \fn float AngC (float grad)
 *  \brief Devuelve un ángulo válido.
 *
 *  \param grad Ángulo de referencia.
 *
 *  \return Devuelve el valor equivalente a \c grad en el intervalo \f$[0, 2\pi]\f$.
 *
 *  \note Ésta función es útil en los casos en que se trabaje con ángulos aditivos, y no se
 *        controle si un ángulo \e desborda o no de una circunferencia pero tampoco interese tratar
 *        con valores ajenos a ellos.
 *
 *  \note Ejemplo: \f[AngC(\frac{5\pi}{2})\rightarrow\frac{\pi}{2}\f]\f[(\equiv AngC(450^o)\rightarrow 90^o)\f].
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
float AngC (float grad);


/*! \fn float AngGR (float grad)
 *  \brief Transforma grados en radianes.
 *
 *  \param grad Ángulo de referencia en grados.
 *
 *  \return Devuelve el valor equivalente a \c grad en radianes.
 *
 *  \note Ejemplo: \f[AngGR(\frac{5\pi}{2})\rightarrow 450\f].
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
float AngGR (float grad);


/*! \fn float AngRG (float rad)
 *  \brief Transforma radianes en grados.
 *
 *  \param rad Ángulo de referencia en radianes.
 *
 *  \return Devuelve el valor equivalente a \c rad en grados.
 *
 *  \note Ejemplo: \f[AngRG(450)\rightarrow \frac{5\pi}{2}\f].
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
float AngRG (float rad);


/*! \fn bool Comp (float a, float b)
 *  \brief Comprueba que dos reales sean el mismo.
 *
 *  \param a Primer real de referencia.
 *  \param b Segundo real de referencia.
 *
 *  \return Devuelve \c true si los dos reales son el mismo número.
 *          Devuelve \c false en caso contrario.
 *
 *  \note Solo se considerarán, como máximo, los tres primeros decimales.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
bool Comp (float a, float b);


/*! \fn bool Cuad (unsigned short c, float r)
 *  \brief Comprueba que un número real esté en un cuadrante.
 *
 *  \param c Cuadrante de pertenencia.
 *  \param p Punto de referencia.
 *
 *  \pre \f$c\in[1,4]\f$.
 *
 *  \return Devuelve \c true si el punto \c p está en el cuadrante \c c.
 *          Devuelve \c false en caso contrario.
 *
 *  \throw xCilegal Lanzado cuando \c c no es ningún válor válido como cuadrante.
 *
 *  \note Los ejes \e x e \e y dividen el espacio en cuatro cuadrantes:
 *        \li El cuadrante 1 es el formado por los puntos \f$(x,y)\in R^2 : x\geq0, y\geq0\f$.
 *        \li El cuadrante 2 es el formado por los puntos \f$(x,y)\in R^2 : x\leq0, y\geq0\f$.
 *        \li El cuadrante 3 es el formado por los puntos \f$(x,y)\in R^2 : x\leq0, y\leq0\f$.
 *        \li El cuadrante 4 es el formado por los puntos \f$(x,y)\in R^2 : x\geq0, y\leq0\f$.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
bool Cuad (unsigned short c, Punto p) throw (xCilegal);


/*! \fn bool Menor (float a, float b)
 *  \brief Comprueba que un número sea menor que otro.
 *
 *  \param a Primero real de referencia.
 *  \param b Segundo real de referencia.
 *
 *  \return Devuelve \c true si \c a es menor que \c b.
 *          Devuelve \c false en caso contrario.
 *
 *  \note Solo se considerarán, como máximo, las 3 primeras cifras decimales.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
bool Menor (float a, float b);


/*! \fn bool Mayor (float a, float b)
 *  \brief Comprueba que un número sea mayor que otro.
 *
 *  \param a Primero real de referencia.
 *  \param b Segundo real de referencia.
 *
 *  \return Devuelve \c true si \c a es mayor que \c b.
 *          Devuelve \c false en caso contrario.
 *
 *  \note Solo se considerarán, como máximo, las 3 primeras cifras decimales.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
bool Mayor (float a, float b);


/*! \fn bool Intervalo (float a, float b, float p)
 *  \brief Comprueba que un número pertenezca a un intervalo
 *
 *  \param a Primer límite real del intervalo.
 *  \param b Segundo límite real del intervalo.
 *  \param b Número real de referencia.
 *
 *  \return Devuelve \c true si \f$p \in [a, b]\f$.
 *
 *  \note Si b < a, [b, a] es equivalente a [a, b].
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
bool Intervalo (float a, float b, float p);


/*! \fn unsigned ElemXMatriz (unsigned cols, unsigned n)
 *  \brief Devuelve la columna de un elemento en una matriz.
 *
 *  \param cols Número de columnas de una matriz.
 *  \param n Índice del elemento de la matriz.
 *
 *  \return Devuelve la columna correspondiente a \c n en una matriz de \c cols columnas.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
unsigned ElemXMatriz (unsigned cols, unsigned n);


/*! \fn unsigned ElemYMatriz (unsigned cols, unsigned n)
 *  \brief Devuelve la fila de un elemento en una matriz.
 *
 *  \param cols Número de columnas de una matriz.
 *  \param n Índice del elemento de la matriz.
 *
 *  \return Devuelve la fila correspondiente a \c n en una matriz de \c cols columnas.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
unsigned ElemYMatriz (unsigned cols, unsigned n);


/*! \fn float Arco (float r, float ang)
 *  \brief Devuelve la longitud de un arco.
 *
 *  \param r Radio del semidisco de referencia.
 *  \param n Ángulo del semidisco de referencia.
 *
 *  \return Devuelve la longitud del arco de un semidisco de radio \c r y ángulo \c ang.
 *
 *  \sa Semidisco
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
float Arco (float r, float ang);


/*! \fn float Barrido (float r, float l)
 *  \brief Devuelve el barrido de un arco.
 *
 *  \param r Radio del semidisco de referencia.
 *  \param n Longitud del arco del semidisco de referencia.
 *
 *  \return Devuelve el ángulo de un semidisco de arco \c l y radio \c r (barrido del arco).
 *
 *  \sa Semidisco
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
float Barrido (float r, float l);


/*! \fn void Intercambiar (float& a, float& b)
 *  \brief Intercambia dos valores (1)
 *
 *  \param a Referencia de la primera variable.
 *  \param b Referencia de la segunda variable.
 *
 *  \post Inserta el valor de \c a en \c b, y el de \c b en \c a.
 *
 *  \note Versión sobrecargarda de la función \c Intercambiar para flotantes.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
void Intercambiar (float& a, float& b);


/*! \fn void Intercambiar (unsigned& a, unsigned& b)
 *  \brief Intercambia dos valores (2)
 *
 *  \param a Referencia de la primera variable.
 *  \param b Referencia de la segunda variable.
 *
 *  \post Inserta el valor de \c a en \c b, y el de \c b en \c a.
 *
 *  \note Versión sobrecargarda de la función \c Intercambiar para enteros sin signo.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 11/2009
 *  \version 1
 *  \since 1
 */
void Intercambiar (unsigned& a, unsigned& b);

#endif
