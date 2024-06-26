#include "esquema.h";

void Esquema::leerCsv_esquema(std::string& archivo) {
    std::string esquema = "esquema.txt";
    std::string nombreArchivo = archivo + ".csv";

    std::ifstream archivoCsv(nombreArchivo);
    std::ifstream esquemaTxt(esquema);

    int nrolinea = existeRelacion(archivo, esquemaTxt);
    if (nrolinea != 0) {
        //reasignamos el puntero del archivo porque lo movimos al leer esquemaTxt
        esquemaTxt.clear();
        esquemaTxt.seekg(0, std::ios::beg);
        // 2 *****  verificaremos si la estructura del esquema coincide
        validarTipoDato_crearArchivo(archivoCsv, esquemaTxt, nrolinea, archivo);
    }
    archivoCsv.close();
    esquemaTxt.close();
}


int Esquema::existeRelacion(const std::string& archivo, std::ifstream& esquemaTxt) {
    std::string linea;
    int numeroLinea = 0;
    while (std::getline(esquemaTxt, linea)) {
        ++numeroLinea;
        std::istringstream ss(linea);
        std::string palabra;
        if (std::getline(ss, palabra, '#')) {
            if (palabra == archivo) {
                std::cout << "Coincidencia encontrada en la linea " << numeroLinea << std::endl;
                return numeroLinea;
            }
        }
    }
    std::cout << "No se encontraron coincidencias del nombre del archivo CSV en el archivo TXT." << std::endl;
    return 0;
}

void Esquema::validarTipoDato_crearArchivo(std::ifstream& archivoCsv, std::ifstream& esquemaTxt, int numerolinea, std::string& archivo) {
    //validar tipo de dato wazaaaa

    std::vector<std::vector<std::string>> datosCsv;
    std::vector<std::string> datosEsquema;

    // Leer el archivo CSV y almacenamos los datos a partir de la segunda fila
    std::string lineaCsv;
    int contadorLinea = 0;
    while (std::getline(archivoCsv, lineaCsv)) {
        if (contadorLinea != 0) { // Ignorar la primera l�nea (t�tulos)
            std::vector<std::string> fila;
            std::istringstream ss(lineaCsv);
            std::string campo;

            while (std::getline(ss, campo, ',')) {
                // Si el campo comienza con comillas
                if (campo.front() == '"') {
                    // Eliminar la primera comilla
                    campo.erase(campo.begin());
                    // Concatenar campos hasta encontrar una comilla al final
                    std::string temp;
                    bool dentroComillas = true;
                    temp += campo;
                    while (std::getline(ss, campo, ',')) {
                        temp += "," + campo;
                        // Si el campo termina con comillas
                        if (campo.back() == '"') {
                            // Eliminar la �ltima comilla
                            temp.pop_back();
                            dentroComillas = false;
                            break;
                        }
                    }
                    // A�adir el campo corregido a la fila
                    fila.push_back(temp);
                }
                else { // Si el campo no comienza con comillas
                    fila.push_back(campo);
                }
            }
            datosCsv.push_back(fila);
        }
        contadorLinea++;
    }

    // Leer el archivo de esquema y almacenar los datos de la l�nea 
    std::string lineaEsquema;
    contadorLinea = 0;
    while (std::getline(esquemaTxt, lineaEsquema)) {
        if (contadorLinea == numerolinea - 1) {
            std::istringstream ss(lineaEsquema);
            std::string dato;
            while (std::getline(ss, dato, '#')) {
                datosEsquema.push_back(dato);
            }
            break;
        }
        contadorLinea++;
    }

    //comparamos los datos si sigue el esquema entonces creamos el archivo txt con todos los datos del csv
    if (compararTipoDeDato(datosCsv, datosEsquema)) {
        std::ofstream archivoTxt(archivo + ".txt");

        for (const auto& fila : datosCsv) {
            for (int i = 0; i < fila.size(); ++i) {
                archivoTxt << fila[i];
                if (i < fila.size() - 1) {
                    archivoTxt << "#"; // Separar por #
                }
            }
            archivoTxt << "\n";
        }

        archivoTxt.close();
    }

    datosEsquema.clear();
    datosCsv.clear();
}

std::string Esquema::saberTipoDato(const std::string& str) {
    try {
        size_t pos = 0;
        std::stoi(str, &pos); // Intenta convertir a int
        if (pos == str.length()) {
            return "int";
        }
    }
    catch (const std::invalid_argument&) {
    }
    catch (const std::out_of_range&) {
    }

    try {
        std::stof(str); // Intenta convertir a float
        return "float";
    }
    catch (const std::invalid_argument&) {
    }
    catch (const std::out_of_range&) {
    }

    return "string"; // Si no es ni int ni float, entonces es string
}

bool Esquema::compararTipoDeDato(std::vector<std::vector<std::string>>& datosCsv, std::vector<std::string>& datosEsquema) {
    bool verificar = true;
    for (const auto& fila : datosCsv) {
        for (int i = 0; i < fila.size(); ++i) {
            std::cout << fila[i] + " -" + saberTipoDato(fila[i]) + " . " + datosEsquema[((i + 1) * 2)] << std::endl;
            if (saberTipoDato(fila[i]) != datosEsquema[((i + 1) * 2)]) {
                verificar = false;
                std::cout << "Tipo de dato incorrecto en la fila " << (&fila - &datosCsv[0]) + 1
                    << ", columna " << (i / 2) + 1 << ": se esperaba " << datosEsquema[((i + 1) * 2)]
                    << " pero se encontr� " << saberTipoDato(fila[i]) << std::endl;
                return false;
            }

        }
    }

}


