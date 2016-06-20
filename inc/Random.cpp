#pragma once

#include <cstdlib>
#include <ctime>

class cRandom
{
public:
	static void Inicializar()
	{
		srand( time( NULL ) );
	};

	static int getRandom()
	{
		return rand();
	};

	static int getRandom( int fin )
	{
		return rand() % fin+1;
	};

	static int getRandom( int inicio, int fin )
	{
		return ( rand() % ( fin + 1 - inicio ) ) + inicio;
	}
};
