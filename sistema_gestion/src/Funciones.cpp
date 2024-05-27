#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <locale.h>
#include <stdio.h>
#include "Funciones.h"
#include "Administrador.h"
#include "Director.h"
#include "Profesor.h"
#include "Alumno.h"
#include "Materia.h"
#include "InscripcionMateria.h"
#include "Evaluacion.h"
//#include "rlutil.h"

using namespace std;
//using namespace rlutil;

const int CANTIDADOBJETOS = 4;

//ARCHIVOS
FILE *pAdm;
FILE *pDirectivo;
FILE *pProfesor;
FILE *pAlumno;

//VECTORES ARCHIVOS
const char* vecNombresFiles[CANTIDADOBJETOS] = {"administradores.dat", "directores.dat", "profesores.dat", "alumnos.dat"};
int vecTamObjetos[CANTIDADOBJETOS] = {sizeof(Administrador), sizeof(Director), sizeof(Profesor), sizeof(Alumno)};
string vecNombresRoles[CANTIDADOBJETOS] = {"ADMINISTRADOR", "DIRECTOR", "PROFESOR", "ALUMNO"};

//OBJETOS
Administrador administradorObj;
Director directorObj;
Profesor profesorObj;
Alumno alumnoObj;
InscripcionMateria inscripcionMateriaObj;



//VARIABLES GLOBALES
int rol;
int x;
int legajo;
int clave;

void menuPrincipal()
{
    setlocale(LC_ALL, "Spanish");


    rol = seleccionarRol(rol);

    while(true)
    {
        switch (rol)
        {
        case 49: //ADMINISTRADOR
            system("cls");
            if(usuariosCargados())
            {
                system("cls");
                login(rol, "ADMINISTRADOR");
            }
            else
            {
                cout << endl << "---- ERROR: NO SE ENCONTRARON USUARIOS CON ROL 'ADMINISTRADOR' CARGADOS ----" << endl << endl;
                cout << endl << endl;
                system("pause");
                system("cls");
                administradorObj.grabarEnDiscoAdministrador();
                system("cls");
                rol = seleccionarRol(rol);
            }
            break;
        case 50: //DIRECTOR
            system("cls");
            if(usuariosCargados())
            {
                if(!usuariosEspecificosCargados("DIRECTOR", vecNombresFiles, vecTamObjetos, vecNombresRoles))
                {
                    mensajeUsuariosNoEncontrados("DIRECTOR");
                }
                else
                {
                    system("cls");
                    login(rol, "DIRECTOR");
                }
            }
            else
            {
                mensajeUsuariosNoEncontrados("DIRECTOR");
            }
            break;
        case 51: //PROFESOR
            system("cls");
            if(usuariosCargados())
            {
                if(!usuariosEspecificosCargados("PROFESOR", vecNombresFiles, vecTamObjetos, vecNombresRoles))
                {
                    mensajeUsuariosNoEncontrados("PROFESOR");
                }
                else
                {
                    system("cls");
                    login(rol, "PROFESOR");
                }
            }
            else
            {
                mensajeUsuariosNoEncontrados("PROFESOR");
            }
            break;
        case 52: // ALUMNO
            system("cls");
            if(usuariosCargados())
            {
                if(!usuariosEspecificosCargados("ALUMNO", vecNombresFiles, vecTamObjetos, vecNombresRoles))
                {
                    mensajeUsuariosNoEncontrados("ALUMNO");
                }
                else
                {
                    system("cls");
                    login(rol, "ALUMNO");
                }
            }
            else
            {
                mensajeUsuariosNoEncontrados("ALUMNO");
            }
            break;
        case 48: // SALIR
            system("cls");
            cout << endl << "SALIENDO...." << endl;
            Sleep(2000);
            return;
            break;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }
    }
}

int seleccionarRol(int rol)
{
    setlocale(LC_ALL, "Spanish");

    cout << "----------------------------------------------------"<< endl;
    cout << "                     MENÚ ROLES                     "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "1. ADMINISTRADOR                                    "<< endl;
    cout << "2. DIRECTOR                                         "<< endl;
    cout << "3. PROFESOR                                         "<< endl;
    cout << "4. ALUMNO                                           "<< endl;
    cout << "0. SALIR                                            "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "       - SELECCIONE SU ROL CORRESPONDIENTE: -       "<< endl;
    cout << "----------------------------------------------------"<< endl;

    rol = _getch();

    while(rol != 49 && rol != 50 && rol != 51 && rol != 52 && rol != 48)
    {
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "----------------------------------------------------"<< endl;
        cout << "                     MENÚ ROLES                     "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "1. ADMINISTRADOR                                    "<< endl;
        cout << "2. DIRECTOR                                         "<< endl;
        cout << "3. PROFESOR                                         "<< endl;
        cout << "4. ALUMNO                                           "<< endl;
        cout << "0. SALIR                                            "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "       - SELECCIONE SU ROL CORRESPONDIENTE: -       "<< endl;
        cout << "----------------------------------------------------"<< endl;

        rol = _getch();
    }

    return rol;
}

///--- SETTEAR LEGAJO AUTOMÁTICO ---\\

int settearNuevoLegajo()
{

    int nuevoLegajo = 0;


    nuevoLegajo = contarLegajos(vecNombresFiles, vecTamObjetos) + 1;

    return nuevoLegajo;

}


int contarLegajos(const char* vecNombresFiles[], int vecTamObjetos[])
{
    int legajosTotales = 0;
    FILE* pFile = nullptr;

    for(x = 0; x < CANTIDADOBJETOS; x++)
    {
        if(!(pFile = fopen(vecNombresFiles[x], "rb+")))
        {
            if (!(pFile = fopen(vecNombresFiles[x], "wb+")))
            {
                cout << endl << "---- ERROR AL ABRIR O CREAR EL ARCHIVO ----" << endl;
                return 0;
            }
        }

        fseek(pFile, 0, SEEK_END);
        legajosTotales += ftell(pFile) / vecTamObjetos[x];
        fseek(pFile, 0, SEEK_SET);
        fclose(pFile);
    }

    return legajosTotales;

}

///--- VALIDAR EXISTENCIA DE USUARIOS ---\\

bool usuariosCargados()
{
    return contarLegajos(vecNombresFiles, vecTamObjetos) == 0 ? false : true;
}

