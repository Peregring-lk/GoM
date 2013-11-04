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

/*! \file ListaTexto.cpp
 *  \brief Implementación de la clase \c ListaTexto.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#include <iostream>
#include "SDL/SDL_image.h"
#include "ListaTexto.h"
#include "../../../Tipos/Matematicas.h"

using namespace std;

// ListaTexto::InRect
/*************************************/
bool InRect (const SDL_Rect& r, int a, int b)
{
  return (Intervalo(r.x, r.x + r.w, a) && Intervalo(r.y, r.y + r.h, b));
}

// ListaTexto::ListaTexto
/*************************************/
ListaTexto::ListaTexto(TTF_Font* fuente, SDL_Color color,
											 SDL_Rect marco, Img selector, Img marcador,
											 Img base)
  : fuente(fuente), color(color), marco(marco),
		selector(selector), marcador(marcador), base(base)
{
  if (!(subir = IMG_Load("Imagenes/Especiales/flechaListaUp.png")))
    cerr << SDL_GetError() << endl;
  if (!(bajar = IMG_Load("Imagenes/Especiales/flechaListaDown.png")))
    cerr << SDL_GetError() << endl;

  if (base)
    {
      h = base->h;
      marco.h = 0;
    }
  else
    h = TTF_FontHeight(fuente);

  filas = marco.h / h;

  inicio = final = 0;

  bbajar = bsubir = false;

  rsubir.x = rbajar.x = marco.x + marco.w - subir->w - 15;
  rsubir.y = marco.y + 15;
  rbajar.y = marco.y + marco.h - subir->h - 15;

  rsubir.w = subir->w;
  rbajar.w = bajar->w;
  rsubir.h = subir->h;
  rbajar.h = bajar->h;

  textoSeleccionado = iNULO;
  textoMarcado = iNULO;
}

// ListaTexto::LeerTexto
/*************************************/
string ListaTexto::LeerTexto (int iTexto) const
{
  if (iTexto != iNULO)
    return (lista[iTexto].texto);
  else
    return ("");
}

// ListaTexto::Imprimir
/*************************************/
void ListaTexto::Imprimir (Img screen)
{
  for (unsigned i = inicio; i < final; ++i)
    {
      Item& item = lista[i];

      SDL_Rect r = item.cuadro;
      SDL_Rect rimagenTexto = { r.x, r.y, 0, 0 };

      if (item.texto != "")
				{
					rimagenTexto.w = item.imagenTexto->w;
					rimagenTexto.h = item.imagenTexto->h;
				}

      r.y -= inicio * h;

      if (base)
				SDL_BlitSurface (base, 0, screen, &r);

      r.x += (r.w - rimagenTexto.w) / 2;
      r.y += (r.h - rimagenTexto.h) / 2;

      r.w = rimagenTexto.w;
      r.h = rimagenTexto.h;

      if (item.etiqueta)
				{
					SDL_Rect s = r;

					r.x -= item.etiqueta->w / 2;
					s.x += r.w;
					s.y -= (item.etiqueta->h - r.h) / 2;

					s.h = item.etiqueta->h;
					s.w = item.etiqueta->w;

					SDL_BlitSurface (item.etiqueta, NULL, screen, &s);
				}

      if (item.texto != "")
				SDL_BlitSurface (item.imagenTexto, NULL, screen, &r);
    }

  if (bbajar)
		SDL_BlitSurface (bajar, NULL, screen, &rbajar);

  if (bsubir)
		SDL_BlitSurface (subir, NULL, screen, &rsubir);

  if (selector && textoSeleccionado >= (int)inicio && textoSeleccionado < (int)final)
    {
      SDL_Rect r = lista[textoSeleccionado].cuadro;

      r.x += (r.w - selector->w) / 2;
      r.y += (h - selector->h) / 2;
      r.y -= inicio * h;

      if (base)
				r.y += (base->h - h) / 2;

      SDL_BlitSurface (selector, 0, screen, &r);
    }

  if (marcador && textoMarcado >= (int)inicio && textoMarcado < (int)final)
    {
      SDL_Rect r = lista[textoMarcado].cuadro;

      r.x += (r.w - marcador->w) / 2;
      r.y += (h - marcador->h) / 2;
      r.y -= inicio * h;

      if (base)
				r.y += (base->h - h) / 2;

      SDL_BlitSurface (marcador, 0, screen, &r);
    }
}

// ListaTexto::SiguienteId
/*************************************/
int ListaTexto::SiguienteId() const
{
  return (lista.size());
}

// ListaTexto::SiguienteId
/*************************************/
int ListaTexto::Marcado() const
{
  return (textoMarcado);
}

// ListaTexto::Marcado
/*************************************/
bool ListaTexto::Marcado(int iTexto) const
{
  return (iTexto == textoMarcado);
}

// ListaTexto::Marcado
/*************************************/
void ListaTexto::Marcar(int iTexto)
{
  if (iTexto > iNULO && (unsigned)iTexto < lista.size())
    textoMarcado = iTexto;
}

// ListaTexto::NuevoTexto
/*************************************/
int ListaTexto::NuevoTexto(string texto)
{
  SDL_Rect r;

  if (lista.empty())
    {
      r = marco;

      if (base)
				{
					r.h = base->h;
					marco.h = r.h;
				}
      else
				r.h = h;
    }
  else
    {
      r = lista[lista.size() - 1].cuadro;

      if (base)
				{
					r.y += r.h;
					marco.h += r.h;
				}
      else
				r.y += h;
    }

  Item item;

  item.cuadro = r;
  item.texto = texto;
  item.etiqueta = 0;
  item.imagenTexto = TTF_RenderUTF8_Solid (fuente, texto.c_str(), color);

  lista.push_back(item);
  ++final;

  if (!base && final > filas)
    {
      inicio += (lista.size() - final) + 1;
      final = lista.size();

      bsubir = true;
      bbajar = false;
    }

  return (lista.size() - 1);
}

