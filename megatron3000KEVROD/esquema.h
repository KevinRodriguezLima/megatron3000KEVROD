#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

class Esquema {
public:

	void leerCsv_esquema(std::string& archivo);
	int existeRelacion(const std::string& archivo, std::ifstream& esquemaTxt);
	void validarTipoDato_crearArchivo(std::ifstream& archivoCsv, std::ifstream& esquemaTxt, int numerolinea, std::string& archivo);
	bool compararTipoDeDato(std::vector<std::vector<std::string>>& datosCsv, std::vector<std::string>& datosEsquema);
	std::string saberTipoDato(const std::string& str);

};