bool usuariosEspecificosCargados(string Rol, const char* vecNombresFiles[], int vecTamObjetos[], string vecNombresRoles[])
{
    int usuariosEspecificos = 0;
    bool existe = true;
    FILE* pFile = nullptr;

    for(x = 0; x < CANTIDADOBJETOS; x++)
    {
        if(Rol == vecNombresRoles[x])
        {
            if(!(pFile = fopen(vecNombresFiles[x], "rb+")))
            {
                cout << endl << "No encontró el archivo" << endl;
                if (!(pFile = fopen(vecNombresFiles[x], "wb+")))
                {
                    cout << endl << "---- ERROR AL ABRIR O CREAR EL ARCHIVO ----" << endl;
                    return false;
                }
            }

            fseek(pFile, 0, SEEK_END);
            usuariosEspecificos += ftell(pFile) / vecTamObjetos[x];
            fseek(pFile, 0, SEEK_SET);
            fclose(pFile);

            if(usuariosEspecificos == 0)
            {
                existe = false;
                return existe;
            }

            return existe;
        }
    }
}

void mensajeUsuariosNoEncontrados(string Rol)
{
    cout << endl << "---- ERROR: NO SE ENCONTRARON USUARIOS CON ROL '" << Rol << "' CARGADOS EN EL SISTEMA ----" << endl << endl;
    cout << endl << endl;
    system("pause");
    system("cls");

    rol = seleccionarRol(rol);
}

///--- LOGIN ROLES ---\\

