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

void Profesor::activarProfesor(int legajo){
    bool usuarioEncontrado = false;
    FILE *pProf;

    if(!(pProf = fopen("profesores.dat", "rb+"))) {
        system("cls");
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    while (fread(this, sizeof(Profesor), 1, pProf)) {
        if(this->getLegajo() == legajo){
            usuarioEncontrado = true;
            if(this->getEstado() == false){
                this->setEstado(true);
                long offset = ftell(pProf) - sizeof(Profesor);
                fseek(pProf, offset, SEEK_SET);
                fwrite(this, sizeof(Director), 1, pProf);
                cout << endl << "USUARIO MARCADO COMO ACTIVO CON ÉXITO " << endl << endl;
                system("pause");
                break;
            }
            else{
                cout << endl << "---- ATENCIÓN: EL USUARIO YA HABÍA SIDO MARCADO COMO ACTIVO PREVIAMENTE ----" << endl << endl;
                system("pause");
            }
        }
    }

    if(!usuarioEncontrado) {
        cout << endl << "---- ERROR: USUARIO NO ENCONTRADO ----" << endl << endl;
        system("pause");
    }

    fclose(pProf);
}

void Profesor::desactivarProfesor(int legajo){
    bool usuarioEncontrado = false;
    FILE *pProf;

    if(!(pProf = fopen("profesores.dat", "rb+"))) {
        system("cls");
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    };
    while (fread(this, sizeof(Profesor), 1, pProf)) {
        if(this->getLegajo() == legajo){
            usuarioEncontrado = true;
            if(this->getEstado() == true){
                this->setEstado(false);
                long offset = ftell(pProf) - sizeof(Profesor);
                fseek(pProf, offset, SEEK_SET);
                fwrite(this, sizeof(Profesor), 1, pProf);
                cout << endl << "USUARIO MARCADO COMO INACTIVO CON ÉXITO " << endl;
                system("pause");
                break;
            }
            else{
                cout << endl << "---- ATENCIÓN: EL USUARIO YA HABÍA SIDO MARCADO COMO INACTIVO PREVIAMENTE ----" << endl;
                system("pause");
            }
        }
    }

    if(!usuarioEncontrado) {
        cout << endl << "---- ERROR: USUARIO NO ENCONTRADO ----" << endl << endl;
        system("pause");
    }

    fclose(pProf);

}

void Profesor::cambiarClave(int legajo, int clave) {

    bool usuarioEncontrado = false;
    FILE *pProf;

    if(!(pProf = fopen("profesores.dat", "rb+"))) {
        system("cls");
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    while (fread(this, sizeof(Profesor), 1, pProf)) {
        if(this->getLegajo() == legajo){
            usuarioEncontrado = true;
            if(this->getClave() != clave){
                this->setClave(clave);
                long offset = ftell(pProf) - sizeof(Profesor);
                fseek(pProf, offset, SEEK_SET);
                fwrite(this, sizeof(Profesor), 1, pProf);
                cout << endl << "CONTRASEÑA CAMBIADA CON ÉXITO " << endl << endl;
                system("pause");
                break;
            }
            else{
                cout << endl << "---- ERROR: CONTRASEÑAS IGUALES ----" << endl << endl;
                system("pause");
            }
        }
    }

    if(!usuarioEncontrado) {
        cout << endl << "---- ERROR: USUARIO NO ENCONTRADO ----" << endl << endl;
        system("pause");
    }

    fclose(pProf);
}

void Profesor::cargarProfesor(){

    cout << "CREANDO PERFIL DIRECTOR" << endl;

    cout<< endl <<"\t - Legajo: ";
    setLegajo();
    cout << getLegajo();
    cout << endl;

    Persona::cargar();

    cout<< endl << "\t - Clave: ";
    cin >> _clave;

    cout << endl << "\t - Estado (1 para activo, 0 para inactivo): ";
    cin >> _estado;

}
void Profesor::mostrarProfesor(){
    Persona::mostrar();
    cout << endl;
    cout <<"Legajo: " << _legajo<<endl;
    cout <<"Clave: " << _clave<<endl;
    cout << endl << "Estado: " << _estado<<endl;
    cout << endl << endl;
}
void Profesor::grabarEnDiscoProfesor(){
    FILE *p;

    p = fopen("profesores.dat", "ab");

    if(p == nullptr){
        cout << "ERROR DE ARCHIVO.";
    }

    this->cargarProfesor();
    fwrite(this, sizeof(Profesor), 1, p);

    fclose(p);

}

void Profesor::leerEnDiscoProfesor() {
    FILE *pProfesor;

    if(!(pProfesor = fopen("profesores.dat", "rb"))) {
        cout << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    cout << "MOSTRANDO PERFILES PROFESOR:" << endl;
    while(fread(this, sizeof(Profesor), 1, pProfesor)) {
        this->mostrarProfesor();
    };

    fclose(pProfesor);
}