// ListaTexto::CambiarColor
/*************************************/
void ListaTexto::CambiarColor (int iTexto, SDL_Color _color)
{
  if (iTexto > iNULO && (unsigned)iTexto < lista.size() && lista[iTexto].imagenTexto)
    {
      delete lista[iTexto].imagenTexto;
      lista[iTexto].imagenTexto = TTF_RenderUTF8_Solid (fuente, lista[iTexto].texto.c_str(), _color);
    }
}

// ListaTexto::ModificarTexto
/*************************************/
void ListaTexto::ModificarTexto (int iTexto, string texto)
{
  if ((unsigned)iTexto == lista.size())
    NuevoTexto(texto);
  else if (iTexto > iNULO && (unsigned)iTexto < lista.size())
    {
      if (lista[iTexto].imagenTexto)
				delete lista[iTexto].imagenTexto;

      lista[iTexto].texto = texto;
      lista[iTexto].imagenTexto = TTF_RenderUTF8_Solid (fuente, texto.c_str(), color);
    }
}

// ListaTexto::EliminarTexto
/*************************************/
void ListaTexto::EliminarTexto (int iTexto)
{
  if (iTexto > iNULO && (unsigned)iTexto < lista.size())
    {
			unsigned tam = lista.size();

      if (final == tam)
				{
					if (inicio)
						{
							--inicio;

							if (!inicio)
								bsubir = false;
						}

					--final;
				}
      else if (!iTexto && inicio == 1)
				bsubir = false;

      if (lista[iTexto].imagenTexto)
				delete lista[iTexto].imagenTexto;

      lista.erase(lista.begin() + iTexto);

			--tam;

			if (final == lista.size())
				bbajar = false;

			if ((unsigned)textoSeleccionado >= tam)
				{
					if (tam > 0)
						--textoSeleccionado;
					else
						textoSeleccionado = iNULO;
				}

			if ((unsigned)textoMarcado >= tam)
				{
					if (tam > 0)
						--textoMarcado;
					else
						textoMarcado = iNULO;
				}

      if (base)
				{
					marco.h -= base->h;

					while ((unsigned)iTexto < lista.size())
						lista[iTexto++].cuadro.y -= base->h;
				}
      else
				while ((unsigned)iTexto < lista.size())
					lista[iTexto++].cuadro.y -= h;
    }
}

// ListaTexto::NuevaEtiqueta
/*************************************/
void ListaTexto::NuevaEtiqueta(int iTexto, Img etiqueta)
{
  if ((unsigned)iTexto == lista.size())
    {
      NuevoTexto("");
      NuevaEtiqueta(iTexto, etiqueta);
    }
  else if (iTexto > iNULO && (unsigned)iTexto < lista.size())
    lista[iTexto].etiqueta = etiqueta;
}

// ListaTexto::NuevaEtiqueta
/*************************************/
void ListaTexto::EliminarEtiqueta(int iTexto)
{
  if (iTexto > iNULO && (unsigned)iTexto < lista.size())
    lista[iTexto].etiqueta = 0;
}

// ListaTexto::LimpiarEtiquetas
/*************************************/
void ListaTexto::LimpiarEtiquetas()
{
	for (unsigned i = 0; i < lista.size(); ++i)
		lista[i].etiqueta = 0;
}

// ListaTexto::Evento
/*************************************/
int ListaTexto::Evento (int a, int b, bool click)
{
  // Primero se comprueba donde está el "ratón" y sus efectos, y luego sus efectos adicionales si además click = true.
  if (lista.size() && (lista[0].texto != "" || lista[0].etiqueta) && InRect (marco, a, b))
    {
      textoSeleccionado = iNULO;

      if (bsubir && InRect (rsubir, a, b))
				{
					if (click)
						{
							--inicio;
							--final;

							bbajar = true;

							if (!inicio)
								bsubir = false;
						}

					return (iNULO);
				}
      else if (bbajar && InRect (rbajar, a, b))
				{
					if (click)
						{
							++inicio;
							++final;

							bsubir = true;

							if (final == lista.size())
								bbajar = false;
						}

					return (iNULO);
				}
      else
				{
					for (unsigned i = inicio; i < final; ++i)
						{
							SDL_Rect r = lista[i].cuadro;

							r.y -= inicio * h;

							if (InRect (r, a, b))
								{
									textoSeleccionado = i;

									if (click)
										{
											textoMarcado = i;

											return (textoMarcado);
										}
									else
										return (textoSeleccionado);
								}}

					textoSeleccionado = iNULO;

					if (click)
						textoMarcado = iNULO;

					return (iNULO);
				}
    }
  else
    {
      textoSeleccionado = iNULO;

      if (click)
				textoMarcado = iNULO;

      return (iNULO);
    }}

// ListaTexto::Reiniciar
/*************************************/
void ListaTexto::Reiniciar()
{
  textoSeleccionado = iNULO;
  textoMarcado = iNULO;
}

// ListaTexto::Vaciar
/*************************************/
void ListaTexto::Vaciar()
{
  lista.clear();

  bsubir = bbajar = false;
  inicio = final = 0;
  textoSeleccionado = textoMarcado = iNULO;
}

// ListaTexto::~ListaTexto
/*************************************/
ListaTexto::~ListaTexto()
{
  for (unsigned i = 0; i < lista.size(); i++)
    delete lista[i].imagenTexto;

  delete subir;
  delete bajar;
}
