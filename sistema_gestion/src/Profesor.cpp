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

/*bool Profesor::leerEnDiscoProfesor(int pos){ ARREGLAR PARA QUE NO NECESITE PARÁMETRO
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
} */

