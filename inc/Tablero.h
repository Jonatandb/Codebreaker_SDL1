#pragma once

#include "Defines.h"
#include "Includes.h"

class Mazo;	// http://stackoverflow.com/a/23283140

/*
// Tablero:
// Por defecto foco al 1º mazo y todas cartas default (con signo "?")
// Si presionan Izq o Der: cambian el mazo con foco
// Si presionan Enter: Devuelve bool luego de ver si son iguales el numero al azar y el de las cartas
// Si presionan un numero: el mazo activo muestra la carta con ese numero
// Si presionan otra tecla: el mazo activo muestra la carta default	(o puede ignorar el ingreso)
*/
class Tablero
{
private:
	int		_id;
	int		_x;
	int		_y;
	int		_cantMazos;
	Mazo*	_mazos[ 5 ]; // Por defecto el tablero esta preparado para contener 5 mazos (no descubrí como hacer esto dinamico).  TODO: Usar un vector<Mazo>  :)
	int		_mazoActivo;
	bool	_dibujarBorde;
	int		_tiempoSinDibujarBorde;
	int		_tiempoDibujandoBorde;
	bool	_bordeEstatico;
	SDL_Surface* _window;
	bool BuscarEnVector( vector<int> origen, int numero );
	void DibujarBordes();
	void SetearUbicacion( int nivelActual );
public:
	Tablero( int nivelActual, int cantidadMazos, SDL_Surface* window );
	~Tablero();
	bool Dibujar();
	void FocoMazoDerecha();
	void FocoMazoIzquierda();
	void CartaSiguiente();
	void CartaAnterior();
	void ActivarCarta( int carta );
	void ResetearSeleccionRepetida();
	/// Se encarga de que cuando se da el foco a un nuevo mazo, aparezca el borde inmediatamente.
	void ForzarDibujadoDeBorde();
	// Devuelve un string con el numero seleccionado en los mazos
	// Si algun mazo no posee seleccion (tiene aun el signo de pregunta), devuelve "0".
	string GetNumeroIngresadoString();
	// Devuelve un vector<int> con los numeros de las cartas seleccionadas
	// Devuelve el vector vacío si en algún mazo falta seleccionar una carta (tiene activa la carta con el signo de pregunta, valor 10).
	vector<int> GetNumeroIngresadoVecInt();
};