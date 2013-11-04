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

#include <iostream>
#include <fstream>
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "Ejercito.h"
#include "../Estado.h"

using namespace std;

const unsigned AnchoPredt(4);
const Punto POPredt(0, 0);

const string rutaSeleccionadoP("Imagenes/Especiales/selectorUnidadesP.png");
const string rutaSeleccionadoS("Imagenes/Especiales/selectorUnidadesS.png");
const string rutaUnidadActual("Imagenes/Especiales/UnidadActual.png");

// Unidad::Unidad
/*************************************/
Unidad::Unidad (Atrib _a, string dir, Ejercito *_e, unsigned min,
								unsigned max, double _fw, double _fh, string nomUnidad)
	: a(_a), e(_e), nomUnidad(nomUnidad), fw(_fw), fh(_fh)
{
  sel = false;
  vir = false;
  act = true;
	actualizar = true;

	marchar = true;
	marchado = false;

  movmax = 0;
  marcha = false;
  carga = false;
  comb = false;
  desmo = false;
  huida = false;
	disp = false;

  r = Rectangulo();

  nmin = min;
  nmax = max;

	Ejer ej = e->eEjercito();

	if (ej != eGAIA)
		{
			if (!(marcOr = IMG_Load(rutaUnidadActual.c_str())))
				cerr << SDL_GetError() << endl;

			if (ej == ePRIM)
				{
					if (!(selOr = IMG_Load(rutaSeleccionadoP.c_str())))
						cerr << SDL_GetError() << endl;
				}
			else if (ej == eSEG)
				{
					if (!(selOr = IMG_Load(rutaSeleccionadoS.c_str())))
						cerr << SDL_GetError() << endl;
				}
		}

	imgSeleccionado = NULL;
	imgMarcado = NULL;

  ActualizarRect (min, (nmax < AnchoPredt) ? nmax : AnchoPredt);
	heridas = min * a.h;
	no = 0;

	if (dir != "")
		{
			SDL_Surface *imgOr;

			if (!(imgOr = IMG_Load (dir.c_str())))
				cerr << SDL_GetError() << endl;

			if (!(imagenes[0] = zoomSurface(imgOr, fw, fh, 0)))
				cerr << SDL_GetError() << endl;

			delete imgOr;
		}
}

// Unidad:Activo
/*************************************/
string Unidad::NombreUnidad() const
{
	return (nomUnidad);
}

// Unidad::Activo
/*************************************/
bool Unidad::Activo() const
{
  return (act);
}

// Unidad::Actualizar
/*************************************/
bool Unidad::Actualizar() const
{
  return (actualizar);
}

// Unidad::Atributos
/*************************************/
const Atrib& Unidad::Atributos () const
{
  return (a);
}

// Unidad::MovMax
/*************************************/
float Unidad::MovMax () const
{
	return (movmax);
}

// Unidad::AngMax
/*************************************/
float Unidad::AngMax () const
{
	return (Barrido (r.w, movmax));
}

// Unidad::MinEfecs
/*************************************/
unsigned Unidad::MinEfecs() const
{
  return (nmin);
}

// Unidad::MaxEfecs
/*************************************/
unsigned Unidad::MaxEfecs() const
{
  return (nmax);
}

// Unidad::N
/*************************************/
unsigned Unidad::N() const
{
  return (n);
}

// Unidad::NO
/*************************************/
unsigned Unidad::NO() const
{
	return (no);
}

// Unidad::Frente
/*************************************/
unsigned Unidad::Frente() const
{
  return (frente);
}

// Unidad::Filas
/*************************************/
unsigned Unidad::Filas() const
{
  return (frente ? (1 + (n - 1) / frente) : n);
}

// Unidad::P
/*************************************/
unsigned Unidad::P() const
{
  return (n * a.p);
}

// Unidad::Puntos
/*************************************/
unsigned Unidad::Puntos() const
{
  return (n * a.puntos);
}
			
// Unidad::Psi
/*************************************/
const Punto& Unidad::Psi() const
{
  return (r.a);
}

// Unidad::Psd
/*************************************/
const Punto& Unidad::Psd() const
{
  return (r.b);
}

// Unidad::Pii
/*************************************/
const Punto& Unidad::Pii() const
{
  return (r.d);
}

// Unidad::Pid
/*************************************/
const Punto& Unidad::Pid() const
{
  return (r.c);
}

