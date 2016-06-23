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
	_mostrarDebugInfo = false;
	_mouse_x = 0;
	_mouse_y = 0;
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
	cantidadRestanteString << cantidadRestante;
	intentos.append( cantidadRestanteString.str() );
	_texto->MostrarTexto( intentos, ImpresionDeTexto::Pixelated20, pos, _window, Colores::Blanco_R, Colores::Blanco_G, Colores::Blanco_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );

	if( DEBUG_INFO_HABILITADA )
	{
		//static int tiempoMostrandoDebugInfo = SDL_GetTicks();
		if( _mostrarDebugInfo )
		{

			int y_debugInfo = 0;

			// Numero secreto:
			pos.x = 235;
			pos.y = y_debugInfo;
			string numeroSecreto = "Numero secreto: ";
			numeroSecreto.append( _ia->GetNumeroSecretoString() );
			_texto->MostrarTexto( numeroSecreto, ImpresionDeTexto::Pixelated20, pos, _window, Colores::Amarillo_R, Colores::Amarillo_G, Colores::Amarillo_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );

			// Info de los vectores:
			y_debugInfo += 25;
			pos.y = y_debugInfo;
			string ingresosSize = "_ingresos.size(): ";
			int i = _ingresos.size();
			std::ostringstream ingresosSizeString;
			ingresosSizeString << i;
			ingresosSize.append( ingresosSizeString.str() );
			_texto->MostrarTexto( ingresosSize, ImpresionDeTexto::Pixelated20, pos, _window, Colores::Amarillo_R, Colores::Amarillo_G, Colores::Amarillo_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );

			y_debugInfo += 25;
			pos.y = y_debugInfo;
			string resultadosSize = "_resultados.size(): ";
			int j = _resultados.size();
			std::ostringstream resultadosSizeString;
			resultadosSizeString << j;
			resultadosSize.append( resultadosSizeString.str() );
			_texto->MostrarTexto( resultadosSize, ImpresionDeTexto::Pixelated20, pos, _window, Colores::Amarillo_R, Colores::Amarillo_G, Colores::Amarillo_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );

			//y_debugInfo += 25;
			//pos.y = y_debugInfo;
			//string ingresos = "Ingresos: ";
			//numeroSecreto.append( _ia->GetNumeroSecretoString() );
			//_texto->MostrarTexto( numeroSecreto, ImpresionDeTexto::Pixelated20, pos, _window, Colores::Amarillo_R, Colores::Amarillo_G, Colores::Amarillo_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );

			//y_debugInfo += 25;
			//pos.y = y_debugInfo;			
			//string resultados = "Resultados: ";
			//numeroSecreto.append( _ia->GetNumeroSecretoString() );
			//_texto->MostrarTexto( numeroSecreto, ImpresionDeTexto::Pixelated20, pos, _window, Colores::Amarillo_R, Colores::Amarillo_G, Colores::Amarillo_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );


			// Mouse coords:
			y_debugInfo += 25;	
			pos.y = y_debugInfo;
			string mouse_x = "x = ";
			mouse_x.append( to_string( _mouse_x ) );
			_texto->MostrarTexto( mouse_x, ImpresionDeTexto::Pixelated20, pos, _window, Colores::Amarillo_R, Colores::Amarillo_G, Colores::Amarillo_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );
			pos.x = 325;
			string mouse_y = "y = ";
			mouse_y.append( to_string( _mouse_y ) );
			_texto->MostrarTexto( mouse_y, ImpresionDeTexto::Pixelated20, pos, _window, Colores::Amarillo_R, Colores::Amarillo_G, Colores::Amarillo_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );

			//if( ( SDL_GetTicks() - tiempoMostrandoDebugInfo ) > 5000 )
			//{
			//	// Si se mostró por mas de 5 segundo, dejo de mostrarlo
			//	_mostrarDebugInfo = false;
			//}
		}
		//else
		//{
		//	tiempoMostrandoDebugInfo = SDL_GetTicks();
		//}
	}
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

void Resultados::HandleInput( SDL_Event* event)
{	
	if( event->type == SDL_KEYDOWN )
	{
		if( event->key.keysym.sym == SDLK_j )
		{
			_mostrarDebugInfo = !_mostrarDebugInfo;
		}
	}
	if( event->type == SDL_MOUSEMOTION)
	{
		_mouse_x = event->motion.x;
		_mouse_y = event->motion.y;
	}
}