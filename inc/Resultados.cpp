#pragma once

#include "Resultados.h"

Resultados::Resultados( SDL_Surface* window, Nivel* nivel, IA* ia, ImpresionDeTexto* texto )
{
	_id = cRandom::getRandom();	//Logger::Log( "Resultados\t\tId = " + to_string( _id) + "\t\tCreado." );
	_window = window;
	_nivel = nivel;
	_ia = ia;
	_texto = texto;
	_grosorBorde = 10;
}

Resultados::~Resultados()
{
	//Logger::Log( "Resultados\t\tId = " + to_string( _id) + "\t\tEliminado." );
}

bool Resultados::BuscarEnVector( string numero )
{
	vector<string>::iterator it;
	it = find ( _ingresos.begin(), _ingresos.end(), numero );
	if (it != _ingresos.end())
		return true;
	else
		return false;
}

void Resultados::DibujarBordes()
{
	Uint32 color;

	switch ( _nivel->GetNivelActual() )
	{
	case 1:
		bordesInfo_x = 0;
		bordesInfo_y = 0;
		bordesInfo_w = 230;
		bordesInfo_h = 128;
		bordesResultado_x = bordesInfo_x;
		bordesResultado_y = bordesInfo_y + bordesInfo_h;
		bordesResultado_w = bordesInfo_w;
		bordesResultado_h = ( WINDOW_HEIGHT - ( bordesInfo_y + bordesInfo_h) - bordesInfo_y ) + bordesInfo_y;
		color = SDL_MapRGB( _window->format, Colores::Blanco_R, Colores::Blanco_G, Colores::Blanco_B );
		break;
	case 2:
		bordesInfo_x = 0;
		bordesInfo_y = 0;
		bordesInfo_w = 230;
		bordesInfo_h = 128;
		bordesResultado_x = bordesInfo_x;
		bordesResultado_y = bordesInfo_y + bordesInfo_h;
		bordesResultado_w = bordesInfo_w;
		bordesResultado_h = WINDOW_HEIGHT - bordesInfo_h;
		color = SDL_MapRGB( _window->format, Colores::Verde_R, Colores::Verde_G, Colores::Verde_B );
		break;
	case 3:
		bordesInfo_x = 0;
		bordesInfo_y = 0;
		bordesInfo_w = 230;
		bordesInfo_h = 128;
		bordesResultado_x = bordesInfo_x;
		bordesResultado_y = bordesInfo_y + bordesInfo_h;
		bordesResultado_w = bordesInfo_w;
		bordesResultado_h = WINDOW_HEIGHT - ( bordesInfo_y + bordesInfo_h) - bordesInfo_y;
		color = SDL_MapRGB( _window->format, Colores::Azul_R, Colores::Azul_G, Colores::Azul_B );
		break;
	case 4:
		bordesInfo_x = 0;
		bordesInfo_y = WINDOW_HEIGHT - 128;
		bordesInfo_w = 230;
		bordesInfo_h = 128;
		bordesResultado_x = bordesInfo_x + bordesInfo_w;
		bordesResultado_y = bordesInfo_y;
		bordesResultado_w = WINDOW_WIDTH - ( bordesInfo_x + bordesInfo_w) - bordesInfo_x;
		bordesResultado_h = bordesInfo_h;
		color = SDL_MapRGB( _window->format, Colores::Rojo_R, Colores::Rojo_G, Colores::Rojo_B );
		break;
	}

	Borde* bordesInfo = new Borde( bordesInfo_x, bordesInfo_y, bordesInfo_w, bordesInfo_h, _grosorBorde, color );
	bordesInfo->Dibujar( _window );

	Borde* bordesResultado = new Borde( bordesResultado_x, bordesResultado_y, bordesResultado_w, bordesResultado_h, _grosorBorde, color );
	bordesResultado->Dibujar( _window );

	delete bordesInfo;
	delete bordesResultado;
}