void login(int rol, string Rol)
{
    setlocale(LC_ALL, "Spanish");

    cout << Rol << ": INICIO DE SESIÓN (Nro. de Legajo 0 para salir)" << endl;
    cout << endl << endl << "\t - Legajo: ";
    cin >> legajo;

    if(legajo == 0)
    {
        system("cls");
        menuPrincipal();
    }
    if(!usuarioValido(Rol, legajo, vecNombresFiles, vecTamObjetos, vecNombresRoles))
    {
        cout << endl << "---- ERROR: NO SE ENCONTRÓ UN USUARIO " << Rol << " CON LEGAJO '" << legajo << "' CARGADO EN EL SISTEMA ----" << endl << endl;
        cout << endl << endl;
        system("pause");
        system("cls");
        login(rol, Rol);
    }

    cout << endl << "\t - Contraseña (numérica): ";
    cin >> clave;
    if(!claveValida(Rol, legajo, clave, vecNombresFiles, vecTamObjetos, vecNombresRoles))
    {
        cout << endl << "---- ERROR: CONTRASEÑA INCORRECTA ----" << endl << endl;
        cout << endl << endl;
        system("pause");
        system("cls");
        login(rol, Rol);
    }

    if(!estadoValido(Rol, legajo, vecNombresFiles, vecTamObjetos, vecNombresRoles))
    {
        cout << endl << "---- ERROR: USUARIO INACTIVO ----" << endl << endl;
        cout << endl << endl;
        system("pause");
        system("cls");
        login(rol, Rol);
    }


    switch (rol)
    {
    case 49: //ADMINISTRADOR
        system("cls");
        menuAdministrador();
        break;
    case 50: //DIRECTOR
        system("cls");
        menuDirectivo();
        break;
    case 51: //PROFESOR
        system("cls");
        menuProfesor();
        break;
    case 52: //ALUMNO
        system("cls");
        menuAlumno();
        break;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}

///--- VALIDAR CREDENCIALES LOGIN ---\\

bool usuarioValido(string Rol, int legajo, const char* vecNombresFiles[], int vecTamObjetos[], string vecNombresRoles[])
{
    bool valido = false;
    FILE* pFile = nullptr;

    for(x = 0; x < CANTIDADOBJETOS; x++)
    {
        if(Rol == vecNombresRoles[x])
        {
            if(!(pFile = fopen(vecNombresFiles[x], "rb+")))
            {
                if (!(pFile = fopen(vecNombresFiles[x], "wb+")))
                {
                    cout << endl << "---- ERROR AL ABRIR O CREAR EL ARCHIVO ----" << endl;
                    return false;
                }
            }

            if(Rol == "ADMINISTRADOR")
            {
                Administrador obj;
                while (fread(&obj, vecTamObjetos[x], 1, pFile))
                {
                    if(obj.getId() == legajo)
                        valido = true;
                    return valido;
                }
            }
            else if(Rol == "DIRECTOR")
            {
                Director obj;
                while (fread(&obj, vecTamObjetos[x], 1, pFile))
                {
                    if(obj.getLegajo() == legajo)
                    {
                        valido = true;
                        return valido;
                    }
                }
            }
            else if(Rol == "PROFESOR")
            {
                Profesor obj;
                while (fread(&obj, vecTamObjetos[x], 1, pFile))
                {
                    if(obj.getLegajo() == legajo)
                    {
                        valido = true;
                        return valido;
                    }
                }
            }
            else
            {
                Alumno obj;
                while (fread(&obj, vecTamObjetos[x], 1, pFile))
                {
                    if(obj.getLegajo() == legajo)
                    {
                        valido = true;
                        return valido;
                    }
                }
            }
        }
    }

    return valido;
}

bool claveValida(string Rol, int legajo, int clave, const char* vecNombresFiles[], int vecTamObjetos[], string vecNombresRoles[])
{
    bool valida = false;
    FILE* pFile = nullptr;

    for(x = 0; x < CANTIDADOBJETOS; x++)
    {
        if(Rol == vecNombresRoles[x])
        {
            if(!(pFile = fopen(vecNombresFiles[x], "rb+")))
            {
                if (!(pFile = fopen(vecNombresFiles[x], "wb+")))
                {
                    cout << endl << "---- ERROR AL ABRIR O CREAR EL ARCHIVO ----" << endl;
                    return false;
                }
            }

            if(Rol == "ADMINISTRADOR")
            {
                Administrador obj;
                while (fread(&obj, vecTamObjetos[x], 1, pFile))
                {
                    if(obj.getId() == legajo)
                    {
                        if(obj.getClave() == clave)
                        {
                            valida = true;
                            return valida;
                        }
                    }
                }
            }
            else if(Rol == "DIRECTOR")
            {
                Director obj;
                while (fread(&obj, vecTamObjetos[x], 1, pFile))
                {
                    if(obj.getLegajo() == legajo)
                    {
                        if(obj.getClave() == clave)
                        {
                            valida = true;
                            return valida;
                        }
                    }
                }
            }
            else if(Rol == "PROFESOR")
            {
                Profesor obj;
                while (fread(&obj, vecTamObjetos[x], 1, pFile))
                {
                    if(obj.getLegajo() == legajo)
                    {
                        if(obj.getClave() == clave)
                        {
                            valida = true;
                            return valida;
                        }
                    }
                }
            }
            else
            {
                Alumno obj;
                while (fread(&obj, vecTamObjetos[x], 1, pFile))
                {
                    if(obj.getLegajo() == legajo)
                    {
                        if(obj.getClave() == clave)
                        {
                            valida = true;
                            return valida;
                        }
                    }
                }
            }
        }
    }

    return valida;
}

bool estadoValido(string Rol, int legajo, const char* vecNombresFiles[], int vecTamObjetos[], string vecNombresRoles[])
{
    bool valido = false;
    FILE* pFile = nullptr;

    for(x = 0; x < CANTIDADOBJETOS; x++)
    {
        if(Rol == vecNombresRoles[x])
        {
            if(!(pFile = fopen(vecNombresFiles[x], "rb+")))
            {
                if (!(pFile = fopen(vecNombresFiles[x], "wb+")))
                {
                    cout << endl << "---- ERROR AL ABRIR O CREAR EL ARCHIVO ----" << endl;
                    return false;
                }
            }

            if(Rol == "ADMINISTRADOR")
            {
                Administrador obj;
                while (fread(&obj, vecTamObjetos[x], 1, pFile))
                {
                    if(obj.getId() == legajo)
                        valido = true;
                    return valido;
                }
            }
            else if(Rol == "DIRECTOR")
            {
                Director obj;
                while (fread(&obj, vecTamObjetos[x], 1, pFile))
                {
                    if(obj.getLegajo() == legajo)
                    {
                        if(obj.getEstado() == true)
                        {
                            valido = true;
                            return valido;
                        }
                    }
                }
            }
            else if(Rol == "PROFESOR")
            {
                Profesor obj;
                while (fread(&obj, vecTamObjetos[x], 1, pFile))
                {
                    if(obj.getLegajo() == legajo)
                    {
                        if(obj.getEstado() == true)
                        {
                            valido = true;
                            return valido;
                        }
                    }
                }
            }
            else
            {
                Alumno obj;
                while (fread(&obj, vecTamObjetos[x], 1, pFile))
                {
                    if(obj.getLegajo() == legajo)
                    {
                        if(obj.getEstado() == true)
                        {
                            valido = true;
                            return valido;
                        }
                    }
                }
            }
        }
    }

    return valido;
}

Alumno buscarAlumno(int ID)
{
    Alumno aux;
    int pos=0;

    while (aux.leerEnDiscoAlumnoPorPosicion(pos))
    {
        if (aux.getLegajo() == ID)
        {
            return aux;
        }
        pos++;
    }

}

Materia buscarMateria(int ID)
{
    Materia aux;
    int pos=0;

    while (aux.leerEnDiscoMateriaPorPosicion(pos))
    {
        if (aux.getId() == ID)
        {
            return aux;
        }
        pos++;
    }

}

int buscarInscripcionMateria(int Legajo)
{
    InscripcionMateria aux;
    int pos=0;

    while (aux.leerEnDiscoInscripcionMateriaPorPosicion(pos))
    {
        if(aux.getAlumno().getLegajo()==Legajo)
        {
            return pos;
        }
        pos++;
    }
    cout<<"No Hay inscriciones aun"<<endl;
    system("pause");
    return -1;
}

bool estaAlumnoInscritoEnMateria (int legAlumno, int idMateria)
{
    InscripcionMateria aux;
    int pos=0;

    while (aux.leerEnDiscoInscripcionMateriaPorPosicion(pos))
    {

        if (aux.getAlumno().getLegajo() == legAlumno)
        {
            Materia* materias = aux.getMaterias();  // Obtener el puntero al arreglo de materias
            for (int i = 0; i < 7; i++)
            {


                if (materias[i].getId() == idMateria)
                {
                    return true;

                }

            }
        }
        pos++;
    }


    return false;

}


///--- MENÚS ROLES ---\\

///--- MENÚ ADMINISTRADOR ---\\

void menuAdministrador()
{

    int opcion;
    int legajoDirector;
    int nuevaClave;


    cout << "----------------------------------------------------"<< endl;
    cout << "                 MENÚ ADMINISTRADOR                 "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "1. CREAR PERFIL DIRECTOR                            "<< endl;
    cout << "2. ACTIVAR PERFIL DIRECTOR                          "<< endl;
    cout << "3. DESACTIVAR PERFIL DIRECTOR                       "<< endl;
    cout << "4. GESTION CONTRASEÑAS                              "<< endl;
    cout << "5. CAMBIAR CONTRASEÑA                               "<< endl;
    cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 53 && opcion != 48)
    {
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "----------------------------------------------------"<< endl;
        cout << "                 MENÚ ADMINISTRADOR                 "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "1. CREAR PERFIL DIRECTOR                            "<< endl;
        cout << "2. ACTIVAR PERFIL DIRECTOR                          "<< endl;
        cout << "3. DESACTIVAR PERFIL DIRECTOR                       "<< endl;
        cout << "4. GESTION CONTRASEÑAS                              "<< endl;
        cout << "5. CAMBIAR CONTRASEÑA                               "<< endl;
        cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();

    }

    switch(opcion)
    {
    case 49:
        system("cls");
        directorObj.grabarEnDiscoDirector();
        system("cls");
        menuAdministrador();
        break;
    case 50:
        system("cls");
        cout << "ACTIVANDO PERFIL DIRECTOR" << endl;

        cout << endl << "\t- Legajo: ";
        cin >> legajoDirector;
        validarLegajo(legajoDirector);

        directorObj.activarDirector(legajoDirector);

        system("cls");
        menuAdministrador();
        break;
    case 51:
        system("cls");
        cout << "DESACTIVANDO PERFIL DIRECTOR" << endl;

        cout << endl << "\t- Legajo: ";
        cin >> legajoDirector;
        validarLegajo(legajoDirector);

        directorObj.desactivarDirector(legajoDirector);

        system("cls");
        menuAdministrador();
        break;
    case 52:
        system("cls");
        subMenuAdministradorClaves();
        break;
    case 53:
        system("cls");
        cout << "CAMBIANDO CONTRASEÑA" << endl;

        cout << endl << "\t - Contraseña anterior: " << clave << endl;
        cout << endl << "\t - Contraseña nueva (numérica): ";
        cin >> nuevaClave;

        administradorObj.cambiarClave(legajo, nuevaClave);

        clave = nuevaClave;

        system("cls");
        menuAdministrador();
        break;
    case 48:
        system("cls");
        cout << "VOLVIENDO AL MENÚ PRINCIPAL..." << endl;
        Sleep(2000);
        system("cls");
        menuPrincipal();
        break;
    default:
        cout << "OPCIÓN no válida." << endl;
    }

}

