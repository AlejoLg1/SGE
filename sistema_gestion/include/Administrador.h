#ifndef ADMINISTRADOR_H_INCLUDED
#define ADMINISTRADOR_H_INCLUDED
#include <locale.h>

class Administrador {
    private:
        int _id;
        int _clave;
        char _nombre[16];

    public:

        ///---- SETTERS ----\\\

        void setId();

        void setClave(int);

        bool esValido(const char*);

        void setNombre(char*);

        ///---- GETTERS ----\\\

        int getId();

        int getClave();

        char* getNombre();


        ///---- MÉTODOS ----\\\

        void cargar();

        void mostrar();

        void cambiarClave(int, int);

        void grabarEnDiscoAdministrador();

        void leerEnDiscoAdministrador();

};

#endif // ADMINISTRADOR_H_INCLUDED
