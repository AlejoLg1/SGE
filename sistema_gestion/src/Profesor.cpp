#include <iostream>
#include <cstdlib>
#include "Funciones.h"
#include "Profesor.h"

using namespace std;

Profesor::Profesor()
{
    Persona();
    _legajo = 0;
    _clave = 0;
    _estado = false;
}

void Profesor::setLegajo(){
    _legajo = settearNuevoLegajo();
}
void Profesor::setClave(int clave){
    _clave = clave;
}
void Profesor::setEstado(bool estado){
    _estado = estado;
}

///GETTERS

int Profesor::getLegajo(){
    return _legajo;
}
int Profesor::getClave(){
    return _clave;
}
bool Profesor::getEstado(){
    return _estado;
}

///MÉTODOS

void Profesor::cargarProfesor(){

    cout << "CREANDO PERFIL DIRECTOR" << endl;

    cout<< endl <<"\t - Legajo: ";
    setLegajo();
    cout << getLegajo();
    cout << endl;

    Persona::cargar();

    cout<< endl << "\t - Clave: ";
    cin >> _clave;

    cout << endl << "\t - Estado (1 para activo, 0 para inactivo): ";
    cin >> _estado;

}
void Profesor::mostrarProfesor(){
    Persona::mostrar();
    cout << endl;
    cout <<"Legajo: " << _legajo<<endl;
    cout <<"Clave: " << _clave<<endl;
    cout << endl << "Estado: " << _estado<<endl;
    cout << endl << endl;
}
void Profesor::grabarEnDiscoProfesor(){
    FILE *p;

    p = fopen("profesores.dat", "ab");

    if(p == nullptr){
        cout << "ERROR DE ARCHIVO.";
    }

    this->cargarProfesor();
    fwrite(this, sizeof(Profesor), 1, p);

    fclose(p);

}

void Profesor::leerEnDiscoProfesor() {
    FILE *pProfesor;

    if(!(pProfesor = fopen("profesores.dat", "rb"))) {
        cout << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    cout << "MOSTRANDO PERFILES ALUMNO:" << endl;
    while(fread(this, sizeof(Profesor), 1, pProfesor)) {
        this->mostrarProfesor();
    };

    fclose(pProfesor);
}

