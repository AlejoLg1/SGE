#ifndef PERSONA_H
#define PERSONA_H
#include <locale.h>

class Persona
{
    private:
        char _nombre [16];
        char _apellido [16];


    public:
        ///---- CONSTRUCTOR ----\\\

        Persona();

        ///---- SETTERS ----\\\

        bool esValido(const char*);

        void setNombre(char*);

        void setApellido(char*);



        ///---- GETTERS ----\\\

        char* getNombre();

        char* getApellido();


        ///---- MÉTODOS ----\\\

        bool cargar();

        void mostrar();

        void grabarEnDisco();

        void leerEnDisco();



};

#endif // PERSONA_H
