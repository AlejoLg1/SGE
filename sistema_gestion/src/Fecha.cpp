#include <iostream>
using namespace std;
#include <cstdlib>
#include <string>
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

    cout << "DIA: ";
    cin >> _dia;
    cout << "MES: ";
    cin >> _mes;
    cout << "ANIO: ";
    cin >> _anio;

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
