#pragma once

#include "ImpresionDeTexto.h"

ImpresionDeTexto::ImpresionDeTexto()
{
	_id = cRandom::getRandom();	//Logger::Log( "ImpresionDeTexto\t\tId = " + to_string( _id) + "\t\tCreado." );
	_arial40		= TTF_OpenFont( "assets/fonts/arial.ttf",     40 );
	_pretendo18		= TTF_OpenFont( "assets/fonts/pretendo.ttf",  18 );
	_pretendo90		= TTF_OpenFont( "assets/fonts/pretendo.ttf",  90 );
	_pixelated20	= TTF_OpenFont( "assets/fonts/pixelated.ttf", 20 );
}

ImpresionDeTexto::~ImpresionDeTexto()
{
	//Logger::Log( "ImpresionDeTexto\t\tId = " + to_string( _id) + "\t\tEliminado." );
	TTF_CloseFont( _arial40 );
	TTF_CloseFont( _pretendo90 );
	TTF_CloseFont( _pretendo18 );
	TTF_CloseFont( _pixelated20 );
}

void ImpresionDeTexto::MostrarTexto( string texto, int fuente, int x, int y, SDL_Surface* pantallaDestino, int fR, int fG, int fB, int bR, int bG, int bB )
{
	SDL_Color foreground = { fR, fG, fB };  // Text color.
	SDL_Color background = { bR, bG, bB };  // Color of what's behind the text.
	SDL_Rect destination = { x, y, 0, 0 };	// A structure storing the destination of our text.
	MostrarTexto( texto, fuente, destination, pantallaDestino, foreground, background );
}

void ImpresionDeTexto::MostrarTexto( string texto, int fuente, SDL_Rect destination, SDL_Surface* pantallaDestino, int fR, int fG, int fB, int bR, int bG, int bB )
{
	SDL_Color foreground = { fR, fG, fB };  // Text color.
	SDL_Color background = { bR, bG, bB };  // Color of what's behind the text.
	MostrarTexto( texto, fuente, destination, pantallaDestino, foreground, background );
}

void ImpresionDeTexto::MostrarTexto( string texto, int fuente, int x, int y, SDL_Surface* pantallaDestino, SDL_Color foreground, SDL_Color background )
{
	SDL_Rect destination = { x, y, 0, 0 };	// A structure storing the destination of our text.
	MostrarTexto( texto, fuente, destination, pantallaDestino, foreground, background );
}

void ImpresionDeTexto::MostrarTexto( string texto, int fuente, SDL_Rect destination, SDL_Surface* pantallaDestino, SDL_Color foreground, SDL_Color background )
{
	// This renders our text to a temporary surface.
	SDL_Surface* temp = TTF_RenderText_Shaded( GetFont(fuente), texto.c_str(), foreground, background );
	// Blit the text surface to our window surface, the NULL specifies the whole surface.
	SDL_BlitSurface( temp, NULL, pantallaDestino, &destination );
	// Always free memory!
	SDL_FreeSurface( temp );
}

TTF_Font* ImpresionDeTexto::GetFont( int fuente )
{
	switch ( fuente )
	{
		default:
		case 0:
				return _arial40;
				break;
		case 1:
				return _pixelated20;
				break;
		case 2:
				return _pretendo18;
				break;
		case 3:
				return _pretendo90;
				break;
	}
}
