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


bool Persona::esValido(const char* str) {
    for (int i = 0; i < strlen(str); ++i) {
        if (!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

void Persona::setNombre(char* nombre) {
    while (!esValido(nombre)) {
        cout << "\n\t---- ERROR : NOMBRE INVÁLIDO ----" << endl;
        cout << "\n\t - Nombre: ";
        cin >> nombre;
    }
    strncpy(_nombre, nombre, 15);
    _nombre[15] = '\0';
}

void Persona::setApellido(char* apellido) {
    while (!esValido(apellido)) {
        cout << "\n\t---- ERROR : APELLIDO INVÁLIDO ----" << endl;
        cout << "\n\t - Apellido: ";
        cin >> apellido;
    }
    strncpy(_apellido, apellido, 15);
    _apellido[15] = '\0';
}


 ///---- GETTERS ----\\\

char* Persona::getNombre() {
    return _nombre;
}

char* Persona::getApellido() {
    return _apellido;
}

///---- MÉTODOS ----\\\

void Persona::cargar() {
    char nombre[16];
    char apellido[16];

    cout << endl << "\t - Nombre: ";
    cin >> nombre;
    setNombre(nombre);
    cout << endl << "\t - Apellido: ";
    cin >> apellido;
    setApellido(apellido);

}
void Persona::mostrar() {

    cout << endl << "\t - Nombre: " << _nombre << endl;
    cout << "\t - Apellido: " << _apellido;

}

void Persona::grabarEnDisco() {

}
void Persona::leerEnDisco() {

}
