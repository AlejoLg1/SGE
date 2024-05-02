#include <iostream>
using namespace std;
#include <cstdlib>
#include "Factura.h"

Factura::Factura()
{
    _numFactura = 0;
    _fechaEmision = Fecha();
    _monto = 0.00;
    _estado = false;
}

void Factura::setNumFactura(int numerodeFctura){
    _numFactura = numerodeFctura;
}

void Factura::setFechaEmision(Fecha fechaEmision){
    _fechaEmision = fechaEmision;
}
void Factura::setMonto(float monto){
    _monto = monto;
}
void Factura::setEstado(bool estado){
    _estado = estado;
}

int Factura::getNumFactura(){
    return _numFactura;
}
Fecha Factura::getFechaEmision(){
    return _fechaEmision;
}
float Factura::getMonto(){
    return _monto;
}
bool Factura::getEstado(){
    return _estado;
}