void subMenuAdministradorClaves() {
    int opcion;
    int legajoAux = -1;

    cout << "----------------------------------------------------"<< endl;
    cout << "                  MENÚ CONTRASEÑAS                  "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "1. BLANQUEAR CONTRASEÑA DIRECTOR                    "<< endl;
    cout << "2. BLANQUEAR CONTRASEÑA PROFESOR                    "<< endl;
    cout << "3. BLANQUEAR CONTRASEÑA ALUMNO                      "<< endl;
    cout << "0. VOLVER AL MENÚ ADMINISTRADOR                     "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 48)
    {
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "----------------------------------------------------"<< endl;
        cout << "                  MENÚ CONTRASEÑAS                  "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "1. BLANQUEAR CONTRASEÑA DIRECTOR                    "<< endl;
        cout << "2. BLANQUEAR CONTRASEÑA PROFESOR                    "<< endl;
        cout << "3. BLANQUEAR CONTRASEÑA ALUMNO                      "<< endl;
        cout << "0. VOLVER AL MENÚ ADMINISTRADOR                     "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();

    }

    switch(opcion)
    {
    case 49:
        system("cls");
        cout << "BLANQUEANDO CONTRASEÑA PERFIL DIRECTOR" << endl << endl;

        cout << "AVISO: Al blanquear la contraseña, la misma se establecerá" << endl;
        cout << "       como el número de legajo del usuario." << endl << endl;

        cout << endl << "\t - Legajo Director : ";
        cin >> legajoAux;
        directorObj.cambiarClave(legajoAux, legajoAux);

        system("cls");
        subMenuAdministradorClaves();
        break;
    case 50:
        system("cls");
        cout << "BLANQUEANDO CONTRASEÑA PERFIL PROFESOR" << endl << endl;

        cout << "AVISO: Al blanquear la contraseña, la misma se establecerá" << endl;
        cout << "       como el número de legajo del usuario." << endl << endl;

        cout << endl << "\t - Legajo Profesor : ";
        cin >> legajoAux;
        profesorObj.cambiarClave(legajoAux, legajoAux);

        system("cls");
        subMenuAdministradorClaves();
        break;
    case 51:
        system("cls");
        cout << "BLANQUEANDO CONTRASEÑA PERFIL ALUMNO" << endl << endl;

        cout << "AVISO: Al blanquear la contraseña, la misma se establecerá" << endl;
        cout << "       como el número de legajo del usuario." << endl << endl;

        cout << endl << "\t - Legajo Alumno : ";
        cin >> legajoAux;
        alumnoObj.cambiarClave(legajoAux, legajoAux);

        system("cls");
        subMenuAdministradorClaves();
        break;
    case 48:
        system("cls");
        cout << "VOLVIENDO AL MENÚ ADMINISTRADOR..." << endl;
        Sleep(2000);
        system("cls");
        menuAdministrador();
        break;
    default:
        cout << "OPCIÓN no válida." << endl;
    }
}

///--- MENÚ DIRECTIVO ---\\

void menuDirectivo()
{
    int opcion;
    int legajoDirector;
    int nuevaClave;

    cout << "----------------------------------------------------"<< endl;
    cout << "                   MENÚ DIRECTIVO                   "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "1. GESTIÓN PERFIL PROFESOR                          "<< endl;
    cout << "2. GESTIÓN PERFIL ALUMNO                            "<< endl;
    cout << "3. GESTIÓN PLAN DE ESTUDIO                          "<< endl;
    cout << "4. GESTIÓN AVISOS                                   "<< endl;
    cout << "5. CAMBIAR CONTRASEÑA                               "<< endl;
    cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 53 && opcion != 48)
    {
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "----------------------------------------------------"<< endl;
        cout << "                   MENÚ DIRECTIVO                   "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "1. GESTIÓN PERFIL PROFESOR                          "<< endl;
        cout << "2. GESTIÓN PERFIL ALUMNO                            "<< endl;
        cout << "3. GESTIÓN PLAN DE ESTUDIO                          "<< endl;
        cout << "4. GESTIÓN AVISOS                                   "<< endl;
        cout << "5. CAMBIAR CONTRASEÑA                               "<< endl;
        cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();

    }

    switch(opcion)
    {
    case 49:
        system("cls");
        subMenuDirectivoProfesor();
        break;
    case 50:
        system("cls");
        subMenuDirectivoAlumno();
        break;
    case 51:
        system("cls");
        subMenuDirectivoPlanEstudio();
        break;
    case 52:
        //FALTA HACER LA CLASE AVISOS
        system("cls");
        menuDirectivo();
        break;
    case 53:
        system("cls");
        cout << "CAMBIANDO CONTRASEÑA" << endl;

        cout << endl << "\t - Contraseña anterior: " << clave << endl;
        cout << endl << "\t - Contraseña nueva (numérica): ";
        cin >> nuevaClave;

        directorObj.cambiarClave(legajo, nuevaClave);

        clave = nuevaClave;

        system("cls");
        menuDirectivo();
        break;
    case 48:
        system("cls");
        cout << "VOLVIENDO AL MENÚ PRINCIPAL..." << endl;
        Sleep(2000);
        system("cls");
        menuPrincipal();
        break;
    default:
        cout << "OPCIÓN no válida." << endl;
    }
}

void subMenuDirectivoProfesor()
{
    int opcion;
    int legajoProfesor;
    int nuevaClave;

    cout << "----------------------------------------------------"<< endl;
    cout << "                  GESTIÓN PROFESOR                  "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "1. CREAR PERFIL PROFESOR                            "<< endl;
    cout << "2. ACTIVAR PERFIL PROFESOR                          "<< endl;
    cout << "3. DESACTIVAR PERFIL PROFESOR                       "<< endl;
    cout << "0. VOLVER AL MENÚ DIRECTIVO                         "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 48)
    {
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "----------------------------------------------------"<< endl;
        cout << "                  GESTIÓN PROFESOR                  "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "1. CREAR PERFIL PROFESOR                            "<< endl;
        cout << "2. ACTIVAR PERFIL PROFESOR                          "<< endl;
        cout << "3. DESACTIVAR PERFIL PROFESOR                       "<< endl;
        cout << "0. VOLVER AL MENÚ DIRECTIVO                         "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();
    }

    switch(opcion)
    {
    case 49:
        system("cls");
        profesorObj.grabarEnDiscoProfesor();
        system("cls");
        subMenuDirectivoProfesor();
        break;
    case 50:
        system("cls");
        cout << "ACTIVANDO PERFIL PROFESOR" << endl;

        cout << endl << "\t- Legajo: ";
        cin >> legajoProfesor;
        validarLegajo(legajoProfesor);

        profesorObj.activarProfesor(legajoProfesor);

        system("cls");
        subMenuDirectivoProfesor();
        break;
    case 51:
        system("cls");
        cout << "DESACTIVANDO PERFIL PROFESOR" << endl;

        cout << endl << "\t- Legajo: ";
        cin >> legajoProfesor;
        validarLegajo(legajoProfesor);

        profesorObj.desactivarProfesor(legajoProfesor);

        system("cls");
        subMenuDirectivoProfesor();
        break;
    case 48:
        system("cls");
        cout << "VOLVIENDO AL MENÚ DIRECTIVO..." << endl;
        Sleep(2000);
        system("cls");
        menuDirectivo();
        break;
    default:
        cout << "OPCIÓN no válida." << endl;
    }

}

