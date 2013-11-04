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

/*! \file GestorEscenario.cpp
 *  \brief Implementaciones del gestor de escenarios.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "GestorEscenario.h"

const float PI(3.141593);
const float DistSeg(10);

using namespace std;

// MovCarga::MovCarga
/*************************************/
MovCarga::MovCarga()
{
  efec = false;
  nEfec = 0;
}

// MovCarga::MovCarga
/*************************************/
MovCarga::MovCarga (const Carga& _C, const Segmento& _s) : C(_C), s(_s)
{
  efec = false;
  nEfec = 0;
}

// GestorEscenario::GestorEscenario
/*************************************/
GestorEscenario::GestorEscenario (const Punto& DimEsc)
	:inf(sqrt (pow (DimEsc.x, 2) + pow (DimEsc.y, 2)))
{
  esc[0] = Punto(0, DimEsc.y);
  esc[1] = Punto(DimEsc.x, DimEsc.y);
  esc[2] = Punto(DimEsc.x, 0);
  esc[3] = Punto(0, 0);
}

// GestorEscenario::escenario
/*************************************/
const Punto& GestorEscenario::DimEscenario() const
{
  return (esc[1]);
}

// GestorEscenario::DesplMax
/*************************************/
float GestorEscenario::DesplMax (const Estado& E, Unidad *uAct,
																 Carga *c, Unidad **prim) const
{
  float DistSegaux;
  float dMax = inf;

  if (prim)
    *prim = 0;
  else
    dMax = uAct->MovMax();

  if (c)
    DistSegaux = 0;
  else
    DistSegaux = DistSeg * sqrt(2);

  if (uAct)
    {
      // Se engrosa a la unidad para que se respete la distancia de seguridad entre unidades.
      Rectangulo r(uAct->R());
      Punto p(r.a.x - DistSegaux * cos (AngGR (45) - r.ang), r.a.y + DistSegaux * sin (AngGR (45) - r.ang));
      Rectangulo s(p, r.w + sqrt (2) * DistSegaux, r.h + sqrt (2) * DistSegaux, r.ang);

      Punto v[2] = { s.a, s.b };

      float m = AngC (uAct->Ang() + AngGR (90));

      // Construcción matemática compleja.
      for (unsigned i = 0; i < 3; ++i)
				{
					Ejercito *e = E.pEjer ((Ejer)i);

					for (unsigned j = 0; j < e->nUnidades(); ++j)
						{
							Unidad *u = (*e)[j];

							float min = dMax;
							if (u->Activo() && u != uAct && (!c || (c && u != c->v)))
								{
									Punto w[4] = { u->Psi(), u->Psd(), u->Pid(), u->Pii() };

									for (unsigned k = 0; k < 2; ++k)
										{
											Recta r(v[k], m);
											for (unsigned l = 0; l < 4; ++l)
												{
													Segmento s(w[l], w[(l + 1) % 4]);

													try
														{
															Punto p = s * r;
															if (v[1].Sentido(v[0], p))
																min = Min ((p - v[k]).mod, min);
														}
													catch (xScoincidentes x)
														{
															if (v[1].Sentido(v[0], s.a))
																min = Min (Min ((s.a - v[k]).mod, (s.b - v[k]).mod), min);
														}
													catch (xPnulo x) {}
												}
										}

									for (unsigned k = 0; k < 4; ++k)
										if (w[k].Sentido(v[1], v[0]))
											{
												try
													{
														Punto p = Segmento(v[0], v[1]) * Recta(w[k], m);
														min = Min ((w[k] - p).mod, min);
													}
												catch (xPnulo x) {}
											}}

							if (!Comp (dMax, min))
								{
									dMax = min;

									if (prim)
										*prim = u;
								}}}

      for (unsigned i = 0; i < 2; ++i)
				{
					Recta r(v[i], m);
					for (unsigned j = 0; j < 4; ++j)
						{
							Segmento s(esc[j], esc[(j + 1) % 4]);

							try
								{
									Punto p = s * r;
									Segmento s(v[i], p);

									if (v[1].Sentido(v[0], p))
										dMax = Min (s.l, dMax);
								}
							catch(xPnulo x){}
						}
				}
    }

  return (dMax);
}

