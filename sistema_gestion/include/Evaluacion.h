#ifndef EVALUACION_H
#define EVALUACION_H
#include <locale.h>
#include "Fecha.h"

class Evaluacion
{
    private:
        int _id;
        int _idProfesor;
        int _idMateria;
        Fecha _fecha;
        bool _estado;

        int generarId();

        bool validarExistenciaFinal(int);
    public:
        Evaluacion();

        ///SETTERS
        void setId();
        void setIdProfesor(int);
        bool setIdMateria(int, int);
        void setFecha(Fecha);
        void setEstado(bool);

        ///GEETERS
        int getId();
        int getIdProfesor();
        int getIdMateria();
        Fecha getFecha();
        bool getEstado();

        ///METODOS
        bool cargarEvaluacion(int);
        void mostrarEvaluacion();
        void grabarEnDisco(int);
        void leerEnDisco();
        bool leerEnDiscoEvaluacionPorPosicion(int);
        tm createDate(int, int, int);

};

#endif // EVALUACION_H
