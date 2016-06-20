#pragma once

#include "Nivel.h"

Nivel::Nivel()
{
	_id = cRandom::getRandom();	//Logger::Log( "Nivel\t\tId = " + to_string( _id) + "\t\tCreado." );
	_nivelActual = 1;
	_cantidadMazos = GetCantidadMazos();
	_maximosIntentos = GetMaximosIntentos();
}

Nivel::~Nivel()
{
	//Logger::Log( "Nivel\t\tId = " + to_string( _id) + "\t\tEliminado." );
}

int Nivel::GetNivelActual()
{
	return _nivelActual;
}

void Nivel::SubirNivel()
{
	_nivelActual++;
	if( _nivelActual > 4 )
	{
		_nivelActual = 1;
	}
	_cantidadMazos = GetCantidadMazos();
	_maximosIntentos = GetMaximosIntentos();
}

int Nivel::GetMaximosIntentos()
{
	switch ( _nivelActual )
	{
	case 1:
		return 5;
		break;
	case 2:
		return 10;
		break;
	case 3:
		return 20;
		break;
	case 4:
		return 30;
		break;
	default:
		return 0;
		break;
	}
}

int Nivel::GetCantidadMazos()
{
	switch ( _nivelActual )
	{
	case 1:
		return 2;
		break;
	case 2:
		return 3;
		break;
	case 3:
		return 4;
		break;
	case 4:
		return 5;
		break;
	default:
		return 0;
		break;
	}
}