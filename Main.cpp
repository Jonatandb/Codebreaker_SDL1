// Jonatandb@gmail.com
//
// PENDIENTES / MEJORAS / BUGS / ETC.: https://github.com/Jonatandb/Codebreaker_SDL1/issues

#include "inc/Header.h"

// The STL stack can't take a function pointer as a type
// so we encapsulate a function pointer within a struct.
struct StateStruct
{
	void ( *StatePointer )();
};

// Global data
stack<StateStruct>	g_StateStack;				// Our state stack
SDL_Event			g_Event;					// An SDL event structure for input
int					g_Timer;					// Our timer is just an integer
SDL_Surface*		g_Window			= NULL;	// Our back buffer
Nivel*				g_Nivel				= NULL;
Tablero*			g_Tablero			= NULL;
Resultados*			g_Resultados		= NULL;
IA*					g_IA				= NULL;
Background*			g_Background		= NULL;
ImpresionDeTexto*	g_Textos			= NULL;
bool				g_MostrarDebugInfo;

void InicializarGameObjects();

// Functions to handle the states of the game
void Menu();
void Game();
void Exit();
void WinLose();

// Init and Shutdown functions
void Init();
void Shutdown();

// Helper functions for the game state functions
void DrawBackground();
void ClearScreen();
void HandleMenuInput();
void HandleGameInput();
void HandleExitInput();
void HandleWinLoseInput();

int main(int argc, char* argv[] )
{
	Init();

	// Our game loop is just a while loop that breaks when our state stack is empty.
	while (!g_StateStack.empty())
	{
		//{ // Debug info a nivel de todas las pantallas:
		//	int stackSize = g_StateStack.size();
		//	SDL_Rect pos;
		//	pos.x = 235;
		//	pos.y = 0;
		//	string info = "Items en la pila: ";
		//	info.append( to_string( stackSize ) );
		//	info.append( " - Nivel actual: " );
		//	info.append( to_string( g_Nivel->GetNivelActual() ) );
		//	g_Textos->MostrarTexto( info, ImpresionDeTexto::Pixelated20, pos, g_Window, Colores::Amarillo_R, Colores::Amarillo_G, Colores::Amarillo_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );
		//	SDL_UpdateRect( g_Window, 0, 0, 0, 0 );
		//}
		g_StateStack.top().StatePointer();
	}

	Shutdown();

	return 0;
}

// This function initializes our game.
void Init()
{
	// Initiliaze SDL video and our timer.
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER);

	// Initialize the true type font library.
	TTF_Init();

	// Setup our window's dimensions, bits-per-pixel (0 tells SDL to choose for us),
	// and video format (SDL_ANYFORMAT leaves the decision to SDL). This function
	// returns a pointer to our window which we assign to g_Window.
	g_Window = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_ANYFORMAT);

	// Set the title of our window.
	SDL_WM_SetCaption(WINDOW_CAPTION, 0);

	// Get the number of ticks since SDL was initialized.
	g_Timer = SDL_GetTicks();

	g_Textos = new ImpresionDeTexto();

	g_Nivel = new Nivel();

	InicializarGameObjects();

	// We start by adding a pointer to our exit state, this way
	// it will be the last thing the player sees of the game.
	StateStruct state;
	state.StatePointer = Exit;
	g_StateStack.push(state);

	// Then we add a pointer to our menu state, this will
	// be the first thing the player sees of our game.
	state.StatePointer = Menu;
	g_StateStack.push(state);
}

void InicializarGameObjects()
{
	cRandom::Inicializar();

	delete g_Tablero;
	delete g_Resultados;
	delete g_IA;
	delete g_Background;

	g_Tablero = new Tablero( g_Nivel->GetNivelActual(), g_Nivel->GetCantidadMazos(), g_Window );
	g_IA = new IA( g_Nivel->GetCantidadMazos() );
	g_Resultados = new Resultados( g_Window, g_Nivel, g_IA, g_Textos );
	g_Background = new Background();
}

// This function shuts down our game.
void Shutdown()
{
	// Free our surfaces.
	SDL_FreeSurface( g_Window );

	delete g_Background;
	delete g_IA;
	delete g_Resultados;
	delete g_Tablero;
	delete g_Nivel;
	delete g_Textos;

	// Shutdown the true type font library.
	TTF_Quit();

	// Tell SDL to shutdown and free any resources it was using.
	SDL_Quit();
}

