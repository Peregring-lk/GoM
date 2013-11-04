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

#include "Matematicas.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

const float RAD(3.141592653 / 180);          // El valor en radianes de un grado.

// Punto::Punto
/*************************************/
Punto::Punto() : x(0), y(0)
{
	mod = 0;
}

// Punto::Punto
/*************************************/
Punto::Punto (float x, float y) : x(x), y(y)
{
	mod = sqrt (pow (x, 2) + pow (y, 2));
}

// Punto::operator+
/*************************************/
Punto Punto::operator+ (const Punto& p) const
{
	return (Punto(*this) += p);
}

// Punto::operator+
/*************************************/
Punto Punto::operator+ (float k) const
{
	return (Punto(*this) += k);
}

// Punto::operator-
/*************************************/
Punto Punto::operator- (const Punto& p) const
{
	return (Punto(*this) -= p);
}

// Punto::operator-
/*************************************/
Punto Punto::operator- (float k) const
{
	return (Punto(*this) -= k);
}

// Punto::operator*
/*************************************/
Punto Punto::operator* (float k) const
{
	return (Punto(*this) *= k);
}

// Punto::operator*
/*************************************/
float Punto::operator* (const Punto& p) const
{
	return (x * p.x + y * p.y);
}

// Punto::operator==
/*************************************/
bool Punto::operator== (const Punto& p) const
{
	return (Comp (x, p.x) && Comp (y, p.y));
}

// Punto::operator!=
/*************************************/
bool Punto::operator!= (const Punto& p) const
{
	return (!Comp (x, p.x) || !Comp (y, p.y));
}

// Punto::Sentido
/*************************************/
bool Punto::Sentido (const Punto& p, const Punto& q) const
{
// Construcción matemática compleja.
	float aux = (*this - q) * Punto (p.y - q.y, q.x - p.x);

	return (!Mayor(aux, 0));
}

// Punto::operator+=
/*************************************/
Punto& Punto::operator+= (const Punto& p)
{
	*this = Punto (x += p.x, y += p.y);

	return (*this);
}

// Punto::operator+=
/*************************************/
Punto& Punto::operator+= (float k)
{
	*this = Punto (x += k, y += k);

	return (*this);
}

// Punto::operator-=
/*************************************/
Punto& Punto::operator-= (const Punto& p)
{
	*this = Punto (x -= p.x, y -= p.y);

	return (*this);
}

// Punto::operator-=
/*************************************/
Punto& Punto::operator-= (float k)
{
	*this = Punto (x -= k, y -= k);

	return (*this);
}

// Punto::operator*=
/*************************************/
Punto& Punto::operator*= (float k)
{
	*this = Punto (x *= k, y *= k);

	return (*this);
}

// Recta::Recta
/*************************************/
// Todas las rectas (más bien hiperplanos), tienen la forma ax + by = c.
// Por simplificación, 'a' valdrá siempre 0 o 1. En el segundo caso, b = 1/-m, (m es la pendiente de la recta).
Recta::Recta () : a(0), b(1), c(0)
{
	ang = 0;
}

// Recta::Recta
/*************************************/
Recta::Recta (const Punto& p, const Punto& q)
{
// Para evitar dividir entre 0.
	if (!Comp (p.y, q.y))
	{
		float m = (q.y - p.y) / (q.x - p.x);

		a = 1;
		b = -1 / m;
		c = p.x + p.y * b;

 // Si la recta tiene la forma x = p.x (equivalente a x = q.x).
		if (!b)
			if (Menor (p.y, q.y))
				ang = AngGR (90);
			else
// En caso de que la recta deba dirigirse en sentido negativo respecto al eje y.
				ang = AngGR (270);
		else
		{
// 1 / -b es la pendiente 'm' de la recta, y se cumple que m = tan (ang).
			ang = atan (m);

			if (Menor (ang, 0))
				if (Mayor (q.y, p.y))
					ang += AngGR (180);
				else
					ang += AngGR (360);
			else if (Mayor (ang, 0) && Menor (q.y, p.y))
				ang += AngGR (180);
	}}
	else
	{
// Ecuación y = p.y (equivalente a y = q.y).
		a = 0;
		b = 1;
		c = p.y;
		ang = 0;

// En caso de que la recta deba dirigirse en sentido negativo respecto al eje x.
		if (Menor (q.x, p.x))
			ang = AngGR (180);
}}

