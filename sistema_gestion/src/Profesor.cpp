#include <iostream>
#include <cstdlib>
#include <limits>
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

void Profesor::setLegajo() {
    _legajo = settearNuevoLegajo();
}
void Profesor::setClave(int clave) {

    while(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "\t---- ERROR : CONTRASEÑA INVÁLIDA ----" << endl;
        cout <<  endl << "\t - Contraseña (numérica): ";
        cin >> clave;
    }

    _clave = clave;
}
void Profesor::setEstado(bool estado) {

    while((estado != 1 && estado != 0) || cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "\t---- ERROR : ESTADO INVÁLIDO ----" << endl;
        cout <<  endl << "\t - Estado (1 para activo, 0 para inactivo): ";
        cin >> estado;
    }

    _estado = estado;
}

///GETTERS

int Profesor::getLegajo() {
    return _legajo;
}
int Profesor::getClave() {
    return _clave;
}
bool Profesor::getEstado() {
    return _estado;
}

///MÉTODOS

void Profesor::activarProfesor(int legajo) {
    bool usuarioEncontrado = false;
    FILE *pProf;

    if(!(pProf = fopen("profesores.dat", "rb+"))) {
        system("cls");
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    while (fread(this, sizeof(Profesor), 1, pProf)) {
        if(this->getLegajo() == legajo) {
            usuarioEncontrado = true;
            if(this->getEstado() == false) {
                this->setEstado(true);
                long offset = ftell(pProf) - sizeof(Profesor);
                fseek(pProf, offset, SEEK_SET);
                fwrite(this, sizeof(Profesor), 1, pProf);
                cout << endl << "USUARIO MARCADO COMO ACTIVO CON ÉXITO " << endl << endl;
                system("pause");
                break;
            }
            else {
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

void Profesor::desactivarProfesor(int legajo) {
    bool usuarioEncontrado = false;
    FILE *pProf;

    if(!(pProf = fopen("profesores.dat", "rb+"))) {
        system("cls");
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    };
    while (fread(this, sizeof(Profesor), 1, pProf)) {
        if(this->getLegajo() == legajo) {
            usuarioEncontrado = true;
            if(this->getEstado() == true) {
                this->setEstado(false);
                long offset = ftell(pProf) - sizeof(Profesor);
                fseek(pProf, offset, SEEK_SET);
                fwrite(this, sizeof(Profesor), 1, pProf);
                cout << endl << "USUARIO MARCADO COMO INACTIVO CON ÉXITO " << endl << endl;
                system("pause");
                break;
            }
            else {
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
        if(this->getLegajo() == legajo) {
            usuarioEncontrado = true;
            if(this->getClave() != clave) {
                this->setClave(clave);
                long offset = ftell(pProf) - sizeof(Profesor);
                fseek(pProf, offset, SEEK_SET);
                fwrite(this, sizeof(Profesor), 1, pProf);
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

    fclose(pProf);
}

void Profesor::cargarProfesor() {
    int clave;
    bool estado;

    cout << "CREANDO PERFIL DIRECTOR" << endl;

    cout<< endl <<"\t - Legajo: ";
    setLegajo();
    cout << getLegajo();
    cout << endl;

    Persona::cargar();

    cout<< endl << "\t - Contraseña (numérica): ";
    cin >> clave;
    setClave(clave);

    cout << endl << "\t - Estado (1 para activo, 0 para inactivo): ";
    cin >> estado;
    setEstado(estado);

}
void Profesor::mostrarProfesor() {
    Persona::mostrar();
    cout << endl;
    cout <<"Legajo: " << _legajo<<endl;
    cout <<"Clave: " << _clave<<endl;
    cout << endl << "Estado: " << _estado<<endl;
    cout << endl << endl;
}
void Profesor::grabarEnDiscoProfesor() {
    FILE *p;

    p = fopen("profesores.dat", "ab");

    if(p == nullptr) {
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

bool Profesor::leerEnDiscoProfesorPorPosicion(int pos)
{
    FILE *p;
    bool Leyo;

    p=fopen ("profesores.dat","rb");
    if (p==NULL) {cout<<"El ARCHIVO NO SE PUDO LEER"<<endl; return false;}

    fseek (p,sizeof(Profesor)*pos,0);

    Leyo=fread(this,sizeof (Profesor),1,p);

    fclose(p);
    return Leyo;
}

