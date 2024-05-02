#pragma once
#include <string>
#include "Factura.h"


class FacturaArchivo
{
    private:
        std::string _nombreArchivo;
    public:
        FacturaArchivo(std::string);
        bool guardar(Factura);
        bool guardar(Factura, int);
        int contarRegistros();
        Factura leer(int);
        Factura leerUltimo();
        int buscar(int);

};
