// megatron3000KEVROD.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//


/*
#include <iostream>
#include <string>
#include <stdexcept>

// Función para intentar convertir a entero
bool tryParseInt(const std::string& str, int& result) {
    try {
        result = std::stoi(str);
        return true; // Si la conversión fue exitosa
    }
    catch (const std::invalid_argument&) {
        return false; // Si la cadena no es un número válido
    }
    catch (const std::out_of_range&) {
        return false; // Si el número es demasiado grande para un int
    }
}

// Función para intentar convertir a flotante
bool tryParseFloat(const std::string& str, float& result) {
    try {
        result = std::stof(str);
        return true; // Si la conversión fue exitosa
    }
    catch (const std::invalid_argument&) {
        return false; // Si la cadena no es un número válido
    }
    catch (const std::out_of_range&) {
        return false; // Si el número es demasiado grande para un float
    }
}

int main() {
    std::string str = "123.45";

    int intResult;
    float floatResult;

    if (tryParseInt(str, intResult)) {
        std::cout << "La cadena se pudo convertir a entero: " << intResult << std::endl;
    }
    else if (tryParseFloat(str, floatResult)) {
        std::cout << "La cadena se pudo convertir a flotante: " << floatResult << std::endl;
    }
    else {
        std::cout << "La cadena no se pudo convertir a entero ni a flotante, se deja como string: " << str << std::endl;
    }

    return 0;
}*/
/*
#include <iostream>
#include <string>
#include <stdexcept>

std::string parseType(const std::string& str) {
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

int main() {
    std::string str = "hola";

    std::string type = parseType(str);

    if (type == "int") {
        std::cout << "La cadena se pudo convertir a entero: " << str << std::endl;
    }
    else if (type == "float") {
        std::cout << "La cadena se pudo convertir a flotante: " << str << std::endl;
    }
    else if (type == "string") {
        std::cout << "La cadena se identifica como string: " << str << std::endl;
    }

    return 0;
}*/

/*
#include <iostream>
#include <string>
#include <stdexcept>

std::string parseType(const std::string& str) {
    try {
        std::stoi(str); // Intenta convertir a float
        return "int";
    }
    catch (const std::invalid_argument&) {
        // La cadena no es un número válido como float
    }
    catch (const std::out_of_range&) {
        // El número es demasiado grande para un float
    }

    try {
        std::stof(str); // Intenta convertir a int
        return "float";
    }
    catch (const std::invalid_argument&) {
        // La cadena no es un número válido como int
    }
    catch (const std::out_of_range&) {
        // El número es demasiado grande para un int
    }

    return "string"; // Si no es ni int ni float, entonces es string
}

int main() {
    std::string str = "15.6";

    std::string type = parseType(str);

    if (type == "int") {
        std::cout << "La cadena se pudo convertir a entero: " << str << std::endl;
    }
    else if (type == "float") {
        std::cout << "La cadena se pudo convertir a flotante: " << str << std::endl;
    }
    else if (type == "string") {
        std::cout << "La cadena se identifica como string: " << str << std::endl;
    }

    return 0;
}*/



#include <iostream>
#include <fstream>
#include "MenteMaestra.h"
//no olvidar solo pasar el nombre del archivo, sin la estension 
int main() {
    Megatron megatron("estudiantes");
    megatron.iniciar();
    return 0;
}