//Borde* Resultados::GetBorde()
//{
//	int x = 0;
//	int y = 0;
//	int alto = 10;
//	int ancho = 10;
//	Uint32 color = SDL_MapRGB( _window->format, Colores::Amarillo_R, Colores::Amarillo_G, Colores::Amarillo_B );
//	int alturaTexto = 20; // Porque uso Pixelated20
//
//	x = _x;
//	y = _y;
//	ancho = _w;
//	alto = _h;
//
//
//	switch ( _nivel->GetNivelActual() )
//	{
//	case 1:
//		//x = _x; //831;
//		//y = _y; //640; //20;
//		////alto = 128; //_nivel->GetMaximosIntentos() * alturaTexto + y + 5; //225 // Espacio para 10 intentos
//		////ancho = WINDOW_WIDTH - _x; //173;
//		//ancho = _w;
//		//alto = _h;
//		color = SDL_MapRGB( _window->format, Colores::Blanco_R, Colores::Blanco_G, Colores::Blanco_B );
//		break;
//	case 2:
//		//x = 831;
//		//y = 20;
//		//alto = _nivel->GetMaximosIntentos() * alturaTexto + y + 5; //425; // Espacio para 20 intentos
//		//ancho = 173;
//		color = SDL_MapRGB( _window->format, Colores::Verde_R, Colores::Verde_G, Colores::Verde_B );
//		break;
//	case 3:
//		//x = 831;
//		//y = 20;
//		//alto = _nivel->GetMaximosIntentos() * alturaTexto + y + 5;  //625; // Espacio para 30 intentos
//		//ancho = 173;
//		color = SDL_MapRGB( _window->format, Colores::Azul_R, Colores::Azul_G, Colores::Azul_B );
//		break;
//	case 4:
//		//x = 831;
//		//y = 20;
//		//alto = _nivel->GetMaximosIntentos() * alturaTexto + y + 5;  //325;	// Espacio para 15 intentos
//		//ancho = 173;
//		color = SDL_MapRGB( _window->format, Colores::Rojo_R, Colores::Rojo_G, Colores::Rojo_B );
//		break;
//	}
//
//	Borde* test = new Borde( 0, 640, 255, 128, 10, SDL_MapRGB( g_Window->format, Colores::Azul_R, Colores::Azul_G, Colores::Azul_B ) );
//
//	return new Borde( x, y, ancho, alto, _grosorBorde, color );
//}

// Almacena el número y su resultado.
// No almacena el ingreso de "0".
// No almacena el ingreso de números que ya hayan sido almacenados.
// Muestra por consola el numero que se intenta registrar.
void Resultados::RegistrarIngreso( string numero, string resultado )
{
	//printf( "Numero ingresado: %s\n", numero.c_str() );

	if( numero == "0" ) return;				// Solo permito ingresar numeros distintos de cero.

	if( BuscarEnVector( numero ) ) return;	// Solo ingreso numeros que no hayan sido ingresados.

	_ingresos.push_back( numero );
	_resultados.push_back( resultado );
}

// Dibuja los ingresos hechos por el usuario y los colorea según se van agotando los intentos
void Resultados::Dibujar()
{
	DibujarBordes();
	DibujarInfo();
	DibujarResultados();
}

