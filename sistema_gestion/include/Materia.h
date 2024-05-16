#ifndef MATERIA_H
#define MATERIA_H


class Materia
{

    private:
        int _id ;
        int _legajoProfesor;
        char _nombreMateria [20];



    public:

         ///---- CONSTRUCTOR ----\\\

        Materia();

        ///---- SETTERS ----\\\

        void setId(int);

        void setLegajoProfesor(int);

        void setNombreMateria(char*);


        ///---- GETTERS ----\\\

        int getId();

        int getLegajoProfesor();

        char* getNombreMateria();




        ///---- MÉTODOS ----\\\

        void cargarMateria();

        void mostrarMateria();

        void grabarEnDisco();

        int leerEnDisco(int pos);





};

#endif // MATERIA_H
