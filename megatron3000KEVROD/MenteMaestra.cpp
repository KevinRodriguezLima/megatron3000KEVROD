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
        else {
            std::istringstream iss(texto);
            std::vector<std::string> palabras;
            std::string palabra;
            while (iss >> palabra) {
                palabras.push_back(palabra);
            }

            if (esQuery(palabras)) {
                std::cout << "Consulta válida: " << texto << std::endl;
                ejecutarQuery(palabras);
            }
            else {
                std::cout << "Consulta incorrecta. Inténtelo de nuevo." << std::endl;
            }
        }
    }
}
bool Megatron::esQuery(std::vector<std::string>& palabras) {
    std::string consulta = "";
    for (const auto& palabra : palabras) {
        consulta += palabra + " ";
    }
    std::cout << "Consulta construida: " << consulta << std::endl;

    if (palabras.size() < 6 || palabras[0] != "&" || palabras[1] != "SELECT") {
        std::cout << "La consulta no comienza con '& SELECT'." << std::endl;
        return false;
    }

    // Paso 2: Verificar los atributos o el asterisco después de "SELECT"
    if (palabras[2] != "*" && palabras.size() < 6) {
        std::cout << "Faltan atributos después de 'SELECT'." << std::endl;
        return false;
    }

    // Paso 3: Verificar que la consulta contenga "FROM" después de los atributos
    auto from_pos = std::find(palabras.begin(), palabras.end(), "FROM");
    if (from_pos == palabras.end()) {
        std::cout << "No se encontró 'FROM' en la consulta." << std::endl;
        return false;
    }

    // Paso 4: Verificar que haya un nombre de tabla después de "FROM"
    if (std::distance(from_pos, palabras.end()) < 2) {
        std::cout << "Falta el nombre de la tabla después de 'FROM'." << std::endl;
        return false;
    }

    // Paso 5: Verificar que la consulta termine con '#'
    if (palabras.back() != "#") {
        std::cout << "La consulta no termina con '#'." << std::endl;
        return false;
    }

    // Si la consulta pasa todas las verificaciones, es válida
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
    /*std::regex pattern("&\s*SELECT\s+(\*|\w+)\s+FROM\s+\w+\s*#");
    if (std::regex_match(texto, pattern)) {
        imprimir(palabras[2], palabras[4]);
    }*/
}
void Megatron::imprimir(std::string& palabra1, std::string& palabra2) {
    std::ifstream esquemaTxt("esquema.txt");
    std::cout << "funciona";
}