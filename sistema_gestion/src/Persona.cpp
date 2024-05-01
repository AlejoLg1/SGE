#include <iostream>
#include <cstring>
#include <limits>
#include "Persona.h"


///---- CONSTRUCTOR ----\\\

Persona::Persona()
{
    strncpy(_nombre, "-", 16);
    strncpy(_apellido, "-", 16);
    //Fecha _nacimiento;
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

/*void Persona::setNacimiento (Fecha nacimiento)
{
    _nacimiento = nacimiento;
}
*/


 ///---- GETTERS ----\\\

char* Persona::getNombre()
{
    return _nombre;
}

char* Persona::getApellido()
{
    return _apellido;
}
/*
bool Persona::getNacimiento()
{
    return _nacimiento;
}
*/

///---- MÉTODOS ----\\\

void Persona::cargar()
{

}
void Persona::mostrar()
{

}
void Persona::grabarEnDisco()
{

}
void Persona::leerEnDisco()
{

}