// Recta::Recta
/*************************************/
Recta::Recta (const Punto& p, float _ang) : ang(AngC(_ang))
{
// Si la recta debe tener la forma y = p.y.
	if (Comp (ang, 0) || Comp (ang, AngGR (180)))
	{
		a = 0;
		b = 1;
		c = p.y;
	}
// Si la recta debe tener la forma x = p.x.
	else if (Comp (ang, AngGR (90)) || Comp (ang, AngGR (270)))
	{
		a = 1;
		b = 0;
		c = p.x;
	}
	else
	{
		a = 1;
		b = -1 / tan (ang);
		c = p.x + b * p.y;
}}

// Recta::operator+
/*************************************/
Recta Recta::operator+ (float k) const
{
	return (Recta (*this) += k);
}

// Recta::operator-
/*************************************/
Recta Recta::operator- (float k) const
{
	return (Recta (*this) -= k);
}

// Recta::operator<
/*************************************/
Recta Recta::operator< (float k) const
{
	return (Recta (*this) <= k);
}

// Recta::operator>
/*************************************/
Recta Recta::operator> (float k) const
{
	return (Recta (*this) >= k);
}

// Recta::operator>>
/*************************************/
Recta Recta::operator>> (const Punto& p) const
{
	return (Recta (p, ang));
}

// Recta::operator*
/*************************************/
Punto Recta::operator* (const Recta& r) const throw (xPnulo, xRiguales)
{
	if (*this == r)
		throw (xRiguales());
	if (*this || r)
		throw (xPnulo());

// Se buscan soluciones del sistema de ecuaciones:
//   a  * x +  b  * y =  c   |
//  r.a * x + r.b * y = r.c  |

	if (Comp (a, 0))
		return (Punto (r.c - r.b * c, c));
	if (Comp (r.a, 0))
		return (Punto (c - b * r.c, r.c));

	Punto p;

	p.y = (r.c - c) / (r.b - b);
	p.x = c - b * p.y;

	return (p);
}

// Recta::operator<<
/*************************************/
bool Recta::operator<< (const Punto& p) const
{
	return (Comp (p.x * a + p.y * b, c));
}

// Recta::operator==
/*************************************/
bool Recta::operator== (const Recta& r) const
{
	return ((*this || r) && Comp (c, r.c));
}

// Recta::operator!=
/*************************************/
bool Recta::operator!= (const Recta& r) const
{
	return (!(*this == r));
}

// Recta::operator||
/*************************************/
bool Recta::operator|| (const Recta& r) const
{
	return (Comp (ang, r.ang) || Comp (Abs (ang - r.ang), AngGR (180)));
}

// Recta::operator^
/*************************************/
float Recta::operator^ (const Recta& r) const
{
	return (AngC (r.ang - ang));
}

// Recta::MinAng
/*************************************/
float Recta::AngMin (const Recta& r) const
{
	float angAux = *this ^ r;

	return (Min (angAux, AngC (AngGR (180) - angAux)));
}

// Recta::ExtremoSegmento
/*************************************/
Punto Recta::ExtremoSegmento (const Punto& p, float l) const throw (xPnulo)
{
	if (!(*this << p))
		throw (xPnulo());

	return (p + Punto (cos (ang), sin (ang)) * l);
}

// Recta::ExtremoSegmento
/*************************************/
float Recta::Distancia (const Punto& p) const
{
// Se contruye la recta perpendicular a 'r' que contiene a 'p'.
	Recta r(p, ang + AngGR (90));

// Se devuelve la distancia entre 'p' y la intersecci�n entre ambas rectas.
	return ((p - (*this * r)).mod);
}

// Recta::operator+=
/*************************************/
Recta& Recta::operator+= (float k)
{
	c += b * k;

	return (*this);
}

// Recta::operator-=
/*************************************/
Recta& Recta::operator-= (float k)
{
	c -= b * k;

	return (*this);
}

// Recta::operator>=
/*************************************/
Recta& Recta::operator>= (float k)
{
	c += a * k;

	return (*this);
}

