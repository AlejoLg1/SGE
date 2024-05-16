#ifndef PROFESOR_H_INCLUDED
#define PROFESOR_H_INCLUDED
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

        void setLegajo();
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
        bool leerEnDiscoProfesor();

};

#endif
