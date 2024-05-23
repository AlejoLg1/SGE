#include "InscripcionMateria.h"
#include <cstdlib> // Para std::system
#include <limits>  // Para std::numeric_limits
#include "Funciones.h"
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
    if (pos >= 0 && pos < 7)
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
    // Verificación de Rango: Se asegura de que pos esté dentro del rango válido de _estadoMaterias

    if (pos >= 0 && pos < 7)
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

Materia* InscripcionMateria::getMaterias()
{
    return _materias;  // Devuelve un puntero al arreglo de materias
}

bool* InscripcionMateria::getEstadoMaterias()
{
    return _estadoMaterias;  // Devuelve un puntero al arreglo de estados de materias
}

        ///---- MÉTODOS ----\\\

bool InscripcionMateria::cargarInscripcionMateria(const Alumno& alumno, const Materia& materia)
{
    if (_numMaterias >= 7)
    {
        throw std::runtime_error("No se pueden cargar más de 7 materias");
        return false;
    }
    else
    {
        _alumno = alumno;
        _materias[_numMaterias] = materia;  // Agrega la materia al final del arreglo
        _estadoMaterias[_numMaterias] = true;  // Agrega el estado de la materia al final del arreglo
        _numMaterias++; // Incrementa el contador de materias
    }

    return true;;
}

void InscripcionMateria::inscribirseMateria(int legajo)
{
    Alumno legAux;
    Materia matAux;
    int idMateria = 0, opcion = 0;
    bool validacion = false;

    while (!validacion)
    {
        std::system("cls");

        mostrarPlanEstudio();
        std::cout << "-----------------------------" << std::endl;
        std::cout << "    INCRIPCION DE MATERIA    " << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Ingrese la ID de la Materia: ";
        std::cin >> idMateria;

        if (std::cin.fail()) {
            std::cin.clear(); // Limpiar el estado de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar entrada inválida
            std::cout << "Entrada inválida. Por favor, ingrese un número válido." << std::endl;
            continue;
        }

        if (!validarMateria(idMateria))
        {
            std::cout << "La ID ingresada no Existe" << std::endl;
            std::cout << "-------------------------------" << std::endl;
            std::cout << "Quiere volver a ingresar la ID?" << std::endl;
            std::cout << "SI = 1      NO = 0             " << std::endl;
            std::cout << "-------------------------------" << std::endl;
            std::cin >> opcion;

            if (std::cin.fail()) {
                std::cin.clear(); // Limpiar el estado de error
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar entrada inválida
                std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                continue;
            }

            switch (opcion)
            {
                case 1:
                    validacion = false;
                    break;
                case 0:
                    return; // Sale de la función si el usuario elige no continuar
                default:
                    std::cout << "Opción incorrecta. Intente de nuevo." << std::endl;
                    break;
            }
        }
        else
        {
            validacion = true;
        }
    }

   legAux = buscarAlumno(legajo);
    matAux = buscarMateria(idMateria);

    if (cargarInscripcionMateria(legAux , matAux))
    {
        grabarEnDiscoInscripcionMateria(legAux,matAux);
        std::cout << "Materia Cargada correctamente" << std::endl;
    }
    else
    {
        std::cout << "NO SE PUDO CARGAR LA MATERIA" << std::endl;
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
    for (int i = 0; i < 7; ++i) {
        std::cout << "Materia " << i+1 << ": " << _materias[i].getNombreMateria() << std::endl;
    }
    std::cout << "----------------------------- " <<std::endl;
    system("pause");
}

void InscripcionMateria::mostrarRegistroDeIncriccionesMateria(int legajo)
{
Alumno legAux;
int pos=0;

    legAux = buscarAlumno(legajo);

    while (leerEnDiscoInscripcionMateriaPorPosicion(pos))
     {
         if(_alumno.getLegajo()== legAux.getLegajo())
         {
            mostrarInscripcionMateria();

         }

        pos++;
     }


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

bool InscripcionMateria::leerEnDiscoInscripcionMateriaPorPosicion(int pos)
{
    FILE *p;
    bool Leyo;

    p=fopen ("InscripcionMateria.dat","rb");
    if (p==NULL){cout<<"El ARCHIVO NO SE PUDO LEER"<<endl; return false;}

    fseek (p,sizeof(InscripcionMateria)*pos,0);

    Leyo=fread(this,sizeof (InscripcionMateria),1,p);

    fclose(p);
    return Leyo;

}