// Recta::operator<=
/*************************************/
Recta& Recta::operator<= (float k)
{
	c -= a * k;

	return (*this);
}

// Recta::operator>>=
/*************************************/
Recta& Recta::operator>>= (const Punto& p)
{
	*this = Recta (p, ang);

	return (*this);
}

// Segmento::Segmento
/*************************************/
Segmento::Segmento() : a(0, 0), b(1, 0), r(a, b)
{
	l = 1;
}

// Segmento::Segmento
/*************************************/
Segmento::Segmento (const Punto& p, const Punto& q) : a(p), b(q), r(p, q)
{
	l = Punto (q - p).mod;
}

// Segmento::Segmento
/*************************************/
Segmento::Segmento (const Punto& p, float ang, float _l) : a(p), l(_l), r(a, ang)
{
	b = r.ExtremoSegmento (a, l);
}

// Segmento::Segmento
/*************************************/
Segmento::Segmento (float _l, const Punto& p, float ang)
{
	Punto q(cos(ang), sin(ang));

	*this = Segmento(p - q * (_l / 2), ang, _l);
}

// Segmento::operator+
/*************************************/
Segmento Segmento::operator+ (const Punto& p) const
{
	return (Segmento (a + p, b + p));
}

// Segmento::operator+
/*************************************/
Segmento Segmento::operator+ (float k) const
{
	return (Segmento(*this) += k);
}

// Segmento::operator-
/*************************************/
Segmento Segmento::operator- (const Punto& p) const
{
	return (Segmento (a - p, b - p));
}

// Segmento::operator-
/*************************************/
Segmento Segmento::operator- (float k) const
{
	return (Segmento(*this) += k);
}

// Segmento::operator-
/*************************************/
Segmento Segmento::operator- () const
{
	return (Segmento (b, a));
}

// Segmento::operator>
/*************************************/
Segmento Segmento::operator> (float k) const
{
	return (Segmento(*this) >= k);
}

// Segmento::operator<
/*************************************/
Segmento Segmento::operator< (float k) const
{
	return (Segmento(*this) <= k);
}

// Segmento::operator>>
/*************************************/
Segmento Segmento::operator>> (const Punto& p) const
{
	return (Segmento(*this) >>= p);
}

// Segmento::operator<<
/*************************************/
bool Segmento::operator<< (const Punto& p) const
{
// Primero vemos si pertenece a la recta. En caso afirmativo, solo queda ver que 'p' pertenezca a la envoltura del
// segmento.

	return ((r << p) && Intervalo (a.x, b.x, p.x) && Intervalo (a.y, b.y, p.y));
}

// Segmento::operator<<
/*************************************/
bool Segmento::operator<< (const Segmento& s) const
{
// Solo devuelve afirmativo cuando 's' est� "completamente" contenido en el segmento.
	return (*this << s.a && *this << s.b);
}

// Segmento::operator==
/*************************************/
bool Segmento::operator== (const Segmento& s) const
{
	return (a == s.a && b == s.b);
}

// Segmento::operator!=
/*************************************/
bool Segmento::operator!= (const Segmento& s) const
{
	return (a != s.a || b != s.b);
}

// Segmento::operator||
/*************************************/
bool Segmento::operator|| (const Segmento& s) const
{
	return (r || s.r);
}

// Segmento::operator||
/*************************************/
bool Segmento::operator|| (const Recta& _r) const
{
	return (r || _r);
}

// Segmento::operator^
/*************************************/
float Segmento::operator^ (const Segmento& s) const
{
	return (r ^ s.r);
}

// Segmento::operator^
/*************************************/
float Segmento::operator^ (const Recta& _r) const
{
	return (r ^ _r);
}

// Segmento::operator*
/*************************************/
Punto Segmento::operator* (const Segmento& s) const throw (xPnulo, xScoincidentes)
{
	try
	{
// Obtiene la interseccion entre segmentos. Si los segmentos son coincidentes, devuelve el segmento interseccion.
		Punto p(r * s.r);

		if (s << p && *this << p)
			return (p);

		throw (xPnulo ());
	}
	catch (xRiguales)
	{
		if (*this << s.a || *this << s.b || s << a)
			throw (xScoincidentes());

		throw (xPnulo());
}}

