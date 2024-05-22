#include "InscripcionMateria.h"
#include "Alumno.h"
#include "Materia.h"

using namespace std;


        ///---- CONSTRUCTOR ----\\\

InscripcionMateria::InscripcionMateria()
{
    //ctor
}

        ///---- SETTERS ----\\\

void InscripcionMateria::setAlumno(Alumno aux)
{
    _alumno = aux;
}

void InscripcionMateria::setMaterias(const Materia& aux, int pos)
{
    //Verificación de Rango: Se asegura de que pos está dentro del rango válido de _materias

    if (pos >= 0 && pos < _materias.size())
    {
        _materias[pos] = aux;
    }
    else
    {
        throw std::out_of_range("Posición fuera de rango");
    }

}

void InscripcionMateria::setEstadoMaterias(bool aux, int pos)
{
    //Verificación de Rango: Se asegura de que pos está dentro del rango válido de _estadoMaterias

    if (pos >= 0 && pos < _estadoMaterias.size())
    {
        _estadoMaterias[pos] = aux;
    }
    else
    {
        throw std::out_of_range("Posición fuera de rango");
    }
}

        ///---- GETTERS ----\\\

Alumno InscripcionMateria::getAlumno()
{
    return _alumno;

}

std::vector<Materia> InscripcionMateria::getMaterias()
{
    std::vector<Materia> vec;


    // Verifica que _materias tenga al menos 1 elementos
    if ( _materias.size() < 1) {
        throw std::out_of_range("No hay materias");
    }

    // Copia todos los elementos de _estadoMaterias al vector vec

    for (int i = 0; i < _materias.size(); i++) {
        vec.push_back(_materias.at(i));
    }

    return vec;
}

std::vector<bool> InscripcionMateria::getEstadoMaterias()
{

    std::vector<bool> vec;


    // Verifica que _materias tenga al menos 1 elementos
    if ( _estadoMaterias.size() < 1) {
        throw std::out_of_range("No hay materias");
    }

    // Copia todos los elementos de _estadoMaterias al vector vec

    for (int i = 0; i < _estadoMaterias.size(); i++) {
        vec.push_back(_estadoMaterias.at(i));
    }

    return vec;

}

        ///---- MÉTODOS ----\\\

void InscripcionMateria::cargarInscripcionMateria(const Alumno& alumno, const Materia& materia)
{

 // Verificar si ya se alcanzó el máximo de materias
    if (_materias.size() >= 7) {
        throw std::runtime_error("No se pueden cargar más de 7 materias");
    }
    //Si el vector tiene lugar aun, se carga la materia
    else
    {

    _alumno = alumno;

    // Agregar la materia al final del vector de materias
    _materias.push_back(materia);

    // Agregar el estado de la materia al final del vector de estados de materias
    _estadoMaterias.push_back(true);

    }


}

void InscripcionMateria::mostrarInscripcionMateria() {
    // Mostrar detalles del alumno
    std::cout << "----------------------------- " <<std::endl;
    std::cout << "Nombre: " << _alumno.getNombre() << std::endl;
    std::cout << "Apellido: " << _alumno.getApellido() << std::endl;
    std::cout << "Legajo: " << _alumno.getLegajo() << std::endl;

    // Mostrar materias inscritas y sus estados
    std::cout << "Materias inscritas:" << std::endl;
    for (size_t i = 0; i < _materias.size(); ++i) {
    std::cout << "Materia " << i+1 << ": " << _materias[i].getNombreMateria() << std::endl;

    }
    std::cout << "----------------------------- " <<std::endl;
}

void InscripcionMateria::grabarEnDiscoInscripcionMateria(const Alumno& alumno, const Materia& materia)
{
    FILE *p;

    if(!(p = fopen("InscripcionMateria.dat", "ab"))) {

        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    this->cargarInscripcionMateria(alumno,materia);
    fwrite(this, sizeof(InscripcionMateria), 1, p);

    fclose(p);



}


void InscripcionMateria::leerEnDiscoInscripcionMateria()
{

    FILE *p;

    if(!(p = fopen("InscripcionMateria.dat", "rb"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    cout << "MOSTRANDO INSCRIPCIONES:" << endl;
    while(fread(this, sizeof(InscripcionMateria), 1, p)){
        this->mostrarInscripcionMateria();
    };

    fclose(p);


}

