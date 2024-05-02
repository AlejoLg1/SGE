#include <iostream>
using namespace std;
#include <cstdlib>
#include <string>
#include "FacturaManager.h"
#include "rlutil.h"
using namespace rlutil;

void FacturaManager::cargar(){

    int numeroFactura;
    Fecha fechaEmision;
    float monto;

    cout << "INGRESE EL NUMERO DE FACTURA: " << endl;
    cin >> numeroFactura;
    cout << "INGRESE LA FECHA DE EMISION: " << endl;
            fechaEmision.CargarFecha();
    cout << "INGRESE EL MONTO A PAGAR: " << endl;
    cin >> monto;

    Factura factura;
    factura.setNumFactura(numeroFactura);
    factura.setFechaEmision(fechaEmision);
    factura.setMonto(monto);
    factura.setEstado(true);

    bool guardo = _archivo.guardar(factura);

    if (guardo){
        cout << "LA FACTURA NUMERO: #" << factura.getNumFactura() << ", SE CARGO EXITOSAMENTE.";
    }

    else{
        cout << "> LA FACTURA NO SE REGISTRO CORRECTAMENTE.";
    }
}

void FacturaManager::mostrar(Factura factura){

    cout << "NUMERO DE FACTURA: " << factura.getNumFactura();
    cout << "FECHA DE EMISION: " << factura.getFechaEmision().toString("DD/MM/YYYY");
    cout << "MONTO A PAGAR: " << factura.getMonto();
}

void FacturaManager::mostrarTodos(){

    int cantidadFacturas = _archivo.contarRegistros();

    for(int i = 0 ; i < cantidadFacturas ; i++){
        mostrar(_archivo.leer(i));
    }
}

int FacturaManager::buscar(int numeroFactura){

    int cantidadFacturas = _archivo.contarRegistros();

    for(int i = 0; i < cantidadFacturas; i++){

        Factura factura = _archivo.leer(i);

        if(factura.getNumFactura() == numeroFactura){
            return i;
        }
    }
    return -1;
}

void FacturaManager::listarPorNumeroFactura(){

    int numeroFactura, posicion;

    cout << "INGRESE EL NUMERO DE FACTURA QUE DESEA MOSTRAR POR PANTALLA: ";
    cin >> numeroFactura;

    posicion = _archivo.buscar(numeroFactura);

    if(posicion >= 0){
        Factura factura = _archivo.leer(posicion);
        mostrar(factura);
    }

    else{
        cout << "NO SE ENCONTRO EL NUMERO DE FACTURA QUE DESEA MOSTRAR POR PANTALLA.";
    }

}