// GestorEscenario::PivotMaxIzq
/*************************************/
float GestorEscenario::PivotMaxIzq (const Estado& E, Unidad *uAct) const
{
  // Construcción matemática compleja.
  float angMax = 0;

  if (uAct)
    {
      angMax = Min (uAct->AngMax(), AngGR(359));

      Segmento r(uAct->Psi(), uAct->Psd());
      Circunferencia c(r.a, (uAct->Psi() - uAct->Pid()).mod);

      for (int i = 0; i < 3 && Mayor (angMax, 0); ++i)
				{
					const Ejercito *e = E.pEjer ((Ejer)i);

					for (unsigned j = 0; j < e->nUnidades() && Mayor (angMax, 0); ++j)
						{
							Unidad *u = (*e)[j];

							if (u->Activo() && u != uAct)
								{
									Punto w[4] = { u->Psi(), u->Psd(), u->Pid(), u->Pii() };

									for (int k = 0; k < 4 && Mayor (angMax, 0); ++k)
										{
											Segmento s(w[k], w[(k + 1) % 4]);

											if (c << s.a)
												{
													Segmento t(Circunferencia(c.o, Segmento (c.o, s.a).l) * Circunferencia(s.a, DistSeg));

													angMax = Min (r ^ Recta(c.o, t.a), angMax);
													if (t.a != t.b)
														angMax = Min (r ^ Recta(c.o, t.b), angMax);
												}

											try
												{
													Segmento t(c * s);
													Segmento u(c * Circunferencia(t.a, DistSeg));

													angMax = Min (r ^ Recta(c.o, u.a), angMax);

													if (u.a != u.b)
														angMax = Min (r ^ Recta(c.o, u.b), angMax);

													if (t.a != t.b)
														{
															Segmento v(c * Circunferencia (t.b, DistSeg));

															angMax = Min (r ^ Recta (c.o, v.a), angMax);
															if (v.a != v.b)
																angMax = Min (r ^ Recta (c.o, v.b), angMax);
														}}
											catch (xPnulo x) {}
										}}}}

      for (int i = 0; i < 4 && Mayor (angMax, 0); ++i)
				{
					Segmento s(esc[i], esc[(i + 1) % 4]);
					try
						{
							Segmento t(c * s);

							angMax = Min (r ^ Recta(c.o, t.a), angMax);
							if (t.a != t.b)
								angMax = Min (r ^ Recta(c.o, t.b), angMax);
						}
					catch (xPnulo x) {}
				}

      if (Menor (angMax, 0))
				angMax = 0;
    }

  return (angMax);
}

