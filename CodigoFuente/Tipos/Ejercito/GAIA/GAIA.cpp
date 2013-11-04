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
#include <cstdlib>
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include "GAIA.h"

using namespace std;

// GAIA::GAIA
/*************************************/
GAIA::GAIA (Ejer _e) : Ejercito("GAIA"), e(_e)
{}

// GAIA::~GAIA
/*************************************/
GAIA::~GAIA()
{}

// GAIA::InicializarGAIA
/*************************************/
void GAIA::InicializarGAIA(double fw, double fh, SDL_Surface *s)
{
	SDL_Surface *sOr, *bosque, *edificio;

	if (!(sOr = IMG_Load("Imagenes/Peanas/GAIA/bosque.png")))
		cerr << SDL_GetError() << endl;

	if (!(bosque = zoomSurface(sOr, fw, fh, 0)))
		cerr << SDL_GetError() << endl;

	delete sOr;

	if (!(sOr = IMG_Load("Imagenes/Peanas/GAIA/edificio.png")))
		cerr << SDL_GetError() << endl;

	if (!(edificio = zoomSurface(sOr, fw, fh, 0)))
		cerr << SDL_GetError() << endl;

	delete sOr;

	// Habrá entre 2 y 3 elementos GAIA.
	unsigned num(2 + rand() % 2);

	// Dividimos el escenario en num secciones, y colocamos un elemento
	// de escenografía en cualquier posición aleatoria dentro de esa
	// sección, pero respetando un borde de 100.
	unsigned anchocuad = 1000 / num;
	unsigned altocuad = 300;

	unsigned limiteHinf = 140;
	unsigned limiteVinf = 450;
	unsigned sensibilidad = 40;

	/*
	 *  Un solo edificio.
	 */
	unsigned cuadedificio(rand() % num);

	Edificio *e = new Edificio("", this, fw, fh);

	// El edificio ocupa 200 x 94.
	unsigned desplH(rand() % (anchocuad - edificio->w - 2 * sensibilidad));
	unsigned desplV(rand() % (altocuad - edificio->h - 2 * sensibilidad));
	Punto posEdificio(limiteHinf + sensibilidad + anchocuad * cuadedificio + desplH,
										limiteVinf - sensibilidad - desplV);

	e->Inicializar(posEdificio, edificio, s, fw, fh);

	Ejercito::NuevaUnidad (e);

	for (unsigned i = 0; i < num; ++i)
		{
			if (i != cuadedificio)
				{
					Bosque *b = new Bosque("", this, fw, fh);

					desplH = rand() % (anchocuad - 120 - 2 * sensibilidad);
					desplV = rand() % (altocuad - 120 - 2 * sensibilidad);

					Punto posBosque(limiteHinf + sensibilidad + desplH,
													limiteVinf - sensibilidad - desplV);

					unsigned frente = 4 + rand() % 3;
					unsigned alto = 4 + rand() % 3;

					b->Inicializar(posBosque, frente, alto, bosque, s, fw, fh);

					Ejercito::NuevaUnidad (b);
				}

			limiteHinf += anchocuad;
		}

	delete bosque;
}

// GAIA::NuevaUnidad
/*************************************/
Unidad* GAIA::NuevaUnidad (string nombre, double fw, double fh)
{
	return (NULL);
}
