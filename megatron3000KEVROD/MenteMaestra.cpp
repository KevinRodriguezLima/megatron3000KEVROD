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

    if (palabras.size() < 6 || palabras[0] != "&" || palabras[1] != "SELECT") {
        std::cout << "La consulta no comienza con '& SELECT' o falta rellenar campos" << std::endl;
        return false;
    }
    if (palabras[2] != "*" && palabras.size() < 4) {
        std::cout << "Faltan atributos después de 'SELECT'." << std::endl;
        return false;
    }
    auto from_pos = std::find(palabras.begin(), palabras.end(), "FROM");
    if (from_pos == palabras.end()) {
        std::cout << "No se encontró 'FROM' en la consulta." << std::endl;
        return false;
    }
    if (std::distance(from_pos, palabras.end()) < 2) {
        std::cout << "Falta el nombre de la tabla después de 'FROM'." << std::endl;
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
        tabla = *(from_pos + 1); // El nombre de la tabla está después de "FROM"
        std::cout << "Nombre de la relacion"<<tabla;
    }
    else {
        std::cout << "No se pudo obtener el nombre de la tabla." << std::endl;
        return;
    }

    std::vector<std::string> titulos;
    auto select_pos = std::find(palabras.begin(), palabras.end(), "SELECT");
    auto from_pos2 = std::find(palabras.begin(), palabras.end(), "FROM");
    if (select_pos != palabras.end() && from_pos2 != palabras.end() && select_pos < from_pos2) {
        auto inicio = select_pos + 1;
        auto fin = from_pos2;
        while (inicio != fin) {

            std::istringstream ss(*inicio);
            std::string titulo;
            while (std::getline(ss, titulo, ',')) {

                titulo.erase(titulo.find_last_not_of(" \t\n\r\f\v") + 1);
                titulo.erase(0, titulo.find_first_not_of(" \t\n\r\f\v"));
                titulos.push_back(titulo);
            }
            ++inicio;
        }
    }

    //sacamos los atributos
    std::vector<std::string> atributos;
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
                std::string atributo;
                while (std::getline(ss, atributo, '#')) {
                    if (atributo != tabla && atributo != "string" && atributo != "int" && atributo != "float") {
                        atributos.push_back(atributo);
                    }
                }
                break;
            }
        }
    }
    if (titulos.size() == 1 && titulos[0] == "*") {
        for (const auto& atributo : atributos) {
            std::cout << "- " << atributo << "   -   ";
        }
        std::cout << std::endl << "---------------------------" << std::endl;
        std::ifstream archivoTabla(tabla + ".txt");
        std::string lineaTabla;
        while (std::getline(archivoTabla, lineaTabla)) {
            std::istringstream ss(lineaTabla);
            std::string columna;
            while (std::getline(ss, columna, '#')) {
                std::cout << columna << " ";
            }
            std::cout << std::endl;
         }
        
    }
    else {
        //ubique la linea ahora que era? xd
        std::cout << "Titulos de las columnas:" << std::endl;
        for (const auto& titulo : titulos) {
            std::cout << "- " << titulo << "   -   ";
        }
        //pos vector
        std::vector<int> posiciones;
        for (size_t i = 0; i < titulos.size(); ++i) {
            for (size_t j = 0; j < atributos.size(); ++j) {
                if (titulos[i] == atributos[j]) {
                    posiciones.push_back(j + 1);
                    break;
                }
            }
        }

        // Imprimir las coincidencias encontradas
        /*std::cout << "Coincidencias encontradas:" << std::endl;
        for (size_t i = 0; i < titulos.size(); ++i) {
            std::cout << "Columna: " << titulos[i];
            if (i < posiciones.size()) {
                std::cout << ", Posicion en atributos: " << posiciones[i];
            }
            std::cout << std::endl;
        }*/
        //imprimir daots
        std::cout << std::endl << "---------------------------" << std::endl;
        std::ifstream archivoTabla(tabla + ".txt");
        std::string lineaTabla;
        while (std::getline(archivoTabla, lineaTabla)) {
            std::istringstream ss(lineaTabla);
            std::vector<std::string> columnas;
            std::string columna;
            while (std::getline(ss, columna, '#')) {
                columnas.push_back(columna);
            }
            for (int pos : posiciones) {

                std::cout << columnas[pos - 1];
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }
    

}
void Megatron::imprimir(std::string& palabra1, std::string& palabra2) {
    std::ifstream esquemaTxt("esquema.txt");
    std::cout << "funciona";
}