// GestorEscenario::PivotMaxDer
/*************************************/
float GestorEscenario::PivotMaxDer (const Estado& E, Unidad *uAct) const
{
  // Construcción matemática compleja.
  float angMax = 0;

  if (uAct)
    {
      angMax = Min (uAct->AngMax(), AngGR(359));

      Segmento r(uAct->Psd(), uAct->Psi());
      Circunferencia c(r.a, (uAct->Psi() - uAct->Pid()).mod);

      for (int i = 0; i < 3 && Mayor (angMax, 0); ++i)
				{
					const Ejercito *e = E.pEjer ((Ejer)i);

					for (unsigned j = 0; j < e->nUnidades() && Mayor (angMax, 0); ++j)
						{
							Unidad *u = (*e)[j];

							if (u->Activo() && u != uAct)
								{
									Punto w[4] = { u->Psi(), u->Psd(), u->Pid(), u->Pii() };

									for (int k = 0; k < 4 && Mayor (angMax, 0); ++k)
										{
											Segmento s(w[k], w[(k + 1) % 4]);

											if (c << s.a)
												{
													Segmento t(Circunferencia(c.o, Segmento (c.o, s.a).l) * Circunferencia(s.a, DistSeg));

													angMax = Min (Recta(c.o, t.a) ^ r.r, angMax);

													if (t.a != t.b)
														angMax = Min (Recta(c.o, t.b) ^ r.r, angMax);
												}

											try
												{
													Segmento t(c * s);
													Segmento u(c * Circunferencia(t.a, DistSeg));

													angMax = Min (Recta (c.o, u.a) ^ r.r, angMax);

													if (u.a != u.b)
														angMax = Min (Recta (c.o, u.b) ^ r.r, angMax);

													if (t.a != t.b)
														{
															Segmento v(c * Circunferencia (t.b, DistSeg));

															angMax = Min (Recta (c.o, v.a) ^ r.r, angMax);

															if (v.a != v.b)
																angMax = Min (Recta (c.o, v.b) ^ r.r, angMax);
														}}
											catch (xPnulo x) {}
										}}}}

      for (int i = 0; i < 4 && Mayor (angMax, 0); ++i)
				{
					Segmento s(esc[i], esc[(i + 1) % 4]);
					try
						{
							Segmento t(c * s);

							angMax = Min (Recta(c.o, t.a) ^ r.r, angMax);

							if (t.a != t.b)
								angMax = Min (Recta(c.o, t.b) ^ r.r, angMax);
						}
					catch (xPnulo x) {}
				}

      if (Menor (angMax, 0))
				angMax = 0;
    }

  return (angMax);
}

// GestorEscenario::Visible
/*************************************/
bool GestorEscenario::Visible (const Estado& E, Unidad *u) const
{
  Unidad *uAct = E.UnidadActual();

  Rectangulo r(uAct->R());

  // Para establecer si una unidad vé a otra, comprobamos que exista al menos una franja contínua de 5 decímetros
  //  que 'vea' a otra franja continua de 5 decímetros de la unidad objetivo. Establecemos dos segmentos, el frente
  //  de la unidad que está mirando, y el segmento (diagonal de la unidad) que separa la parte de la unidad objetivo
  //  que es ocultada por el resto de la unidad. Éste segmento, si puede ser visto (obviando todos los efectivos de la
  //  misma que estén delante), se podrá concluir que la unidad ha sido vista.
  Segmento s(r.a, r.b);

  // Sólo tenemos el frente de la unidad, necesitamos el punto de convergencia de las lineas de visibilidad.
  Semidisco sc(AnguloVision (E, uAct));

	pair<Dir, Dir> indices = SegVision (E, uAct, u);
	Segmento t(u->Lado(indices.first, false).a, u->Lado(indices.second, false).b);

	// El segmento de visión debe estar completamente dentro del ángulo
	// de visión.
	if (!(sc << t.a || sc << t.b))
		return (false);

	float amplitudVision = u->Atributos().ro.x / 2;

  // Puntos de transformación, para desplazarnos de 5 en 5 decímetros en segmento, con su ángulo dado.
  Punto w(amplitudVision * cos (r.ang), amplitudVision * sin (r.ang));
  Punto x(amplitudVision * cos (t.r.ang), amplitudVision * sin (t.r.ang));

  Segmento a(r.a, r.a + w);

  while (Mayor (Segmento (a.a, s.b).l, amplitudVision - 0.5)) // Para no sobrepasar, tras tantos incrementos, los segmentos.
    {
			Segmento b(t.a, t.a + x);
      while (Mayor (Segmento (b.a, t.b).l, amplitudVision - 0.5))
				{
					try
						{
							Cuadrilatero cd(a.a, a.b, b.a, b.b);

							Segmento pC[2] = { Segmento(cd.a, cd.d), Segmento(cd.b, cd.c) };

							bool cont = true;
							for (unsigned i = 0; cont && i < 3; ++i)
								{
									const Ejercito *e = E.pEjer ((Ejer)i);

									for (unsigned j = 0; cont && j < e->nUnidades(); ++j)
										{
											Unidad *w = (*e)[j];
											if (w->Activo() && w != uAct && w != u)
												{
													Segmento pS[4] = { w->Lado(FRE, true), w->Lado(DER, true),
																						 w->Lado(RET, true), w->Lado(IZQ, true) };

													for (short k = 0; cont && k < 4; ++k)
														for (short l = 0; cont && l < 2; ++l)
															{
																try
																	{
																		pS[k] * pC[l];
																		cont = false;
																	}	
																catch (xPnulo){}
																catch (xScoincidentes) { cont = false; }
															}
												}
										}
								}
							// Si ha recorrido todo el bucle de forma "limpia", cont
							// == true y la franja de visión estará limpia.
							if (cont)
								return (true);
						}
					catch (xCDnulo x){}

					b = Segmento (b.b, b.b + x);
				}
      a = Segmento (a.b, a.b + w);
    }

  return (false);
}

