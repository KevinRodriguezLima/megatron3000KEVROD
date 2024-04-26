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
            std::cout << "Comando incorrecto. Int�ntelo de nuevo." << std::endl;
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
        else {
            std::istringstream iss(texto);
            std::vector<std::string> palabras;
            std::string palabra;
            while (iss >> palabra) {
                palabras.push_back(palabra);
            }

            if (esQuery(palabras)) {
                std::cout << "Consulta v�lida: " << texto << std::endl;
                ejecutarQuery(palabras);
            }
            else {
                std::cout << "Consulta incorrecta. Int�ntelo de nuevo." << std::endl;
            }
        }
    }
}
bool Megatron::esQuery(std::vector<std::string>& palabras) {

    if (palabras.size() < 3 || palabras[0] != "&" || palabras[1] != "SELECT") {
        std::cout << "La consulta no comienza con '& SELECT'." << std::endl;
        return false;
    }
    if (palabras[2] != "*" && palabras.size() < 4) {
        std::cout << "Faltan atributos despu�s de 'SELECT'." << std::endl;
        return false;
    }
    auto from_pos = std::find(palabras.begin(), palabras.end(), "FROM");
    if (from_pos == palabras.end()) {
        std::cout << "No se encontr� 'FROM' en la consulta." << std::endl;
        return false;
    }
    if (std::distance(from_pos, palabras.end()) < 2) {
        std::cout << "Falta el nombre de la tabla despu�s de 'FROM'." << std::endl;
        return false;
    }
    if (palabras.back() != "#") {
        std::cout << "La consulta no termina con '#'." << std::endl;
        return false;
    }

    return true;


    //intento con expresiones regulares

    /*std::string consulta = "";
    for (const auto& palabra : palabras) {
        consulta += palabra + " ";
    }
    std::cout << "Consulta construida: " << consulta << std::endl;
    std::regex pattern("&\\s*SELECT\\s+(\\*|\\w+(\\s*,\\s*\\w+)*)\\s+FROM\\s+\\S+\\s*#");
    bool resultado = std::regex_match(consulta, pattern);
    */

}
    
void Megatron::ejecutarQuery(std::vector<std::string>& palabras) {
    std::string tabla;
    auto from_pos = std::find(palabras.begin(), palabras.end(), "FROM");
    if (from_pos != palabras.end() && std::distance(from_pos, palabras.end()) >= 2) {
        tabla = *(from_pos + 1); // El nombre de la tabla est� despu�s de "FROM"
        std::cout << "Nombre de la relacion"<<tabla;
    }
    else {
        std::cout << "No se pudo obtener el nombre de la tabla." << std::endl;
        return;
    }

    std::ifstream esquemaTxt("esquema.txt");
    std::string linea;
    int numeroLinea = 0;
    while (std::getline(esquemaTxt, linea)) {
        ++numeroLinea;
        std::istringstream ss(linea);
        std::string palabra;
        if (std::getline(ss, palabra, '#')) {
            if (palabra == tabla) {
                std::cout << "Coincidencia encontrada en la linea " << numeroLinea << std::endl;
                break;
            }
        }
    }

    


}
void Megatron::imprimir(std::string& palabra1, std::string& palabra2) {
    std::ifstream esquemaTxt("esquema.txt");
    std::cout << "funciona";
}