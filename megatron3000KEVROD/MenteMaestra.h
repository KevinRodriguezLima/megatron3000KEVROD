#pragma once
#include <iostream>


#include "esquema.h"


class Megatron {
public:
    Megatron(const std::string& archivo);
    ~Megatron();
    void iniciar();
    void leerConsulta();
    bool esQuery(std::vector<std::string>& palabras);
    void ejecutarQuery(std::vector<std::string>& palabras);
private:
    Esquema esquema;
    std::string archivo_1;
};