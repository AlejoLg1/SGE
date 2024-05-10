#pragma once
#include "Persona.h"


class Profesor : public Persona
{
    private:
        int _legajo;
        int _clave;
        bool _estado;

    public:

        Profesor();

        ///SETTERS

        void setLegajo(int);
        void setClave(int);
        void setEstado(bool);

        ///GETTERS

        int getLegajo();
        int getClave();
        bool getEstado();

        ///MÉTODOS

        void cargarProfesor();
        void mostrarProfesor();
        void grabarEnDiscoProfesor();
        bool leerEnDiscoProfesor(int);

};

