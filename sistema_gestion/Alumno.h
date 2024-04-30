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

        void setlegajo(int);

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

        void mostrar();

        void grabarEnDisco();

        void leerEnDisco();

};


#endif // ALUMNO_H_INCLUDED
