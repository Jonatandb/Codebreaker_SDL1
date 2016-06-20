#pragma once

#include "Defines.h"
#include "Includes.h"

class Resultados;	// http://stackoverflow.com/a/23283140

class IA
{
private:
	int _id;
	int _cantIntentos;
	int _cantMazos;
	bool _usuarioGano;
	vector<int> _aleatorio;
	unsigned short searchDigit( vector <int> v, int value, unsigned short pos );
public:
	IA( int cantidadMazos );
	~IA();
	string GetNumeroSecretoString();
	// Devuelve un vector<char> con el resultado de comprar el numero ingresado contra el numero al azar.
	// Devuelve el vector<char> vacío si recibe un vector<int> vacío.
	// Devuelve el vector<char> vacío si el numero ya existe entre los numeros registrados.
	// Incrementa la cantidad de intentos realizados.
	// Registra internamente si el usuario ganó luego de verificarse el ingreso.
	vector <char> GetResultadoValidarIngreso( Resultados* resultados, vector<int> numeroIngresado );
	bool UsuarioGano();
	int CantidadIntentos();
};