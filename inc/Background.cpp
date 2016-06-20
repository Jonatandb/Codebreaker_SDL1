#pragma once

#include "Background.h"

Background::Background()
{
	_id = cRandom::getRandom();	////Logger::Log( "Background\t\tId = " + to_string( _id) + "\t\tCreado." );
	_imagen = SDL_LoadBMP("assets/images/10.bmp");
}

Background::~Background()
{
	////Logger::Log( "Background\t\tId = " + to_string( _id) + "\t\tEliminado." );
	SDL_FreeSurface( _imagen );
}

void Background::Dibujar( int nivelActual, int cantMazos, SDL_Surface* window )
{
	int x = 0;
	int y = 30;
	int anchoPanel = 230;		// Ver si dejo asi o obtengo una referencia al ancho del panel
	int sup_disponible = WINDOW_WIDTH - anchoPanel; // total sin panel 
	int mitad_sup_disponible = sup_disponible / 2;
	int centro_sup_disponible = mitad_sup_disponible + anchoPanel;
	int ancho_final_carta = ( CARTA_W * cantMazos ) + ( 25 * ( cantMazos - 1 ) ) ;
	for( int i = 0; i < cantMazos; i++ )
	{
		switch ( nivelActual )
		{
			case 1:
			case 2:
			case 3:
					x = centro_sup_disponible - ( ancho_final_carta / 2 );		// 639 - ( 381 / 2 ) => 639 - 190 => 449
					x += i * CARTA_W;	// i:0 x => 194 + 0 => 194  // i:1 x => 194 + 178 => 372
					x += i * 25;		// i:0 x => 194 + 0 => 194  // i:1 x => 372 + 25  =>  397
					break;
			case 4:	
					centro_sup_disponible = WINDOW_WIDTH / 2;
					x = centro_sup_disponible - ( ancho_final_carta / 2 );		
					x += i * CARTA_W;
					x += i * 25;
					break;
		}
		SDL_Rect destino = { x , y, 0, 0 };
		if( _imagen != NULL )	SDL_BlitSurface( _imagen, NULL, window, &destino );
	}
}