// GestorEscenario::SegmentoVision
/*************************************/
pair<Dir, Dir> GestorEscenario::SegVision (const Estado& E, Unidad *u, Unidad *v) const
{
	/*
	 *
	 *  La recta de visión será la diagonal de 'v' mejor posicionada
	 *  respecto a 'u' (la que haga invisible para 'u' el resto de la
	 *  unidad 'v').
	 *
	 *  Para obtener el segmento de visión, obtenemos la recta que llega
	 *  desde el centro del frente de la unidad u, hasta el centro del
	 *  rectángulo de la unidad v.
	 *
	 *  La arista de v que se cruce con dicho segmento, será nuestro
	 *  segmento de referencia.
	 *
	 *  Según la inclinación de dicho segmento, el segmento de visión
	 *  será una u otra diagonal.
	 *
	 */
	Punto p(u->Lado(FRE,false).Mediatriz());
	Segmento Vsg[4] = { v->Lado(FRE, false), v->Lado(DER, false),
											v->Lado(RET, false), v->Lado(IZQ, false) };
	Punto centro(Segmento(Vsg[0].a, Vsg[1].b).Mediatriz());

	// Segmento entre centros.
	Segmento segCentros(p, centro);

	/*
	 *  Segmento entre centros.
	 */
	bool continuar = true;
	int i = 0;
	while(i < 4 && continuar)
		{
			try
				{
					segCentros * Vsg[i];
					// 'i' es el índice del segmento.
					continuar = false;
				}
			catch(xPnulo x)
				{
					++i;
				}
		}

	/*
	 *  Determinamos el segmento de visión.
	 */
	float dist1 = (Vsg[i].a - p).mod;
	float dist2 = (Vsg[i].b - p).mod;

	Dir d, f;

	if (Mayor(dist1, dist2))
		{
			d = (Dir)i;
			f = (Dir)((i + 1) % 4);
		}
	else if (Menor(dist1, dist2))
		{
			d = (Dir)((i + 3) % 4);
			f = (Dir)i;
		}
	else
		d = f = (Dir)i;

	return (make_pair(d, f));
}

// GestorEscenario::AnguloVision
/*************************************/
Semidisco GestorEscenario::AnguloVision (const Estado& E, Unidad *u) const
{
  Rectangulo r(u->R());

	/*
	 *  Ángulos de referencia.
	 */
	float vision = AngGR(60);
	float anguloCaracteristico = AngC(AngGR(90) - vision);
	float actual = AngC(r.ang - vision);

	/*
	 *  Triángulo de caracterización del origen.
	 */
	float hipotenusa = r.w / (2 * cos(anguloCaracteristico));
	float catetoContiguo = hipotenusa * cos(actual);
	float catetoOpuesto = hipotenusa * sin(actual);

	/*
	 *  Origen semidisco.
	 */
  Punto p(r.a + Punto(catetoContiguo, catetoOpuesto));

	float angInf = AngC(anguloCaracteristico + r.ang);
	float angSup = AngC(angInf + 2 * vision);

	return (Semidisco(p, angInf, angSup, inf));
}

