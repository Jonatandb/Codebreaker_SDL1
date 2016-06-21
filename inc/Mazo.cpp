#pragma once

#include "Mazo.h"

Mazo::Mazo( SDL_Rect ubicacion )
{
	_id = cRandom::getRandom();	//////Logger::Log( "Mazo\t\tId = " + to_string( _id) + "\t\tCreado." );
	_ubicacion = ubicacion;
	_posCartaActiva = CARTAS_POR_MAZO - 1; // Por defecto un mazo tiene como carta activa la carta con signo de pregunta.
	for( int i = 0; i < CARTAS_POR_MAZO; i++ )
	{
        std::ostringstream rutaImagenString;
        rutaImagenString << i;
		string rutaImagen = "assets/images/" + rutaImagenString.str() + ".bmp";
		_carta[i] = new Carta( i, rutaImagen, 0, 0, CARTA_W, CARTA_H );
	}
}

Mazo::~Mazo()
{
	//////Logger::Log( "Mazo\t\tId = " + to_string( _id) + "\t\tEliminado." );
	for( int i = 0; i < CARTAS_POR_MAZO; i++ )
	{
		delete _carta[i];
	}
}

bool Mazo::Dibujar( SDL_Surface* window )
{
	return _carta[_posCartaActiva]->Dibujar( window, _ubicacion );
}

SDL_Rect Mazo::Posicion()
{
	return _ubicacion;
}

void Mazo::ActivarCartaSiguiente()
{
	_posCartaActiva++;
	if( _posCartaActiva > CARTAS_POR_MAZO - 2)	// Evito que al pasar a la siguiente apareza la que tiene el signo de pregunta.
		_posCartaActiva = 0;
}

void Mazo::ActivarCartaAnterior()
{
	_posCartaActiva--;
	if( _posCartaActiva < 0 )
		_posCartaActiva = CARTAS_POR_MAZO - 2;	// Evito que al pasar a la anterior aparezca la que tiene el signo de pregunta.
}

void Mazo::ActivarCarta(int carta)
{
	if( carta >= 0 && carta < CARTAS_POR_MAZO )
	{
		_posCartaActiva = carta;
	}
}

int Mazo::CartaActiva()
{
	return _posCartaActiva;
}