// Segmento::SegCoincidente
/*************************************/
Segmento Segmento::SegCoincidente (const Segmento& s) throw (xPnulo)
{
	bool i = (*this << s.a);
	bool j = (*this << s.b);
	bool k = (s << a);

	if (i && j)
		return (s);

	if (k && s << b)
		return (*this);

	if (i)
		if (k)
			return (Segmento(a, s.a));
		else
			return (Segmento(s.a, b));
	else if (j)
		if (k)
			return (Segmento(a, s.b));
		else
			return (Segmento(s.b, b));
	else
		throw (xPnulo());
}


// Segmento::operator*
/*************************************/
Punto Segmento::operator* (const Recta& _r) const throw (xPnulo, xScoincidentes)
{
	try
	{
		Punto p = r * _r;

		if (*this << p)
			return (p);
		else
			throw (xPnulo());
	}
	catch (xRiguales)
	{
		throw (xScoincidentes());
}}

// Segmento::ExisteInter
/*************************************/
bool Segmento::ExisteInter (const Recta& _r) const
{
	if (_r || r)
		return (_r == r);
	else if (_r << a || _r << b)
		return (true);
	else
	{
		Punto p, q;

		if (Comp (_r.b, 0))
		{
			p = Punto(_r.c, 0);
			q = Punto(_r.c, 1);
		}
		else
		{
			p = Punto(0, _r.c / _r.b);
			q = Punto(1, (_r.c - 1) / _r.b);
		}

		return (p.Sentido(q, a) != p.Sentido(q, b));
}}

// Segmento::operator&
/*************************************/
Segmento Segmento::operator& (float ang) const
{
	return (Segmento(*this) &= ang);
}

// Segmento::Mediatriz
/*************************************/
Punto Segmento::Mediatriz() const
{
	return (r.ExtremoSegmento (a, l / 2));
}

// Segmento::DistanciaRect
/*************************************/
float Segmento::DistanciaRect (const Segmento& s) const
{
	float dist = -1, distaux = -1;
	float aux = r.ang + AngGR (90);

// Buscamos la distancia a los puntos que cortan las "proyecciones" perpendiculares de los extremos del segmento *this
//  quedandonos con el minimo.
	try
	{
		Punto p = s * Recta (a, aux);
		dist = Segmento (a, p).l;

		try
		{
			Punto q = s * Recta (b, aux);

			float aux = Segmento (b, q).l;
			if (Menor (aux, dist))
				dist = aux;
		}
		catch	(...) {}
	}
	catch (...)
	{
		try
		{
			Punto p = s * Recta (b, aux);

			dist = Segmento (b, p).l;
		}
		catch (...) {}
	}


// Buscamos ahora las distancias a los puntos "interiores" a las dos proyecciones, simplemente lanzando proyecciones
//  perpendiculares desde cada extremo del segmento 's', y mirando en qué punto de *this lo corta.
	try
	{
		Punto p = *this * Recta (s.a, aux);
		distaux = Segmento (s.a, p).l;

		Punto q = *this * Recta (s.b, aux);
		if (Menor (aux = Segmento (s.b, p).l, distaux))
			distaux = aux;
	}
	catch (...)
	{
		try
		{
			Punto p = *this * Recta (s.b, aux);
			distaux = Segmento (s.a, p).l;
		}
		catch (...) {}
	}

	if (distaux != -1 && Menor (distaux, dist))
		dist = distaux;

	return (dist);
}

// Segmento::operator+=
/*************************************/
Segmento& Segmento::operator+= (const Punto& p)
{
	*this = Segmento (a + p, b + p);

	return (*this);
}

// Segmento::operator+=
/*************************************/
Segmento& Segmento::operator+= (float k)
{
	float angAux = AngC(AngGR(90) - r.ang);
	Punto p(Punto(-cos(angAux), sin(angAux)) * k);

	*this = Segmento (a + p, b + p);

	return (*this);
}

// Segmento::operator-=
/*************************************/
Segmento& Segmento::operator-= (const Punto& p)
{
	*this += p * -1;

	return (*this);
}

// Segmento::operator-=
/*************************************/
Segmento& Segmento::operator-= (float k)
{
	*this += -k;

	return (*this);
}