void Resultados::DibujarInfo()
{
	SDL_Rect pos;

	// Titulo
	pos.x = bordesInfo_x + _grosorBorde + 30;
	pos.y = bordesInfo_y + _grosorBorde + 15;
	string titulo = "Codebreaker";
	_texto->MostrarTexto( titulo, ImpresionDeTexto::Pretendo18, pos, _window, Colores::GrisOscuro_R, Colores::GrisOscuro_G, Colores::GrisOscuro_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );

	// Nivel:
	pos.x = bordesInfo_x + _grosorBorde + 5;
	pos.y = bordesInfo_y + _grosorBorde + 50;
	string nivel = "Nivel: ";
    std::ostringstream nivelString;
    nivelString << _nivel->GetNivelActual();
	nivel.append( nivelString.str() );
	_texto->MostrarTexto( nivel, ImpresionDeTexto::Pixelated20, pos, _window, Colores::Blanco_R, Colores::Blanco_G, Colores::Blanco_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );

	// Intentos restantes:
	pos.x = bordesInfo_x + _grosorBorde + 5;
	pos.y = bordesInfo_y + _grosorBorde + 80;
	string intentos = "Intentos restantes: ";
	int cantidadRestante = ( int ) _nivel->GetMaximosIntentos() - _ia->CantidadIntentos();
    std::ostringstream cantidadRestanteString;
    cantidadRestanteString << _nivel->GetNivelActual();
	intentos.append( cantidadRestanteString.str() );
	_texto->MostrarTexto( intentos, ImpresionDeTexto::Pixelated20, pos, _window, Colores::Blanco_R, Colores::Blanco_G, Colores::Blanco_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );

	//// Numero secreto:
	//if( DEBUG_INFO_HABILITADA )
	//{
	//	static int tiempoMostrandoDebugInfo = SDL_GetTicks();
	//	if( g_MostrarDebugInfo )
	//	{
			// Numero secreto:
			//pos.x = WINDOW_WIDTH - 215;
			//pos.y = WINDOW_HEIGHT - 40;
			//string numeroSecreto = "Numero secreto: ";
			//numeroSecreto.append( _ia->GetNumeroSecretoString() );
			//_texto->MostrarTexto( numeroSecreto, ImpresionDeTexto::Pixelated20, pos, _window, Colores::GrisOscuro_R, Colores::GrisOscuro_G, Colores::GrisOscuro_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );

	//		// Mouse coords:
	//		if( g_Event.type == SDL_MOUSEMOTION)
	//		{
	//			string mouse_x = "x = ";
	//			mouse_x.append( to_string( g_Event.motion.x ) );
	//			g_Textos->MostrarTexto( mouse_x, ImpresionDeTexto::Pixelated20, WINDOW_WIDTH - 120, 0, g_Window, Colores::Blanco_R, Colores::Blanco_G, Colores::Blanco_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );
	//			string mouse_y = "y = ";
	//			mouse_y.append( to_string( g_Event.motion.y ) );
	//			g_Textos->MostrarTexto( mouse_y, ImpresionDeTexto::Pixelated20, WINDOW_WIDTH - 60, 0, g_Window, Colores::Blanco_R, Colores::Blanco_G, Colores::Blanco_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );
	//		}

	//		if( ( SDL_GetTicks() - tiempoMostrandoDebugInfo ) > 5000 )
	//		{
	//			// Si se mostró por mas de 5 segundo, dejo de mostrarlo
	//			g_MostrarDebugInfo = false;
	//		}
	//	}
	//	else
	//	{
	//		tiempoMostrandoDebugInfo = SDL_GetTicks();
	//	}
	//}
}

