#ifndef MATERIA_H
#define MATERIA_H
#include <locale.h>
#include <string>
#include "Profesor.h"

using namespace std;

class Materia
{

    private:
        int _id;
        Profesor _profesor;
        int _nivel;
        char _nombreMateria[30];

        int generarId();
        Profesor BuscarProfesor(int);
    public:

         ///---- CONSTRUCTOR ----\\\

        Materia();

        ///---- SETTERS ----\\\

        void setId();

        void setProfesor(int);

        void setNivel(int);

        void setNombreMateria(string);

        ///---- GETTERS ----\\\

        int getId()const;

        Profesor getProfesor();

        int getNivel();

        char* getNombreMateria();




        ///---- MÉTODOS ----\\\

        void cargarMateria();

        void mostrarMateria();

        void grabarEnDiscoMateria();

        void leerEnDiscoMateria();

        bool leerEnDiscoMateriaPorPosicion(int);


};

#endif // MATERIA_H
