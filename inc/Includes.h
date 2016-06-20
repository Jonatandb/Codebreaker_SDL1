#pragma once 

#include <string>
#include <vector>
#include <stack>     // We'll use the STL stack to store our function pointers

using namespace std; // save us from writing "std::" everywhere

#include "SDL.h"     // Main SDL header 
#include "SDL_TTF.h" // True Type Font header

#include "Logger.cpp"
#include "Colores.cpp"
#include "Random.cpp"
#include "Background.h"
#include "Borde.h"
#include "Nivel.h"
#include "ImpresionDeTexto.h"

#include "Carta.h"
	#include "Mazo.h"
		#include "Tablero.h"

#include "Resultados.h"
	#include "IA.h"
