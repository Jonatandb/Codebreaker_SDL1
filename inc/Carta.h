#pragma once

#include "Defines.h"
#include "Includes.h"

class Carta
{
private:
	int				_id;
	SDL_Rect		_origen;
	int				_valor;
	SDL_Surface*	_imagen;
public:
	Carta( int valor, string ruta, int x, int y, int w, int h );
	~Carta();
	bool Dibujar( SDL_Surface* window, SDL_Rect destino );
};