// GestorEscenario::MovimientoCarga
/*************************************/
MovCarga GestorEscenario::MovimientoCarga (const Estado& E, const Carga& c) const
{
	/*
	 *  El procedimiento es buscar cual es la mejor posición de carga:
	 *  es decir, la que consigue trabar más efectivos. Se probarán
	 *  distintas posiciones, a intervalos discretos, y, si la carga es
	 *  efectiva, se actualiza si traba más efectivos que en la última
	 *  carga efectiva encontrada.
	 *
	 *  Si no hay ninguna posición en donde se produzca una carga
	 *  efectiva, la carga será fállida.
	 */
	pair<Dir, Dir> indicesSeg = SegVision(E, c.u, c.v);

	MovCarga M(c, Segmento());
	M.despl = inf;

	Segmento t(c.u->Lado(FRE, false));

	/*
	 *  Primer segmento de carga.
	 */
	Segmento r(c.v->Lado(indicesSeg.first, false));

	float amplitudVision = c.u->Atributos().ro.x / 2;

	// Punto de incremento gradual, para tener el siguiente segmento
	// ficticio.
	Punto p(amplitudVision * cos(r.r.ang), amplitudVision * sin(r.r.ang));
	// Primer segmento ficticio.
	Segmento w(r.a + p, AngC(r.r.ang + AngGR(180)), t.l);

	for (float max = t.l + r.l - amplitudVision * 2; Mayor (max, 0); max -= amplitudVision, w += p)
		{
			MovCarga Mi = MovSeg(c, w, (Dir)indicesSeg.first);

			if (MejorarMov(E, Mi, M))
				{
					M = Mi;
					M.efec = true;
				}
		}

	/*
	 *  Segundo segmento de carga.
	 */
	if (indicesSeg.first != indicesSeg.second)
		{
			Segmento r(c.v->Lado(indicesSeg.second, false));
			Punto p(amplitudVision * cos(r.r.ang), amplitudVision * sin(r.r.ang));

			// Segundo segmento ficticio.
			Segmento w(r.a + p, AngC(r.r.ang + AngGR(180)), t.l);

			for (float max = t.l + r.l - amplitudVision * 2; Mayor (max, 0); max -= amplitudVision, w += p)
				{
					MovCarga Mi = MovSeg(c, w, indicesSeg.second);

					if (MejorarMov(E, Mi, M))
						{
							M = Mi;
							M.efec = true;
						}
				}
		}

	/*
	 *  Devolución correcta.
	 */
	if (M.efec)
		return (M);
	else
			return (CargaFallida(E, M));
}

// GestorEscenario::Huida
/*************************************/
bool CompP(Unidad *u, Unidad *v) {	return (u->P() > v->P());	}

bool CompSeg(const pair<Unidad*, float>& s, const pair<Unidad*, float> t)
{
	return (Menor(s.second, t.second));
}