// This function handles the game's main menu. From here
// the player can select to enter the game, or quit.
void Menu()
{
	// Here we compare the difference between the current time and the last time we
	// handled a frame. If FRAME_RATE amount of time has, it's time for a new frame.
	if ( (SDL_GetTicks() - g_Timer) >= FRAME_RATE )
	{
		HandleMenuInput();

		// Make sure nothing from the last frame is still drawn.
		ClearScreen();

		g_Textos->MostrarTexto("Codebreaker", ImpresionDeTexto::Pretendo90, WINDOW_WIDTH/2-338, 100, g_Window, Colores::Blanco_R, Colores::Blanco_G, Colores::Blanco_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B);
		g_Textos->MostrarTexto("(C)omenzar juego", ImpresionDeTexto::Arial40, WINDOW_WIDTH/2-338, 250, g_Window, Colores::Blanco_R, Colores::Blanco_G, Colores::Blanco_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B);
		g_Textos->MostrarTexto("(S)alir", ImpresionDeTexto::Arial40, WINDOW_WIDTH/2-338, 300, g_Window, Colores::Blanco_R, Colores::Blanco_G, Colores::Blanco_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B);
		g_Textos->MostrarTexto("2016 - asimon@gmail.com - jonatandb@gmail.com", ImpresionDeTexto::Pixelated20, WINDOW_WIDTH - 450, 728, g_Window, Colores::GrisOscuro_R, Colores::GrisOscuro_G, Colores::GrisOscuro_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B);
		// Tell SDL to display our backbuffer. The four 0's will make SDL display the whole screen.
		SDL_UpdateRect( g_Window, 0, 0, 0, 0 );

		// We've processed a frame so we now need to record the time at which we did it.
		// This way we can compare this time with the next time our function gets called and
		// see if enough time has passed between calls.
		g_Timer = SDL_GetTicks();
	}
	else
	{
		SDL_Delay( SDL_GetTicks() - g_Timer );
	}
}

// This function handles the main game. We'll control the
// drawing of the game as well as any necessary game logic.
void Game()
{
	// Here we compare the difference between the current time and the last time we
	// handled a frame. If FRAME_RATE amount of time has, it's time for a new frame.
	if ( ( SDL_GetTicks() - g_Timer ) >= FRAME_RATE )
	{
		HandleGameInput();  // No puedo dibujar desde aca adentro!

		// Make sure nothing from the last frame is still drawn.
		ClearScreen();

		g_Background->Dibujar( g_Nivel->GetNivelActual(), g_Nivel->GetCantidadMazos(), g_Window );

		g_Tablero->Dibujar();

		g_Resultados->HandleInput( &g_Event );
		g_Resultados->Dibujar();

		// Tell SDL to display our backbuffer. The four 0's will make SDL display the whole screen.
		SDL_UpdateRect( g_Window, 0, 0, 0, 0 );

		// We've processed a frame so we now need to record the time at which we did it.
		// This way we can compare this time with the next time our function gets called and
		// see if enough time has passed between calls.
		g_Timer = SDL_GetTicks();
	}
	else
	{
		SDL_Delay( SDL_GetTicks() - g_Timer );
	}
}

// This function handles the game's exit screen. It will display
// a message asking if the player really wants to quit.
void Exit()
{
	// Here we compare the difference between the current time and the last time we
	// handled a frame. If FRAME_RATE amount of time has, it's time for a new frame.
	if ( ( SDL_GetTicks() - g_Timer ) >= FRAME_RATE )
	{
		HandleExitInput();

		// Make sure nothing from the last frame is still drawn.
		ClearScreen();

		g_Textos->MostrarTexto( "Codebreaker", ImpresionDeTexto::Pretendo90, WINDOW_WIDTH/2-338, 100, g_Window, Colores::Blanco_R, Colores::Blanco_G, Colores::Blanco_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );
		g_Textos->MostrarTexto( "¿Realmente desea salir (S)i / (N)o?", ImpresionDeTexto::Arial40, WINDOW_WIDTH/2-338, 250, g_Window, Colores::Blanco_R, Colores::Blanco_G, Colores::Blanco_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );

		// Tell SDL to display our backbuffer. The four 0's will make SDL display the whole screen.
		SDL_UpdateRect( g_Window, 0, 0, 0, 0 );

		// We've processed a frame so we now need to record the time at which we did it.
		// This way we can compare this time with the next time our function gets called and
		// see if enough time has passed between calls.
		g_Timer = SDL_GetTicks();
	}
	else
	{
		SDL_Delay( SDL_GetTicks() - g_Timer  );
	}
}

