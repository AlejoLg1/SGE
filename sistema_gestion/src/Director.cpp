#include <iostream>
#include <cstring>
#include <limits>
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
    //Persona::cargar();
    cout<< "Legajo: ";
    // _legajo=ContarLegajos(); CONSULTAR A LOS CHICOS YA QUE HAY LEGAJOS EN VARIOS ARCHIVOS
    cout<< "Clave: ";
    cin >> _clave;
    cout<< "DIRECTOR CARGADOR CORRECTAMENTE"<<endl<<endl;

}

void Director::mostrarDirector()
{
    Persona::mostrar();
    cout <<"Legajo: " << _legajo<<endl;
    cout <<"Clave: " << _clave<<endl;
    cout << endl << endl;


}
void Director::grabarEnDiscoDirector()
{
    FILE *p;
    p=fopen ("Director.dat","ab");
    if (p==NULL){cout<<"El ARCHIVO NO SE PUDO CREAR O ABRIR"<<endl;}

    this->cargar();
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
