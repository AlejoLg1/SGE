#include <iostream>
using namespace std;
#include <cstdlib>
#include "Profesor.h"

Profesor::Profesor()
{
    Persona();
    _legajo = 0;
    _clave = 0;
    _estado = false;
}

void Profesor::setLegajo(int legajo){
    _legajo = legajo;
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
    this->cargar();
    cout << "Legajo: ";
    cin >> _legajo;
    cout << "Clave (numérica): ";
    cin >> _clave;
}
void Profesor::mostrarProfesor(){
    this->mostrar();
    cout << "Legajo: " << getLegajo();
    cout << "Clave: " << getClave();
}
void Profesor::grabarEnDiscoProfesor(){
    FILE *p;

    p = fopen("profesores.dat", "ab");

    if(p == nullptr){
        cout << "ERROR DE ARCHIVO.";
    }

    this->cargar();
    fwrite(this, sizeof(Profesor), 1, p);

    fclose(p);

}

bool Profesor::leerEnDiscoProfesor(int pos){
    FILE *p;

    p = fopen("profesores.dat", "rb");

    if(p == nullptr){
        cout << "ERROR DE ARCHIVO.";
        return false;
    }

    fseek(p, sizeof(Profesor)*pos, SEEK_SET);

    bool leyo = fread(this, sizeof(Profesor), 1, p);

    fclose(p);
    return leyo;


}

