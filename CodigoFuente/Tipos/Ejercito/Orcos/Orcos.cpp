#include <iostream>
#include "Orcos.h"

using namespace std;

// Orcos::Orcos
/*************************************/
Orcos::Orcos (Ejer _e) : Ejercito("Orcos", _e), e(_e)
{}

// Orcos::~Orcos
/*************************************/
Orcos::~Orcos()
{}

// Orcos::NuevaUnidad
/*************************************/
Unidad* Orcos::NuevaUnidad (string nombre, double fw, double fh)
{
	bool guardar = true;
	string dir = "Imagenes/Peanas/Orcos/" + nombre;

	if (e == ePRIM)
		dir += "P";
	else if (e == eSEG)
		dir += "S";
	else
		guardar = false;

	dir += ".png";

	if (nombre == "Guerreros")
		Ejercito::NuevaUnidad (new Guerreros (dir, this, fw, fh));
	else if (nombre == "Trasgos")
		Ejercito::NuevaUnidad (new Trasgos (dir, this, fw, fh));
	else if (nombre == "Wargos")
		Ejercito::NuevaUnidad (new Wargos (dir, this, fw, fh));
	else if (nombre == "Onis")
		Ejercito::NuevaUnidad (new Onis (dir, this, fw, fh));
	else if (nombre == "Jabalíes")
		Ejercito::NuevaUnidad (new Jabalies (dir, this, fw, fh));
	else if (nombre == "Garms")
		Ejercito::NuevaUnidad (new Garms (dir, this, fw, fh));
	else if (nombre == "Abominación")
		Ejercito::NuevaUnidad (new Abominacion (dir, this, fw, fh));
	else if (nombre == "Gigante")
		Ejercito::NuevaUnidad (new Gigante (dir, this, fw, fh));
	else if (nombre == "Trolls")
		Ejercito::NuevaUnidad (new Trolls (dir, this, fw, fh));
	else
		guardar = false;

	if (guardar)
		return ((*this)[this->nUnidades() - 1]);
	else
		return (NULL);
}
