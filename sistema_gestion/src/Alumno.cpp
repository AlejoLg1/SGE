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

    while(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "\t---- ERROR : CONTRASEÑA INVÁLIDA ----" << endl;
        cout <<  endl << "\t - Contraseña (numérica): ";
        cin >> clave;
    }
    _clave = clave;
}

void Alumno::setEstado(bool estado) {
    while((estado != 1 && estado != 0) || cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "\t---- ERROR : ESTADO INVÁLIDO ----" << endl;
        cout <<  endl << "\t - Estado (1 para activo, 0 para inactivo): ";
        cin >> estado;
    }
    _estado = estado;
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


///---- MÉTODOS ----\\\

bool Alumno::cargar() {
    int legajo;
    int clave;
    bool estado;
    int materias[7] = {-1};
    int materia, cont = 0;
    bool salir = false;


    cout << "CREANDO PERFIL ALUMNO" << endl;

    cout << endl << "\t - Legajo: ";
    setlegajo();
    cout << getLegajo();
    cout << endl;

    salir = Persona::cargar();
    if(salir) {
        return true;
    }

    cout << endl << "\t - Contraseña (numérica): ";
    cin >> clave;
    setClave(clave);

    cout << endl << "\t - Estado (1 para activo, 0 para inactivo): ";
    cin >> estado;
    setEstado(estado);

    return false;
}

void Alumno::activarAlumno(int legajo) {
    bool usuarioEncontrado = false;
    FILE *pAlumno;

    if(legajo != 0){
        if(!(pAlumno = fopen("alumnos.dat", "rb+"))) {
            system("cls");
            cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
            return;
        }

        while (fread(this, sizeof(Alumno), 1, pAlumno)) {
            if(this->getLegajo() == legajo) {
                usuarioEncontrado = true;
                if(this->getEstado() == false) {
                    this->setEstado(true);
                    long offset = ftell(pAlumno) - sizeof(Alumno);
                    fseek(pAlumno, offset, SEEK_SET);
                    fwrite(this, sizeof(Alumno), 1, pAlumno);
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

        fclose(pAlumno);
    }
}

void Alumno::desactivarAlumno(int legajo) {
    bool usuarioEncontrado = false;
    FILE *pAlumno;

    if(legajo != 0){
        if(!(pAlumno = fopen("alumnos.dat", "rb+"))) {
            system("cls");
            cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
            return;
        };
        while (fread(this, sizeof(Alumno), 1, pAlumno)) {
            if(this->getLegajo() == legajo) {
                usuarioEncontrado = true;
                if(this->getEstado() == true) {
                    this->setEstado(false);
                    long offset = ftell(pAlumno) - sizeof(Alumno);
                    fseek(pAlumno, offset, SEEK_SET);
                    fwrite(this, sizeof(Alumno), 1, pAlumno);
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

        fclose(pAlumno);
    }
}

void Alumno::cambiarClave(int legajo, int clave) {

    bool usuarioEncontrado = false;
    FILE *pAlumno;

    if(!(pAlumno = fopen("alumnos.dat", "rb+"))) {
        system("cls");
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    while (fread(this, sizeof(Alumno), 1, pAlumno)) {
        if(this->getLegajo() == legajo) {
            usuarioEncontrado = true;
            if(this->getClave() != clave) {
                this->setClave(clave);
                long offset = ftell(pAlumno) - sizeof(Alumno);
                fseek(pAlumno, offset, SEEK_SET);
                fwrite(this, sizeof(Alumno), 1, pAlumno);
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

    system("cls");
    fclose(pAlumno);
}

void Alumno::mostrar() {
    bool inscripto = false;

    cout << endl << "\t - Legajo: " << getLegajo();
    Persona::mostrar();
    cout << endl << "\t - Clave: " << getClave();
    cout << endl << "\t - Estado: " << (getEstado() ? "Activo" : "Inactivo");
    cout << endl << endl;
}

void Alumno::grabarEnDiscoAlumno() {
    FILE *pAlumno;

    if(!(pAlumno = fopen("alumnos.dat", "ab"))) {
        cout << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    if(this->cargar()) {
        fclose(pAlumno);
        return;
    }

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

bool Alumno::leerEnDiscoAlumnoPorPosicion(int pos)
{
    FILE *p;
    bool Leyo;

    p=fopen ("alumnos.dat","rb");
    if (p==NULL) {cout<<"El ARCHIVO NO SE PUDO LEER"<<endl; return false;}

    fseek (p,sizeof(Alumno)*pos,0);

    Leyo=fread(this,sizeof (Alumno),1,p);

    fclose(p);
    return Leyo;
}
