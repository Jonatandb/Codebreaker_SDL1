#pragma once

#include <fstream>	 // Para loguear en log.txt
#include <string>
using namespace std; // save us from writing "std::" everywhere

class Logger
{
private:
	int _id;
	static fstream _file;
public:
	Logger()
	{
		_file.open("log.txt");	// http://www.cplusplus.com/reference/fstream/ofstream/open/
		_id = rand();	////Logger::Log( "Logger\t\tId = " + to_string( _id) + "\t\tCreado." );
	}
	~Logger()
	{
		//Logger::Log( "Logger\t\tId = " + to_string( _id) + "\t\tEliminado." );
		// Cerrar el fichero, 
		// para luego poder abrirlo para lectura:
		_file.close();
	}
	static void Log( string mensaje )
	{
	   // Enviamos una cadena al fichero de salida:
	   _file << mensaje << endl;
	}
};