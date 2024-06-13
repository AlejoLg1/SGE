#include "InscripcionMateria.h"
#include <cstdlib> // Para std::system
#include <limits>  // Para std::numeric_limits
#include <iomanip>
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
        cout << endl << "---- ERROR : POSICIÓN FUERA DE RANGO ----" << endl << endl;
        system("pause");
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
        cout << endl << "---- ERROR : POSICIÓN FUERA DE RANGO ----" << endl << endl;
        system("pause");
    }
}

void InscripcionMateria::setNumMaterias(bool sumar){
    if(sumar)
    {
        _numMaterias++;
    }
    else{
        _numMaterias--;
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

int InscripcionMateria::getNumMaterias()
{
    return _numMaterias;
}

///---- MÉTODOS ----\\\

int InscripcionMateria::cargarInscripcionMateria(const Alumno& alumno, const Materia& materia,int Legajo)
{
    if (getNumMaterias() >= 7)
    {
        cout << endl << "---- LÍMITE INSCRIPCIONES REALIZADAS ALCANZADO ----" << endl;
        return -2;
    }
    else
    {
        if(int posicion = buscarInscripcionMateria(Legajo) == -1)
        {
            _alumno = alumno;
            _materias[getNumMaterias()] = materia;  // Agrega la materia al final del arreglo
            _estadoMaterias[getNumMaterias()] = true;  // Agrega el estado de la materia al final del arreglo
            setNumMaterias(true); // Incrementa el contador de materias
            return -1;
        }
        else
        {
            _alumno = alumno;
            _materias[getNumMaterias()] = materia;  // Agrega la materia al final del arreglo
            _estadoMaterias[getNumMaterias()] = true;  // Agrega el estado de la materia al final del arreglo
            setNumMaterias(true); // Incrementa el contador de materia
            return posicion;
        }
    }

    return -1;
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
        std::cout << "    INCRIPCIÓN DE MATERIA    " << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Ingrese el ID de la materia (ID Materia 0 para salir): ";

        if (!leerEntrada(idMateria))
        {
            std::cout << "Entrada inválida. Por favor, ingrese un número válido." << std::endl;
            continue;
        }

        if(idMateria == 0){
            return;
        }

        if (!validarMateria(idMateria))
        {
            system("cls");
            std::cout << "El ID ingresado no existe" << std::endl;
            if (!preguntarContinuar("¿Quiere volver a ingresar el ID?"))
            {
                return;
            }
            continue;
        }

        if (estaAlumnoInscritoEnMateria(legajo, idMateria))
        {
            system("cls");
            std::cout << "Ya se inscribió en esta materia previamente " << std::endl;
            if (!preguntarContinuar("¿Quiere inscribirse en otra materia?"))
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
        }
        else if(posicionDeInscripcion == -2)
        {
            system("pause");
            return;
        }
        else
        {
            ModificarEnDiscoInscripcionMateria(posicionDeInscripcion);
        }
        std::cout << std::endl << std::endl << "---- INSCRIPCIÓN REALIZADA CON ÉXITO ----" << std::endl ;
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
    std::cout << "----------------------------- " <<std::endl << std::endl;
    system("pause");
}

void InscripcionMateria::mostrarInscripcionMateriaSinElNombreDeUsuario(int legajo)
{
    int anchoID = 6;
    int anchoMateria = 21;

    Alumno legAux;
    int pos=0;

    legAux = buscarAlumno(legajo);

    cout << "Materias inscritas:" << std::endl << std::endl;
    cout << left << setw(anchoID) << "ID";
    cout << "|";
    cout << left << setw(anchoMateria) << "Materia";
    cout << "|" << endl;
    cout << string(anchoID, '-') << "+" << string(anchoMateria, '-') << "+" << endl;

    while (leerEnDiscoInscripcionMateriaPorPosicion(pos))
    {
        if(_alumno.getLegajo()== legAux.getLegajo())
        {
            for (int i = 0; i < 7; ++i)
            {
                if(_estadoMaterias[i]== true)
                {
                    cout << left << setw(anchoID) << _materias[i].getId() << "|" << left << setw(anchoMateria) << _materias[i].getNombreMateria() << "|" << endl;
                }
            }

            cout << endl << endl;
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
        mostrarInscripcionMateriaSinElNombreDeUsuario(legajo);

        std::cout << "   DARSE DE BAJA EN MATERIA  " << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Ingrese el ID de la Materia (ID Materia 0 para salir): ";

        if (!leerEntrada(idMateria)) ///chequea qe sea un numero y no otra cosa
        {
            std::cout << "Entrada inválida. Por favor, ingrese un número válido." << std::endl;
            continue;
        }

        if(idMateria == 0){
            return;
        }

        if (!validarMateria(idMateria))
        {
            system("cls");
            std::cout << "El ID ingresado no existe" << std::endl;
            if (!preguntarContinuar("¿Quiere volver a ingresar el ID?"))
            {
                return;
            }
            continue;
        }

        if (estaAlumnoInscritoEnMateria(legajo, idMateria)== false)
        {
            system("cls");
            std::cout << "No está inscripto en esa Materia  " << std::endl;
            if (!preguntarContinuar("¿Quiere volver a ingresar el ID?"))
            {
                return;
            }
            continue;
        }

        legAux = buscarAlumno(legajo);
        matAux = buscarMateria(idMateria);

        int posicionDeInscripcion = cargarBajaDeUnRegistroDeIncriccionesMateria(legAux, matAux, legajo, idMateria);


        ModificarEnDiscoInscripcionMateria(posicionDeInscripcion);
        std::cout << endl << endl << "---- MATERIA DADA DE BAJA CON ÉXITO ----" << std::endl;
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
    std::cout << "SI = 1      NO = 0" << std::endl << std::endl;

    std::cout << "> ";
    if (!leerEntrada(opcion))
    {
        std::cout << "Opción inválida. Intente de nuevo." << std::endl;
        return false;
    }
    return opcion == 1;
}