// Segmento::operator>=
/*************************************/
Segmento& Segmento::operator>= (float k)
{
	Punto p(Punto(cos(r.ang), sin(r.ang)) * k);

	a += p;
	b += p;

	return (*this);
}

// Segmento::operator<=
/*************************************/
Segmento& Segmento::operator<= (float k)
{
	*this >= -k;

	return (*this);
}

// Segmento::operator>>=
/*************************************/
Segmento& Segmento::operator>>= (const Punto& p)
{
	*this = Segmento (p, p + Punto (b - a));

	return (*this);
}

// Segmento::operator&=
/*************************************/
Segmento& Segmento::operator&= (float ang)
{
	r = Recta (a, AngC (ang + r.ang));
	b = r.ExtremoSegmento (a, l);

	return (*this);
}

// Rectangulo::Rectangulo
/*************************************/
Rectangulo::Rectangulo() : a(), b(1, 0), c(1, -1), d(0, -1)
{
	w = h = 1;
	ang = 0;
}

// Rectangulo::Rectangulo
/*************************************/
Rectangulo::Rectangulo (const Punto& p, float _w, float _h, float _ang) : w(_w), h(_h), ang(AngC(_ang))
{
	float aux(AngC(ang + AngGR(270)));
	Punto paux(Punto(cos(aux), sin(aux)) * h);

	a = p;
	b = a + Punto(cos(ang), sin(ang)) * w;
	c = b + paux;
	d = a + paux;
}

// Rectangulo::operator+
/*************************************/
Rectangulo Rectangulo::operator+ (float k) const
{
	return (Rectangulo (*this) += k);
}

// Rectangulo::operator&
/*************************************/
Rectangulo Rectangulo::operator& (float _ang) const
{
	return (Rectangulo (*this) &= _ang);
}

// Rectangulo::operator^
/*************************************/
Rectangulo Rectangulo::operator^ (float _ang) const
{
	return (Rectangulo (*this) ^= _ang);
}

// Rectangulo::operator~
/*************************************/
Rectangulo Rectangulo::operator~() const
{
	return (Rectangulo (b, h, w, AngC (AngGR (270) + ang)));
}

// Rectangulo::operator<<
/*************************************/
bool Rectangulo::operator<< (const Punto& p) const
{
	// Contrucción matemática compleja.
	return (a.Sentido (b, p) && b.Sentido (c, p) && c.Sentido (d, p) && d.Sentido (a, p));
}

// Rectangulo::operator<<
/*************************************/
bool Rectangulo::operator<< (const Rectangulo& R) const
{
	return (*this << R.a && *this << R.b && *this << R.c && *this << R.d);
}

// Rectangulo::operator*
/*************************************/
bool Rectangulo::operator* (const Rectangulo& R) const
{
	return (*this << R.a || *this << R.b || *this << R.c || *this << R.d);
}

// Rectangulo::Envoltura
/*************************************/
Rectangulo Rectangulo::Envoltura() const
{
	float xmin, xmax, ymin, ymax;

// Se buscan las 4 coordenadas más extremas, y ésto formará el rectángulo 'envoltura'.
	xmin = Min (Min (a.x, b.x), Min (c.x, d.x));
	xmax = Max (Max (a.x, b.x), Max (c.x, d.x));

	ymin = Min (Min (a.y, b.y), Min (c.y, d.y));
	ymax = Max (Max (a.y, b.y), Max (c.y, d.y));

	return (Rectangulo (Punto (xmin, ymax), xmax - xmin, ymax - ymin, 0));
}

// Rectangulo::Ensanchar
/*************************************/
Rectangulo Rectangulo::Ensanchar(float ens) const
{
	Segmento s(a, ang + AngGR(135), ens);
	float inc = 2 * ens * cos(AngGR(45));

	return (Rectangulo(s.b, w + inc, h + inc, ang));
}

// Rectangulo::Centro
/*************************************/
Punto Rectangulo::Centro() const
{
	return (Segmento(a, c).Mediatriz());
}

// Rectangulo::operator+=
/*************************************/
Rectangulo& Rectangulo::operator+= (float k)
{
	float angT = AngC (AngGR (90) - ang);

// Construimos el vector "desplazamiento"
	Punto p = Punto (-1 * cos (angT), sin (angT)) * k;

// Y se desplazan los cuatro puntos por igual (el �ngulo no cambia).
	a += p;
	b += p;
	c += p;
	d += p;

	return (*this);
}

