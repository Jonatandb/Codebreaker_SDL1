#pragma once

#include "Tablero.h"

Tablero::Tablero( int nivelActual, int cantidadMazos, SDL_Surface* window )
{
	_id = cRandom::getRandom();	//Logger::Log( "Tablero\t\tId = " + to_string( _id) + "\t\tCreado." );
	_window = window;
	_cantMazos = cantidadMazos;
	SetearUbicacion( nivelActual );
	_mazoActivo = 0;
	_dibujarBorde = true;
	_tiempoSinDibujarBorde = SDL_GetTicks();
	_tiempoDibujandoBorde  = SDL_GetTicks();
	_bordeEstatico = false;
	SDL_Rect posMazos;
	for( int i = 0; i < _cantMazos; i++ )
	{
		posMazos.x = _x + ( ( CARTA_W + 25 ) * i );
		posMazos.y = _y;
		posMazos.w = 0;
		posMazos.h = 0;
		_mazos[i] = new Mazo( posMazos );
	}
}

Tablero::~Tablero()
{
	//Logger::Log( "Tablero\t\tId = " + to_string( _id) + "\t\tEliminado." );
	for( int i = 0; i < _cantMazos; i++ )
	{
		delete _mazos[i];
	}
}

void Tablero::SetearUbicacion( int nivelActual )
{
	_y = 350;
	int anchoPanel = 230;		// Ver si dejo asi u obtengo una referencia al ancho del panel...
	int sup_disponible = WINDOW_WIDTH - anchoPanel;
	int mitad_sup_disponible = sup_disponible / 2;
	int centro_sup_disponible = mitad_sup_disponible + anchoPanel;
	int ancho_final_carta = 0;
	switch ( nivelActual )
	{
		case 1:
		case 2:
		case 3:
				ancho_final_carta = CARTA_W * _cantMazos + ( 25 * ( _cantMazos - 1 ) ) ;
				_x = centro_sup_disponible - ( ancho_final_carta / 2);
				break;
		case 4:
				ancho_final_carta = CARTA_W * _cantMazos + ( 25 * ( _cantMazos - 1 ) );
				_x = WINDOW_WIDTH / 2 - ( ancho_final_carta / 2 ) ;
				break;
	}
}

bool Tablero::BuscarEnVector( vector<int> origen, int numero )
{
	vector<int>::iterator it;
	it = find ( origen.begin(), origen.end(), numero );
	if (it != origen.end())
		return true;
	else
		return false;
}

void Tablero::DibujarBordes()
{
	Uint32 colorRojoIntenso	= SDL_MapRGB( _window->format, Colores::RojoIntenso_R, Colores::RojoIntenso_G, Colores::RojoIntenso_B );
	Uint32 colorBorde = colorRojoIntenso;
	SDL_Rect posMazoActivo = _mazos[_mazoActivo]->Posicion();
	int grosorBorde = 10;

	if( _dibujarBorde )
	{
		if( ( SDL_GetTicks() - _tiempoDibujandoBorde ) <= 650  || _bordeEstatico)
		{
			SDL_Rect lineaSuperior  = { posMazoActivo.x, posMazoActivo.y, CARTA_W, grosorBorde };
			SDL_FillRect(_window, &lineaSuperior,  colorBorde );
			SDL_Rect lineaInferior  = { posMazoActivo.x, posMazoActivo.y + CARTA_H - grosorBorde, CARTA_W, grosorBorde };
			SDL_FillRect(_window, &lineaInferior,  colorBorde );
			SDL_Rect lineaIzquierda = { posMazoActivo.x, posMazoActivo.y, grosorBorde, CARTA_H };
			SDL_FillRect(_window, &lineaIzquierda, colorBorde );
			SDL_Rect lineaDerecha   = { posMazoActivo.x + CARTA_W - grosorBorde, posMazoActivo.y, grosorBorde, CARTA_H };
			SDL_FillRect(_window, &lineaDerecha,   colorBorde );
		}
		else
		{
			_dibujarBorde = false;
			_tiempoSinDibujarBorde = SDL_GetTicks();
		}
	}
	else
	{
		if( ( SDL_GetTicks() - _tiempoSinDibujarBorde) >= 800 )
		{
			_dibujarBorde = true;
			_tiempoDibujandoBorde = SDL_GetTicks();
		}
	}
}

bool Tablero::Dibujar()
{
	bool result = true;
	for( int i = 0; i < _cantMazos; i++ )
	{
		if( !_mazos[i]->Dibujar( _window ) )
		{
			result = false;
			break;
		}
	}
	DibujarBordes();
	return result;
}

void Tablero::FocoMazoDerecha()
{
	_mazoActivo++;
	if( _mazoActivo > _cantMazos - 1)
		_mazoActivo = 0;
	ForzarDibujadoDeBorde();
}

void Tablero::FocoMazoIzquierda()
{
	_mazoActivo--;
	if( _mazoActivo < 0)
		_mazoActivo = _cantMazos - 1;
	ForzarDibujadoDeBorde();
}

void Tablero::CartaSiguiente()
{
	_mazos[ _mazoActivo ]->ActivarCartaSiguiente();
	ResetearSeleccionRepetida();
}

void Tablero::CartaAnterior()
{
	_mazos[ _mazoActivo ]->ActivarCartaAnterior();
	ResetearSeleccionRepetida();
}

void Tablero::ActivarCarta( int carta )
{
	_mazos[ _mazoActivo ]->ActivarCarta( carta );
	ResetearSeleccionRepetida();
}

void Tablero::ResetearSeleccionRepetida()
{
	for( int i = 0; i < _cantMazos; i++ )
	{
		if( i != _mazoActivo )
		{
			if( _mazos[ i ]->CartaActiva() == _mazos[ _mazoActivo ]->CartaActiva() )
			{
				_mazos[ i ]->ActivarCarta( 10 );  // 10 -> Carta con signo de pregunta.
			}
		}
	}
}

/// Se encarga de que cuando se da el foco a un nuevo mazo, aparezca el borde inmediatamente.
void Tablero::ForzarDibujadoDeBorde()
{
	_dibujarBorde = true;
	_tiempoDibujandoBorde = SDL_GetTicks();
}

// Devuelve un string con el numero seleccionado en los mazos
// Si algun mazo no posee seleccion (tiene aun el signo de pregunta), devuelve "0".
string Tablero::GetNumeroIngresadoString()
{
	string numeroSeleccionado = "";
	for( int i = 0; i < _cantMazos ; i++ )
	{
		if( _mazos[ i ]->CartaActiva() > 9 )
		{
			return "0";
		}
		else
		{
			std::ostringstream numeroSeleccionadoString;
			numeroSeleccionadoString << _mazos[ i ]->CartaActiva();
			numeroSeleccionado.append( numeroSeleccionadoString.str() );	//numeroSeleccionado += to_string( _mazos[ i ]->CartaActiva() );	// No funciona en Codeblocks
		}
	}
	return numeroSeleccionado;
}

// Devuelve un vector<int> con los numeros de las cartas seleccionadas
// Devuelve el vector vacío si en algún mazo falta seleccionar una carta (tiene activa la carta con el signo de pregunta, valor 10).
vector<int> Tablero::GetNumeroIngresadoVecInt()
{
	vector<int> numeros;
	for( int i = 0; i < _cantMazos ; i++ )
	{
		numeros.push_back( _mazos[ i ]->CartaActiva() );
	}
	if( BuscarEnVector( numeros, 10 ) )
		numeros.clear();
	return numeros;
}