void Resultados::DibujarResultados()
{
	// Ingreso - Resultado:
	int entrelineado = 20; // Por el tamaño de la fuente usada.

	int ultimo_x = 0;
	int ultimo_y = 0;
	int contador_x = 0;
	int contador_y = 0;

	int anchoMaximoEstimado = 150; // NOTA: Como no se el ancho del texto, estimé a ojo que con la fuente utilizada y basandome en la cadena mas larga ( "44444 - OOOOO" ) que el ancho del texto es de aprox. 80 pixeles.

	for( int pos = 0; pos < _ingresos.size(); pos++ )
	{
		int porcentajeProgreso = CalcularPorcentajeProgreso( pos );
		int _altoFuente = 20;	// Establecer el alto en pixeles de la fuente utilizada, usé 20 basandome en la altura estimada de la fuente Pixelated20;

		// Calculo Y
		ultimo_y = bordesResultado_y + _grosorBorde + contador_y * _altoFuente;
		contador_y++;

		// Verifico Y
		if( ultimo_y > ( bordesResultado_y + bordesResultado_h - _grosorBorde - _altoFuente ) )
		{
			contador_y = 0;
			ultimo_y = bordesResultado_y + _grosorBorde + contador_y * _altoFuente;
			contador_y++;
			contador_x++;
		}

		// Calculo X
		ultimo_x = bordesResultado_x + 5 + _grosorBorde + contador_x * anchoMaximoEstimado;

		// Verifico X
		if( ultimo_x > ( bordesResultado_x + 5 + bordesResultado_w - _grosorBorde - anchoMaximoEstimado ) )
		{
			contador_x = 0;
			ultimo_x = bordesResultado_x + 5 + _grosorBorde + contador_x * anchoMaximoEstimado;
		}

		string salida = _ingresos[ pos ];
		salida.append( " - " );
		salida.append( _resultados[ pos ] );

		// Establezco color de frente del texto según cantidad de intetos utilizados y restantes:
		SDL_Color colorFrente;

		if( porcentajeProgreso <= 17 )
		{
			colorFrente.r = Colores::Blanco_R;
			colorFrente.g = Colores::Blanco_G;
			colorFrente.b = Colores::Blanco_B;
		}
		else if( porcentajeProgreso > 17 && porcentajeProgreso <= 32 )
		{
			// Amarillo suave
			colorFrente.r = Colores::Amarillo_R;
			colorFrente.g = Colores::Amarillo_G;
			colorFrente.b = 179;
		}
		else if( porcentajeProgreso > 32 && porcentajeProgreso <= 48 )
		{
			colorFrente.r = Colores::Amarillo_R;
			colorFrente.g = Colores::Amarillo_G;
			colorFrente.b = Colores::Amarillo_B;
		}
		else if( porcentajeProgreso > 48 && porcentajeProgreso <= 64 )
		{
			// Naranja 1
			colorFrente.r = 236;
			colorFrente.g = 179;
			colorFrente.b = 0;
		}
		else if( porcentajeProgreso > 64 && porcentajeProgreso <= 80 )
		{
			// Naranja 2
			colorFrente.r = 255;
			colorFrente.g = 127;
			colorFrente.b = 39;
		}
		else
		{
			colorFrente.r = Colores::Rojo_R;
			colorFrente.g = Colores::Rojo_G;
			colorFrente.b = Colores::Rojo_B;
		}

		SDL_Color colorFondo = { Colores::Negro_R, Colores::Negro_G, Colores::Negro_B };

		SDL_Rect destino = { ultimo_x, ultimo_y };

		// Limpio linea
		_texto->MostrarTexto( "WWWWWWWWW", ImpresionDeTexto::Pixelated20, destino, _window, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );

		// Muestro Ingreso - Resultado
		_texto->MostrarTexto( salida, ImpresionDeTexto::Pixelated20, destino, _window, colorFrente, colorFondo );
	}
}

float Resultados::CalcularPorcentajeProgreso( int pos )
{
	int maximosIntentos = _nivel->GetMaximosIntentos();
	int cantIntentos = pos; //_ia->CantidadIntentos();
	float porcentaje = 0;
	if( maximosIntentos <= 0 ) // Evito dividir por 0 o un numero negativo.
		return porcentaje;
	if( cantIntentos > maximosIntentos ) // Evito devolver un porcentaje superior al 100%.
		return porcentaje;
	porcentaje = ( float ) ( ( cantIntentos * 100 ) / maximosIntentos );
	return porcentaje;
}