// Rectangulo::operator&=
/*************************************/
Rectangulo& Rectangulo::operator&= (float _ang)
{
	return (*this = Rectangulo(a, w, h, AngC (ang + _ang)));
}

// Rectangulo::operator^=
/*************************************/
Rectangulo& Rectangulo::operator^= (float _ang)
{
	Segmento s(b, AngGR (180) + ang - _ang, w);

	return (*this = Rectangulo(s.b, w, h, AngGR (360) + ang - _ang));
}

// Rectangulo::operator>>
/*************************************/
Rectangulo& Rectangulo::operator>>= (const Punto& p)
{
	return (*this = Rectangulo (p, w, h, ang));
}

// Cuadrilatero::Cuadrilatero
/*************************************/
Cuadrilatero::Cuadrilatero()
{
	a = Punto(0, 1);
	b = Punto(1, 1);
	c = Punto(1, 0);
	d = Punto(0, 0);
}

// Cuadrilatero::Cuadrilatero
/*************************************/
Cuadrilatero::Cuadrilatero (const Punto& _a, const Punto& _b, const Punto& _c, const Punto& _d) throw (xCDnulo)
{
	if (_a == _b || _a == _c || _a == _d || _b == _c || _b == _d || _c == _d)
		throw (xCDnulo());

	a = _a;
	b = _b;
	
	try
	{
		Punto p = Segmento(b, _c) * Segmento(_d, a);

		c = _d;
		d = _c;
	}
	catch (xScoincidentes)
	{
		throw (xCDnulo());
	}
	catch (xPnulo)
	{
		c = _c;
		d = _d;
}}


// Cuadrilatero::operator<<
/*************************************/
bool Cuadrilatero::operator<< (const Punto& p) const
{
	bool _a = a.Sentido (b, p);
	bool _b = b.Sentido (c, p);
	bool _c = c.Sentido (d, p);
	bool _d = d.Sentido (a, p);

	return (_a == _b && _b == _c && _c == _d);
}

// La ecuaci�n de la circunferencia sigue la f�rmula (x - o.a) ^ 2 + (y - o.b) ^ 2 = r ^ 2
// Circunferencia::Circunferencia
/*************************************/
Circunferencia::Circunferencia() : o(0, 0), r(1)
{}

// Circunferencia::Circunferencia
/*************************************/
Circunferencia::Circunferencia (const Punto _o, float _r) : o(_o), r(_r)
{}

// Circunferencia::operator*
/*************************************/
Segmento Circunferencia::operator* (const Recta& s) const throw (xPnulo)
{
	Recta _r(s);
	Punto a, b;

// Se desplaza la circuferencia al origen, y se desplaza 's' del mismo modo junto a él.
// Se buscan entonces las intersecciones, y luego se llevan las soluciones al punto
// correcto deshaciendo la transformación.
// La solución se busca, entonces, resolviendo el sistema (previa transformación):
//      x1^2    +    y1^2   =   r^2
// 		a  *  x   +  b  *  y  =    c

	_r <= o.x;
	_r -= o.y;

// Para optimizar y simplificar, se resuelven primero los casos básicos.
	if (Comp (_r.a, 0))
	{
		if (Mayor (Abs (_r.c), r))
			throw (xPnulo());

		a.y = b.y = _r.c;
		a.x = sqrt (pow (r, 2) - pow (_r.c, 2));
		b.x = -a.x;
	}
	else if (Comp (_r.b, 0))
	{
		if (Mayor (Abs (_r.c), r))
			throw (xPnulo());

		a.x = b.x = _r.c;
		a.y = sqrt (pow (r, 2) - pow (_r.c, 2));
		b.y = -a.y;
	}
	else
	{
		float ca = pow (_r.b, 2) + 1;
		float cb = 2 * _r.b * _r.c;
		float cc = pow(_r.c, 2) - pow(r, 2);

		float cr = pow(cb, 2) - 4 * ca * cc;

		if (Menor (cr, 0))
			throw (xPnulo ());

		ca = 2 * ca;
		cr = sqrt(cr);

		a.y = (cb + cr) / ca;
		b.y = (cb - cr) / ca;

		a.x = _r.c - _r.b * a.y;
		b.x = _r.c - _r.b * b.y;
	}

	return (Segmento(a, b) += o);
}

