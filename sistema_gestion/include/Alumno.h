#ifndef ALUMNO_H_INCLUDED
#define ALUMNO_H_INCLUDED
#include "Persona.h"

class Alumno : public Persona{
    private:
        int _legajo;
        int _clave;
        bool _estado;
        int _materias[7];


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

        int* getMaterias();


        ///---- MÉTODOS ----\\\

        void cargar();

        void activarAlumno(int);

        void desactivarAlumno(int);

        void cambiarClave(int , int);

        void mostrar();

        void grabarEnDiscoAlumno();

        void leerEnDiscoAlumno();

};


#endif // ALUMNO_H_INCLUDED
