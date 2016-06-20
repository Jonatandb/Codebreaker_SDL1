#pragma once

#include "Defines.h"
#include "Includes.h"

class Nivel
{
private:
	int _id;
	int _nivelActual;
	int _cantidadMazos;
	int _maximosIntentos;
public:
	Nivel();
	~Nivel();
	int GetNivelActual();
	void SubirNivel();
	int GetMaximosIntentos();
	int GetCantidadMazos();
};