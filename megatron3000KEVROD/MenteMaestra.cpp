#include "MenteMaestra.h";


Megatron::Megatron(const std::string& archivo) : archivo_1(archivo) {}

Megatron::~Megatron() {}

void Megatron::iniciar() {

    esquema.leerCsv_esquema(archivo_1);

    while (true) {
        std::string texto;
        std::cout << "Ingrese el comando: ";
        std::getline(std::cin, texto);

        if (texto == "MEGATRON3000") {
            std::cout << "BIENVENIDO A MEGATRON 3000 !!!!!!" << std::endl;
            leerConsulta();
        }
        else if (texto == "QUIT" || texto == "quit") {
            std::cout << "Saliendo del programa..." << std::endl;
            break;
        }
        else {
            std::cout << "Comando incorrecto. Inténtelo de nuevo." << std::endl;
        }
    }
}

void Megatron::leerConsulta() {
    while (true) {
        std::string texto;
        std::cout << "Ingrese su consulta ('QUIT' para salir): ";
        std::getline(std::cin, texto);

        if (texto == "QUIT" || texto == "quit") {
            std::cout << "Saliendo de la consulta..." << std::endl;
            break;
        }
        else if (esQuery(texto)) {
            std::cout << "Consulta válida: " << texto << std::endl;
            ejecutarQuery(texto);
            // Procesar la consulta
        }
        else {
            std::cout << "Consulta incorrecta. Inténtelo de nuevo." << std::endl;
        }
    }
}
bool Megatron::esQuery(std::string& texto) {
    std::istringstream iss(texto);
    std::vector<std::string> palabras;
    std::string palabra;

    while (iss >> palabra) {
        palabras.push_back(palabra);
    }

    if (palabras.size() < 6) {
        return false;
    }

    if (palabras[0] != "&") {
        return false;
    }
    if (palabras[1] != "SELECT") {
        return false;
    }
    if (palabras[3] != "FROM") {
        return false;
    }
    if (palabras.back() != "#") {
        return false;
    }
    return true;
    /*std::regex pattern("&\s*SELECT\s+(\*|\w+)\s+FROM\s+\w+\s*#");

    // Verificar si la cadena coincide con el patrón
    return std::regex_match(texto, pattern);*/
}
    
void Megatron::ejecutarQuery(std::string& texto) {
    std::istringstream iss(texto);
    std::vector<std::string> palabras;
    std::string palabra;

    while (iss >> palabra) {
        palabras.push_back(palabra);
    }
    std::regex pattern("&\s*SELECT\s+(\*|\w+)\s+FROM\s+\w+\s*#");
    if (std::regex_match(texto, pattern)) {
        imprimir(palabras[2], palabras[4]);
    }
}
void Megatron::imprimir(std::string& palabra1, std::string& palabra2) {
    std::ifstream esquemaTxt("esquema.txt");
    std::cout << "funciona";
}