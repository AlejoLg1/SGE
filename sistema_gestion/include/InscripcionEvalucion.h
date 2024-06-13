#ifndef INSCRIPCIONEVALUCION_H
#define INSCRIPCIONEVALUCION_H
#include "Materia.h"
#include "Alumno.h"
#include "Evaluacion.h"

class InscripcionEvalucion
{
    private:
        Alumno _alumno;
        Materia _materias [7];
        float _materiasNotas [7]; //-> Nota
        bool _inscriptoMaterias [7]; //--> PARA SABER SI YA ESTA INSCRIPTO EN ESTA MATERIA
        int _numMaterias;

    public:
        ///---- CONSTRUCTOR ----\\\

        InscripcionEvalucion();

        ///---- SETTERS ----\\\

        void setAlumno(Alumno);

        void setMaterias(const Materia& aux, int pos);

        void setMateriasNotas(float, int);

        void setNumMaterias(int);

        ///---- GETTERS ----\\\

        Alumno getAlumno();

        Materia* getMaterias();

        int getMaterias2(int pos) const;

        float* getMateriasNotas();

        int getNumMaterias();

        ///---- MÉTODOS ----\\\

        int cargarInscripcionEvaluacion(const Alumno& alumno, const Materia& materia, int legajo);

        void inscribirseEvaluacion(int);

        void mostrarInscripcionEvaluacion();

        void mostrarInscripcionEvaluacionSinElNombreDeUsuario(int );

        void mostrarRegistroDeIncriccionesEvaluacion(int);

        void DarseDeBajaEvaluacion(int);

        int cargarBajaDeUnRegistroDeIncriccionesEvaluacion(const Alumno& alumno, const Materia& materia, int , int);

        void grabarEnDiscoInscripcionEvaluacion(const Alumno& alumno, const Evaluacion& evaluacion);

        void ModificarEnDiscoInscripcionEvaluacion(int pos);

        void leerEnDiscoInscripcionEvaluacion();

        bool leerEnDiscoInscripcionEvaluacionPorPosicion(int);

        bool leerEntrada(int& entrada);

        bool preguntarContinuar(const std::string& mensaje);




};

#endif // INSCRIPCIONEVALUCION_H
