#include <iostream>
#include <cstring>
#include <string>
#include <limits>
#include "Aviso.h"
#include "Funciones.h"

using namespace std;


    /// CONSTRUCTOR

Aviso::Aviso()
{
    _id = 0;
    strncpy(_fecha,"-", 11);
    strncpy(_asunto, "-", 30);
    strncpy(_descripcion, "-", 300);

}

    /// SETTTERS

void Aviso::setId(){
    _id = generarId();
}

void Aviso::setFecha(std::string fecha){
    strncpy(_fecha, fecha.c_str(), 11);
}

void Aviso::setAsunto(std::string asunto){
    strncpy(_asunto, asunto.c_str(), 30);
}

void Aviso::setDescripcion(std::string descripcion){
    strncpy(_descripcion, descripcion.c_str(), 300);
}

    /// GETTERS

int Aviso::getId(){return _id;}

const char* Aviso::getFecha(){return _fecha;}

const char* Aviso::getAsunto(){return _asunto;}



    /// METODOS

void Aviso::cargarAviso(){
    std::string asunto, descripcion;
    Fecha f;
    setFecha(f.FechaActual());

    cin.sync();
    cin.clear();
    cout << "INGRESE EL ASUNTO: > ";
    getline(cin, asunto);
    setAsunto(asunto);

    cout << endl << endl << "----- ** REVISAR ANTES DE CONFIRMAR LA DESCRIPCION COMPLETA - NO SE PODRA EDITAR. ** -----" << endl;
    setDescripcion(cargaDescripcion());


    setId();
}

void Aviso::mostrarAviso(){
    cout << "------------------------------->++<--------------------------------+" << endl;
    cout << "- Fecha: " << this->_fecha << endl;
    cout << "- Asunto: " << this->_asunto << endl;
    cout << "- Descripción:" << endl << endl << this->_descripcion << endl;
    cout << "------------------------------->++<--------------------------------+" << endl;

}

void Aviso::grabarEnDisco(){
    FILE *pAviso;

    if(!(pAviso = fopen("avisos.dat", "ab"))){

        cout << "ERROR AL ABRIR EL ARCHIVO.";
    }

    this->cargarAviso();

    fwrite(this, sizeof(Aviso), 1, pAviso);

    fclose(pAviso);

    cout << endl << endl << endl << endl << "---- AVISO GENERADO CON ÉXITO ----" << endl << endl;

    system("pause");
}

void Aviso::leerEnDisco(){
    FILE *pAviso;

    if(!(pAviso = fopen("avisos.dat", "rb"))){
        cout << "ERROR AL ABRIR EL ARCHIVO.";
    }

    while(fread(this, sizeof(Aviso), 1, pAviso)){
        this->mostrarAviso();
        cout << endl;
    }
    cout << endl;

    fclose(pAviso);
}

int Aviso::generarId(){
    FILE *pAviso;
    int idsTotales = 1;

    if(!(pAviso = fopen("avisos.dat", "rb"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return -1;
    }

    fseek(pAviso, 0, SEEK_END);
    idsTotales += ftell(pAviso) / sizeof(Aviso);
    fclose(pAviso);

    return idsTotales;

}