// Unidad::Lado
/*************************************/
Segmento Unidad::Lado (Dir d, bool prec) const
{
  Segmento s;

  if (d == FRE)
    s = Segmento(r.a, r.b);
  else if (d == RET)
    {
      s = Segmento(r.c, r.d);

      if (prec && ufila)
				{
					Punto desp(cos(s.r.ang), sin(s.r.ang));

					unsigned nAux = 1 + (n - 1) % frente;

					s.a += desp * a.ro.x * (frente - nAux - ufila);
					s.b -= desp * a.ro.x * ufila;
					s.l = a.ro.x * nAux;
				}}
  else
    {
      if (d == DER)
				s = Segmento(r.b, r.c);
      else if (d == IZQ)
				s = Segmento(r.d, r.a);

      if (prec && ((d == DER && ElemXMatriz (frente, n) != frente) || (d == IZQ && ufila)))
				{
					Punto p(cos(s.r.ang), sin(s.r.ang));
					s.b -= p * a.ro.y;
					s.l -= a.ro.y;
				}}

  return (s);
}

// Unidad::Efecs
/*************************************/
unsigned Unidad::Efecs (Dir d) const
{
  if (!n)
    return (0);
  else if (d == FRE)
    return (frente);
  else if (d == IZQ)
    {
      unsigned aux = ElemYMatriz (frente, n);

      if (ufila)
	--aux;

      return (aux);
    }
  else if (d == DER)
    {
      unsigned aux = ElemYMatriz (frente, n);

      if ((n + ufila) % frente)
	--aux;

      return (aux);
    }
  else
    return (1 + (n - 1) % frente);
}

// Unidad::Efec
/*************************************/
Rectangulo Unidad::Efec (unsigned _n) const
{
	/*
	 *  Corregimos el posible desplazamiento de una última fila
	 *  incompleta (cuyos efectivos estarán centrados).
	 */
  if (ElemYMatriz (frente, _n) == ElemYMatriz (frente, n))
    _n += ufila;

	/*
	 *  Rectángulo del efectivo.
	 */
  Punto x(a.ro.x * (ElemXMatriz (frente, _n) - 1),
					-1 * a.ro.y * (ElemYMatriz (frente, _n) - 1));

	x = (Segmento(r.a, r.a + x) & r.ang).b;

  return (Rectangulo(x, a.ro.x, a.ro.y, r.ang));
}

// Unidad::R
/*************************************/
const Rectangulo& Unidad::R() const
{
  return (r);
}

// Unidad::Cargando
/*************************************/
bool Unidad::Cargando() const
{
  return (carga);
}

// Unidad::Marchando
/*************************************/
bool Unidad::Marchando() const
{
  return (marcha);
}

// Unidad::Marchado
/*************************************/
bool Unidad::Marchado() const
{
  return (marchado);
}

// Unidad::Combatiendo
/*************************************/
bool Unidad::Combatiendo() const
{
  return (comb);
}

// Unidad::Desmoralizado
/*************************************/
bool Unidad::Desmoralizado() const
{
  return (desmo);
}

// Unidad::Huyendo
/*************************************/
bool Unidad::Huyendo() const
{
  return (huida);
}

// Unidad::bMarchar
/**************************************/
bool Unidad::bMarchar() const
{
	return (marchar);
}

// Unidad::Seleccionado
/*************************************/
bool Unidad::Seleccionado() const
{
  return (sel);
}

// Unidad::Disparado
/*************************************/
bool Unidad::Disparado() const
{
	return (disp);
}

// Unidad::Heridas
/*************************************/
unsigned Unidad::Heridas() const
{
	return (heridas);
}

// Unidad::Contacto
/*************************************/
unsigned Unidad::Contacto (const Segmento& s, Dir d) const
{
  Segmento t = Lado(d, true);

  unsigned nAux;
  float aux;

  if (d == FRE || d == RET)
    aux = a.ro.x;
  else
    aux = a.ro.y;

  nAux = (unsigned)((t.l + 1) / aux);

  try
    {
      Segmento w = t.SegCoincidente (s);

      float l1 = Segmento(t.a, w.a).l;
      if (l1 >= 1)
				l1 -= 1;

      float l2 = Segmento(t.a, w.b).l + 1;

      if (Menor (l2, l1))
				Intercambiar (l1, l2);

      return (nAux - (unsigned)(l1 / aux) - (unsigned)((t.l - l2) / aux));
    }
  catch (xPnulo x) {}

  return (0);
}

