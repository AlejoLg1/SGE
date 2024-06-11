#pragma once
#include "Fecha.h"


class Aviso
{
    private:
        int _id;
        char _fecha[11];
        char _asunto[30];
        char _descripcion[300];
        int generarId();
    public:

        /// CONSTRUCTOR
        Aviso();

        /// SETTERS

        void setId();
        void setFecha(std::string);
        void setAsunto(std::string);
        void setDescripcion(std::string);

        /// GETTERS

        int getId();
        const char* getFecha();
        const char* getAsunto();
        const char* getDescripcion();

        /// METODOS

        void cargarAviso();
        void mostrarAviso();
        void grabarEnDisco();
        void leerEnDisco();

};


