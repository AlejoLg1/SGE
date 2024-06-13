#ifndef PROFESOR_H_INCLUDED
#define PROFESOR_H_INCLUDED
#include <locale.h>
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

        void activarProfesor(int);
        void desactivarProfesor(int);
        void cambiarClave(int, int);
        void cargarProfesor();
        void mostrarProfesor();
        void grabarEnDiscoProfesor();
        void leerEnDiscoProfesor();
        bool leerEnDiscoProfesorPorPosicion(int);

};

#endif
