#include <iostream>
#include <cstring>
#include <limits>
#include "Materia.h"


using namespace std;


///---- CONSTRUCTOR ----\\\

Materia::Materia()
{
    //_id=GenerarLegajo(); hay que crear la funcion
    _legajoProfesor = 0;
    strncpy(_nombreMateria, "-", 20);
    //Fecha _nacimiento;
}

///---- SETTERS ----\\\

void Materia::setId(int id)
{
    _id = id;

}

void Materia::setLegajoProfesor(int legajo)
{
    _legajoProfesor = legajo;

}


void Materia::setNombreMateria(char* nombre)
{
    strncpy(_nombreMateria, nombre, 20);

}

        ///---- GETTERS ----\\\

int Materia::getId()
{
    return _id;
}

int Materia::getLegajoProfesor()
{
    return _legajoProfesor;
}

char* Materia::getNombreMateria()
{
    return _nombreMateria;
}

///---- MÉTODOS ----\\\

void Materia::cargarMateria()
{
    cout << endl << "\t - Legajo Profesor: ";
    cin >> _legajoProfesor;
    cout << endl << "\t - Nombre De La Materia: ";
    cin >> _nombreMateria;


}
void Materia::mostrarMateria()
{
    cout << endl << "\t - ID: " << _id << endl;
    cout << endl << "\t - Legajo Profesor: " << _legajoProfesor << endl;
    cout << "\t - Nombre De La Materia: " << _nombreMateria;


}
void Materia::grabarEnDisco()
{
FILE *p;
    p=fopen ("Materia.dat","ab");
    if (p==NULL){cout<<"El ARCHIVO NO SE PUDO CREAR O ABRIR"<<endl;}

    this->cargarMateria();
    fwrite (this, sizeof (Materia),1,p);

    fclose (p);
}
int Materia::leerEnDisco(int pos)
{
     FILE *p;
    bool Leyo;

    p=fopen ("Materia.dat","rb");
    if (p==NULL){cout<<"El ARCHIVO NO SE PUDO LEER"<<endl;return false;}

    fseek (p,sizeof(Materia)*pos,0);

    Leyo=fread(this,sizeof (Materia),1,p);

    fclose(p);
    return Leyo;
}


