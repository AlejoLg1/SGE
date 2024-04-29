#ifndef ADMINISTRADOR_H_INCLUDED
#define ADMINISTRADOR_H_INCLUDED

class Administrador {
    private:
        int _id;
        int _clave;
        char _nombre[16];

    public:

        ///---- SETTERS ----\\\

        void setId();

        void setClave(int);

        void setNombre(char*);

        ///---- GETTERS ----\\\

        int getId();

        int getClave();

        char* getNombre();


        ///---- MÉTODOS ----\\\

        void cargar();

        void mostrar();

        void grabarEnDisco();

        void leerEnDisco();

};

#endif // ADMINISTRADOR_H_INCLUDED