void WinLose()
{
	// Here we compare the difference between the current time and the last time we
	// handled a frame. If FRAME_RATE amount of time has, it's time for a new frame.
	if ( (SDL_GetTicks() - g_Timer) >= FRAME_RATE )
	{
		// Make sure nothing from the last frame is still drawn.
		ClearScreen();

		bool gano = g_IA->UsuarioGano();
		bool ultimoNivel = g_Nivel->GetNivelActual() > 4;

		if( gano )
		{
			if( ultimoNivel )
			{
				g_Textos->MostrarTexto( "Ganaste", ImpresionDeTexto::Pretendo90, WINDOW_WIDTH/2-338, 100, g_Window, 50, 255, 25, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );
			}
			else
			{
				g_Textos->MostrarTexto( "Perfecto", ImpresionDeTexto::Pretendo90, WINDOW_WIDTH/2-338, 100, g_Window, 50, 255, 25, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );
			}
			g_Textos->MostrarTexto( "(C)ontinuar", ImpresionDeTexto::Arial40, WINDOW_WIDTH/2-338, 200, g_Window, Colores::Blanco_R, Colores::Blanco_G, Colores::Blanco_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );
		}
		else
		{
			g_Textos->MostrarTexto( "Perdiste", ImpresionDeTexto::Pretendo90, WINDOW_WIDTH/2-338, 100, g_Window, 255, 25, 25, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );
		}
		g_Textos->MostrarTexto( "(N)uevo juego", ImpresionDeTexto::Arial40, WINDOW_WIDTH/2-338, 250, g_Window, Colores::Blanco_R, Colores::Blanco_G, Colores::Blanco_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );
		g_Textos->MostrarTexto( "(S)alir", ImpresionDeTexto::Arial40, WINDOW_WIDTH/2-338, 300, g_Window, Colores::Blanco_R, Colores::Blanco_G, Colores::Blanco_B, Colores::Negro_R, Colores::Negro_G, Colores::Negro_B );

		// Tell SDL to display our backbuffer. The four 0's will make SDL display the whole screen.
		SDL_UpdateRect(g_Window, 0, 0, 0, 0);

		HandleWinLoseInput();

		// We've processed a frame so we now need to record the time at which we did it.
		// This way we can compare this time with the next time our function gets called and
		// see if enough time has passed between calls.
		g_Timer = SDL_GetTicks();
	}
	else
	{
		SDL_Delay( SDL_GetTicks() - g_Timer );
	}
}

// This function simply clears the back buffer to black.
void ClearScreen()
{
	// This function just fills a surface with a given color. The
	// first 0 tells SDL to fill the whole surface. The second 0
	// is for black.
	SDL_FillRect( g_Window, 0, 0 );
}

// This function receives player input and
// handles it for the game's menu screen.
void HandleMenuInput()
{
	// Fill our event structure with event information.
	if( SDL_PollEvent(&g_Event) )
	{
		// Handle user manually closing game window
		if( g_Event.type == SDL_QUIT )
		{
			// While state stack isn't empty, pop
			while( !g_StateStack.empty() )
			{
				g_StateStack.pop();
			}
			return;
		}

		// Handle keyboard input here
		if( g_Event.type == SDL_KEYDOWN )
		{
			if( g_Event.key.keysym.sym == SDLK_ESCAPE )
			{
				g_StateStack.pop();
				return;
			}
			if( g_Event.key.keysym.sym == SDLK_s )
			{
				g_StateStack.pop();
				return;
			}
			if( g_Event.key.keysym.sym == SDLK_c )
			{
				delete g_Nivel;
				g_Nivel = new Nivel();

				InicializarGameObjects();

				StateStruct temp;
				temp.StatePointer = Game;
				g_StateStack.push(temp);
				return;
			}
		}
	}
}

