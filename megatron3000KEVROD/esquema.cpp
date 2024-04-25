#include "esquema.h";

void Esquema::leerCsv_esquema(std::string& archivo) {
	std::string esquema = "esquema.txt";
	std::string nombreArchivo = archivo + ".csv";
	std::ifstream archivoCsv(nombreArchivo);
	std::ifstream esquemaTxt(esquema);

    if (archivoCsv.is_open()) {
        std::cout << "el archivo " << nombreArchivo << " se pudo abrir" << std::endl;
    }
    else
        std::cout << "el no se pudo abrir ";
	if (esquemaTxt.is_open()) {
		std::cout << "el archivo " << esquema << " se pudo abrir" << std::endl;
	}

	// 1 *****  verificamos si hay una relacion con el nombre del archivo:
	std::string linea;
	int numeroLinea = 0;
	bool coincidenciaEncontrada = false;
	while (std::getline(esquemaTxt, linea)) {
		++numeroLinea;
		std::istringstream ss(linea);
		std::string palabra;
		if (std::getline(ss, palabra, '#')) {
			if (palabra == archivo) {
				coincidenciaEncontrada = true;
				std::cout << "Coincidencia encontrada en la linea " << numeroLinea << std::endl;
			}
		}
	}
	if (!coincidenciaEncontrada) {
		std::cout << "No se encontraron coincidencias del nombre del archivo CSV en el archivo TXT." << std::endl;
	}
    //reasignamos el puntero del archivo
    esquemaTxt.clear();
    esquemaTxt.seekg(0, std::ios::beg);

	// 2 *****  verificaremos si la estructura del esquema coincide
	validarTipoDato_crearArchivo(archivoCsv,esquemaTxt,numeroLinea,archivo);

	archivoCsv.close();
	esquemaTxt.close();
}
void Esquema::validarTipoDato_crearArchivo(std::ifstream& archivoCsv, std::ifstream& esquemaTxt, int numerolinea, std::string& archivo) {
	//validar tipo de dato wazaaaa
    std::vector<std::vector<std::string>> datosCsv;
    std::vector<std::string> datosEsquema;

    // Leer el archivo CSV y almacenar los datos a partir de la segunda fila
    std::string lineaCsv;
    int contadorLinea = 0;
    while (std::getline(archivoCsv, lineaCsv)) {
        if (contadorLinea > 0) { // Saltar la primera fila
            std::vector<std::string> fila;
            std::istringstream ss(lineaCsv);
            std::string dato;
            while (std::getline(ss, dato, ',')) {
                fila.push_back(dato);
            }
            datosCsv.push_back(fila);
        }
        contadorLinea++;
    }

    // Imprimir los datos del archivo CSV
    std::cout << "Datos del archivo CSV:" << std::endl;
    for (const auto& fila : datosCsv) {
        for (const auto& dato : fila) {
            std::cout << dato << "\t";
        }
        std::cout << std::endl;
    }

    // Leer el archivo de esquema y almacenar los datos de la línea indicada
    std::string lineaEsquema;
    contadorLinea = 0;
    while (std::getline(esquemaTxt, lineaEsquema)) {
        if (contadorLinea == numerolinea - 1) { // Restar 1 porque el índice de línea comienza desde 0
            std::istringstream ss(lineaEsquema);
            std::string dato;
            while (std::getline(ss, dato, '#')) {
                datosEsquema.push_back(dato);
            }
            break; // Salir del bucle una vez que se hayan leído los datos de la línea indicada
        }
        contadorLinea++;
    }

    // Imprimir datos de depuración
    std::cout << "Datos del archivo de esquema:" << std::endl;
    if (datosEsquema.empty()) {
        std::cout << "El vector de datos del archivo de esquema está vacío." << std::endl;
    }
    else {
        for (const auto& dato : datosEsquema) {
            std::cout << dato << "\t";
        }
        std::cout << datosEsquema[2]<< std::endl;
        std::cout << std::endl;
    }


    //comparamos los datos si sigue el esquema entonces creamos el archivo txt con todos los datos del csv
    if (compararTipoDeDato(datosCsv, datosEsquema)){
        std::ofstream archivoTxt(archivo + ".txt");

        if (archivoTxt.is_open()) {
            // Escribir los datos del archivo CSV en el archivo de texto
            for (const auto& fila : datosCsv) {
                for (const auto& dato : fila) {
                    archivoTxt << dato << "#"; // Separar por #
                }
                archivoTxt << "\n"; // Nueva línea al final de cada fila
            }

            // Cerrar el archivo de texto
            archivoTxt.close();

            std::cout << "Se ha creado el archivo de texto \"" << archivo + ".txt" << "\" con éxito." << std::endl;
        }
    }


	//std::vector<std::string> datosTxt;
	//std::vector<std::string> datosCsv;



	std::vector<std::string> titulos_columnas;


	titulos_columnas.clear();
	datosEsquema.clear();
	datosCsv.clear();
}

std::string Esquema::parseType(const std::string& str) {
    try {
        size_t pos = 0;
        std::stoi(str, &pos); // Intenta convertir a int
        if (pos == str.length()) {
            return "int";
        }
    }
    catch (const std::invalid_argument&) {
        // La cadena no es un número válido como int
    }
    catch (const std::out_of_range&) {
        // El número es demasiado grande para un int
    }

    try {
        std::stof(str); // Intenta convertir a float
        return "float";
    }
    catch (const std::invalid_argument&) {
        // La cadena no es un número válido como float
    }
    catch (const std::out_of_range&) {
        // El número es demasiado grande para un float
    }

    return "string"; // Si no es ni int ni float, entonces es string
}

bool Esquema::compararTipoDeDato(std::vector<std::vector<std::string>>& datosCsv, std::vector<std::string>& datosEsquema) {
    bool verificar = true;
    for (const auto& fila : datosCsv) {
        // Iterar sobre cada elemento de la fila
        for (int i = 0; i < fila.size(); ++i) {
            std::cout << fila[i] + " -" + parseType(fila[i]) + " . " + datosEsquema[((i + 1) * 2)] << std::endl;
            if (parseType(fila[i]) != datosEsquema[((i + 1) * 2)]) {
                verificar = false;
                std::cout << "Tipo de dato incorrecto en la fila " << (&fila - &datosCsv[0]) + 1
                    << ", columna " << (i / 2) + 1 << ": se esperaba " << datosEsquema[((i + 1) * 2)]
                    << " pero se encontró " << parseType(fila[i]) << std::endl;
                return false;
            }

        }
    }
    
}


