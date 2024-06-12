#include "InscripcionEvalucion.h"
#include <iostream>
#include <stdexcept>  // Necesario para std::out_of_range
#include <limits>     // Necesario para std::numeric_limits
#include "Funciones.h"
#include "Materia.h"
#include "Alumno.h"
#include "Evaluacion.h"

InscripcionEvalucion::InscripcionEvalucion()
{
    //ctor
}

///---- SETTERS ----\\\

void InscripcionEvalucion::setAlumno(Alumno aux)
{
    _alumno = aux;
}

void InscripcionEvalucion::setMaterias(const Materia& aux, int pos)
{
    if (pos >= 0 && pos < 7)
    {
        _materias[pos] = aux;
    }
    else
    {
        throw std::out_of_range("Posición fuera de rango");
    }
}

void InscripcionEvalucion::setMateriasNotas(float nota, int pos)
{
    if (pos >= 0 && pos < 7)
    {
        _materiasNotas[pos] = nota;
    }
    else
    {
        throw std::out_of_range("Posición fuera de rango");
    }
}

void InscripcionEvalucion::setNumMaterias(int num)
{
    _numMaterias = num;
}

///---- GETTERS ----\\\

Alumno InscripcionEvalucion::getAlumno()
{
    return _alumno;
}

Materia* InscripcionEvalucion::getMaterias()
{
    return _materias;
}

float* InscripcionEvalucion::getMateriasNotas()
{
    return _materiasNotas;
}

int InscripcionEvalucion::getNumMaterias()
{
    return _numMaterias;
}

///---- MÉTODOS ----\\\

int InscripcionEvalucion::cargarInscripcionEvaluacion(const Alumno& alumno, const Materia& materia, int legajo)
{
    if (_numMaterias >= 7)
    {
        throw std::runtime_error("No se pueden cargar más de 7 materias");
    }
    else
    {
        if (int posicion = buscarInscripcionEvaluacion(legajo) == -1)
        {

        _alumno = alumno;
        _materias[_numMaterias] = materia;
        _materiasNotas[_numMaterias] = 0;  // Initializing the note
        _numMaterias++;
        return -1;
        }

        else
        {
        _alumno = alumno;
        _materias[_numMaterias] = materia;
        _materiasNotas[_numMaterias] = 0;  // Initializing the note
        _numMaterias++;
        return posicion;

        }
    }
    return -1;
}

void InscripcionEvalucion::inscribirseEvaluacion(int legajo)
{
    Alumno legAux;
    Evaluacion evalAux;
    Materia matAux;
    int idEvaluacion = 0;
    bool continuar = true;

    while (continuar)
    {
        std::system("cls");

        //mostrarEvaluaciones();
        std::cout << "-----------------------------" << std::endl;
        std::cout << "  INSCRIPCION DE EVALUACION  " << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Ingrese la ID de la Evaluacion: ";

        if (!leerEntrada(idEvaluacion))
        {
            std::cout << "Entrada inválida. Por favor, ingrese un número válido." << std::endl;
            continue;
        }

        if (!validarEvaluacion(idEvaluacion))  // Assuming there's a function to validate the evaluation ID
        {
            system("cls");
            std::cout << "La ID ingresada no Existe" << std::endl;
            if (!preguntarContinuar("Quiere volver a ingresar la ID?"))
            {
                return;
            }
            continue;
        }

        if (estaAlumnoInscritoEnEvaluacion(legajo, idEvaluacion))  // Assuming there's a function to check if the student is already enrolled
        {
            system("cls");
            std::cout << " Ya Esta Inscripto en Esa Evaluacion " << std::endl;
            if (!preguntarContinuar("Quiere inscribirse en otra evaluacion?"))
            {
                return;
            }
            continue;
        }

        legAux = buscarAlumno(legajo);
        evalAux = buscarEvaluacion(idEvaluacion);
        int posicionDeInscripcion = cargarInscripcionEvaluacion(legAux, matAux, legajo);

        if (posicionDeInscripcion == -1)
        {
            grabarEnDiscoInscripcionEvaluacion(legAux, evalAux);
            std::cout << std::endl << "Evaluacion Cargada correctamente" << std::endl << std::endl;
        }
        else
        {
            ModificarEnDiscoInscripcionEvaluacion(posicionDeInscripcion);
            std::cout << std::endl << "Evaluacion Agregada correctamente" << std::endl << std::endl;
        }
        system("Pause");
        continuar = false;
    }
}

void InscripcionEvalucion::mostrarInscripcionEvaluacion()
{
    // Mostrar detalles del alumno
    std::cout << "----------------------------- " << std::endl;
    std::cout << "Nombre: " << _alumno.getNombre() << std::endl;
    std::cout << "Apellido: " << _alumno.getApellido() << std::endl;
    std::cout << "Legajo: " << _alumno.getLegajo() << std::endl;

    // Mostrar materias inscritas y sus notas
    std::cout << "Materias inscritas y notas:" << std::endl;
    for (int i = 0; i < _numMaterias; ++i)
    {
        std::cout << "| " << _materias[i].getNombreMateria() << " | Nota: " << _materiasNotas[i] << std::endl;
    }
    std::cout << "----------------------------- " << std::endl;
    system("pause");
}

void InscripcionEvalucion::mostrarInscripcionEvaluacionSinElNombreDeUsuario(int legajo)
{
    Alumno legAux;
    int pos = 0;

    legAux = buscarAlumno(legajo);

    while (leerEnDiscoInscripcionEvaluacionPorPosicion(pos))
    {
        if (_alumno.getLegajo() == legAux.getLegajo())
        {
            std::cout << "Materias inscritas y notas:" << std::endl;
            for (int i = 0; i < _numMaterias; ++i)
            {
                std::cout << "| ID: " << _materias[i].getId() << " | Materia: " << _materias[i].getNombreMateria() << " | Nota: " << _materiasNotas[i] << std::endl;
            }
            std::cout << "----------------------------- " << std::endl;
        }
        pos++;
    }
}

