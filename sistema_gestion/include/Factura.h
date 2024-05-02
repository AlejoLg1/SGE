#pragma once
#include "Fecha.h"

class Factura
{
    private:
        int _numFactura;
        Fecha _fechaEmision;
        float _monto;
        bool _estado;

    public:
        Factura();
        ///setters
        void setNumFactura(int);
        void setFechaEmision(Fecha);
        void setMonto(float);
        void setEstado(bool);
        ///getters
        int getNumFactura();
        Fecha getFechaEmision();
        float getMonto();
        bool getEstado();



};
