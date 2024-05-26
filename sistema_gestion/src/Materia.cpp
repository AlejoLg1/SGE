#include <iostream>
#include <cstring>
#include <limits>
#include "Materia.h"
#include "Profesor.h"


using namespace std;


///---- CONSTRUCTOR ----\\\

Materia::Materia() {
    _id = 0;
    _legajoProfesor = 0;
    _nivel = 0;
    strncpy(_nombreMateria, "-", 20);
}

///---- SETTERS ----\\\

void Materia::setId() {
    _id = generarId();
}

void Materia::setLegajoProfesor(int legajo) {
    _legajoProfesor = legajo;
}

void Materia::setNivel(int nivel) {

    while(nivel < 0 || nivel > 4){
        cout << endl << "---- ERROR : NIVEL INVÁLIDO ----" << endl;
        cin >> nivel;
    }
    _nivel = nivel;
}

void Materia::setNombreMateria(char* nombre) {
    strncpy(_nombreMateria, nombre, 20);
}

        ///---- GETTERS ----\\\

int Materia::getId() {
    return _id;
}

int Materia::getLegajoProfesor() {
    return _legajoProfesor;
}

int Materia::getNivel() {
    return _nivel;
}

char* Materia::getNombreMateria() {
    return _nombreMateria;
}

///---- MÉTODOS ----\\\

void Materia::cargarMateria() {
    int legajoProfesor;
    int nivel;

    setId();

    cout << endl << "\t - ID Materia: ";
    cout << getId() << endl;

    setLegajoProfesor(-1);

    cout << endl << "\t - Nombre de la Materia: ";
    cin >> _nombreMateria;

    cout << endl << "\t - Nivel (1 a 4): ";
    cin >> nivel;
    setNivel(nivel);

}
void Materia::mostrarMateria() {
    cout << endl << "\t - ID: " << this->getId();
    cout << endl <<"\t - Nombre de la Materia: " << this->getNombreMateria();
    cout << endl <<"\t - Nivel: " << this->getNivel();
    cout << endl << "\t - Legajo Profesor: ";
    if(this->getLegajoProfesor() == -1){
        cout << "No asignado" << endl;
    }
    else{
        cout << this->getLegajoProfesor() << endl;
    }


}
void Materia::grabarEnDiscoMateria() {
    FILE *pMat;

    if(!(pMat = fopen("materias.dat", "ab"))) {
        system("cls");
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    this->cargarMateria();
    fwrite(this, sizeof(Materia), 1, pMat);

    fclose(pMat);

}

void Materia::leerEnDiscoMateria() {
    FILE *pMat;

    if(!(pMat = fopen("materias.dat", "rb"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    cout << "MOSTRANDO MATERIAS:" << endl;
    while(fread(this, sizeof(Materia), 1, pMat)){
        this->mostrarMateria();
    };

    fclose(pMat);
}

int Materia::generarId() {
    FILE *pMat;
    int idsTotales = 1;

    if(!(pMat = fopen("materias.dat", "ab"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return -1;
    }

    fseek(pMat, 0, SEEK_END);
    idsTotales += ftell(pMat) / sizeof(Materia);
    fseek(pMat, 0, SEEK_SET);
    fclose(pMat);


    return idsTotales;
}

bool Materia::leerEnDiscoMateriaPorPosicion(int pos)
{
    FILE *p;
    bool Leyo;

    p=fopen ("materias.dat","rb");
    if (p==NULL){cout<<"El ARCHIVO NO SE PUDO LEER"<<endl; return false;}

    fseek (p,sizeof(Materia)*pos,0);

    Leyo=fread(this,sizeof (Materia),1,p);

    fclose(p);
    return Leyo;

}


