#pragma once

#include "Carta.h"

Carta::Carta( int valor, string ruta, int x, int y, int w, int h )
{
	_id = cRandom::getRandom();	//Logger::Log( "Carta\t\tId = " + to_string( _id) + "\t\tCreado." );
	_valor = valor;
	_origen.x = x;
	_origen.y = y;
	_origen.w = w;
	_origen.h = h;
	_imagen = SDL_LoadBMP( ruta.c_str() );
	if( _imagen == NULL )
	{
		printf( "Carta: Error cargando la imagen: %s\n", SDL_GetError() );
		_valor = -1;
	}
}

Carta::~Carta()
{
	//Logger::Log( "Carta\t\tId = " + to_string( _id) + "\t\tEliminado." );
	if( _imagen != NULL )
		SDL_FreeSurface( _imagen );
}

bool Carta::Dibujar( SDL_Surface* window, SDL_Rect destino )
{
	bool result = false;
	if( _valor != -1 && _imagen != NULL && SDL_BlitSurface( _imagen, &_origen, window, &destino ) == 0 )
		result = true;
	return result;
}