void GestorEscenario::Huida (const Estado& E, Unidad *u,
														 vector<Unidad*> *v) const
{
	u->Huir(true);

	/*
	 *  Obtenemos el segmento de partida (segmento dir).
	 */
	Segmento dir;

	Rectangulo R(u->R());

	// Si es huida de inicio de turno
	if (v == NULL)
		dir = Segmento(R.a, R.b);
	else
		{
			// El primer elemento del vector, será el de mayor potencia.
			sort (v->begin(), v->end(), CompP);

	 		// La dirección del segmento de partida estará orientado en la
	 		// dirección contraria a la unidad de 'v' de mayor potencia.
	 		dir = Segmento((R.b - R.a).mod, Segmento(R.a, R.c).Mediatriz(),
										 (*v)[0]->Ang());
	 		dir += R.h / 2;
	 	}

	// Distancia de huida.
  float distMin(u->MovMax() / 2);
	float distMax(3 * u->MovMax());

  float dist((NumAzar(distMin, distMax) + NumAzar(distMin, distMax)
							+ NumAzar(distMin, distMax)) / 3);

	/*
	 *  Obtenemos el conjunto de unidades que se encuentran en el camino
	 *  de huida de la unidad, ordenados según la proximidad del
	 *  'SiguienteEmplazamiento' a 'dir'.
	 */
	vector<pair<Unidad*, float> > vUnidades;

	vUnidades.push_back(make_pair(u, 0));

	Rectangulo r((dir + DistSeg - 1).b, R.w, inf, AngC(dir.r.ang + AngGR(180)));

	for (unsigned i = 0; i < 3; ++i)
		{
			const Ejercito *e = E.pEjer ((Ejer)i);

			for (unsigned j = 0; j < e->nUnidades(); ++j)
				{
					Unidad *w = (*e)[j];

					if (w->Activo() && (r << w->Psd() || r << w->Psi() ||
															r << w->Pid() || r << w->Pii() ||
															r << Segmento(w->Psd(), w->Pii()).Mediatriz()))
						vUnidades.push_back(make_pair(w, SigEmplazamiento(dir, w, true)));
				}
		}

	int i = 0;
	if (vUnidades.size())
		{
			sort(vUnidades.begin(), vUnidades.end(), CompSeg);

			// Añadimos una 'unidad' final para evitar desbordamientos.
			vUnidades.push_back(make_pair(u, inf));

			/*
			 *  Nos colocamos en la posición de 'corte' (todas aquellas
			 *  unidades sobre las cuales sabemos que vamos a dejar
			 *  completamente atrás al movernos, al menos, dist).
			 */
			while (i + 1 < (int)vUnidades.size() && Menor(vUnidades[i + 1].second, dist))
				++i;

			/*
			 *  Conseguimos ahora el vector de 'AnteriorEmplazamiento', a partir
			 *  del 'punto' de corte.
			 *
			 *  NOTA: Es importante hacer este cálculo a posteriori, y no junto
			 *  al bucle anterior, porque calculamos los 'anteriores
			 *  desplazamientos' de forma 'ordenada'.
			 */
			vector<float> vAntEmplazamiento;

			for (unsigned j = i + 1; j < vUnidades.size(); ++j)
				{
					if (j == vUnidades.size() - 1)
						vAntEmplazamiento.push_back(inf);
					else
						vAntEmplazamiento.push_back(SigEmplazamiento(dir, vUnidades[j].first, false));
				}

			/*
			 *  Calculamos, a partir del punto de corte, la primera posición donde
			 *  la unidad que huye 'cabe' entre unidades.
			 */
			// Estudiamos el caso base (j == 0) -ver bucle, abajo-.
			bool continuar = true;

			{
				float separacion;

				if (vAntEmplazamiento.empty())
					separacion = inf;
				else
					separacion = vAntEmplazamiento[0] - dist - DistSeg;

				float profundidad = vUnidades[i].second - (dist - R.h) + DistSeg;

				if (!Menor (separacion, 0) && !Menor (separacion, profundidad))
					{
						continuar = false;

						if (Mayor (profundidad, 0))
							dist += profundidad;
					}
			}

			if (continuar)
				{
					for (unsigned j = 1; continuar && j < vAntEmplazamiento.size(); ++j)
						{
							float distBase = vUnidades[i + j].second;
							float distSegm = vAntEmplazamiento[j] - distBase;

							if (!Menor (distSegm, R.h + 2 * DistSeg))
								{
									dist = distBase + R.h + DistSeg;
									i += j + 1;
									continuar = false;
								}
						}
				} // fin if continuar.
			else
				++i;
		} // Fin if(vUnidades.size());


	/*
	 *  Movemos a la unidad.
	 */
	u->Trasladar(dir + dist);

	if (vUnidades.size())
		{
			/*
			 *  Calculamos el efecto de todas las unidades por las que pasa la
			 *  unidad que huye.
			 */
			for (int j = 1; j < i && u->N(); ++j)
				{
					Unidad *w = vUnidades[j].first;

					if (w->uEjercito() == u->uEjercito())
						{
							if (!w->Huyendo() && !w->Combatiendo())
								{
									bool huir = !Chequeo(w->Atributos().l);

									if (huir)
										{
											vector<Unidad*> aux;

											aux.push_back(u);

											Huida(E, w, &aux);
										}
								}
						}
					else if (w->eEjercito() != eGAIA)
						u->MenosEfectivos(.5 + w->Heridas() / 2);
				}
		} // Fin 'if (vUnidades.size())'

	/*
	 * Calculamos los efectos de magia.
	 */
	unsigned prob = rand() % 4;

	if (prob > 1)
		prob -= 1;
						
	u->ModificarAtributo(rand() % 12, -prob);

	/*
	 * Si procede, eliminamos a la unidad del combate.
	 */
	if (!u->N() || FueraCampo(u))
		u->Eliminar();
}

