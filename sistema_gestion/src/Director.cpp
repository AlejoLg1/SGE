#include <iostream>
#include <cstring>
#include <limits>
#include <windows.h>
#include "Funciones.h"
#include "Director.h"


using namespace std;

Director::Director()
{
    //ctor
}


///---- SETTERS ----\\\


void Director::setLegajo(int legajo)
{
    _legajo = legajo;

}

void Director::setClave(int clave)
{
    _clave = clave;

}

void Director::setEstado(bool estado)
{
    _estado = estado;

}

///---- GETTERS ----\\\

int Director::getLegajo()
{
   return _legajo;

}
int Director::getClave ()
{
   return _clave;

}
bool Director::getEstado ()
{
    return _estado;

}


///---- MÉTODOS ----\\\

void Director::cargarDirector()
{
    cout << "CREANDO PERFIL DIRECTOR" << endl;

    cout<< endl <<"\t - Legajo: ";
    _legajo = settearNuevoLegajo();
    cout << getLegajo() << endl;

    Persona::cargar();

    cout<< endl << "\t - Clave: ";
    cin >> _clave;

    cout << endl << "\t - Estado (1 para activo, 0 para inactivo): ";
    cin >> _estado;
}

void Director::activarDirector(int legajo)
{
    bool usuarioEncontrado = false;
    FILE *pDirectivo;

    if(!(pDirectivo = fopen("Director.dat", "rb+"))) {
        system("cls");
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    while (fread(this, sizeof(Director), 1, pDirectivo)) {
        if(this->getLegajo() == legajo){
            usuarioEncontrado = true;
            if(this->getEstado() == false){
                this->setEstado(true);
                long offset = ftell(pDirectivo) - sizeof(Director);
                fseek(pDirectivo, offset, SEEK_SET);
                fwrite(this, sizeof(Director), 1, pDirectivo);
                cout << endl << "DIRECTOR MARCADO COMO ACTIVO CON ÉXITO " << endl << endl;
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

    fclose(pDirectivo);
}

void Director::desactivarDirector(int legajo)
{
    bool usuarioEncontrado = false;
    FILE *pDirectivo;

    if(!(pDirectivo = fopen("Director.dat", "rb+"))) {
        system("cls");
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    };
    while (fread(this, sizeof(Director), 1, pDirectivo)) {
        if(this->getLegajo() == legajo){
            usuarioEncontrado = true;
            if(this->getEstado() == true){
                this->setEstado(false);
                long offset = ftell(pDirectivo) - sizeof(Director);
                fseek(pDirectivo, offset, SEEK_SET);
                fwrite(this, sizeof(Director), 1, pDirectivo);
                cout << endl << "DIRECTOR MARCADO COMO INACTIVO CON ÉXITO " << endl;
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

    fclose(pDirectivo);
}


void Director::mostrarDirector()
{
    Persona::mostrar();
    cout << endl;
    cout <<"Legajo: " << _legajo<<endl;
    cout <<"Clave: " << _clave<<endl;
    cout << endl << "estado: " << _estado<<endl;
    cout << endl << endl;


}
void Director::grabarEnDiscoDirector()
{
    FILE *p;
    p=fopen ("Director.dat","ab");
    if (p==NULL){cout<<"El ARCHIVO NO SE PUDO CREAR O ABRIR"<<endl;}

    this->cargarDirector();
    fwrite (this, sizeof (Director),1,p);

    fclose (p);

}
int Director::leerEnDiscoDirector(int pos)
{
    FILE *p;
    bool Leyo;

    p=fopen ("Director.dat","rb");
    if (p==NULL){cout<<"El ARCHIVO NO SE PUDO LEER"<<endl;return false;}

    fseek (p,sizeof(Director)*pos,0);

    Leyo=fread(this,sizeof (Director),1,p);

    fclose(p);
    return Leyo;

}
