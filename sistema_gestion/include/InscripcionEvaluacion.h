#ifndef INSCRIPCIONEVALUCION_H
#define INSCRIPCIONEVALUCION_H
#include "Materia.h"
#include "Alumno.h"
#include "Evaluacion.h"

class InscripcionEvaluacion
{
    private:
        Alumno _alumno;
        Materia _materias [7];
        float _materiasNotas [7]; //-> Nota
        bool _inscriptoMaterias [7]; //--> PARA SABER SI YA ESTA INSCRIPTO EN ESTA MATERIA
        int _numMaterias;

    public:
        ///---- CONSTRUCTOR ----\\\

        InscripcionEvaluacion();

        ///---- SETTERS ----\\\

        void setAlumno(Alumno);

        void setMaterias(const Materia& aux, int pos);

        void setMateriasNotas(float, int);

        void setInscriptoMaterias(bool, int);

        void setNumMaterias(bool);

        ///---- GETTERS ----\\\

        Alumno getAlumno();

        Materia* getMaterias();

        int getMaterias2(int pos) const;

        float* getMateriasNotas();

        bool* getInscriptoMaterias();

        int getNumMaterias();

        ///---- MÉTODOS ----\\\

        int cargarInscripcionEvaluacion(const Alumno& alumno, const Materia& materia, int legajo);

        void inscribirseEvaluacion(int);

        void mostrarInscripcionEvaluacion();

        void mostrarInscripcionEvaluacionSinElNombreDeUsuario(int );

        void mostrarRegistroDeIncriccionesEvaluacion(int);

        void DarseDeBajaEvaluacion(int);

        int cargarBajaDeUnRegistroDeIncriccionesEvaluacion(const Alumno& alumno, const Materia& materia, int , int);

        void grabarEnDiscoInscripcionEvaluacion();

        void ModificarEnDiscoInscripcionEvaluacion(int pos);

        void leerEnDiscoInscripcionEvaluacion();

        bool leerEnDiscoInscripcionEvaluacionPorPosicion(int);

        bool leerEntrada(int& entrada);

        bool preguntarContinuar(const std::string& mensaje);

        void reset();




};

#endif // INSCRIPCIONEVALUCION_H