void subMenuDirectivoAlumno()
{
    int opcion;
    int legajoAlumno;
    int nuevaClave;

    cout << "----------------------------------------------------"<< endl;
    cout << "                   GESTIÓN ALUMNO                   "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "1. CREAR PERFIL ALUMNO                              "<< endl;
    cout << "2. ACTIVAR PERFIL ALUMNO                            "<< endl;
    cout << "3. DESACTIVAR PERFIL ALUMNO                         "<< endl;
    cout << "0. VOLVER AL MENÚ DIRECTIVO                         "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;


    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 48)
    {
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "----------------------------------------------------"<< endl;
        cout << "                   GESTIÓN ALUMNO                   "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "1. CREAR PERFIL ALUMNO                              "<< endl;
        cout << "2. ACTIVAR PERFIL ALUMNO                            "<< endl;
        cout << "3. DESACTIVAR PERFIL ALUMNO                         "<< endl;
        cout << "0. VOLVER AL MENÚ DIRECTIVO                         "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();
    }

    switch(opcion)
    {
    case 49:
        system("cls");
        alumnoObj.grabarEnDiscoAlumno();
        system("cls");
        subMenuDirectivoAlumno();
        break;
    case 50:
        system("cls");
        cout << "ACTIVANDO PERFIL ALUMNO" << endl;

        cout << endl << "\t- Legajo: ";
        cin >> legajoAlumno;
        validarLegajo(legajoAlumno);

        alumnoObj.activarAlumno(legajoAlumno);

        system("cls");
        subMenuDirectivoAlumno();
        break;
    case 51:
        system("cls");
        cout << "DESACTIVANDO PERFIL ALUMNO" << endl;

        cout << endl << "\t- Legajo: ";
        cin >> legajoAlumno;
        validarLegajo(legajoAlumno);

        alumnoObj.desactivarAlumno(legajoAlumno);

        system("cls");
        subMenuDirectivoAlumno();
        break;
    case 48:
        system("cls");
        cout << "VOLVIENDO AL MENÚ DIRECTIVO..." << endl;
        Sleep(2000);
        system("cls");
        menuDirectivo();
        break;
    default:
        cout << "OPCIÓN no válida." << endl;
    }
}

void subMenuDirectivoPlanEstudio()
{
    int opcion;
    int cantMaterias;
    Materia materiaObj;

    cout << "----------------------------------------------------"<< endl;
    cout << "               GESTIÓN PLAN DE ESTUDIO              "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "1. CARGAR MATERIAS                                  "<< endl;
    cout << "2. ASIGNAR CORRELATIVAS                             "<< endl;
    cout << "3. ASIGNAR PROFESORES                               "<< endl;
    cout << "4. VER PLAN DE ESTUDIO                              "<< endl;
    cout << "0. VOLVER AL MENÚ DIRECTIVO                         "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;


    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 48)
    {
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "----------------------------------------------------"<< endl;
        cout << "               GESTIÓN PLAN DE ESTUDIO              "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "1. CARGAR MATERIAS                                  "<< endl;
        cout << "2. ASIGNAR CORRELATIVAS                             "<< endl;
        cout << "3. ASIGNAR PROFESORES                               "<< endl;
        cout << "4. VER PLAN DE ESTUDIO                              "<< endl;
        cout << "0. VOLVER AL MENÚ DIRECTIVO                         "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();
    }

    switch(opcion)
    {
    case 49:
        system("cls");

        cout << "CARGANDO MATERIAS - PLAN DE ESTUDIO 2003" << endl;

        if(contarMaterias() < 21)
        {
            cout << endl << "\t- Cantidad de materias a cargar: ";
            cin >> cantMaterias;

            while(cantMaterias > 21 || cantMaterias > (21 - contarMaterias()) || cantMaterias <= 0)
            {
                cout << endl <<"---- ERROR: CANTIDAD DISPONIBLE: " << (21 - contarMaterias()) << " ----" << endl;
                Sleep(1500);
                system("cls");

                cout << "CARGANDO MATERIAS - PLAN DE ESTUDIO 2003" << endl;

                cout << endl << "\t- Cantidad de materias a cargar: ";
                cin >> cantMaterias;
            }


            for(int x = 0; x < cantMaterias; x++)
            {
                system("cls");
                cout << "CARGANDO MATERIAS - PLAN DE ESTUDIO 2003" << endl;
                materiaObj.grabarEnDiscoMateria();
            }

        }
        else
        {
            cout << endl <<"---- LÍMITE DE MATERIAS CARGADAS ALCANZADO ----" << endl;
            cout << endl << endl;
            system("pause");
        }

        system("cls");
        subMenuDirectivoPlanEstudio();
        break;
    case 50:
        system("cls");
        /// --> FUNCIÓN MATERIAS CORRELATIVAS
        system("cls");
        subMenuDirectivoPlanEstudio();
        break;
    case 51:
        system("cls");

        cout << "ASIGNANDO PROFESORES - PLAN DE ESTUDIO 2003" << endl;

        if(!usuariosEspecificosCargados("PROFESOR", vecNombresFiles, vecTamObjetos, vecNombresRoles))
        {
            cout << endl << "---- ERROR: NO SE ENCONTRARON USUARIOS CON ROL 'PROFESOR' CARGADOS EN EL SISTEMA ----" << endl << endl;
            cout << endl << endl;
            system("pause");
            system("cls");
        }
        else
        {
            if(contarMaterias() < 21)
            {
                cout << endl << "---- ERROR: PLAN DE ESTUDIOS INCOMPLETO, " << 21 - contarMaterias() << " MATERIAS RESTANTES POR CARGAR ----" << endl << endl;
                cout << endl << endl;
                system("pause");
                system("cls");
            }
            else
            {
                asignarProfesores();
            }
        }


        system("cls");
        subMenuDirectivoPlanEstudio();
        break;
    case 52:
        system("cls");

        if(contarMaterias() > 0)
        {
            cout << "PLAN DE ESTUDIO 2003" << endl << endl;
            mostrarPlanEstudio();
            system("pause");
        }
        else
        {
            cout << endl << "---- ERROR: NO SE ENCONTRARON MATERIAS CARGADAS EN EL SISTEMA ----" << endl << endl;
            cout << endl << endl;
            system("pause");
            system("cls");
        }

        system("cls");
        subMenuDirectivoPlanEstudio();
        break;
    case 48:
        system("cls");
        cout << "VOLVIENDO AL MENÚ DIRECTIVO..." << endl;
        Sleep(2000);
        system("cls");
        menuDirectivo();
        break;
    default:
        cout << "OPCIÓN no válida." << endl;
    }
}