void InscripcionEvalucion::mostrarRegistroDeIncriccionesEvaluacion(int legajo)
{
    Alumno legAux;
    int pos = 0;

    legAux = buscarAlumno(legajo);

    while (leerEnDiscoInscripcionEvaluacionPorPosicion(pos))
    {
        if (_alumno.getLegajo() == legAux.getLegajo())
        {
            mostrarInscripcionEvaluacion();
        }
        pos++;
    }
}

void InscripcionEvalucion::DarseDeBajaEvaluacion(int legajo)
{
    Alumno legAux;
    Materia matAux;
    int idEvaluacion = 0;
    bool continuar = true;

    while (continuar)
    {
        std::system("cls");
        mostrarInscripcionEvaluacionSinElNombreDeUsuario(legajo);

        std::cout << "   DARSE DE BAJA EN EVALUACION  " << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Ingrese la ID de la Evaluacion: ";

        if (!leerEntrada(idEvaluacion)) // chequea que sea un número y no otra cosa
        {
            std::cout << "Entrada inválida. Por favor, ingrese un número válido." << std::endl;
            continue;
        }

        if (!validarEvaluacion(idEvaluacion))
        {
            system("cls");
            std::cout << "La ID ingresada no Existe" << std::endl;
            if (!preguntarContinuar("Quiere volver a ingresar la ID?"))
            {
                return;
            }
            continue;
        }

        if (!estaAlumnoInscritoEnEvaluacion(legajo, idEvaluacion))
        {
            system("cls");
            std::cout << "No Esta Inscripto en Esa Evaluacion" << std::endl;
            if (!preguntarContinuar("Quiere volver a ingresar la ID?"))
            {
                return;
            }
            continue;
        }

        legAux = buscarAlumno(legajo);
        matAux = buscarMateria(idEvaluacion);

        int posicionDeInscripcion = cargarBajaDeUnRegistroDeIncriccionesEvaluacion(legAux, matAux, legajo, idEvaluacion);

        ModificarEnDiscoInscripcionEvaluacion(posicionDeInscripcion);
        std::cout << "Evaluacion Dada de baja" << std::endl;

        system("Pause");
        continuar = false;
    }
}

int InscripcionEvalucion::cargarBajaDeUnRegistroDeIncriccionesEvaluacion(const Alumno& alumno, const Materia& materia, int Legajo, int idEvaluacionBaja)
{
    int posicion = buscarInscripcionEvaluacion(Legajo);  // Assuming there's a function to find the enrollment position

    _alumno = alumno;
    for (int i = 0; i < 7; i++)
    {
        if (_materias[i].getId() == idEvaluacionBaja)
        {
            _materiasNotas[i] = -1;  // Set a flag value to indicate the evaluation is dropped
            return posicion;
        }
    }
    return posicion;
}

void InscripcionEvalucion::grabarEnDiscoInscripcionEvaluacion(const Alumno& alumno, const Evaluacion& evaluacion)
{
    FILE *p;

    if (!(p = fopen("InscripcionEvaluacion.dat", "ab")))
    {
        std::cout << "---- ERROR AL ABRIR EL ARCHIVO ----" << std::endl;
        return;
    }

    fwrite(this, sizeof(InscripcionEvalucion), 1, p);
    fclose(p);
}

void InscripcionEvalucion::ModificarEnDiscoInscripcionEvaluacion(int pos)
{
    FILE *p;

    p = fopen("InscripcionEvaluacion.dat", "rb+");
    if (p == nullptr)
    {
        std::cout << "NO SE PUDO ABRIR/CREAR EL ARCHIVO" << std::endl;
        return;
    }

    fseek(p, sizeof(InscripcionEvalucion) * pos, 0);
    fwrite(this, sizeof(InscripcionEvalucion), 1, p);
    fclose(p);
}

void InscripcionEvalucion::leerEnDiscoInscripcionEvaluacion()
{
    FILE *p;

    if (!(p = fopen("InscripcionEvaluacion.dat", "rb")))
    {
        std::cout << "---- ERROR AL ABRIR EL ARCHIVO ----" << std::endl;
        return;
    }

    std::cout << "MOSTRANDO INSCRIPCIONES:" << std::endl;
    while (fread(this, sizeof(InscripcionEvalucion), 1, p))
    {
        this->mostrarInscripcionEvaluacion();
    }
    fclose(p);
}

bool InscripcionEvalucion::leerEnDiscoInscripcionEvaluacionPorPosicion(int pos)
{
    FILE *p;
    bool leyo;

    p = fopen("InscripcionEvaluacion.dat", "rb");
    if (p == nullptr)
    {
        return false;
    }

    fseek(p, sizeof(InscripcionEvalucion) * pos, 0);
    leyo = fread(this, sizeof(InscripcionEvalucion), 1, p);
    fclose(p);
    return leyo;
}

bool InscripcionEvalucion::leerEntrada(int& entrada)
{
    std::cin >> entrada;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

bool InscripcionEvalucion::preguntarContinuar(const std::string& mensaje)
{
    int opcion = 0;
    std::cout << mensaje << std::endl;
    std::cout << "SI = 1      NO = 0" << std::endl;
    if (!leerEntrada(opcion))
    {
        std::cout << "Opción inválida. Intente de nuevo." << std::endl;
        return false;
    }
    return opcion == 1;
}
