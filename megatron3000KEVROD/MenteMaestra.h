#pragma once
#include <iostream>
#include <regex>

#include "esquema.h"


class Megatron {
public:
    Megatron(const std::string& archivo);
    ~Megatron();
    void iniciar();
    void leerConsulta();
    bool esQuery(std::vector<std::string>& palabras);
    void ejecutarQuery(std::vector<std::string>& palabras);
    void imprimir(std::string& palabra1, std::string& palabra2);
private:
    Esquema esquema;
    std::string archivo_1;
};