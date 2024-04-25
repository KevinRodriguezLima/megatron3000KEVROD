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
    bool esQuery(std::string& texto);
    void ejecutarQuery(std::string& texto);
    void imprimir(std::string& palabra1, std::string& palabra2);
private:
    Esquema esquema;
    std::string archivo_1;
};