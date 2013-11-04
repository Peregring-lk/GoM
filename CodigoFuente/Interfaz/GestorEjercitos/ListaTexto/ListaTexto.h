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

/*! \file ListaTexto.h
 *  \brief Fichero que define a la clase \c ListaTexto.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */
#ifndef _LISTA_TEXTO_
#define _LISTA_TEXTO_

#include <vector>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

const int iNULO = -1;

typedef SDL_Surface* Img;

bool InRect (const SDL_Rect& r, int a, int b);

struct Item
{
  Img imagenTexto;
  Img etiqueta;
  std::string texto;
  SDL_Rect cuadro;
};

/*! \class ListaTexto
 *  \brief Clase de la clase \c ListaTexto.
 *
 *  \sa GestorInterfaz
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2010
 *  \version 1
 *  \since 1
 */	
class ListaTexto
{
 public:
  /* Constructores y destructor */
  ListaTexto(TTF_Font* fuente, SDL_Color color, SDL_Rect marco, Img selector, Img marcador, Img base = NULL);

  ~ListaTexto();

  /* Lectoras */
  std::string LeerTexto(int iTexto) const;

  void Imprimir (Img screen);

  int SiguienteId() const;

  int Marcado() const;

  bool Marcado(int iTexto) const;

  /* Modificadoras */
  void Marcar(int iTexto);

  int NuevoTexto (std::string texto);

  void CambiarColor (int iTexto, SDL_Color _color);

  void ModificarTexto (int iTexto, std::string texto);

  void EliminarTexto(int iTexto);

  void NuevaEtiqueta (int iTexto, Img etiqueta);

  void EliminarEtiqueta(int iTexto);

	void LimpiarEtiquetas();

  int Evento (int a, int b, bool click);

  void Reiniciar();

  void Vaciar();

 private:
  /* Atributos de configuracion */
  TTF_Font *fuente;
  SDL_Color color;

  SDL_Rect marco;
  SDL_Rect rsubir, rbajar;
  unsigned h, filas;

  Img selector;
  Img marcador;
  Img base;
  Img subir, bajar;

  /* Atributos de estado */
  bool bsubir, bbajar;

  unsigned inicio, final;

  int textoSeleccionado;
  int textoMarcado; 

  std::vector<Item> lista;
};

#endif