int contarMaterias()
{
    FILE *pMat;
    int cantMaterias = 0;

    if(!(pMat = fopen("materias.dat", "ab")))
    {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return -1;
    }

    fseek(pMat, 0, SEEK_END);
    cantMaterias += ftell(pMat) / sizeof(Materia);
    fseek(pMat, 0, SEEK_SET);
    fclose(pMat);

    return cantMaterias;
}

void asignarProfesores()
{
    int legajoProfesor;

    FILE *pMat;
    Materia materiaObj;

    Profesor profesorObj;
    FILE *pProfesor;

    if (!(pMat = fopen("materias.dat", "rb+")))
    {
        cout << endl << "--- NO SE ENCONTRARON REGISTROS DE MATERIAS ----" << endl;
        return;
    }

    while (fread(&materiaObj, sizeof(Materia), 1, pMat))
    {
        if (materiaObj.getLegajoProfesor() != -1)
        {
            continue;
        }

        bool valido = false;

        while (!valido)
        {
            if (!(pProfesor = fopen("profesores.dat", "rb")))
            {
                system("cls");
                cout << endl << "---- ERROR AL ABRIR EL ARCHIVO DE PROFESORES ----" << endl;
                fclose(pMat);
                return;
            }


            cout << endl << "\t - Materia: " << materiaObj.getNombreMateria();
            cout << endl << "\t - Legajo Profesor: ";
            cin >> legajoProfesor;

            while (fread(&profesorObj, sizeof(Profesor), 1, pProfesor))
            {
                if (profesorObj.getLegajo() == legajoProfesor)
                {
                    valido = true;
                    break;
                }
            }
            fclose(pProfesor);

            if (!valido)
            {
                cout << endl << "---- ERROR: NO SE ENCONTRÓ UN PROFESOR CON LEGAJO '" << legajoProfesor << "' CARGADO EN EL SISTEMA ----" << endl;
            }
        }

        materiaObj.setLegajoProfesor(legajoProfesor);
        long offset = ftell(pMat) - sizeof(Materia);
        fseek(pMat, offset, SEEK_SET);
        fwrite(&materiaObj, sizeof(Materia), 1, pMat);
        fflush(pMat);

        fseek(pMat, offset + sizeof(Materia), SEEK_SET);

    }

    fclose(pMat);
    system("pause");
}

void mostrarPlanEstudio()
{
    FILE *pMat;
    Materia materiaObj;
    int anchoID = 6;
    int anchoMateria = 21;
    int anchoProfesor = 16;


    if(!(pMat = fopen("materias.dat", "rb")))
    {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return ;
    }

    cout << left << setw(anchoID) << "ID";
    cout << "|";
    cout << left << setw(anchoMateria) << "Materia";
    cout << "|";
    cout << left << setw(anchoProfesor) << "Legajo Profesor" << endl;

    cout << string(anchoID, '-') << "+" << string(anchoMateria, '-') << "+" << string(anchoProfesor, '-') << endl;

    while(fread(&materiaObj, sizeof(Materia), 1, pMat))
    {
        cout << left << setw(anchoID) << materiaObj.getId() << "|" << left << setw(anchoMateria) << materiaObj.getNombreMateria() << "|" << left << setw(anchoProfesor) << (materiaObj.getLegajoProfesor() == -1? "No Asignado" : to_string(materiaObj.getLegajoProfesor())) << endl;
    }

    cout << endl << endl;

    fclose(pMat);
}

///--- MENÚ PROFESOR ---\\

void menuProfesor()
{
    int opcion;
    int nuevaClave;

    cout << "----------------------------------------------------"<< endl;
    cout << "                   MENÚ PROFESOR                    "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "1. GESTIÓN MATERIAS                                 "<< endl;
    cout << "2. VER AVISOS                                       "<< endl;
    cout << "3. CAMBIAR CONTRASEÑA                               "<< endl;
    cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 48)
    {
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "----------------------------------------------------"<< endl;
        cout << "                   MENÚ PROFESOR                    "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "1. GESTIÓN MATERIAS                                 "<< endl;
        cout << "2. VER AVISOS                                       "<< endl;
        cout << "3. CAMBIAR CONTRASEÑA                               "<< endl;
        cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();

    }

    switch(opcion)
    {
    case 49:
        system("cls");
        ///-- >> SUB MENÚ GESTIÓN MATERIAS
        subMenuProfesorGestionMaterias();
        break;
    case 50:
        system("cls");
        ///-- >> VER AVISOS

        system("cls");
        menuProfesor();
        break;
    case 51:
        system("cls");
        cout << "CAMBIANDO CONTRASEÑA" << endl;

        cout << endl << "\t - Contraseña anterior: " << clave << endl;
        cout << endl << "\t - Contraseña nueva (numérica): ";
        cin >> nuevaClave;

        profesorObj.cambiarClave(legajo, nuevaClave);

        clave = nuevaClave;

        system("cls");
        menuProfesor();
        break;
    case 48:
        system("cls");
        cout << "VOLVIENDO AL MENÚ PRINCIPAL..." << endl;
        Sleep(2000);
        system("cls");
        menuPrincipal();
        break;
    default:
        cout << "OPCIÓN no válida." << endl;
    }
}