// Unidad::Contacto
/*************************************/
RangoEf Unidad::Contacto (Unidad *u, Dir d, Dir f) const
{
  Segmento s = u->Lado(f, true);
  Segmento t = Lado(d, true);

  unsigned nAux;
  float aux;

  if (d == FRE || d == RET)
    aux = a.ro.x;
  else
    aux = a.ro.y;

  nAux = (unsigned)((t.l + 0.1) / aux);

  try
    {
      Segmento w = t.SegCoincidente (s);

      float l1 = Segmento(t.a, w.a).l;

      if (l1 >= 1)
				l1 -= 1;

      float l2 = Segmento(t.a, w.b).l + 1;

      if (Menor (l2, l1))
				Intercambiar (l1, l2);

      vector<unsigned> v;
      unsigned i = (unsigned)(l1 / aux) + 1;
      unsigned j = nAux - (unsigned)((t.l - l2) / aux);

      if (d == FRE)
				for (unsigned k = i; k <= j; ++k)
					v.push_back(k);
      else if (d == DER)
				for (unsigned k = i; k <= j; ++k)
					v.push_back (k * frente);
      else if (d == RET)
				for (unsigned k = i; k <= j; ++k)
					v.push_back (n - k + 1);
      else
				for (unsigned k = i; k <= j; ++k)
					v.push_back (n - k * frente + 1);

      return (v);
    }
  catch (xPnulo x) {}

  return (vector<unsigned>());
}

// Unidad::uEjercito
/*************************************/
Ejercito* Unidad::uEjercito() const
{
  return (e);
}

// Unidad::eEjercito
/*************************************/
Ejer Unidad::eEjercito() const
{
  return (e->eEjercito());
}

// Unidad::Ang
/*************************************/
float Unidad::Ang() const
{
  return (r.ang);
}

// Unidad::ModificarAtributo
/*************************************/
void Unidad::ModificarAtributo(unsigned i, int cantidad)
{
	switch(i)
		{
		case 0:
			a.m += 10 * cantidad;
			break;
		case 1:
			a.ha += cantidad;
			break;
		case 2:
			a.hp += cantidad;
			break;
		case 3:
			a.f += cantidad;
			break;
		case 4:
			a.r += cantidad;
			break;
		case 5:
			a.a += cantidad;
			break;
		case 6:
			a.h += cantidad;

			if (a.h < 1)
				a.h = 1;

			break;
		case 7:
			a.i += cantidad;
			break;
		case 8:
			a.l += cantidad;
			break;
		case 9:
			a.sa += cantidad;
			break;
		case 10:
			a.fa += cantidad;
			break;
		case 11:
			a.aa += 10 * cantidad;
			break;
		default:
			break;
		}
}

// Unidad::ImgActual
/*************************************/
SDL_Surface* Unidad::ImgActual ()
{
	// Redondea al múltiplo de 5 más cercano.
	unsigned ang = 5 * (unsigned)(.5 + AngRG(r.ang) / 5);
	SDL_Surface *s;

	map<unsigned, SDL_Surface*>::iterator i = imagenes.find(ang), j = imagenes.begin();

	if (i == imagenes.end())
		{
			s = rotozoomSurface(j->second, ang, 1, 0);
			imagenes[ang] = s;
		}
	else
		s = i->second;

	actualizar = false;

  return (s);
}

// Unidad::ImgSeleccionado
/*************************************/
SDL_Surface* Unidad::ImgSeleccionado() const
{
	return (imgSeleccionado);
}

// Unidad::ImgMarcado
/*************************************/
SDL_Surface* Unidad::ImgMarcado() const
{
	return (imgMarcado);
}

// Unidad::puntoImpr
/*************************************/
Punto Unidad::puntoImpr() const
{
	return (posImpr);
}

// Unidad::Inicializar
/*************************************/
void Unidad::Inicializar()
{
	no = n;
}

// Unidad::operator<<
/*************************************/
bool Unidad::operator<< (const Punto& p) const
{
  return (r << p);
}

// Unidad::Seleccionar
/*************************************/
void Unidad::Seleccionar()
{
	actualizar = true;
  sel = true;
}

// Unidad::Deseleccionar
/*************************************/
void Unidad::Deseleccionar()
{
	actualizar = true;
  sel = false;
}

