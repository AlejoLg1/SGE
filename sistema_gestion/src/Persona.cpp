#include <iostream>
#include <cstring>
#include <limits>
#include "Persona.h"

using namespace std;


///---- CONSTRUCTOR ----\\\

Persona::Persona()
{
    strncpy(_nombre, "-", 16);
    strncpy(_apellido, "-", 16);
}

///---- SETTERS ----\\\


void Persona::setNombre(char* nombre)
{
    strncpy(_nombre, nombre, 16);

}

void Persona::setApellido(char* apellido)
{
    strncpy(_apellido, apellido, 16);

}


 ///---- GETTERS ----\\\

char* Persona::getNombre()
{
    return _nombre;
}

char* Persona::getApellido()
{
    return _apellido;
}

///---- MÉTODOS ----\\\

void Persona::cargar()
{
    cout << endl << "\t - Nombre: ";
    cin >> _nombre;
    cout << endl << "\t - Apellido: ";
    cin >> _apellido;

}
void Persona::mostrar()
{

    cout << endl << "\t - Nombre: " << _nombre << endl;
    cout << "\t - Apellido: " << _apellido;

}
void Persona::grabarEnDisco()
{

}
void Persona::leerEnDisco()
{

}
