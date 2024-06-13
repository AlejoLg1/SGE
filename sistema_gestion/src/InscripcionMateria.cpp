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

int InscripcionMateria::getMaterias2(int pos)const
{

    return _materias[pos].getId();
}

bool* InscripcionMateria::getEstadoMaterias()
{
    return _estadoMaterias;  // Devuelve un puntero al arreglo de estados de materias
}

///---- MÉTODOS ----\\\

int InscripcionMateria::cargarInscripcionMateria(const Alumno& alumno, const Materia& materia,int Legajo)
{
    if (_numMaterias >= 7)
    {
        throw std::runtime_error("No se pueden cargar más de 7 materias");
        return false;
    }
    else
    {
        if(int posicion = buscarInscripcionMateria(Legajo)== -1)
        {
            _alumno = alumno;
            _materias[_numMaterias] = materia;  // Agrega la materia al final del arreglo
            _estadoMaterias[_numMaterias] = true;  // Agrega el estado de la materia al final del arreglo
            _numMaterias++; // Incrementa el contador de materias
            return -1;
        }

        else
        {
            _alumno = alumno;
            _materias[_numMaterias] = materia;  // Agrega la materia al final del arreglo
            _estadoMaterias[_numMaterias] = true;  // Agrega el estado de la materia al final del arreglo
            _numMaterias++; // Incrementa el contador de materia
            return posicion;
        }
    }

    return -1;;
}

void InscripcionMateria::inscribirseMateria(int legajo)
{
    Alumno legAux;
    Materia matAux;
    int idMateria = 0, opcion = 0;
    bool continuar = true;

    while (continuar)
    {
        std::system("cls");

        mostrarPlanEstudio();
        std::cout << "-----------------------------" << std::endl;
        std::cout << "    INCRIPCION DE MATERIA    " << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Ingrese la ID de la Materia: ";

        if (!leerEntrada(idMateria))
        {
            std::cout << "Entrada inválida. Por favor, ingrese un número válido." << std::endl;
            continue;
        }

        if (!validarMateria(idMateria))
        {
            system("cls");
            std::cout << "La ID ingresada no Existe" << std::endl;
            if (!preguntarContinuar("Quiere volver a ingresar la ID?"))
            {
                return;
            }
            continue;
        }

        if (estaAlumnoInscritoEnMateria(legajo, idMateria))
        {
            system("cls");
            std::cout << " Ya Esta Inscripto en Esa Materia  " << std::endl;
            if (!preguntarContinuar("Quiere inscribirse en otra materia?"))
            {
                return;
            }
            continue;
        }

        legAux = buscarAlumno(legajo);
        matAux = buscarMateria(idMateria);
        int posicionDeInscripcion = cargarInscripcionMateria(legAux, matAux, legajo);

        if (posicionDeInscripcion == -1)
        {
            grabarEnDiscoInscripcionMateria(legAux, matAux);
            std::cout << std::endl << "Materia Cargada correctamente" << std::endl << std::endl;
        }
        else
        {
            ModificarEnDiscoInscripcionMateria(posicionDeInscripcion);
            std::cout << std::endl << "Materia Agregada correctamente" << std::endl << std::endl;
        }
        system("Pause");
        continuar = false;
    }
}

void InscripcionMateria::mostrarInscripcionMateria()
{
// Mostrar detalles del alumno
    std::cout << "----------------------------- " <<std::endl;
    std::cout << "Nombre: " << _alumno.getNombre() << std::endl;
    std::cout << "Apellido: " << _alumno.getApellido() << std::endl;
    std::cout << "Legajo: " << _alumno.getLegajo() << std::endl;

    // Mostrar materias inscritas y sus estados
    std::cout << "Materias inscritas:" << std::endl;
    for (int i = 0; i < 7; ++i)
    {
        if(_estadoMaterias[i]== true)
        {
            std::cout<< "| " << _materias[i].getNombreMateria()<< std::endl;
        }
    }
    std::cout << "----------------------------- " <<std::endl;
    system("pause");
}

