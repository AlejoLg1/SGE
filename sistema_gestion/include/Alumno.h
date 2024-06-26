#ifndef ALUMNO_H_INCLUDED
#define ALUMNO_H_INCLUDED
#include "Persona.h"

class Alumno : public Persona{
    private:
        int _legajo;
        int _clave;
        bool _estado;

    public:

        ///---- SETTERS ----\\\

        void setlegajo();

        void setClave(int);

        void setEstado(bool);

        void setMaterias(int *);

        ///---- GETTERS ----\\\

        int getLegajo();

        int getClave();

        bool getEstado();

        ///---- MÉTODOS ----\\\

        bool cargar();

        void mostrar();

        void activarAlumno(int);

        void desactivarAlumno(int);

        void cambiarClave(int, int);

        void grabarEnDiscoAlumno();

        void leerEnDiscoAlumno();

        bool leerEnDiscoAlumnoPorPosicion(int);

};


#endif // ALUMNO_H_INCLUDED