// GestorEscenario::DistanciaUnidades
/*************************************/
float GestorEscenario::DistanciaUnidades (Unidad *u, Unidad *v, int i, int j) const
{
	Rectangulo R1;(u->R());
	Rectangulo R2;

	if (i >= 0)
		R1 = u->Efec(i);
	else
		R1 = u->R();

	if (j >= 0)
		R2 = v->Efec(j);
	else
		R2 = v->R();

	Punto c1(Segmento(R1.a, R1.c).Mediatriz());
	Punto c2(Segmento(R2.a, R2.c).Mediatriz());

	return ((c2-c1).mod);
}

// GestorEscenario::ResultadoCombate
/*************************************/
Resultado GestorEscenario::ResultadoCombate (const Estado& E) const
{
	Resultado R;

	for (unsigned i = 0; i < 2; ++i)
		{
			const Ejercito *e = E.pEjer ((Ejer)i);

			for (unsigned j = 0; j < e->nUnidades(); ++j)
				{
					Unidad *w = (*e)[j];

					if (w->Activo() && !w->Huyendo() && w->P() >= 5)
						{
							int puntosUnidad = w->Puntos();

							if (Menor((float)w->N() / w->NO(), 0.5))
								puntosUnidad /= 2;

							R.puntos[w] = puntosUnidad;
							R.totalU[i] += puntosUnidad;

							Punto p = w->R().Centro() - (esc[1] * 0.5);

							for (unsigned j = 0; j < 4; ++j)
								if (Cuad(j + 1, p))
									R.cuad[i][j] += w->P();
						}
					else
						R.puntos[w] = 0;
				}
		}

	for (unsigned i = 0; i < 4; ++i)
		{
			if (R.cuad[0][i] == R.cuad[1][i])
				R.cuad[0][i] = R.cuad[1][i] = 0;
			else
				{
					if (R.cuad[0][i] > R.cuad[1][i])
						{
							R.cuad[0][i] = 1;
							R.cuad[1][i] = 0;
						}
					else
						{
							R.cuad[0][i] = 0;
							R.cuad[1][i] = 1;
						}
				}

			R.totalU[0] += 100 * R.cuad[0][i];
			R.totalU[1] += 100 * R.cuad[1][i];
		}

	R.total = R.totalU[0] - R.totalU[1];

	/*
	 *  Creamos un índice que indique al perdedor.
	 */
	int perdedor;

	if (R.total >= 0)
		perdedor = 1;
	else
		{
			perdedor = 0;
			R.total *= -1;
		}

	if (R.total >= 2 * R.totalU[perdedor])
		R.v = Masacre;
	else if (R.total >= R.totalU[perdedor])
		R.v = VictoriaDecisiva;
	else if (R.total >= R.totalU[perdedor] / 2)
		R.v = VictoriaMarginal;
	else
		R.v = Empate;

	/*
	 * Recuperamos el valor original de R.total.
	 */
	if (perdedor == 0)
		R.total *= -1;

	return (R);
}

// GestorEscenario::FueraCampo
/*************************************/
bool GestorEscenario::FueraCampo (Unidad *u) const
{
  Rectangulo R(u->R());

	Rectangulo ESC(esc[0], esc[1].x, esc[1].y, 0);

	return (!(ESC << R.a) || !(ESC << R.b) || !(ESC << R.c) || !(ESC << R.d));
}

