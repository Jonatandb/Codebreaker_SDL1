#pragma once

#include "Borde.h"

Borde::Borde( int x, int y, int w, int h, int grosor, Uint32 color )
{
	_id = cRandom::getRandom();	////Logger::Log( "Borde\t\tId = " + to_string( _id) + "\t\tCreado." );
	_ubicacion.x = x;
	_ubicacion.y = y;
	_ubicacion.w = w;
	_ubicacion.h = h;
	_borde = grosor;
	_color = color;
}

Borde::~Borde()
{
	////Logger::Log( "Borde\t\tId = " + to_string( _id) + "\t\tEliminado." );
}

void Borde::Dibujar( SDL_Surface* window )
{
	SDL_Rect lineaSuperior  = { _ubicacion.x, _ubicacion.y, _ubicacion.w, _borde };							
	SDL_Rect lineaInferior  = { _ubicacion.x, _ubicacion.y + _ubicacion.h - _borde, _ubicacion.w, _borde };	
	SDL_Rect lineaIzquierda = { _ubicacion.x, _ubicacion.y, _borde, _ubicacion.h };							
	SDL_Rect lineaDerecha   = { _ubicacion.x + _ubicacion.w - _borde, _ubicacion.y, _borde, _ubicacion.h }; 	
	SDL_FillRect( window, &lineaSuperior,  _color);
	SDL_FillRect( window, &lineaInferior,  _color);
	SDL_FillRect( window, &lineaIzquierda, _color);
	SDL_FillRect( window, &lineaDerecha,   _color);
}