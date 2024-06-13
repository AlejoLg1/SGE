#include <iostream>
#include <cstring>
#include <limits>
#include "Funciones.h"
#include "Director.h"
#include "Administrador.h"

using namespace std;


///---- SETTERS ----\\\

void Administrador::setId() {
    _id = settearNuevoLegajo();
}

void Administrador::setClave(int clave) {

    while(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "\t---- ERROR : CONTRASEÑA INVÁLIDA ----" << endl;
        cout <<  endl << "\t - Contraseña (numérica): ";
        cin >> clave;
    }
    _clave = clave;
}

bool Administrador::esValido(const char* str) {
    for (int i = 0; i < strlen(str); ++i) {
        if (!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

void Administrador::setNombre(char* nombre) {
    while (!esValido(nombre)) {
        cout << "\n\t---- ERROR : NOMBRE INVÁLIDO ----" << endl;
        cout << "\n\t - Nombre: ";
        cin >> nombre;
    }
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

    cout << endl << "\t - Legajo: ";
    cout << getId() << endl;
    cout << endl << "\t - Usuario: ";
    cin.sync();
    cin.getline(nombre, 16);
    setNombre(nombre);

    cout << endl << "\t - Contraseña (numérica): ";
    cin >> clave;
    setClave(clave);
}

void Administrador::mostrar() {

    cout << endl << "\t - ID: " << getId();
    cout << endl << "\t - Usuario: " << getNombre();
    cout << endl << "\t - Contraseña: " << getClave();
    cout << endl << endl;
}

void Administrador::cambiarClave(int legajo, int clave) {

    bool usuarioEncontrado = false;
    FILE *pAdministrador;

    if(!(pAdministrador = fopen("administradores.dat", "rb+"))) {
        system("cls");
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    while (fread(this, sizeof(Administrador), 1, pAdministrador)) {
        if(this->getId() == legajo) {
            usuarioEncontrado = true;
            if(this->getClave() != clave) {
                this->setClave(clave);
                long offset = ftell(pAdministrador) - sizeof(Administrador);
                fseek(pAdministrador, offset, SEEK_SET);
                fwrite(this, sizeof(Administrador), 1, pAdministrador);
                cout << endl << "CONTRASEÑA CAMBIADA CON ÉXITO " << endl << endl;
                system("pause");
                break;
            }
            else {
                cout << endl << "---- ERROR: CONTRASEÑAS IGUALES ----" << endl << endl;
                system("pause");
            }
        }
    }

    if(!usuarioEncontrado) {
        cout << endl << "---- ERROR: USUARIO NO ENCONTRADO ----" << endl << endl;
        system("pause");
    }

    fclose(pAdministrador);
}

void Administrador::grabarEnDiscoAdministrador() {
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


void Administrador::leerEnDiscoAdministrador() {
    FILE *pAdm;

    if(!(pAdm = fopen("administradores.dat", "rb"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    cout << "MOSTRANDO PERFILES ADMINISTRADOR:" << endl;
    while(fread(this, sizeof(Administrador), 1, pAdm)) {
        this->mostrar();
    };


    fclose(pAdm);
}





