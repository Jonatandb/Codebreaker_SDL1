#pragma once

#include "IA.h"

IA::IA( int cantidadMazos )
{
	_id = cRandom::getRandom();	//Logger::Log( "IA\t\tId = " + to_string( _id) + "\t\tCreado." );
	_cantIntentos = 0;
	_cantMazos = cantidadMazos;
	_usuarioGano = false;
	vector<int>::iterator it;
	int nro;
	for( int i=0; i < _cantMazos; i++ )
	{
		do
		{
			nro = cRandom::getRandom( 0, 9 );
			it = std::find( _aleatorio.begin(), _aleatorio.end(), nro );
		}
		while( it != _aleatorio.end() );
		_aleatorio.push_back( nro );
	}
}

IA::~IA()
{
	//Logger::Log( "IA\t\tId = " + to_string( _id) + "\t\tEliminado." );
}

unsigned short IA::searchDigit( vector <int> v, int value, unsigned short pos )
{
	if ( v.at(pos) == value )
	{
		return 1;
	}
	else
	{
		vector<int>::iterator it;
		it = find( v.begin(), v.end(), value );
		if( it != v.end() )
		{
			return 2;
		}
	}
	return 0;
}

string IA::GetNumeroSecretoString()
{
	string secret = "";
	for( int i = 0 ; i < _aleatorio.size() ; i++ )
	{
        std::ostringstream aleatorioString;
        aleatorioString << _aleatorio[ i ];
        secret.append( aleatorioString.str() );	//secret.append( to_string( _aleatorio[ i ] ) );	// No funciona en Codeblocks
	}
	return secret;
}

// Devuelve un vector<char> con el resultado de comprar el numero ingresado contra el numero al azar.
// Devuelve el vector<char> vacío si recibe un vector<int> vacío.
// Devuelve el vector<char> vacío si el numero ya existe entre los numeros registrados.
// Incrementa la cantidad de intentos realizados.
// Registra internamente si el usuario ganó luego de verificarse el ingreso.
vector<char> IA::GetResultadoValidarIngreso( Resultados* resultados, vector<int> numeroIngresado )
{
	vector <char> result;
	if( numeroIngresado.size() <= 0 || resultados->BuscarEnVectorInt( numeroIngresado ) ) return result;
	_cantIntentos++;
	_usuarioGano = false;
	int cantidadAciertos = 0;

	unsigned short cantDigitosAzar = _aleatorio.size();
	for( int i = 0; i < cantDigitosAzar; i++ )
	{
		int value = searchDigit( _aleatorio, numeroIngresado.at( i ), i );
		if( value == 1 )
		{
			cantidadAciertos++;
			result.push_back( 'O' );
		}
		else if( value == 2 )
		{
			result.push_back( '#' );
		}
	}
	_usuarioGano = ( cantidadAciertos == cantDigitosAzar );
	return result;
}

bool IA::UsuarioGano()
{
	return _usuarioGano;
}

int IA::CantidadIntentos()
{
	return _cantIntentos;
}