void subMenuProfesorGestionMaterias()
{
    int opcion;
    Evaluacion evaluacionObj;

    cout << "----------------------------------------------------"<< endl;
    cout << "                  GESTIÓN MATERIAS                  "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "1. VER MATERIAS ASIGNADAS                           "<< endl;
    cout << "2. CREAR EXAMEN FINAL                               "<< endl;
    cout << "3. VER EXAMENES FINALES                             "<< endl;
    cout << "4. CARGAR NOTAS                                     "<< endl;
    cout << "5. MODIFICAR NOTAS                                  "<< endl;
    cout << "0. VOLVER AL MENÚ PROFESOR                          "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;

    opcion = _getch();


    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 53 &&  opcion != 48)
    {
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "----------------------------------------------------"<< endl;
        cout << "                  GESTIÓN MATERIAS                  "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "1. VER MATERIAS ASIGNADAS                           "<< endl;
        cout << "2. CREAR EXAMEN FINAL                               "<< endl;
        cout << "3. VER EXAMENES FINALES                             "<< endl;
        cout << "4. CARGAR NOTAS                                     "<< endl;
        cout << "5. MODIFICAR NOTAS                                  "<< endl;
        cout << "0. VOLVER AL MENÚ PROFESOR                          "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();

    }

    switch(opcion)
    {
    case 49:
        system("cls");

        cout << "MOSTRANDO MATERIAS ASIGNADAS - PLAN DE ESTUDIO 2003" << endl << endl;

        verMateriasAsignadas();
        system("pause");

        system("cls");
        subMenuProfesorGestionMaterias();
        break;
    case 50:
        system("cls");

        if(MateriasAsignadas()){
            evaluacionObj.grabarEnDisco(legajo);
        }
        system("pause");

        system("cls");
        subMenuProfesorGestionMaterias();
        break;
    case 51:
        system("cls");
        cout << "MOSTRANDO EXAMENES FINALES" << endl << endl;

        verExamenesFinalesProfesor();
        system("pause");

        system("cls");
        subMenuProfesorGestionMaterias();
        break;
    case 52:
        system("cls");
        ///-- >> CARGAR NOTAS

        system("cls");
        subMenuProfesorGestionMaterias();
        break;
    case 53:
        system("cls");
        ///-- >> MODIFICAR NOTAS

        system("cls");
        subMenuProfesorGestionMaterias();
        break;
    case 48:
        system("cls");
        cout << "VOLVIENDO AL MENÚ PROFESOR..." << endl;
        Sleep(2000);
        system("cls");
        menuProfesor();
        break;
    default:
        cout << "OPCIÓN no válida." << endl;
    }
}

bool MateriasAsignadas()
{
    FILE *pMat;
    Materia materiaObj;


    if(!(pMat = fopen("materias.dat", "rb")))
    {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return false;
    }


    while(fread(&materiaObj, sizeof(Materia), 1, pMat))
    {
        if(materiaObj.getLegajoProfesor() == legajo)
        {
            return true;
        }
        //ESTO VA A QUEDAR ASÍ CON EL CAMBIO DE PROPIEDAD EN LA CLASE MATERIA:
        /*if((materiaObj.getProfesor()).getLegajo() == legajo){
            cout << left << setw(anchoID) << materiaObj.getId() << "|" << left << setw(anchoMateria) << materiaObj.getNombreMateria() << endl;
        }*/
    }

    fclose(pMat);
    cout << endl << "---- ERROR : EL PROFESOR CON LEGAJO " << legajo << " NO POSEE MATERIAS ASIGNADAS PARA CREAR EXAMENES FINALES ----" << endl << endl;

    return false;
}

void verMateriasAsignadas()
{
    FILE *pMat;
    Materia materiaObj;
    int anchoID = 6;
    int anchoMateria = 16;

    if(!(pMat = fopen("materias.dat", "rb")))
    {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return ;
    }

    cout << left << setw(anchoID) << "ID";
    cout << "|";
    cout << left << setw(anchoMateria) << "Materia" << endl;

    cout << string(anchoID, '-') << "+" << string(anchoMateria, '-') << endl;

    while(fread(&materiaObj, sizeof(Materia), 1, pMat))
    {
        if(materiaObj.getLegajoProfesor() == legajo)
        {
            cout << left << setw(anchoID) << materiaObj.getId() << "|" << left << setw(anchoMateria) << materiaObj.getNombreMateria() << endl;
        }
        //ESTO VA A QUEDAR ASÍ CON EL CAMBIO DE PROPIEDAD EN LA CLASE MATERIA:
        /*if((materiaObj.getProfesor()).getLegajo() == legajo){
            cout << left << setw(anchoID) << materiaObj.getId() << "|" << left << setw(anchoMateria) << materiaObj.getNombreMateria() << endl;
        }*/
    }

    cout << endl << endl;

    fclose(pMat);
}

void verExamenesFinalesProfesor()
{
    FILE *pEval;
    Evaluacion evaluacionObj;

    FILE *pMat;
    Materia materiaObj;

    time_t t = time(nullptr);
    tm* now = localtime(&t);
    time_t currentTime = mktime(now);


    int anchoID = 9;
    int anchoMateria = 8;
    int anchoFecha = 12;

    if(!(pEval = fopen("evaluaciones.dat", "rb")))
    {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return ;
    }

    cout << left << setw(anchoFecha) << "Fecha";
    cout << "|";
    cout << left << setw(anchoID) << "ID Final";
    cout << "|";
    cout << left << setw(anchoMateria) << "Materia" << endl;

    cout << string(anchoFecha, '-') << "+" << string(anchoID, '-') << "+" << string(anchoMateria, '-') << endl;

    while(fread(&evaluacionObj, sizeof(Evaluacion), 1, pEval))
    {

        if(!(pMat = fopen("materias.dat", "rb")))
        {
            cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
            return ;
        }
        while(fread(&materiaObj, sizeof(Materia), 1, pMat))
        {
            if(materiaObj.getLegajoProfesor() == legajo && evaluacionObj.getIdMateria() == materiaObj.getId())
            {
                break;
            }
        }

        tm specificDate = evaluacionObj.createDate(evaluacionObj.getFecha().getDia(), evaluacionObj.getFecha().getMes(), evaluacionObj.getFecha().getAnio());
        time_t specificTime = mktime(&specificDate);

        if(difftime(specificTime, currentTime) > 0)
        {
            if(evaluacionObj.getIdProfesor() == legajo )
            {
                cout << left << setw(anchoFecha) << evaluacionObj.getFecha().toString("DD/MM/YYYY") << "|" << left << setw(anchoID) << evaluacionObj.getId() << "|" << left << setw(anchoMateria) << materiaObj.getNombreMateria() << endl;
            }
        }
        fclose(pMat);
    }

    cout << endl << endl;

    fclose(pEval);
}

///--- MENÚ ALUMNO ---\\

