#include <iostream>
using namespace std;
#include <cstdlib>
#include <cstdio>

#include "FacturaArchivo.h"

FacturaArchivo::FacturaArchivo(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}
bool FacturaArchivo::guardar(Factura factura){
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");

    if(p == nullptr){
        cout << "EL ARCHIVO NO SE PUDO ABRIR.";
        return false;
    }

    bool guardo = fwrite(&factura,sizeof(Factura), 1, p);

    fclose(p);

    return guardo;
}

bool FacturaArchivo::guardar(Factura factura, int numeroFactura){
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");

    if(p == nullptr){
        cout << "EL ARCHIVO NO SE PUDO ABRIR.";
        return false;
    }
    fseek(p, sizeof(Factura)*numeroFactura,SEEK_SET);
    bool guardo = fwrite(&factura, sizeof(Factura), 1, p);
    fclose(p);

    return guardo;


}

int FacturaArchivo::contarRegistros(){

    FILE *p = fopen(_nombreArchivo.c_str(),"rb");

    if (p == nullptr){
    return -1;
    }

    fseek(p,0,SEEK_END);
    int bytes = ftell(p);

    fclose(p);

    return bytes / sizeof(Factura);

}

Factura FacturaArchivo::leer(int nroFactura){
    Factura factura;

    FILE *p = fopen(_nombreArchivo.c_str(), "rb");

    if (p == nullptr){
    return factura;
    }

    fseek(p, sizeof(Factura)*nroFactura, SEEK_SET);

    fread(&factura,sizeof(Factura), 1, p);

    fclose(p);

    return factura;
}

Factura FacturaArchivo::leerUltimo(){

    Factura factura;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");

    if (p == nullptr){
    return factura;
    }

    fseek(p, 0, SEEK_END);

    fread(&factura, sizeof(Factura), 1, p);

    fclose(p);

    return factura;
}

int FacturaArchivo::buscar(int nroFactura){

    FILE *p = fopen(_nombreArchivo.c_str(), "rb");

    if (p == nullptr){
    return -1;
    }

    int i = 0;
    Factura factura;

    while(fread(&factura, sizeof(Factura), 1, p)){
        if(factura.getNumFactura() == nroFactura){
            fclose(p);
            return i;
        }
        i++;
    }

    fclose(p);

    return -1;

}
