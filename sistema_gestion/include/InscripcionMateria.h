#ifndef INSCRIPCIONMATERIA_H
#define INSCRIPCIONMATERIA_H
#include <iostream>
#include <vector>
#include <locale.h>
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

        void setNumMaterias(bool);
        ///---- GETTERS ----\\\

        Alumno getAlumno();

        Materia* getMaterias();

        int getMaterias2(int pos) const;

        bool getEstadoMaterias(int);

        int getNumMaterias();

        ///---- MÉTODOS ----\\\

        int cargarInscripcionMateria(const Alumno& alumno, const Materia& materia, int);

        void inscribirseMateria(int);

        void mostrarInscripcionMateria();

        void mostrarInscripcionMateriaSinElNombreDeUsuario(int );

        void mostrarRegistroDeIncriccionesMateria(int);

        void DarseDeBajaMateria(int);

        int cargarBajaDeUnRegistroDeIncriccionesMateria(const Alumno& alumno,const Materia& materia,int ,int );

        void grabarEnDiscoInscripcionMateria();

        void ModificarEnDiscoInscripcionMateria(int pos);

        void leerEnDiscoInscripcionMateria();

        bool leerEnDiscoInscripcionMateriaPorPosicion(int);

        bool leerEntrada(int& entrada);

        bool preguntarContinuar(const std::string& mensaje);

        void MostrarTodosLosRegistrosIncripcionMateria (); ///LO ARME PARA VER QUE NO SE ESTEN DUPLICANDO LOS REGISTROS

        void reset();  // Inicializa los miembros con valores predeterminados




};

#endif // INSCRIPCIONMATERIA_H