// Unidad::NuevoMov
/**************************************/
void Unidad::Reiniciar()
{
  movmax = a.m;
  marcha = false;
	marchar = true;
	marchado = false;
	disp = false;
}

// Unidad::NuevaPO
/*************************************/
void Unidad::NuevaPO (const Punto& p, float ang)
{
	if (p != r.a || ang != r.ang)
		{
			r = Rectangulo (p, r.w, r.h, ang);
			actualizar = true;
			ActualizarImgSelMarc();
		}
}

// Unidad::Marchar
/*************************************/
void Unidad::Marchar (bool m)
{
  if (m && !(desmo || huida || carga || comb || !marchar))
		{
			if (marcha != m)                     // Si el valor actual y el real son distintos
				{
					if (m)                           // Si se desea marchar ...
						movmax *= 2;                   // ... se duplica el valor restante de movimiento.
					else                             // Si se desea detenar ...
						movmax /= 2.0;                 // ... se reduce a la mitad el mismo.

					marcha = m;
					marchado = true;
				}
		}
}

// Unidad::MasEfectivos
/*************************************/
void Unidad::MasEfectivos (unsigned _n)
{
	heridas += _n * a.h;

  ActualizarRect (n + _n, frente);
}

// Unidad::MenosEfectivos
/*************************************/
void Unidad::MenosEfectivos (unsigned _n)
{	
	heridas -= _n * a.h;

  if (heridas > 0)
		ActualizarRect (n - _n, frente);
	else
		{
			n = 0;
			heridas = 0;
			act = false;
		}
}

// Unidad::Desplazar
/*************************************/
void Unidad::Desplazar (float k)
{
	if (k != 0)
		actualizar = true;

  if (!vir && Mayor (k, movmax))
    k = movmax;

  r += k;

  if (!vir)
    movmax -= k;

	ActualizarImgSelMarc();
}

// Unidad::Girar
/*************************************/
void Unidad::Girar()
{
	actualizar = true;

  if (!(desmo || comb || carga || marchado || marcha || (!vir && Menor(movmax, a.m / 4))))
		{
			if (!vir)
				movmax -= a.m / 4;

			marchar = false;
			r = ~~r;

			ActualizarImgSelMarc();
		}
}

// Unidad::PivotarIzq
/*************************************/
void Unidad::PivotarIzq (float ang)
{
  if (!(desmo || comb))
		{
			if (Mayor (ang, 0))
				{
					actualizar = true;

					float arco = Arco (r.w, ang);

					if (!vir && Mayor (arco, movmax))
						{
							arco = movmax;
							ang = Barrido (r.w, arco);
						}

					if (!vir)
						movmax -= arco;

					r &= ang;

					ActualizarImgSelMarc();
				}
		}
}

// Unidad::PivotarDer
/*************************************/
void Unidad::PivotarDer (float ang)
{
  if (!(desmo || comb))
		{
			if (Mayor (ang, 0))
				{
					actualizar = true;

					float arco = Arco (r.w, ang);

					if (!vir && Mayor (arco, movmax))
						{
							arco = movmax;
							ang = Barrido(r.w, arco);
						}

					r ^= ang;

					if (!vir)
						movmax -= arco;

					ActualizarImgSelMarc();
				}
		}
}

// Unidad::Transladar
/*************************************/
void Unidad::Trasladar (const Segmento& s)
{
	if (!desmo && (s.a != r.a || s.r.ang != r.ang))
		{
			actualizar = true;
			r = Rectangulo (s.a, r.w, r.h, s.r.ang);
			ActualizarImgSelMarc();
		}
}

// Unidad::NuevoFrente
/*************************************/
void Unidad::NuevoFrente (unsigned _frente)
{
  if (!(desmo || carga || comb || huida || marcha))
		ActualizarRect (n, _frente);
}

// Unidad::Cargar
/*************************************/
void Unidad::Cargar (bool c)
{
  if (!(c && (comb || desmo || huida || marcha)))
		{

			if (!carga && c)
				movmax *= 2;
			else if (carga && !c)
				movmax = 0;

			carga = c;
		}
}

// Unidad::Combatir
/*************************************/
void Unidad::Combatir (bool c, bool ataque)
{
  if (!(c && ataque && (huida || desmo || marcha || carga)))
		comb = c;
}

// Unidad::Desmoralizar
/*************************************/
void Unidad::Desmoralizar (bool d)
{
  desmo = d;

  if (desmo)
    {
      marcha = false;
      comb = false;
      carga = false;
    }
}