// Circunferencia::operator*
/*************************************/
Segmento Circunferencia::operator* (const Segmento& s) const throw (xPnulo)
{
// Se busca la intersección entre la circunferencia y la recta que contiene a 's', y luego
// se mira si dichos puntos pertenecen a la circunferencia.

	Segmento _r(*this * s.r);

	if (s << _r.a)
	{
		if (!(s << _r.b))
			_r.b = _r.a;
	}
	else if (s << _r.b)
		_r.a = _r.b;
	else
		throw (xPnulo());

	return (_r);
}

// Circunferencia::operator*
/*************************************/
Segmento Circunferencia::operator* (const Circunferencia& c) const throw (xSnulo)
{
	// Distancia entre centros.
	Punto oo(c.o - o);
	float d = oo.mod;

	if (Mayor(d, r + c.r) || Menor(d, Abs(r - c.r)) || Comp(d, 0))
		throw(xSnulo());

	// 's' es el segmento formado por los puntos de la
	// intersección (s.a y s.b). Este segmento tiene de mediatriz 'p'. Dicho punto
	// 'p' está en algun lugar intermedio de la recta que une ambos
	// centros. Sea 'a' la distancia desde o hasta p, y 'h' la distancia
	// desde p hasta cualquiera de las dos intersecciones.
	float ra = pow(r, 2);
	float rb = pow(c.r, 2);
	float a = (ra - rb + pow(d, 2)) / (2.0 * d);

	//Conseguimos el punto 'p'.
	Punto p(o + oo * (a / d));

	// Altura h
	float h = sqrt(ra - pow(a, 2));

	//Vector libre desde p hasta s.a 
	Punto vh(Punto(-oo.y, oo.x) * (h / d));

	Segmento s;

	s.a.x = p.x + vh.x;
	s.b.x = p.x - vh.x;

	s.a.y = p.y + vh.y;
	s.b.y = p.y - vh.y;

	return (s);	
}

// Circunferencia::operator<<
/*************************************/
bool Circunferencia::operator<< (const Punto& p) const
{
	return (!Mayor((p - o).mod, r));
}

// Circunferencia::operator<<
/*************************************/
bool Circunferencia::operator<< (const Segmento& s) const
{
	return ((*this << s.a) && (*this << s.b));
}

// Semidisco::operator<<
/*************************************/
Semidisco::Semidisco()
{
	ang1 = 0;
	ang2 = AngGR (90);

	r = 1;
}

// Semidisco::Semidisco
/*************************************/
Semidisco::Semidisco (const Punto& _o, float _ang1, float _ang2, float _r) throw (xSCilegal)
{
	if (Menor (_r, 0))
		throw (xSCilegal());

	o = _o;

	ang1 = AngC (_ang1);
	ang2 = AngC (_ang2);

	r = _r;
}

// Semidisco::operator<<
/*************************************/
bool Semidisco::operator<< (const Punto& p) const
{
	Segmento s(o, p);

// Pertenecerá a la Semidisco, si la distancia de o a p es menor que el radio, y además está dentro
// del ángulo barrido desde ang1 a ang2 (considerando posibles "traspasos" de la linea de 360º)
	if (Menor (ang2, ang1))
		return (!Intervalo (ang1, ang2, s.r.ang) && Menor (s.l, r));
	else
		return (Intervalo (ang1, ang2, s.r.ang) && Menor (s.l, r));
}