void InscripcionMateria::mostrarInscripcionMateriaSinElNombreDeUsuario(int legajo)
{

    Alumno legAux;
    int pos=0;

    legAux = buscarAlumno(legajo);

    while (leerEnDiscoInscripcionMateriaPorPosicion(pos))
    {
        if(_alumno.getLegajo()== legAux.getLegajo())
        {
            std::cout << "Materias inscritas:" << std::endl;
            for (int i = 0; i < 7; ++i)
            {
                if(_estadoMaterias[i]== true)
                {
                    std::cout<<"| ID :"<<_materias[i].getId()<< "| Materia : " << _materias[i].getNombreMateria()<< std::endl;
                }
            }
            std::cout << "----------------------------- " <<std::endl;

        }

        pos++;
    }

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

void InscripcionMateria::DarseDeBajaMateria(int legajo)
{
    Alumno legAux;
    Materia matAux;
    int idMateria = 0, opcion = 0;
    bool continuar = true;



    while (continuar)
    {
        std::system("cls");
        mostrarInscripcionMateriaSinElNombreDeUsuario( legajo);

        std::cout << "   DARSE DE BAJA EN MATERIA  " << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Ingrese la ID de la Materia: ";

        if (!leerEntrada(idMateria)) ///chequea qe sea un numero y no otra cosa
        {
            std::cout << "Entrada inválida. Por favor, ingrese un número válido." << std::endl;
            continue;
        }

        if (!validarMateria(idMateria))
        {
            system("cls");
            std::cout << "La ID ingresada no Existe" << std::endl;
            if (!preguntarContinuar("Quiere volver a ingresar la ID?"))
            {
                return;
            }
            continue;
        }

        if (estaAlumnoInscritoEnMateria(legajo, idMateria)== false)
        {
            system("cls");
            std::cout << "No Esta Inscripto en Esa Materia  " << std::endl;
            if (!preguntarContinuar("Quiere volver a ingresar la ID?"))
            {
                return;
            }
            continue;
        }

        legAux = buscarAlumno(legajo);
        matAux = buscarMateria(idMateria);

        int posicionDeInscripcion = cargarBajaDeUnRegistroDeIncriccionesMateria(legAux, matAux, legajo, idMateria);


        ModificarEnDiscoInscripcionMateria(posicionDeInscripcion);
        std::cout << "Materia Dada de baja" << std::endl;

        system("Pause");
        continuar = false;
    }

}



int InscripcionMateria::cargarBajaDeUnRegistroDeIncriccionesMateria(const Alumno& alumno,const Materia& materia,int Legajo,int idMateriaBaja )
{


    int posicion = buscarInscripcionMateria(Legajo);

    _alumno = alumno;
    for(int i=0; i<7; i++)
    {
        if(_materias[i].getId() == idMateriaBaja)
        {
            _estadoMaterias[i] = false;
            return posicion;
        }
    }

    _numMaterias; // No lo descuenta ya que se supone que el alumno esta cursando
    return posicion;
}




void InscripcionMateria::grabarEnDiscoInscripcionMateria(const Alumno& alumno, const Materia& materia)
{
    FILE *p;

    if(!(p = fopen("InscripcionMateria.dat", "ab")))
    {

        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }


    fwrite(this, sizeof(InscripcionMateria), 1, p);

    fclose(p);



}

void InscripcionMateria::ModificarEnDiscoInscripcionMateria(int pos)
{
    FILE *p;


    p=fopen("InscripcionMateria.dat","rb+");
    if (p==NULL)
    {
        cout<<"NO SE PUDO ABRIR/CREAR EL ARCHIVO"<<endl;
    }

    fseek(p,sizeof(InscripcionMateria)*pos,0);

    fwrite(this,sizeof(InscripcionMateria),1,p);

    fclose (p);
}


void InscripcionMateria::leerEnDiscoInscripcionMateria()
{

    FILE *p;

    if(!(p = fopen("InscripcionMateria.dat", "rb")))
    {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    cout << "MOSTRANDO INSCRIPCIONES:" << endl;
    while(fread(this, sizeof(InscripcionMateria), 1, p))
    {
        this->mostrarInscripcionMateria();
    };

    fclose(p);


}

bool InscripcionMateria::leerEnDiscoInscripcionMateriaPorPosicion(int pos)
{
    FILE *p;
    bool Leyo;

    p=fopen ("InscripcionMateria.dat","rb");
    if (p==NULL)
    {
        return false;
    }

    fseek (p,sizeof(InscripcionMateria)*pos,0);

    Leyo=fread(this,sizeof (InscripcionMateria),1,p);

    fclose(p);
    return Leyo;

}

bool InscripcionMateria::leerEntrada(int& entrada)
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

bool InscripcionMateria::preguntarContinuar(const std::string& mensaje)
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

