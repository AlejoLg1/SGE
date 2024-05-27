#ifndef DIRECTOR_H
#define DIRECTOR_H
#include <locale.h>
#include "Persona.h"




class Director : public Persona
{
    private:
        int _legajo;
        int _clave;
        bool _estado;

    public:

        ///---- CONSTRUCTOR ----\\\

        Director();

        ///---- SETTERS ----\\\

        void setLegajo();

        void setClave(int);

        void setEstado(bool);


        ///---- GETTERS ----\\\

        int getLegajo();

        int getClave ();

        bool getEstado ();


        ///---- MÉTODOS ----\\\

        void cargarDirector();

        void activarDirector(int);

        void desactivarDirector(int);

        void cambiarClave(int , int);

        void mostrarDirector();

        void grabarEnDiscoDirector();

        void leerEnDiscoDirector();



};

#endif // DIRECTOR_H
