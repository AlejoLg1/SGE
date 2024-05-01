#ifndef DIRECTOR_H
#define DIRECTOR_H
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

        void setLegajo(int);

        void setClave(int);

        void setEstado(bool);


        ///---- GETTERS ----\\\

        int getLegajo();

        int getClave ();

        bool getEstado ();


        ///---- MÉTODOS ----\\\

        void cargarDirector();

        void mostrarDirector();

        void grabarEnDiscoDirector();

        int leerEnDiscoDirector(int);



};

#endif // DIRECTOR_H
