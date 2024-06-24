#include "Director.h"

#include <windows.h>

#include <cstring>
#include <iostream>
#include <limits>

#include "Funciones.h"

using namespace std;

Director::Director() {
  // ctor
}

///---- SETTERS ----\\\


void Director::setLegajo() { _legajo = settearNuevoLegajo(); }

void Director::setClave(int clave) {
  while (cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl << "\t---- ERROR : CONTRASEÑA INVÁLIDA ----" << endl;
    cout << endl << "\t - Contraseña (numérica): ";
    cin >> clave;
  }
  _clave = clave;
}

void Director::setEstado(bool estado) {
  while ((estado != 1 && estado != 0) || cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl << "\t---- ERROR : ESTADO INVÁLIDO ----" << endl;
    cout << endl << "\t - Estado (1 para activo, 0 para inactivo): ";
    cin >> estado;
  }
  _estado = estado;
}

///---- GETTERS ----\\\

int Director::getLegajo() { return _legajo; }
int Director::getClave() { return _clave; }
bool Director::getEstado() { return _estado; }

///---- MÉTODOS ----\\\

bool Director::cargarDirector() {
  int clave;
  bool estado;
  bool salir = false;

  cout << "CREANDO PERFIL DIRECTOR" << endl;

  cout << endl << "\t - Legajo: ";
  setLegajo();
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
}

void Director::activarDirector(int legajo) {
  bool usuarioEncontrado = false;
  FILE *pDirectivo;

  if (!(pDirectivo = fopen("directores.dat", "rb+"))) {
    system("cls");
    cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
    return;
  }

  while (fread(this, sizeof(Director), 1, pDirectivo)) {
    if (this->getLegajo() == legajo) {
      usuarioEncontrado = true;
      if (this->getEstado() == false) {
        this->setEstado(true);
        long offset = ftell(pDirectivo) - sizeof(Director);
        fseek(pDirectivo, offset, SEEK_SET);
        fwrite(this, sizeof(Director), 1, pDirectivo);
        cout << endl
             << "USUARIO MARCADO COMO ACTIVO CON ÉXITO " << endl
             << endl;
        system("pause");
        break;
      }
      else {
        cout << endl
             << "---- ATENCIÓN: EL USUARIO YA HABÍA SIDO MARCADO COMO ACTIVO "
                "PREVIAMENTE ----"
             << endl
             << endl;
        system("pause");
      }
    }
  }

  if (!usuarioEncontrado) {
    cout << endl << "---- ERROR: USUARIO NO ENCONTRADO ----" << endl << endl;
    system("pause");
  }

  fclose(pDirectivo);
}

void Director::desactivarDirector(int legajo) {
  bool usuarioEncontrado = false;
  FILE *pDirectivo;

  if (!(pDirectivo = fopen("directores.dat", "rb+"))) {
    system("cls");
    cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
    return;
  };
  while (fread(this, sizeof(Director), 1, pDirectivo)) {
    if (this->getLegajo() == legajo) {
      usuarioEncontrado = true;
      if (this->getEstado() == true) {
        this->setEstado(false);
        long offset = ftell(pDirectivo) - sizeof(Director);
        fseek(pDirectivo, offset, SEEK_SET);
        fwrite(this, sizeof(Director), 1, pDirectivo);
        cout << endl
             << "USUARIO MARCADO COMO INACTIVO CON ÉXITO " << endl
             << endl;
        system("pause");
        break;
      }
      else {
        cout << endl
             << "---- ATENCIÓN: EL USUARIO YA HABÍA SIDO MARCADO COMO INACTIVO "
                "PREVIAMENTE ----"
             << endl;
        system("pause");
      }
    }
  }

  if (!usuarioEncontrado) {
    cout << endl << "---- ERROR: USUARIO NO ENCONTRADO ----" << endl << endl;
    system("pause");
  }

  fclose(pDirectivo);
}

void Director::cambiarClave(int legajo, int clave) {
  bool usuarioEncontrado = false;
  FILE *pDirectivo;

  if (!(pDirectivo = fopen("directores.dat", "rb+"))) {
    system("cls");
    cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
    return;
  }

  while (fread(this, sizeof(Director), 1, pDirectivo)) {
    if (this->getLegajo() == legajo) {
      usuarioEncontrado = true;
      if (this->getClave() != clave) {
        this->setClave(clave);
        long offset = ftell(pDirectivo) - sizeof(Director);
        fseek(pDirectivo, offset, SEEK_SET);
        fwrite(this, sizeof(Director), 1, pDirectivo);
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

  if (!usuarioEncontrado) {
    cout << endl << "---- ERROR: USUARIO NO ENCONTRADO ----" << endl << endl;
    system("pause");
  }

  fclose(pDirectivo);
}

void Director::mostrarDirector() {
  Persona::mostrar();
  cout << endl;
  cout << "Legajo: " << _legajo << endl;
  cout << "Clave: " << _clave << endl;
  cout << endl << "estado: " << _estado << endl;
  cout << endl << endl;
}

void Director::grabarEnDiscoDirector() {
  FILE *p;
  p = fopen("directores.dat", "ab");
  if (p == NULL) {
    cout << "El ARCHIVO NO SE PUDO CREAR O ABRIR" << endl;
  }

  if(this->cargarDirector()) {
    fclose(p);
    return;
  }

  fwrite(this, sizeof(Director), 1, p);

  fclose(p);
}

void Director::leerEnDiscoDirector() {
  FILE *pDir;

  if (!(pDir = fopen("directores.dat", "rb"))) {
    cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
    return;
  }

  cout << "MOSTRANDO PERFILES DIRECTORES:" << endl;
  while (fread(this, sizeof(Director), 1, pDir)) {
    this->mostrarDirector();
  };

  fclose(pDir);
}
