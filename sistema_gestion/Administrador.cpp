#include <iostream>
#include <cstring>
#include "Administrador.h"

using namespace std;


///---- SETTERS ----\\\

void Administrador::setId() {
    FILE *pAdm;
    int cantidadRegistros;

    if(!(pAdm = fopen("administradores.dat", "rb"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    fseek(pAdm, 0, SEEK_END);
    cantidadRegistros = ftell(pAdm) / sizeof(Administrador);
    fseek(pAdm, 0, SEEK_SET);

    _id = cantidadRegistros;

    fclose(pAdm);
}

void Administrador::setClave(int clave) {
    _clave = clave;
}

void Administrador::setNombre(char* nombre) {
    strncpy(_nombre, nombre, 15);
    _nombre[15] = '\0';
}

///---- GETTERS ----\\\

int Administrador::getId() {
    return _id;
}

int Administrador::getClave() {
    return _clave;
}

char* Administrador::getNombre() {
    return _nombre;
}


///---- MÉTODOS ----\\\

void Administrador::cargar() {
    int id;
    int clave;
    char nombre[16];

    cout << "CREANDO PERFIL ADMINISTRADOR" << endl;

    setId();

    cout << endl << "\t - Usuario: ";
    cin.sync();
    cin.getline(nombre, 16);
    setNombre(nombre);

    cout << endl << "\t - Contraseña: ";
    cin >> clave;
    setClave(clave);
}

void Administrador::mostrar() {

    cout << endl << "\t - ID: " << getId();
    cout << endl << "\t - Usuario: " << getNombre();
    cout << endl << "\t - Contraseña: " << getClave();
    cout << endl << endl;
}

void Administrador::grabarEnDisco() {
    FILE *pAdm;

    if(!(pAdm = fopen("administradores.dat", "ab"))) {
        system("cls");
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    this->cargar();

    fwrite(this, sizeof(Administrador), 1, pAdm);

    fclose(pAdm);
}


void Administrador::leerEnDisco() {
    FILE *pAdm;

    if(!(pAdm = fopen("administradores.dat", "rb"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    cout << "MOSTRANDO PERFILES ADMINISTRADOR:" << endl;
    while(fread(this, sizeof(Administrador), 1, pAdm)){
        this->mostrar();
    };


    fclose(pAdm);
}




