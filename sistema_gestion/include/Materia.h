#ifndef MATERIA_H
#define MATERIA_H


class Materia
{

    private:
        int _id;
        int _legajoProfesor;
        char _nombreMateria[30];

        int GenerarId();
    public:

         ///---- CONSTRUCTOR ----\\\

        Materia();

        ///---- SETTERS ----\\\

        void setId();

        void setLegajoProfesor(int);

        void setNombreMateria(char*);


        ///---- GETTERS ----\\\

        int getId();

        int getLegajoProfesor();

        char* getNombreMateria();




        ///---- MÉTODOS ----\\\

        void cargarMateria();

        void mostrarMateria();

        void grabarEnDiscoMateria();

        void leerEnDiscoMateria();

        bool leerEnDiscoMateriaPorPosicion(int);


};

#endif // MATERIA_H
