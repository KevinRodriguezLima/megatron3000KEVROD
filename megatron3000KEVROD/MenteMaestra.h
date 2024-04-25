#pragma once
#include <iostream>

#include "esquema.h"
class Megatron {
public:
    Megatron(const std::string& archivo);
    ~Megatron();
    void iniciar();
private:
    Esquema esquema;
    std::string archivo_1;
};
