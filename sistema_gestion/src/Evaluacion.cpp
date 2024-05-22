#include <iostream>
using namespace std;
#include <cstdlib>
#include "Evaluacion.h"

Evaluacion::Evaluacion()
{
    _id = 0;
    _idProfesor = 0;
    _fecha = Fecha();
    _estado = false;
}

///SETTERS

void Evaluacion::setId(int id){
    _id = id;
}

void Evaluacion::setIdProfesor(int idProfesor){
    _idProfesor = idProfesor;
}

void Evaluacion::setFecha(Fecha fecha){
    _fecha = fecha;
}

void Evaluacion::setEstado(bool estado){
    _estado = estado;
}

///GEETERS

int Evaluacion::getId(){
    return _id;
}

int Evaluacion::getIdProfesor(){
    return _idProfesor;
}

Fecha Evaluacion::getFecha(){
    return _fecha;
}

bool Evaluacion::getEstado(){
    return _estado;
}

void Evaluacion::cargarEvaluacion(){
    cout << "ID: ";
    cin >> _id;
    cout << "ID PROFESOR: ";
    cin >> _idProfesor;
    cout << "FECHA: ";
    _fecha.CargarFecha();
    setEstado(true);
}

void Evaluacion::mostrarEvaluacion(){
    cout << "ID: " << _id;
    cout << "ID PROFESOR: " << _idProfesor;
    cout << "FECHA: " << _fecha.toString("DD/MM/YYYY");
    cout << "ESTADO: " << _estado;
}

void Evaluacion::grabarEnDisco() {
    FILE *pEvaluacion;

    if(!(pEvaluacion = fopen("evaluaciones.dat", "ab"))) {
        system("cls");
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    this->cargarEvaluacion();

    fwrite(this,sizeof(Evaluacion), 1, pEvaluacion);

    fclose(pEvaluacion);
}

void Evaluacion::leerEnDisco() {
    FILE *pEvaluacion;

    if(!(pEvaluacion = fopen("evaluaciones.dat", "rb"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    while(fread(this,sizeof(Evaluacion),1, pEvaluacion)){
        this->mostrarEvaluacion();
    };


    fclose(pEvaluacion);
}
