#pragma once

#include "Defines.h"
#include "Includes.h"

class Borde
{
private:
	int			_id;
	SDL_Rect	_ubicacion;
	int			_borde;
	Uint32		_color;
public:
	Borde( int x, int y, int w, int h, int grosor, Uint32 color );
	~Borde();
	void Dibujar( SDL_Surface* window );
};