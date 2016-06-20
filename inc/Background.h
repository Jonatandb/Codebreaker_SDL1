#pragma once

#include "Defines.h"
#include "Includes.h"

class Background
{
private:
	int _id;
	SDL_Surface* _imagen;
public:
	Background();
	~Background();
	void Dibujar( int nivelActual, int cantMazos, SDL_Surface* window );
};