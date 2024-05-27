#ifndef PERSONA_H
#define PERSONA_H
#include <locale.h>

class Persona
{
    private:
        char _nombre [16];
        char _apellido [16];
        //Fecha _nacimiento;


    public:
        ///---- CONSTRUCTOR ----\\\

        Persona();

        ///---- SETTERS ----\\\

        void setNombre(char*);

        void setApellido(char*);

        //void setNacimiento(Fecha);


        ///---- GETTERS ----\\\

        char* getNombre();

        char* getApellido();

        //bool getFecha(Fecha);



        ///---- MÉTODOS ----\\\

        void cargar();

        void mostrar();

        void grabarEnDisco();

        void leerEnDisco();



};

#endif // PERSONA_H