// This function receives player input and
// handles it for the main game state.
void HandleGameInput()
{
	// Fill our event structure with event information.
	if( SDL_PollEvent( &g_Event) )
	{
		// Handle user manually closing game window
		if( g_Event.type == SDL_QUIT )
		{
			// While state stack isn't empty, pop
			while( !g_StateStack.empty() )
			{
				g_StateStack.pop();
			}
			return; // game is over, exit the function
		}

		// Handle keyboard input here
		if( g_Event.type == SDL_KEYDOWN )
		{
			if( g_Event.key.keysym.sym == SDLK_ESCAPE )
			{
				g_StateStack.pop();
				return; 
			}
			if( g_Event.key.keysym.sym == SDLK_RIGHT || g_Event.key.keysym.sym == SDLK_TAB )
			{
				g_Tablero->FocoMazoDerecha();
			}
			if( g_Event.key.keysym.sym == SDLK_LEFT || g_Event.key.keysym.sym == SDLK_BACKSPACE )
			{
				g_Tablero->FocoMazoIzquierda();
			}
			if( g_Event.key.keysym.sym == SDLK_UP )
			{
				g_Tablero->CartaSiguiente();	
			}
			if( g_Event.key.keysym.sym == SDLK_DOWN )
			{
				g_Tablero->CartaAnterior();
			}
			if( g_Event.key.keysym.sym >= SDLK_0 && g_Event.key.keysym.sym <= SDLK_9)
			{
				g_Tablero->ActivarCarta( g_Event.key.keysym.sym - 48 );
				g_Tablero->FocoMazoDerecha();
				return;
			}
			if( g_Event.key.keysym.sym >= SDLK_KP0 && g_Event.key.keysym.sym <= SDLK_KP9)
			{
				g_Tablero->ActivarCarta( g_Event.key.keysym.sym - 256 );
				g_Tablero->FocoMazoDerecha();
				return;
			}

			if( g_Event.key.keysym.sym == SDLK_RETURN || g_Event.key.keysym.sym == SDLK_KP_ENTER )
			{	
				vector<char> resultado = g_IA->GetResultadoValidarIngreso( g_Resultados, g_Tablero->GetNumeroIngresadoVecInt() );
				// To construct a std::string from a std::vector<char> ( http://stackoverflow.com/a/5115234 )
				string resultadoString ( resultado.begin(), resultado.end() );		

				// Agrego el número y su resultado a la lista de intentos/resultados:
				g_Resultados->RegistrarIngreso( g_Tablero->GetNumeroIngresadoString(), resultadoString );

				// Cambio de estado si el usuario ganó o perdió:
				if( g_IA->UsuarioGano() || g_IA->CantidadIntentos() >= g_Nivel->GetMaximosIntentos() )
				{
					if( g_IA->UsuarioGano() )
					{
						g_Nivel->SubirNivel();
					}
					StateStruct temp;
					temp.StatePointer = WinLose;
					g_StateStack.push( temp );
					return;
				}
			}
		}
	}
}

// This function receives player input and
// handles it for the game's exit screen.
void HandleExitInput()
{
	// Fill our event structure with event information.
	if ( SDL_PollEvent(&g_Event) )
	{
		// Handle user manually closing game window
		if (g_Event.type == SDL_QUIT)
		{
			// While state stack isn't empty, pop
			while (!g_StateStack.empty())
			{
				g_StateStack.pop();
			}
			return;
		}

		if( g_Event.type == SDL_KEYDOWN )
		{
			if( g_Event.key.keysym.sym == SDLK_ESCAPE || g_Event.key.keysym.sym == SDLK_s )
			{
				while (!g_StateStack.empty())
				{
					g_StateStack.pop();
				}
				return;
			}
			if( g_Event.key.keysym.sym == SDLK_n )
			{
				StateStruct temp;
				temp.StatePointer = Menu;	g_StateStack.push(temp);
				return;
			}
		}
	}
}

void HandleWinLoseInput()
{
	// Fill our event structure with event information.
	if ( SDL_PollEvent(&g_Event) )
	{
		// Handle user manually closing game window
		if( g_Event.type == SDL_QUIT )
		{
			// While state stack isn't empty, pop
			while( !g_StateStack.empty() )
			{
				g_StateStack.pop();
			}
			return;
		}

		// Handle keyboard input here
		if( g_Event.type == SDL_KEYDOWN )
		{
			bool continuar		= g_Event.key.keysym.sym == SDLK_c;
			bool nuevoJuego		= g_Event.key.keysym.sym == SDLK_n;
			bool salir			= g_Event.key.keysym.sym == SDLK_s;
			bool gano			= g_IA->UsuarioGano();
			bool ultimoNivel	= g_Nivel->GetNivelActual() > 4;

			if( continuar )
			{
				if( gano )
				{
					if( ultimoNivel )
					{
						nuevoJuego = true;
					}
					else
					{
						InicializarGameObjects();	// Reseta todo excepto el nivel
						g_StateStack.pop();			// Quito WinLose y sigo en Game
						return;
					}
				}
				else
				{
					nuevoJuego = true;
				}
			}

			if( nuevoJuego )
			{
				delete g_Nivel;
				g_Nivel = new Nivel();
				InicializarGameObjects();	// Reseta todo excepto el nivel
				g_StateStack.pop();			// Quito WinLose y sigo en Game
				return;
			}

			if( salir )
			{
				while (!g_StateStack.empty())
				{
					g_StateStack.pop();
				}
				StateStruct temp;
				temp.StatePointer = Exit;	g_StateStack.push(temp);
				return;
			}
		}
	}
}
