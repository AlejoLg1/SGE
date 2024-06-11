#pragma once
#include <locale.h>

class Fecha
{
private:
    int _dia;
    int _mes;
    int _anio;

    void establecerFechaPorDefecto();
    bool esBisiesto();
    void agregarDias();
    void restarDias();
public:
    Fecha();
    Fecha( int, int, int );
    ///getters
    int getDia();
    int getMes();
    int getAnio();
    ///Setters
    void setDia(int);
    void setMes(int);
    void setAnio(int);

    void CargarFecha();
    void CargarFechaEvaluacion(int, int, int);

    void AgregarDias(int);

    void precargarCargaEvaluacion(int , int, int);

    std::string FechaActual();
    std::string toString(std::string formatoFecha = "DD/MM/YYYY");


};


