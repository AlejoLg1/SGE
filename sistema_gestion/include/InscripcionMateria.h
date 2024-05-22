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
        std::vector<Materia> _materias;
        std::vector<bool> _estadoMaterias;

    public:

        ///---- CONSTRUCTOR ----\\\

        InscripcionMateria();

        ///---- SETTERS ----\\\

        void setAlumno(Alumno);

        void setMaterias(const Materia& aux, int pos);

        void setEstadoMaterias(bool, int);

        ///---- GETTERS ----\\\

        Alumno getAlumno();

        std::vector<Materia> getMaterias();

        std::vector<bool> getEstadoMaterias();

        ///---- MÉTODOS ----\\\

        void cargarInscripcionMateria(const Alumno& alumno, const Materia& materia);

        void mostrarInscripcionMateria();

        void grabarEnDiscoInscripcionMateria(const Alumno& alumno, const Materia& materia);

        void leerEnDiscoInscripcionMateria();





};

#endif // INSCRIPCIONMATERIA_H