// Unidad::Huir
/*************************************/
void Unidad::Huir (bool h)
{
  huida = h;

  if (huida)
    {
      desmo = false;
      comb = false;
      marcha = false;
      carga = false;
    }
}

// Unidad::Disparar
/*************************************/
void Unidad::Disparar (bool d)
{
	disp = d;
}

// Unidad::ActualizarRect
/*************************************/
void Unidad::ActualizarRect (unsigned _n, unsigned _frente)
{
  bool cambio = false;

  if (n != _n)
    {
      cambio = true;
      n = _n;
    }

  _frente = (n <= _frente) ? n : _frente;

  if (!(_frente > n || (n > AnchoPredt && nmax >= AnchoPredt
												&& _frente < AnchoPredt)))
		{

			if (_frente != frente)
				{
					cambio = true;
					frente = _frente;
				}

			actualizar = cambio;

			if (cambio && n)
				r = Rectangulo (r.a, frente * a.ro.x, ElemYMatriz (frente, n) * a.ro.y, r.ang);

			unsigned aux;
			if (frente && (aux = n % frente))               // Si la última fila no está completa ...
				ufila = (frente - 1) / 2 - (aux - 1) / 2;       // ... todos sus efectivos se centrarán. *1
			else                                           // Si no ...
				ufila = 0;                                     // ... Ufila vale
			// 0. *1

			ActualizarImgSelMarc();
		}
}

// Unidad::ActualizarImgSelMarc
/*************************************/
void Unidad::ActualizarImgSelMarc()
{
	Ejer ej = e->eEjercito();

	if (ej != eGAIA && ej != eNULO)
		{
			Rectangulo envoltura = r.Envoltura();

			float ancho = 2 * envoltura.w;
			float alto = 2 * envoltura.h;

			float fw2 = fw * ancho / selOr->w;
			float fh2 = fh * alto / selOr->h;

			if (imgSeleccionado != NULL)
				delete imgSeleccionado;

			if (imgMarcado != NULL)
				delete imgMarcado;

			if (!(imgMarcado = zoomSurface(marcOr, fw2, fh2, 0)))
				cerr << SDL_GetError() << endl;

			if (!(imgSeleccionado = zoomSurface(selOr, fw2, fh2, 0)))
				cerr << SDL_GetError() << endl;

			/*
			 *  Buscamos la posición de impresión, de modo que el centro de
			 *  la envoltura y el círculo coincidan.
			 */
			float difx = (ancho - envoltura.w) / 2.0;
			float dify = (alto - envoltura.h) / 2.0;

			posImpr = envoltura.a - Punto(difx, -dify);
		}
}

// Unidad::ModificarHeridas
/*************************************/
void Unidad::ModificarHeridas (int numHeridas)
{
	if (numHeridas != 0)
		{
			heridas += numHeridas;

			unsigned num = (heridas + a.h - 1) / a.h;

			ActualizarRect (num, frente);
		}
}

// Unidad::Eliminar
/*************************************/
void Unidad::Eliminar()
{
  act = false;
}

// Unidad::~Unidad
/*************************************/
Unidad::~Unidad()
{}

/*
 *	Ufila es el número de efectivos que hay delante del primer efectivo
 *  de la última fila de la unidad. Los efectivos de la  última fila
 *  estarán lo más centrados posible. Si solo tenemos un efectivo de
 *  "sobra" y el 'Ancho' es impar, el primer efectivo estará justo en 
 *  el centro, y si es par, en el menor de los dos centrales. En ambos
 *  casos Ufila será el número de efectivos que hay justo delante. 
 *  En todo caso esto viene dado por (Ancho - 1) / 2.
 *  Si añadimos nuevos efectivos a la última fila, estos se añaden,
 *  primero uno a la derecha y luego uno a la izquierda. Así siempre se
 *  preserva la condición que las unidades están lo más centradas
 *  posibles, pero alineados con los efectivos del resto de la unidad.
 *  Es decir, solamente cada 2 nuevos efectivos, Ufila se reducirá en
 *  una unidad. Esto viene dado por (aux - 1) / 2. Si la última fila
 *  esta completa, aux = 0, y Ufila no valdrá 0, que sería lo deseable,
 *  puesto que no hay ningún "hueco" delante del primer efectivo de
 *  la última fila, por eso se fuerza.
*/
