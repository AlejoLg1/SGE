#ifndef INSCRIPCIONMATERIA_H
#define INSCRIPCIONMATERIA_H
#include <iostream>
#include <vector>
#include "Alumno.h"
#include "Materia.h"



class InscripcionMateria
{
    private:
        Alumno _alumno;
        Materia _materias[7];  // Arreglo de tamaño fijo para las materias
        bool _estadoMaterias[7];  // Arreglo de tamaño fijo para los estados de las materias
        int _numMaterias; // Variable para rastrear el número actual de materias


    public:

        ///---- CONSTRUCTOR ----\\\

        InscripcionMateria();

        ///---- SETTERS ----\\\

        void setAlumno(Alumno);

        void setMaterias(const Materia& aux, int pos);

        void setEstadoMaterias(bool, int);

        ///---- GETTERS ----\\\

        Alumno getAlumno();

        Materia* getMaterias();

        bool* getEstadoMaterias();

        ///---- MÉTODOS ----\\\

        bool cargarInscripcionMateria(const Alumno& alumno, const Materia& materia);

        void inscribirseMateria(int);

        void mostrarInscripcionMateria();

        void mostrarRegistroDeIncriccionesMateria(int);

        void grabarEnDiscoInscripcionMateria(const Alumno& alumno, const Materia& materia);

        void leerEnDiscoInscripcionMateria();

        bool leerEnDiscoInscripcionMateriaPorPosicion(int);





};

#endif // INSCRIPCIONMATERIA_H