// GestorEscenario::MovSeg
/*************************************/
MovCarga GestorEscenario::MovSeg (const Carga& c, const Segmento& s, Dir d) const
{
  MovCarga m(c, s);

	m.C.d = d;
  m.despl = (c.u->Lado (FRE, true).Mediatriz() - s.Mediatriz()).mod;

  Unidad *vir = c.u->UnidadVirtual();
  vir->Trasladar(s);
  m.nEfec = vir->Contacto(c.v->Lado(d, true), FRE) + c.v->Contacto(s, d);

  delete vir;

  return (m);
}

// GestorEscenario::MejorarMov
/*************************************/
bool GestorEscenario::MejorarMov (const Estado& E, MovCarga c, MovCarga& C) const
{
  if (Menor(c.despl, c.C.u->MovMax()) && (!C.efec || (c.nEfec > C.nEfec) ||
																						(c.nEfec == C.nEfec && Menor (c.despl, C.despl))))
    {
			Cuadrilatero cd(C.C.u->Psi(), C.C.u->Psd(), c.s.a, c.s.b);
      
      Unidad *vir = C.C.u->UnidadVirtual();

      vir->Trasladar(c.s);
      Rectangulo R(vir->R());

			delete vir;

      for (unsigned i = 0; i < 3; ++i)
				{
					const Ejercito *e = E.pEjer ((Ejer)i);

					for (unsigned j = 0; j < e->nUnidades(); ++j)
						{
							Unidad *w = (*e)[j];

							if (w->Activo() && w != C.C.u && w != C.C.v)
								{
									Punto vPuntosW[5] = { w->Psi(), w->Psd(), w->Pid(),
																				 w->Pii(), Segmento(w->Psi(), w->Pid()).Mediatriz() };

									for (short k = 0; k < 5; ++k)
										{
											Punto p = vPuntosW[k];

											if (cd << p || R << p)
												return (false);
										}
								}
						}
				}

			return (true);
		}

	return (false);
}

// GestorEscenario::SigEmplazamiento
/*************************************/
float GestorEscenario::SigEmplazamiento (const Segmento& s, Unidad *u, bool sig) const
{
  float sol;

	if (sig)
		sol = 0;
	else
		sol = inf;

  float angC(AngC (s.r.ang + AngGR(90)));
  Segmento sV[2] = { Segmento(s.a, angC, inf), Segmento(s.b, angC, inf) };
  Segmento lV[4] = { u->Lado(FRE, false), u->Lado(DER, false), u->Lado(RET, false), u->Lado(IZQ, false) };

  for (short j = 0; j < 4; ++j)
    {
      try
				{
					Punto x(s * Recta(lV[j].a, angC));
					float dist((lV[j].a - x).mod);

					if (sig && Mayor (dist, sol))
						sol = dist;
					else if (!sig && !Mayor (dist, sol))
						sol = dist;
				}
      catch(...) {}

      for (short i = 0; i < 2; ++i)
				try
					{
						Punto x(sV[i] * lV[j]);
						float dist = (x - sV[i].a).mod;	

						if (sig && Mayor (dist, sol))
							sol = dist;
						else if (!sig && !Mayor (dist, sol))
							sol = dist;
					}
				catch (...) {}
    }

  return (sol);
}

// GestorEscenario::CargaFallida
/*************************************/
MovCarga GestorEscenario::CargaFallida (const Estado& E, MovCarga C) const
{
	C.despl = Min (DesplMax(E, C.C.u), C.C.u->MovMax() / 3);

	C.efec = false;

	C.s = C.C.u->Lado(FRE, true) + C.despl;

	return (C);
}

// GestorEscenario::Chequeo
/*************************************/
bool GestorEscenario::Chequeo (unsigned a) const
{
  if (a > 10)
    a = 10;
  else if (a < 0)
    a = 0;
		
  unsigned azar = NumAzar((unsigned)1, (unsigned)10);

  return (azar != 1 && (azar == 10 || azar <= a));
}

// GestorEscenario::Chequeo
/*************************************/
bool GestorEscenario::Chequeo (unsigned a, unsigned b) const
{
  return (Chequeo (5 - (b - a)));
}
