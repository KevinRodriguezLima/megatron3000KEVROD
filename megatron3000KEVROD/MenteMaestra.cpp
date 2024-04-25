#include "MenteMaestra.h";


Megatron::Megatron(const std::string& archivo) : archivo_1(archivo) {}

Megatron::~Megatron() {}

void Megatron::iniciar() {
    std::cout << archivo_1;
    esquema.leerCsv_esquema(archivo_1);
    std::cout << "BIENVENIDO A MEGATRON 3000 !!!!!!" << std::endl;
}