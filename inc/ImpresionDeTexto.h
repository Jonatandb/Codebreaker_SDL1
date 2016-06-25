#pragma once

#include "Defines.h"
#include "Includes.h"

class ImpresionDeTexto
{
private:
	int _id;
	TTF_Font* _arial20;
	TTF_Font* _arial40;
	TTF_Font* _pretendo18;
	TTF_Font* _pretendo90;
	TTF_Font* _pixelated20;
	TTF_Font* GetFont( int fuente );
public:
	ImpresionDeTexto();
	~ImpresionDeTexto();
	static enum
	{
		Arial20,
		Arial40,
		Pixelated20,
		Pretendo18,
		Pretendo90
	} Fuentes;
	void MostrarTexto( string texto, int fuente, int x, int y, SDL_Surface* pantallaDestino, int fR, int fG, int fB, int bR, int bG, int bB );
	void MostrarTexto( string texto, int fuente, SDL_Rect destination, SDL_Surface* pantallaDestino, int fR, int fG, int fB, int bR, int bG, int bB );
	void MostrarTexto( string texto, int fuente, int x, int y, SDL_Surface* pantallaDestino, SDL_Color foreground, SDL_Color background );
	void MostrarTexto( string texto, int fuente, SDL_Rect destination, SDL_Surface* pantallaDestino, SDL_Color foreground, SDL_Color background );
};
