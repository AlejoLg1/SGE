#include <iostream>
using namespace std;
#include <cstdlib>
#include <string>
#include <ctime>
#include <cstring>
#include "Fecha.h"
#include "rlutil.h"

using namespace rlutil;

void Fecha::establecerFechaPorDefecto(){
    _dia = 1;
    _mes = 1;
    _anio = 1900;
}

bool Fecha::esBisiesto(){
    if ((_anio % 4 == 0 && _anio % 100 != 0) || _anio % 400 == 0){
          return true;
    }
    return false;
}

void Fecha::agregarDias(){
    int vDias[12]={ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if(esBisiesto()){
        vDias[1]++;
    }
    _dia++;
    if(_dia > vDias[_mes-1]){
        _dia = 1;
        _mes++;
        if(_mes > 12){
            _mes = 1;
            _anio++;
        }
    }
}

void Fecha::restarDias(){
    int dias[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if(esBisiesto()){
        dias[1]++;
    }

    _dia--;
    if( _dia < 1 ){
        _mes--;
        _dia = dias[_mes-1];
        if( _mes < 1 ){
            _mes = 12;
            _dia = dias[_mes-1];
            _anio--;
            if( _anio < 1900 ){
                establecerFechaPorDefecto();
            }
        }
    }
}

void Fecha::AgregarDias(int cantidadDias){

    if (cantidadDias > 0){
        for( int i = 0; i < cantidadDias; i++ ){
            agregarDias();
        }
    }

    if(cantidadDias < 0){
        int n = cantidadDias * -1;
        for( int i = 0; i < n ; i++ ){
            restarDias();
        }
   }

   if(cantidadDias == 0){
    return;
   }
}

Fecha::Fecha(){
    establecerFechaPorDefecto();
}

std::string Fecha::FechaActual(){

    time_t tSac = time(NULL);
    struct tm* pt1 = localtime(&tSac);
    char fecha[11];


    snprintf(fecha, sizeof(fecha), "%02d/%02d/%04d", pt1->tm_mday, pt1->tm_mon + 1, pt1->tm_year + 1900);
    return std::string(fecha);

}

Fecha::Fecha(int dia, int mes, int anio){
    _dia = dia;
    _mes = mes;
    _anio = anio;

    if (_dia <= 0 || _mes <= 0 || _anio <= 0 || _mes > 12){
        establecerFechaPorDefecto();
    }
    else{
        int dias[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (esBisiesto()){
            dias[1]++;
        }

        if (_dia > dias[_mes-1]){
            establecerFechaPorDefecto();
        }
    }
}

void Fecha::CargarFecha(){
    int dias[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    cout << "DIA: ";
    cin >> _dia;

    while(_dia < 1 || _dia > dias[_mes-1]){
        system("cls");
        cin.clear();
        cout << "EL DIA INGRESADO ES INVALIDO. VUELVA A INGRESAR EL DIA: >";
        cin >> _dia;
    }

    cout << "MES: ";
    cin >> _mes;

    while(_mes < 1 || _mes > 12){
        system("cls");
        cin.clear();
        cout << "EL MES INGRESADO ES INVALIDO. VUELVA A INGRESAR EL MES: >";
        cin >> _mes;
    }

    cout << "ANIO: ";
    cin >> _anio;


    while(_anio < 1900 || !esBisiesto()){
        int dias[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        system("cls");
        cin.clear();
        cout << "LA FECHA INGRESADA ES INCORRECTA (* NO ES ANIO BISIESTO *) - VUELVA A INGRESAR LA FECHA: >";
        cout << "DIA: ";
        cin >> _dia;

        while(_dia < 1 || _dia > dias[_mes-1]){
            system("cls");
            cin.clear();
            cout << "EL DIA INGRESADO ES INVALIDO. VUELVA A INGRESAR EL DIA: >";
            cin >> _dia;
        }

        cout << "MES: ";
        cin >> _mes;

        while(_mes < 1 || _mes > 12){
            system("cls");
            cin.clear();
            cout << "EL MES INGRESADO ES INVALIDO. VUELVA A INGRESAR EL MES: >";
            cin >> _mes;
        }

        cout << "ANIO: ";
        cin >> _anio;
    }
}

void Fecha::CargarFechaEvaluacion(int idEvaluacion, int legajoProfesor, int idMateria){
    int dias[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    cout << "\t\t - Día: ";
    cin >> _dia;
    cout << endl;

    while(_dia < 1 || _dia > dias[_mes-1]){
        cin.clear();
        cout << "\t\t ---- ERROR : DÍA INVÁLIDO ----" << endl << endl;
        Sleep(1000);
        system("cls");
        precargarCargaEvaluacion(idEvaluacion, legajoProfesor, idMateria);
        cout << "\t\t - Día: ";
        cin >> _dia;
        cout << endl;
    }

    cout << "\t\t - Mes: ";
    cin >> _mes;
    cout << endl;

    while(_mes < 1 || _mes > 12){
        cin.clear();
        cout << "\t\t ---- ERROR : MES INVÁLIDO ----" << endl << endl;
        Sleep(1000);
        system("cls");
        precargarCargaEvaluacion(idEvaluacion, legajoProfesor, idMateria);
        cout << "\t\t - Día: " << _dia << endl;
        cout << endl;
        cout << "\t\t - Mes: ";
        cin >> _mes;
        cout << endl;
    }

    cout << "\t\t - Año: ";
    cin >> _anio;
    cout << endl;

    while(_anio < 1900 || !esBisiesto()){
        int dias[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        cin.clear();
        cout << "\t\t ---- ERROR : FECHA INVÁLIDA ----" << endl << endl;
        Sleep(1000);
        system("cls");
        precargarCargaEvaluacion(idEvaluacion, legajoProfesor, idMateria);

        cout << "\t\t - Día: ";
        cin >> _dia;
        cout << endl;

        while(_dia < 1 || _dia > dias[_mes-1]){
            cin.clear();
            cout << "\t\t ---- ERROR : DÍA INVÁLIDO ----" << endl << endl;
            Sleep(1000);
            system("cls");
            precargarCargaEvaluacion(idEvaluacion, legajoProfesor, idMateria);
            cout << "\t\t - Día: ";
            cin >> _dia;
            cout << endl;
        }

        cout << "\t\t - Mes: ";
        cin >> _mes;
        cout << endl;

        while(_mes < 1 || _mes > 12){
            cin.clear();
            cout << "\t\t ---- ERROR : MES INVÁLIDO ----" << endl << endl;
            Sleep(1000);
            system("cls");
            precargarCargaEvaluacion(idEvaluacion, legajoProfesor, idMateria);
            cout << "\t\t - Día: " << _dia << endl;
            cout << endl;
            cout << "\t\t - Mes: ";
            cin >> _mes;
            cout << endl;
        }

        cout << "\t\t - Año: ";
        cin >> _anio;
        cout << endl;
    }
}

string Fecha::toString(string formatoFecha){
   string fechaFormateada = "";

   string DD = to_string(_dia);
   string MM = to_string(_mes);
   string YYYY = to_string(_anio);
   // DD/MM/YYYY
   if (_dia < 10){
      DD = "0" + to_string(_dia);
   }
   if (_mes < 10){
      MM = "0" + to_string(_mes);
   }

   if (formatoFecha == "DD/MM/YYYY"){
      fechaFormateada = DD + "/" + MM + "/" + YYYY;
   }
   else if (formatoFecha == "YYYY/MM/DD"){
      fechaFormateada = YYYY + "/" + MM + "/" + DD;
   }
   else{
      fechaFormateada = DD + "/" + MM + "/" + YYYY;
   }

   return fechaFormateada;
}

int Fecha::getDia(){
    return _dia;
}

int Fecha::getMes(){
    return _mes;
}

int Fecha::getAnio(){
    return _anio;
}

void Fecha::setDia(int dia){_dia = dia;}
void Fecha::setMes(int mes){_mes = mes;}
void Fecha::setAnio(int anio){_anio = anio;}

void Fecha::precargarCargaEvaluacion(int idEvaluacion, int legajoProfesor, int idMateria) {
    cout << "CREANDO EXÁMEN FINAL" << endl << endl;

    cout << "\t - ID Final: ";
    cout << idEvaluacion << endl << endl;

    cout << "\t - Legajo Profesor: ";
    cout << legajoProfesor << endl << endl;

    cout << "\t - ID Materia: ";
    cout << idMateria << endl << endl;

    cout << "\t - Fecha: " << endl;
}