// Semidisco::Envoltura
/*************************************/
Rectangulo Semidisco::Envoltura() const
{
	Rectangulo s;
	Segmento t(Segmento (o, ang1, r).b, Segmento (o, ang2, r).b);

// Se buscan todos los valores extremos de los puntos origen, y extremos de la Semidisco.
// Estos se corrigen si la Semidisco pasa de un cuadrante a otro (puesto que los puntos extremos
// vienen ahora condicionados por el radio de la Semidisco.
	s.a.x = s.d.x = min (min (t.a.x, t.b.x), o.x);
	s.b.x = s.c.x = max (max (t.a.x, t.b.x), o.x);

	s.a.y = s.b.y = max (max (t.a.y, t.b.y), o.y);
	s.c.y = s.d.y = min (min (t.a.y, t.b.y), o.y);

	float angaux = ang2;

	if (Menor (ang2, ang1))
		angaux += AngGR (360);

	if (Intervalo (ang1, angaux, AngGR (90)) || Intervalo (ang1, angaux, AngGR (450)))
		s.a.y = s.b.y = o.y + r;
	if (Intervalo (ang1, angaux, AngGR (180)) || Intervalo (ang1, angaux, AngGR (540)))
		s.a.x = s.d.x = o.x - r;
	if (Intervalo (ang1, angaux, AngGR (270)) || Intervalo (ang1, angaux, AngGR (630)))
		s.c.y = s.d.y = o.y - r;
	if (Intervalo (ang1, angaux, AngGR (360)) || Intervalo (ang1, angaux, AngGR (720)))
		s.b.x = s.c.x = o.x + r;

	s.w = s.b.x - s.a.x;
	s.h = s.a.y - s.d.y;

	return (s);
}

// NumAzar
/*************************************/
unsigned NumAzar (unsigned a, unsigned b)
{
	if (b < a)
		Intercambiar (a, b);

	return (a + rand() % (b - a + 1));
}

// NumAzar
/*************************************/
unsigned NumAzar (float a, float b)
{
	return (NumAzar ((unsigned)a, (unsigned)b));
}

// Abs
/*************************************/
float Abs (float x)
{
	return (Menor (x, 0) ? -1 * x : x);
}

// Min
/*************************************/
float Min (float a, float b)
{
	return (Menor (a, b) ? a : b);
}

// Max
/*************************************/
float Max (float a, float b)
{
	return (Mayor (a, b) ? a : b);
}

// AngRG
/*************************************/
float AngGR (float grad)
{
	return (grad * RAD);
}

// AngRG
/*************************************/
float AngRG (float rad)
{
	return (rad / RAD);
}

// AngC
/*************************************/
float AngC (float grad)
{
	float aux = AngGR (360);

	while (Menor (grad, 0))
		grad += aux;

	while (!Menor (grad, aux))
		grad -= aux;

	return (grad);
}

// Comp
/*************************************/
bool Comp (float a, float b)
{
	return (Intervalo (a - 0.01, a + 0.01, b));
}


// Cuad
/*************************************/
bool Cuad (unsigned short c, Punto p) throw (xCilegal)
{
	if (c == 0 || c > 4)
		throw (xCilegal());

	float cx = 1, cy = 1;

	if (c == 2 || c == 3)
		cx *= -1;

	if (c == 3 || c == 4)
		cy *= -1;

	return (p.x * cx >= 0 && p.y * cy >= 0);
}

// Menor
/*************************************/
bool Menor (float a, float b)
{
	return ((int)((a * 100) + .5) < (int)((b * 100) + .5));
}

// Mayor
/*************************************/
bool Mayor (float a, float b)
{
	return ((int)((a * 100) + .5) > (int)((b * 100) + .5));
}

// Intervalo
/*************************************/
bool Intervalo (float a, float b, float p)
{
	if (!Mayor (a, b))
		return (!Menor (p, a) && !Mayor (p, b));

	return (!Mayor (p, a) && !Menor (p, b));
}

// ElemXMatriz
/*************************************/
unsigned ElemXMatriz (unsigned cols, unsigned n)
{
	return (n ? 1 + (n - 1) % cols : 0);
}

// ElemYMatriz
/*************************************/
unsigned ElemYMatriz (unsigned cols, unsigned n)
{
	return (n ? 1 + (n - 1) / cols : 0);
}

// Arco
/*************************************/
float Arco (float r, float ang)
{
	return (r * ang);
}

// Barrido
/*************************************/
float Barrido (float r, float l)
{
	return (l / r);
}

// Intercambiar
/*************************************/
void Intercambiar (float& a, float& b)
{
	float c = a;

	a = b;
	b = c;
}

// Intercambiar
/*************************************/
void Intercambiar (unsigned& a, unsigned& b)
{
	unsigned c = a;

	a = b;
	b = c;
}
