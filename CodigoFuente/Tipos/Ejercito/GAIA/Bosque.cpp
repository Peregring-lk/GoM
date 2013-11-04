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
#include "Bosque.h"

using namespace std;

const Atrib Bosque::a = { "Bosque", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
													0, 0, Punto(20, 20), 0 };

// Bosque::Bosque
/*************************************/
Bosque::Bosque (string dir, GAIA *g, double fw, double fh)
	: Unidad(Bosque::a, "", (Ejercito*)g, 0, 0, fw, fh, "Bosque")
{}

// Bosque::Inicializar
/*************************************/
void Bosque::Inicializar(Punto posicion, unsigned frente, unsigned fondo,
												 SDL_Surface *bosque, SDL_Surface *s, double fw, double fh)
{
	Unidad::r = Rectangulo(posicion, (frente - 1) * a.ro.x, (fondo - 1) * a.ro.y, 0);

	SDL_Rect posS = { posicion.x - 10, posicion.y + 10, 20, 20 };

	posS.x = posS.x * fw;
	posS.y = (700 - posS.y) * fh;
	posS.w *= fw;
	posS.h *= fh;

	SDL_Rect posTile = { 0, 0, 20 * fw, 20 * fh };
	for (unsigned i = 0; i < frente; ++i)
		{
			for (unsigned j = 0; j < fondo; ++j)
				{
					SDL_BlitSurface(bosque, &posTile, s, &posS);

					if (!j || j + 1 == fondo - 1)
						posTile.y += 20 * fh;

					posS.y += 20 * fh;
				}

			posTile.y = 0;

			if (!i || i + 1 == frente - 1)
				posTile.x += 20 * fw;

			posS.x += 20 * fw;
			posS.y -= 20 * fondo * fh;
		}
}

// Bosque::UnidadVirtual
/*************************************/
Unidad* Bosque::UnidadVirtual()
{
	return (NULL);
}
