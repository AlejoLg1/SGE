#ifndef INSCRIPCIONEVALUCION_H
#define INSCRIPCIONEVALUCION_H
#include "Materia.h"
#include "Alumno.h"
#include "Evaluacion.h"

class InscripcionEvaluacion
{
    private:
        int _alumno;
        int _materias [7];
        float _materiasNotas [7]; //-> Nota
        bool _inscriptoMaterias [7]; //--> PARA SABER SI YA ESTA INSCRIPTO EN ESTA MATERIA
        int _numMaterias;

    public:
        ///---- CONSTRUCTOR ----\\\

        InscripcionEvaluacion();

        ///---- SETTERS ----\\\

        void setAlumno(int);

        void setMaterias(const int& aux, int pos);

        void setMateriasNotas(float, int);

        void setInscriptoMaterias(bool, int);

        void setNumMaterias(bool);

        ///---- GETTERS ----\\\

        int getAlumno();

        int* getMaterias();

        int getMaterias2(int pos) const;

        float* getMateriasNotas();

        bool* getInscriptoMaterias();

        bool getInscriptoMaterias2(int);

        int getNumMaterias();

        ///---- MÉTODOS ----\\\

        int cargarInscripcionEvaluacion(Alumno& alumno, const Materia& materia, int legajo);

        void inscribirseEvaluacion(int);

        void mostrarInscripcionEvaluacion();

        void mostrarInscripcionEvaluacionSinElNombreDeUsuario(int );

        void mostrarRegistroDeIncriccionesEvaluacion(int);

        void grabarEnDiscoInscripcionEvaluacion();

        void ModificarEnDiscoInscripcionEvaluacion(int pos);

        void leerEnDiscoInscripcionEvaluacion();

        bool leerEnDiscoInscripcionEvaluacionPorPosicion(int);

        bool leerEntrada(int& entrada);

        bool preguntarContinuar(const std::string& mensaje);

        void reset();




};

#endif // INSCRIPCIONEVALUCION_H
