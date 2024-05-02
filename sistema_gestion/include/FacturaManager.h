#pragma once
#include "Factura.h"
#include "FacturaArchivo.h"


class FacturaManager
{
    private:
        FacturaArchivo _archivo = FacturaArchivo("Factura.dat");
    public:
        void cargar();
        void mostrar(Factura);
        void mostrarTodos();
        int buscar(int);
        void listarPorNumeroFactura();


};