void menuAlumno()
{
    int opcion;
    int nuevaClave;

    CARGANDO();
    cout << "----------------------------------------------------"<< endl;
    cout << "                    MENÚ ALUMNO                     "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "1. GESTIÓN CURSADA                                  "<< endl;
    cout << "2. VER PLAN DE ESTUDIO                              "<< endl;
    cout << "3. VER AVISOS                                       "<< endl;
    cout << "4. CAMBIAR CONTRASEÑA                               "<< endl;
    cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion !=52 && opcion != 48)
    {
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "----------------------------------------------------"<< endl;
        cout << "                    MENÚ ALUMNO                     "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "1. GESTIÓN CURSADA                                  "<< endl;
        cout << "2. VER PLAN DE ESTUDIO                              "<< endl;
        cout << "3. VER AVISOS                                       "<< endl;
        cout << "4. CAMBIAR CONTRASEÑA                               "<< endl;
        cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();

    }

    switch(opcion)
    {
    case 49:
        system("cls");
        subMenuAlumnoPlanificacionCursada();
        menuAlumno();
        break;
    case 50:
        system("cls");
        if(contarMaterias() > 0)
        {
            cout << "PLAN DE ESTUDIO 2003" << endl << endl;
            mostrarPlanEstudio();
            system("pause");
        }
        else
        {
            cout << endl << "---- ERROR: NO SE ENCONTRARON MATERIAS CARGADAS EN EL SISTEMA ----" << endl << endl;
            cout << endl << endl;
            system("pause");
            system("cls");
        }

        menuAlumno();
        break;
    case 51:
        system("cls");
        ///-- >> FUNCION VER AVISOS

        menuAlumno();
        break;
    case 52:
        system("cls");
        cout << "CAMBIANDO CONTRASEÑA" << endl;

        cout << endl << "\t - Contraseña anterior: " << clave << endl;
        cout << endl << "\t - Contraseña nueva (numérica): ";
        cin >> nuevaClave;

        alumnoObj.cambiarClave(legajo, nuevaClave);
        menuAlumno();
        break;
    case 48:
        system("cls");
        cout << "VOLVIENDO AL MENÚ PRINCIPAL..." << endl;
        Sleep(2000);
        system("cls");
        menuPrincipal();
        break;
    default:
        cout << "OPCIÓN no válida." << endl;
    }
}

void validarLegajo(int legajo)
{

    while(legajo < 0 || cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "\t---- ERROR : LEGAJO INVÁLIDO ----" << endl;
        cout << endl << "\t - Legajo: ";
        cin >> legajo;
    }
}

bool validarMateria(int ID)
{
    Materia aux;
    int posicion = 0;

    while (aux.leerEnDiscoMateriaPorPosicion(posicion))
    {
        if (aux.getId() == ID)
        {
            return true;
        }
        posicion++;
    }

    return false;

}

void subMenuAlumnoPlanificacionCursada()
{
    int opcion;

    CARGANDO();
    cout << "-----------------------------------------------------"<< endl;
    cout << "               MENÚ PLANIFICAR CURSADA               "<< endl;
    cout << "-----------------------------------------------------"<< endl;
    cout << "1. VER PLANIFICACION                                 "<< endl;
    cout << "2. ANOTARSE A MATERIAS                               "<< endl;
    cout << "3. DARSE DE BAJA A MATERIAS                          "<< endl;
    cout << "4. ANOTARSE A EXAMEN FINAL                           "<< endl;
    cout << "5. VER EXAMENES FINALES INSCRIPTO                    "<< endl;
    cout << "0. VOLVER AL MENÚ ALUMNO                             "<< endl;
    cout << "-----------------------------------------------------"<< endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -              "<< endl;
    cout << "-----------------------------------------------------"<< endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 53 && opcion != 48)
    {
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "-----------------------------------------------------"<< endl;
        cout << "               MENÚ PLANIFICAR CURSADA               "<< endl;
        cout << "-----------------------------------------------------"<< endl;
        cout << "1. VER PLANIFICACION                                 "<< endl;
        cout << "2. ANOTARSE A MATERIAS                               "<< endl;
        cout << "3. DARSE DE BAJA A MATERIAS                          "<< endl;
        cout << "4. ANOTARSE A EXAMEN FINAL                           "<< endl;
        cout << "5. VER EXAMENES FINALES INSCRIPTO                    "<< endl;
        cout << "0. VOLVER AL MENÚ ALUMNO                             "<< endl;
        cout << "-----------------------------------------------------"<< endl;
        cout << "             - SELECCIONE UNA OPCIÓN: -              "<< endl;
        cout << "-----------------------------------------------------"<< endl;

        opcion = _getch();

    }

    switch(opcion)
    {
    case 49: ///VER PLANIF
        system("cls");

        if(inscriptoMaterias()) {
            inscripcionMateriaObj.mostrarRegistroDeIncriccionesMateria(legajo);
        }
        else {
            cout << endl << "---- ERROR : EL ALUMNO CON LEGAJO " << legajo << " NO SE ENCUENTRA INSCRIPTO A MATERIAS ----" << endl << endl;
            cout << endl << endl;
            system("pause");
            system("cls");
        }

        subMenuAlumnoPlanificacionCursada();
        break;
    case 50: ///ANOTARSE A MATERIAS
        system("cls");
        if(contarMaterias() > 0)
        {
            inscripcionMateriaObj.inscribirseMateria(legajo);
        }
        else
        {
            cout << endl << "---- ERROR: NO SE ENCONTRARON MATERIAS CARGADAS EN EL SISTEMA ----" << endl << endl;
            cout << endl << endl;
            system("pause");
            system("cls");
        }

        subMenuAlumnoPlanificacionCursada();
        break;
    case 51: ///DARSE DE BAJA A MATERIAS
        system("cls");

        if(inscriptoMaterias()) {

            inscripcionMateriaObj.DarseDeBajaMateria(legajo);
        }
        else{
            cout << endl << "---- ERROR : EL ALUMNO CON LEGAJO " << legajo << " NO SE ENCUENTRA INSCRIPTO A MATERIAS ----" << endl << endl;
            cout << endl << endl;
            system("pause");
            system("cls");
        }

        subMenuAlumnoPlanificacionCursada();
        break;
    case 52: ///INSCRIBIRSE A FINALES
        system("cls");

        subMenuAlumnoPlanificacionCursada();
        break;
    case 53: /// VER FINALES INSCRIPTO
        system("cls");

        // Hay que recorrer el archivo.dat que genere la clase InscripcionEvaluacion, validar si en algun registro coincide
        // el legajo del alumno del registro, con el del alumno actual y mostrar el registro si corresponde.

        subMenuAlumnoPlanificacionCursada();
        break;
    case 48:
        system("cls");
        cout << "VOLVIENDO AL MENÚ ALUMNO..." << endl;
        Sleep(2000);
        system("cls");
        menuAlumno();
        break;
    default:
        cout << "OPCIÓN no válida." << endl;
    }
}


bool inscriptoMaterias()
{
    FILE *pInscMat;
    InscripcionMateria inscripcionObj;


    if(!(pInscMat = fopen("InscripcionMateria.dat", "rb")))
    {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        system("cls");
        return false;
    }

    while(fread(&inscripcionObj, sizeof(InscripcionMateria), 1, pInscMat))
    {
        if(inscripcionObj.getAlumno().getLegajo() == legajo)
        {
            return true;
        }
    }

    fclose(pInscMat);
    return false;
}

void CARGANDO()
{
    system("cls");
    cout<<"CARGANDO";
    Sleep(300);
    cout<<".";
    Sleep(300);
    cout<<".";
    Sleep(300);
    cout<<".";
    Sleep(300);
    cout<<".";
    system("cls");

}

