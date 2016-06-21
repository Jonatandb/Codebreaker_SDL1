#pragma once

#include "Defines.h"
#include "Includes.h"
#include <sstream>		// Para ostringstream

class Carta;	// http://stackoverflow.com/a/23283140

class Mazo
{
private:
	int _id;
	SDL_Rect _ubicacion;
	int	_posCartaActiva;
	Carta *_carta[ CARTAS_POR_MAZO ];
public:
	Mazo( SDL_Rect ubicacion );
	~Mazo();
	bool Dibujar( SDL_Surface* window );
	SDL_Rect Posicion();
	void ActivarCartaSiguiente();
	void ActivarCartaAnterior();
	void ActivarCarta( int carta );
	int CartaActiva();
};
