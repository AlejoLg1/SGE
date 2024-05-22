#ifndef EVALUACION_H
#define EVALUACION_H
#include "Fecha.h"

class Evaluacion
{
    private:
        int _id;
        int _idProfesor;
        Fecha _fecha;
        bool _estado;
    public:
        Evaluacion();

        ///SETTERS
        void setId(int);
        void setIdProfesor(int);
        void setFecha(Fecha);
        void setEstado(bool);

        ///GEETERS
        int getId();
        int getIdProfesor();
        Fecha getFecha();
        bool getEstado();

        ///METODOS
        void cargarEvaluacion();
        void mostrarEvaluacion();
        void grabarEnDisco();
        void leerEnDisco();

};

#endif // EVALUACION_H
