#include <iostream>
#include <cstring>
#include <limits>
#include "Funciones.h"
#include "Alumno.h"
#include "Persona.h"

using namespace std;

///---- SETTERS ----\\\

void Alumno::setlegajo() {
    _legajo = settearNuevoLegajo();
}

void Alumno::setClave(int clave) {

    while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "\t---- ERROR : CLAVE INVÁLIDA ----" << endl;
        cout <<  endl << "\t - Clave (numérica): ";
        cin >> clave;
    }
    _clave = clave;
}

void Alumno::setEstado(bool estado) {
    while((estado != 1 && estado != 0) || cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "\t---- ERROR : ESTADO INVÁLIDO ----" << endl;
        cout <<  endl << "\t - Estado (1 para activo, 0 para inactivo): ";
        cin >> estado;
    }
    _estado = estado;
}

void Alumno::setMaterias(int *materias) {
    memcpy(_materias, materias, sizeof(_materias));
}

///---- GETTERS ----\\\

int Alumno::getLegajo() {
    return _legajo;
}

int Alumno::getClave() {
    return _clave;
}

bool Alumno::getEstado() {
    return _estado;
}

int* Alumno::getMaterias() {
    return _materias;
}

///---- MÉTODOS ----\\\

void Alumno::cargar() {
    int legajo;
    int clave;
    bool estado;
    int materias[7] = {-1};
    int materia, cont = 0;

    cout << "CREANDO PERFIL ALUMNO" << endl;

    cout << endl << "\t - Legajo: ";
    setlegajo();
    cout << getLegajo();

    Persona::cargar();

    cout << "\t - Clave (numérica): ";
    cin >> clave;
    setClave(clave);

    cout << "\t - Estado (1 para activo, 0 para inactivo): ";
    cin >> estado;
    setEstado(estado);

    cout << endl << "\t - Materias (-1 para finalizar carga): " << endl;

    while(materia != -1 && cont != 7) {
        cout << "\t\t - Materia (ingrese N° de materia): ";
        cin >> materia;

        while(materia < -1 || cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\t\t---- ERROR : N° DE MATERIA INVÁLIDO ----" << endl;
            cout << "\t\t - Materia (ingrese N° de materia): ";
            cin >> materia;
        }
        materias[cont] = materia;
        cont ++;
    }
    setMaterias(materias);

}

void Alumno::mostrar() {

    cout << endl << "\t - Legajo: " << getLegajo();
    Persona::mostrar();
    cout << endl << "\t - Clave: " << getClave();
    cout << endl << "\t - Estado: " << (getEstado() ? "Activo" : "Inactivo");
    cout << endl << "\t - Materias: ";
    for (int i = 0; i < 7; ++i) {
        if(getMaterias()[i] != -1) {
            cout << endl << "\t\t - Materia: ";
            cout << getMaterias()[i];
        }
    }
    cout << endl << endl;
}

void Alumno::grabarEnDiscoAlumno() {
    FILE *pAlumno;

    if(!(pAlumno = fopen("alumnos.dat", "ab"))) {
        cout << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    this->cargar();

    fwrite(this, sizeof(Alumno), 1, pAlumno);

    fclose(pAlumno);
}

void Alumno::leerEnDiscoAlumno() {
    FILE *pAlumno;

    if(!(pAlumno = fopen("alumnos.dat", "rb"))) {
        cout << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    cout << "MOSTRANDO PERFILES ALUMNO:" << endl;
    while(fread(this, sizeof(Alumno), 1, pAlumno)) {
        this->mostrar();
    };

    fclose(pAlumno);
}