bool Resultados::BuscarEnVectorInt( vector<int> numero )
{
	if( numero.size() <= 0 ) return false;

	string numeroBuscado = "";
	for( int i = 0 ; i < numero.size() ; i++ )
	{
	    std::ostringstream numeroBuscadoString;
        numeroBuscadoString << i;
        numeroBuscado.append( numeroBuscadoString.str() );
	}

	vector<string>::iterator it;
	it = find ( _ingresos.begin(), _ingresos.end(), numeroBuscado );
	if (it != _ingresos.end())
		return true;
	else
		return false;
}



	//// Ingreso - Resultado:
	//int porcentajeProgreso = CalcularPorcentajeProgreso( cantIntentos, maximosIntentos );
	//int entrelineado = 20; // Por el tamaño de la fuente usada.

	//int ultimo_x = 0;
	//int ultimo_y = 0;
	//int contador_x = 0;
	//int contador_y = 0;

	//int anchoMaximoEstimado = 120; // NOTA: Como no se el ancho del texto, estimé a ojo que con la fuente utilizada y basandome en la cadena mas larga ( "44444 - OOOOO" ) que el ancho del texto es de aprox. 80 pixeles.

	//for( int pos = 0; pos < _ingresos.size(); pos++ )
	//{
	//	int _altoFuente = 20;	// Establecer el alto en pixeles de la fuente utilizada, usé 20 basandome en la altura estimada de la fuente Pixelated20;
	//	ImpresionDeTexto::Fuentes _fuente = ImpresionDeTexto::Fuentes::Pixelated20;

	//	// Que comience la Magia!! :D
	//
	//	/*
	//	Funcionalidades detectadas:
	//	- Verifico Y (Cuando se llega al limite vertical, comenzar arriba mas la derecha)
	//		KO:	(Se llegó al limite vertical)
	//			- Resetear Y	(Comenzar arriba)
	//			- Incrementar X	(Mas a la derecha)		//, calcular x (si no se puede, resetear x) )
	//													si no se puede, comenzar arriba en la misma columna.
	//		OK:
	//			- Incremento Y
	//	- Calculo Y

	//	- Verifico X (Cuando se llega al limite horizontal, comenzar abajo, a la izquierda)
	//		KO:	(Se llegó al limite horizontal)
	//			- Resetear X	(Comenzar a la izquierda)
	//			- Incrementar Y	(Mas abajo)
	//
	//		OK:
	//			- Incrementar X							//, calcular y (si no se puede, resetear y) )
	//													si no se puede, comenzar a la izquierda en la misma fila.
	//	- Calculo X
	//	*/

	//	// Calculo Y
	//	ultimo_y = _y + _grosorBorde + contador_y * _altoFuente;
	//	contador_y++;

	//	// Verifico Y
	//	if( ultimo_y > ( _y + _h - _grosorBorde - _altoFuente ) )
	//	{
	//		contador_y = 0;
	//		ultimo_y = _y + _grosorBorde + contador_y * _altoFuente;
	//		contador_y++;
	//		contador_x++;
	//	}

	//	// Calculo X
	//	ultimo_x = _x + _grosorBorde + contador_x * anchoMaximoEstimado;

	//	// Verifico X
	//	if( ultimo_x > ( _x + _w - _grosorBorde - anchoMaximoEstimado ) )
	//	{
	//		contador_x = 0;
	//		ultimo_x = _x + _grosorBorde + contador_x * anchoMaximoEstimado;
	//		//contador_y++;
	//	}

	//	/*
	//	siempre aumento y
	//	cuando ya no se pueda, reseteo y
	//	aumento x
	//		si no se puede
	//			reseteo x
	//	*/


	//	/*
	//	// Calculo punto x
	//	ultimo_x = 5 + _x + _grosorBorde + contador_x * anchoMaximoEstimado;

	//	// Tengo en cuenta de que la primera vez sola debo contemplar la altura del borde
	//	ultimo_y = _y + _grosorBorde + contador_y * _altoFuente;
	//	contador_y++;
	//
	//	if( ultimo_y >= _y + _h - _altoFuente - _grosorBorde )
	//	{
	//		// No entra verticalemente una linea mas
	//		contador_y = 0;
	//		ultimo_y = _y + _grosorBorde + contador_y * _altoFuente; // Recalculo
	//		contador_y++;

	//		contador_x++;
	//		ultimo_x = 5 + _x + _grosorBorde + contador_x * anchoMaximoEstimado;  // Recalculo
	//	}

	//	if( ultimo_x >= _x + _w - _grosorBorde - anchoMaximoEstimado )
	//	{
	//		// No entra horizontalmente una linea mas
	//		contador_x = 0;
	//		ultimo_x = 5 + _x + _grosorBorde + contador_x * anchoMaximoEstimado;  // Recalculo
	//		contador_x++;
	//	}
	//	*/

	//	/*
	//	Funcionalidades detectadas:
	//		1 - Cuando se llega al limite vertical   - comenzar arriba, mas la derecha ( resetear y, x++, calcular x (si no se puede, resetear x) )
	//				si no se puede, comenzar arriba en la misma columna.
	//		2 - Cuando se llega al limite horizontal - comenzar abajo a la izquierda ( resetear x, y++, calcular y (si no se puede, resetear y) )
	//				si no se puede, comenzar a la izquierda en la misma fila.


	//	 calculo x
	//	 si x se paso
	//		reseteo x
	//		incremento y
	//	 si no se paso
	//		incremente x

	//	 calculo y
	//	 si y se paso
	//		reseteo y
	//		incremento x

	//				// calculo x
	//	// si se paso x
	//	//		reseteo x
	//	//		calculo y
	//	//		si se paso y
	//	//			incremento x
	//	//			si se paso x
	//	//				reseto x
	//	//				reseto y
	//	//			si no paso x
	//	//				reseteo y
	//	//		si no se paso y
	//	// si no se paso x
	//	//		incremento y

	//	 */


	//	// Fin de la magia!

	//	string salida = _ingresos[ pos ];
	//	salida.append( " - " );
	//	salida.append( _resultados[ pos ] );

	//	// Establezco color de frente del texto según cantidad de intetos utilizados y restantes:
	//	SDL_Color colorFrente;
	//	int porcentajeProgreso = CalcularPorcentajeProgreso( cantIntentos, maximosIntentos );

	//	if( porcentajeProgreso <= 17 )
	//	{
	//		colorFrente.r = Colores::Blanco_R;
	//		colorFrente.g = Colores::Blanco_G;
	//		colorFrente.b = Colores::Blanco_B;
	//	}
	//	else if( porcentajeProgreso > 17 && porcentajeProgreso <= 32 )
	//	{
	//		// Amarillo suave
	//		colorFrente.r = Colores::Amarillo_R;
	//		colorFrente.g = Colores::Amarillo_G;
	//		colorFrente.b = 179;
	//	}
	//	else if( porcentajeProgreso > 32 && porcentajeProgreso <= 48 )
	//	{
	//		colorFrente.r = Colores::Amarillo_R;
	//		colorFrente.g = Colores::Amarillo_G;
	//		colorFrente.b = Colores::Amarillo_B;
	//	}
	//	else if( porcentajeProgreso > 48 && porcentajeProgreso <= 64 )
	//	{
	//		// Naranja 1
	//		colorFrente.r = 236;
	//		colorFrente.g = 179;
	//		colorFrente.b = 0;
	//	}
	//	else if( porcentajeProgreso > 64 && porcentajeProgreso <= 80 )
	//	{
	//		// Naranja 2
	//		colorFrente.r = 255;
	//		colorFrente.g = 127;
	//		colorFrente.b = 39;
	//	}
	//	else
	//	{
	//		colorFrente.r = Colores::Rojo_R;
	//		colorFrente.g = Colores::Rojo_G;
	//		colorFrente.b = Colores::Rojo_B;
	//	}

	//	SDL_Color colorFondo = { Colores::Negro_R, Colores::Negro_G, Colores::Negro_B };

	//	SDL_Rect destino = { ultimo_x, ultimo_y };

	//	// Limpio linea
	//	texto->MostrarTexto( "WWWWWWWWW", (ImpresionDeTexto::Fuentes)_fuente, destino, _window, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );

	//	// Muestro Ingreso - Resultado
	//	texto->MostrarTexto( salida, (ImpresionDeTexto::Fuentes)_fuente, destino, _window, colorFrente, colorFondo );
	//}
