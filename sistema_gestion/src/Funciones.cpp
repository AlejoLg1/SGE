#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <string>
#include <limits>
#include "Funciones.h"
#include "Administrador.h"
#include "Director.h"
#include "Profesor.h"
#include "Alumno.h"
#include "Materia.h"
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
FILE* vecPFiles[CANTIDADOBJETOS] = {pAdm, pDirectivo, pProfesor, pAlumno};
const char* vecNombresFiles[CANTIDADOBJETOS] = {"administradores.dat", "directores.dat", "profesores.dat", "alumnos.dat"};
int vecTamObjetos[CANTIDADOBJETOS] = {sizeof(Administrador), sizeof(Director), sizeof(Profesor), sizeof(Alumno)};
string vecNombresRoles[CANTIDADOBJETOS] = {"ADMINISTRADOR", "DIRECTOR", "PROFESOR", "ALUMNO"};

//OBJETOS
Administrador administradorObj;
Director directorObj;
Profesor profesorObj;
Alumno alumnoObj;

//VARIABLES GLOBALES
int rol;
int x;
int legajo;
int clave;

/*void marco(int y, int x, int ancho, int alto, int color)
{

    setBackgroundColor(BLACK);
    //cls();
    setColor(color);
    int i;
    for(i=x; i<=x+ancho; i++)
    {
        setlocale(LC_ALL, "C");
        gotoxy(i,y);
        printf("\xdB");
        gotoxy(i,y+alto);
        printf("\xdB");
    }


    for(i=y; i<=y+alto; i++)
    {
        setlocale(LC_ALL, "C");
        gotoxy(x,i);
        printf("\xdB");
        gotoxy(x+ancho,i);
        printf("\xdB");
    }
}*/


void menuPrincipal() {
    setlocale(LC_ALL, "Spanish");
    rol = seleccionarRol(rol);

    while(true) {
        //marco(12, 10, 80, 48, 9);
        //setColor(15);
        switch (rol) {
            case 49: //ADMINISTRADOR
                system("cls");
                if(usuariosCargados()){
                    system("cls");
                    login(rol, "ADMINISTRADOR");
                }
                else{
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
                if(usuariosCargados()){
                    if(!usuariosEspecificosCargados("DIRECTOR", vecPFiles, vecNombresFiles, vecTamObjetos, vecNombresRoles)){
                        mensajeUsuariosNoEncontrados("DIRECTOR");
                    }
                    else{
                        system("cls");
                        login(rol, "DIRECTOR");
                    }
                }
                else{
                    mensajeUsuariosNoEncontrados("DIRECTOR");
                }
                break;
            case 51: //PROFESOR
                system("cls");
                if(usuariosCargados()){
                    if(!usuariosEspecificosCargados("PROFESOR", vecPFiles, vecNombresFiles, vecTamObjetos, vecNombresRoles)){
                        mensajeUsuariosNoEncontrados("PROFESOR");
                    }
                    else{
                        system("cls");
                        login(rol, "PROFESOR");
                    }
                }
                else{
                    mensajeUsuariosNoEncontrados("PROFESOR");
                }
                break;
            case 52: // ALUMNO
                system("cls");
                if(usuariosCargados()){
                    if(!usuariosEspecificosCargados("ALUMNO", vecPFiles, vecNombresFiles, vecTamObjetos, vecNombresRoles)){
                        mensajeUsuariosNoEncontrados("ALUMNO");
                    }
                    else{
                        system("cls");
                        login(rol, "ALUMNO");
                    }
                }
                else{
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

int seleccionarRol(int rol) {
    setlocale(LC_ALL, "Spanish");
    /*marco(12, 10, 80, 48, 9);
    setColor(15);
    gotoxy(25,16);cout << "Seleccione su rol correspondiente: " << endl;
    gotoxy(25,17);cout << "1) Administrador";
    gotoxy(25,18);cout << "2) Director";
    gotoxy(25,19);cout << "3) Profesor";
    gotoxy(25,20);cout << "4) Alumno";
    gotoxy(25,21);cout << "5) Salir";
    gotoxy(25,22);cout << endl;*/

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

    while(rol != 49 && rol != 50 && rol != 51 && rol != 52 && rol != 48){
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

int settearNuevoLegajo() {

    int nuevoLegajo = 0;


    nuevoLegajo = contarLegajos(vecPFiles, vecNombresFiles, vecTamObjetos) + 1;

    return nuevoLegajo;

}


int contarLegajos(FILE* vecPFiles[], const char* vecNombresFiles[], int vecTamObjetos[]) {
    int legajosTotales = 0;

    for(x = 0; x < CANTIDADOBJETOS; x++){
        if(!(vecPFiles[x] = fopen(vecNombresFiles[x], "rb+"))) {
            if (!(vecPFiles[x] = fopen(vecNombresFiles[x], "wb+"))) {
                cout << endl << "---- ERROR AL ABRIR O CREAR EL ARCHIVO ----" << endl;
                return 0;
            }
        }

        fseek(vecPFiles[x], 0, SEEK_END);
        legajosTotales += ftell(vecPFiles[x]) / vecTamObjetos[x];
        fseek(vecPFiles[x], 0, SEEK_SET);
        fclose(vecPFiles[x]);
    }

    return legajosTotales;

}

///--- VALIDAR EXISTENCIA DE USUARIOS ---\\

bool usuariosCargados() {
    return contarLegajos(vecPFiles, vecNombresFiles, vecTamObjetos) == 0 ? false : true;
}

bool usuariosEspecificosCargados(string Rol, FILE* vecPFiles[], const char* vecNombresFiles[], int vecTamObjetos[], string vecNombresRoles[]) {
    int usuariosEspecificos = 0;
    bool existe = true;

    for(x = 0; x < CANTIDADOBJETOS; x++){
        if(Rol == vecNombresRoles[x]) {
            if(!(vecPFiles[x] = fopen(vecNombresFiles[x], "rb+"))) {
                cout << endl << "No encontró el archivo" << endl;
                if (!(vecPFiles[x] = fopen(vecNombresFiles[x], "wb+"))) {
                    cout << endl << "---- ERROR AL ABRIR O CREAR EL ARCHIVO ----" << endl;
                    return false;
                }
            }

            fseek(vecPFiles[x], 0, SEEK_END);
            usuariosEspecificos += ftell(vecPFiles[x]) / vecTamObjetos[x];
            fseek(vecPFiles[x], 0, SEEK_SET);
            fclose(vecPFiles[x]);

            if(usuariosEspecificos == 0){
                existe = false;
                return existe;
            }

            return existe;
        }
    }
}

void mensajeUsuariosNoEncontrados(string Rol) {
    cout << endl << "---- ERROR: NO SE ENCONTRARON USUARIOS CON ROL '" << Rol << "' CARGADOS EN EL SISTEMA ----" << endl << endl;
    cout << endl << endl;
    system("pause");
    system("cls");

    rol = seleccionarRol(rol);
}

///--- LOGIN ROLES ---\\

void login(int rol, string Rol) {
    setlocale(LC_ALL, "Spanish");

    cout << Rol << ": INICIO DE SESIÓN (Nro. de Legajo 0 para salir)" << endl;
    cout << endl << endl << "\t - Legajo: ";
    cin >> legajo;

    if(legajo == 0){
        system("cls");
        menuPrincipal();
    }
    if(!usuarioValido(Rol, legajo, vecPFiles, vecNombresFiles, vecTamObjetos, vecNombresRoles)) {
        cout << endl << "---- ERROR: NO SE ENCONTRÓ UN USUARIO " << Rol << " CON LEGAJO '" << legajo << "' CARGADO EN EL SISTEMA ----" << endl << endl;
        cout << endl << endl;
        system("pause");
        system("cls");
        login(rol, Rol);
    }

    cout << endl << "\t - Contraseña (numérica): ";
    cin >> clave;
    if(!claveValida(Rol, legajo, clave, vecPFiles, vecNombresFiles, vecTamObjetos, vecNombresRoles)) {
        cout << endl << "---- ERROR: CONTRASEÑA INCORRECTA ----" << endl << endl;
        cout << endl << endl;
        system("pause");
        system("cls");
        login(rol, Rol);
    }

    if(!estadoValido(Rol, legajo, vecPFiles, vecNombresFiles, vecTamObjetos, vecNombresRoles)) {
        cout << endl << "---- ERROR: USUARIO INACTIVO ----" << endl << endl;
        cout << endl << endl;
        system("pause");
        system("cls");
        login(rol, Rol);
    }


    switch (rol) {
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

bool usuarioValido(string Rol, int legajo, FILE* vecPFiles[], const char* vecNombresFiles[], int vecTamObjetos[], string vecNombresRoles[]) {
    bool valido = false;

    for(x = 0; x < CANTIDADOBJETOS; x++){
        if(Rol == vecNombresRoles[x]) {
            if(!(vecPFiles[x] = fopen(vecNombresFiles[x], "rb+"))) {
                if (!(vecPFiles[x] = fopen(vecNombresFiles[x], "wb+"))) {
                    cout << endl << "---- ERROR AL ABRIR O CREAR EL ARCHIVO ----" << endl;
                    return false;
                }
            }

            if(Rol == "ADMINISTRADOR"){
                Administrador obj;
                while (fread(&obj, vecTamObjetos[x], 1, vecPFiles[x])) {
                    if(obj.getId() == legajo)
                        valido = true;
                        return valido;
                    }
                }
            else if(Rol == "DIRECTOR"){
                Director obj;
                while (fread(&obj, vecTamObjetos[x], 1, vecPFiles[x])) {
                    if(obj.getLegajo() == legajo){
                        valido = true;
                        return valido;
                    }
                }
            }
            else if(Rol == "PROFESOR"){
                Profesor obj;
                while (fread(&obj, vecTamObjetos[x], 1, vecPFiles[x])) {
                    if(obj.getLegajo() == legajo){
                        valido = true;
                        return valido;
                    }
                }
            }
            else{
                Alumno obj;
                while (fread(&obj, vecTamObjetos[x], 1, vecPFiles[x])) {
                    if(obj.getLegajo() == legajo){
                        valido = true;
                        return valido;
                    }
                }
            }
        }
    }

    return valido;
}

bool claveValida(string Rol, int legajo, int clave, FILE* vecPFiles[], const char* vecNombresFiles[], int vecTamObjetos[], string vecNombresRoles[]) {
    bool valida = false;

    for(x = 0; x < CANTIDADOBJETOS; x++){
        if(Rol == vecNombresRoles[x]) {
            if(!(vecPFiles[x] = fopen(vecNombresFiles[x], "rb+"))) {
                if (!(vecPFiles[x] = fopen(vecNombresFiles[x], "wb+"))) {
                    cout << endl << "---- ERROR AL ABRIR O CREAR EL ARCHIVO ----" << endl;
                    return false;
                }
            }

            if(Rol == "ADMINISTRADOR"){
                Administrador obj;
                while (fread(&obj, vecTamObjetos[x], 1, vecPFiles[x])) {
                    if(obj.getId() == legajo){
                        if(obj.getClave() == clave){
                            valida = true;
                            return valida;
                        }
                    }
                }
            }
            else if(Rol == "DIRECTOR"){
                Director obj;
                while (fread(&obj, vecTamObjetos[x], 1, vecPFiles[x])) {
                    if(obj.getLegajo() == legajo){
                        if(obj.getClave() == clave){
                            valida = true;
                            return valida;
                        }
                    }
                }
            }
            else if(Rol == "PROFESOR"){
                Profesor obj;
                while (fread(&obj, vecTamObjetos[x], 1, vecPFiles[x])) {
                    if(obj.getLegajo() == legajo){
                        if(obj.getClave() == clave){
                            valida = true;
                            return valida;
                        }
                    }
                }
            }
            else{
                Alumno obj;
                while (fread(&obj, vecTamObjetos[x], 1, vecPFiles[x])) {
                    if(obj.getLegajo() == legajo){
                        if(obj.getClave() == clave){
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

bool estadoValido(string Rol, int legajo, FILE* vecPFiles[], const char* vecNombresFiles[], int vecTamObjetos[], string vecNombresRoles[]) {
    bool valido = false;

    for(x = 0; x < CANTIDADOBJETOS; x++){
        if(Rol == vecNombresRoles[x]) {
            if(!(vecPFiles[x] = fopen(vecNombresFiles[x], "rb+"))) {
                if (!(vecPFiles[x] = fopen(vecNombresFiles[x], "wb+"))) {
                    cout << endl << "---- ERROR AL ABRIR O CREAR EL ARCHIVO ----" << endl;
                    return false;
                }
            }

            if(Rol == "ADMINISTRADOR"){
                Administrador obj;
                while (fread(&obj, vecTamObjetos[x], 1, vecPFiles[x])) {
                    if(obj.getId() == legajo)
                        valido = true;
                        return valido;
                    }
                }
            else if(Rol == "DIRECTOR"){
                Director obj;
                while (fread(&obj, vecTamObjetos[x], 1, vecPFiles[x])) {
                    if(obj.getLegajo() == legajo){
                        if(obj.getEstado() == true){
                            valido = true;
                            return valido;
                        }
                    }
                }
            }
            else if(Rol == "PROFESOR"){
                Profesor obj;
                while (fread(&obj, vecTamObjetos[x], 1, vecPFiles[x])) {
                    if(obj.getLegajo() == legajo){
                        if(obj.getEstado() == true){
                            valido = true;
                            return valido;
                        }
                    }
                }
            }
            else{
                Alumno obj;
                while (fread(&obj, vecTamObjetos[x], 1, vecPFiles[x])) {
                    if(obj.getLegajo() == legajo){
                        if(obj.getEstado() == true){
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


///--- MENÚS ROLES ---\\

///--- MENÚ ADMINISTRADOR ---\\

void menuAdministrador() {

    int opcion;
    int legajoDirector;
    int nuevaClave;

    cout << "----------------------------------------------------"<< endl;
    cout << "                 MENÚ ADMINISTRADOR                 "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "1. CREAR PERFIL DIRECTOR                            "<< endl;
    cout << "2. ACTIVAR PERFIL DIRECTOR                          "<< endl;
    cout << "3. DESACTIVAR PERFIL DIRECTOR                       "<< endl;
    cout << "4. CAMBIAR CONTRASEÑA                               "<< endl;
    cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "             - SELECCIONE UNA OPCION: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 48){
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "----------------------------------------------------"<< endl;
        cout << "                 MENÚ ADMINISTRADOR                 "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "1. CREAR PERFIL DIRECTOR                            "<< endl;
        cout << "2. ACTIVAR PERFIL DIRECTOR                          "<< endl;
        cout << "3. DESACTIVAR PERFIL DIRECTOR                       "<< endl;
        cout << "4. CAMBIAR CONTRASEÑA                               "<< endl;
        cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "             - SELECCIONE UNA OPCION: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();

    }

    switch(opcion) {
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
            cout << "CAMBIANDO CONTRASEÑA" << endl;

            cout << endl << "\t - Contraseña anterior: " << administradorObj.getClave() << endl;
            cout << endl << "\t - Contraseña nueva (numérica): ";
            cin >> nuevaClave;

            administradorObj.cambiarClave(legajo, nuevaClave);

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
            cout << "Opción no válida." << endl;
    }

}

///--- MENÚ DIRECTIVO ---\\

void menuDirectivo() {
    int opcion;
    int legajoDirector;
    int nuevaClave;

    cout << "----------------------------------------------------"<< endl;
    cout << "                   MENÚ DIRECTIVO                   "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "1. GESTIÓN PERFIL PROFESOR                          "<< endl;
    cout << "2. GESTIÓN PERFIL ALUMNO                            "<< endl;
    cout << "3. GESTIÓN PLAN DE ESTUDIO                          "<< endl;
    cout << "4. CAMBIAR CONTRASEÑA                               "<< endl;
    cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "             - SELECCIONE UNA OPCION: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 48){
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "----------------------------------------------------"<< endl;
        cout << "                   MENÚ DIRECTIVO                   "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "1. GESTIÓN PERFIL PROFESOR                          "<< endl;
        cout << "2. GESTIÓN PERFIL ALUMNO                            "<< endl;
        cout << "3. GESTIÓN PLAN DE ESTUDIO                          "<< endl;
        cout << "4. CAMBIAR CONTRASEÑA                               "<< endl;
        cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "             - SELECCIONE UNA OPCION: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();

    }

    switch(opcion) {
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
            system("cls");
            cout << "CAMBIANDO CONTRASEÑA" << endl;

            cout << endl << "\t - Contraseña anterior: " << directorObj.getClave() << endl;
            cout << endl << "\t - Contraseña nueva (numérica): ";
            cin >> nuevaClave;

            directorObj.cambiarClave(legajo, nuevaClave);

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
            cout << "Opción no válida." << endl;
    }
}

void subMenuDirectivoProfesor() {
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
    cout << "             - SELECCIONE UNA OPCION: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 48){
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
        cout << "             - SELECCIONE UNA OPCION: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();
    }

    switch(opcion) {
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

            //profesorObj.activarProfesor(legajoProfesor);

            system("cls");
            subMenuDirectivoProfesor();
            break;
        case 51:
            system("cls");
            cout << "DESACTIVANDO PERFIL PROFESOR" << endl;

            cout << endl << "\t- Legajo: ";
            cin >> legajoProfesor;
            validarLegajo(legajoProfesor);

            //profesorObj.desactivarProfesor(legajoProfesor);

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
            cout << "Opción no válida." << endl;
    }

}

void subMenuDirectivoAlumno() {
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
    cout << "             - SELECCIONE UNA OPCION: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;


    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 48){
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
        cout << "             - SELECCIONE UNA OPCION: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();
    }

    switch(opcion) {
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
            cout << "Opción no válida." << endl;
    }
}

void subMenuDirectivoPlanEstudio() {
    int opcion;
    int cantMaterias;
    Materia materiaObj;

    cout << "----------------------------------------------------"<< endl;
    cout << "               GESTIÓN PLAN DE ESTUDIO              "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "1. CARGAR MATERIAS                                  "<< endl;
    cout << "2. ASIGNAR CORRELATIVAS                             "<< endl;
    cout << "3. ASIGNAR PROFESORES                               "<< endl;
    cout << "0. VOLVER AL MENÚ DIRECTIVO                         "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "             - SELECCIONE UNA OPCION: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;


    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 48){
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "----------------------------------------------------"<< endl;
        cout << "               GESTIÓN PLAN DE ESTUDIO              "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "1. CARGAR MATERIAS                                  "<< endl;
        cout << "2. ASIGNAR CORRELATIVAS                             "<< endl;
        cout << "3. ASIGNAR PROFESORES                               "<< endl;
        cout << "0. VOLVER AL MENÚ DIRECTIVO                         "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "             - SELECCIONE UNA OPCION: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();
    }

    switch(opcion) {
        case 49:
            system("cls");

            cout << "CARGANDO MATERIAS - PLAN DE ESTUDIO 2003" << endl;

            if(contarMaterias() < 21){
                cout << endl << "\t- Cantidad de materias a cargar: ";
                cin >> cantMaterias;

                while(cantMaterias > 21 || cantMaterias > (21 - contarMaterias()) || cantMaterias <= 0){
                    cout << endl <<"---- ERROR: CANTIDAD DISPONIBLE: " << (21 - contarMaterias()) << " ----" << endl;
                    Sleep(1500);
                    system("cls");

                    cout << "CARGANDO MATERIAS - PLAN DE ESTUDIO 2003" << endl;

                    cout << endl << "\t- Cantidad de materias a cargar: ";
                    cin >> cantMaterias;
                }


                for(int x = 0; x < cantMaterias; x++){
                    system("cls");
                    cout << "CARGANDO MATERIAS - PLAN DE ESTUDIO 2003" << endl;
                    materiaObj.grabarEnDiscoMateria();
                }

            }
            else{
                cout << endl <<"---- LÍMITE DE MATERIAS CARGADAS ALCANZADO ----" << endl;
                system("pause");

                system("cls");
                materiaObj.leerEnDiscoMateria();
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

            if(!usuariosEspecificosCargados("PROFESOR", vecPFiles, vecNombresFiles, vecTamObjetos, vecNombresRoles)){
                cout << endl << "---- ERROR: NO SE ENCONTRARON USUARIOS CON ROL 'PROFESOR' CARGADOS EN EL SISTEMA ----" << endl << endl;
                cout << endl << endl;
                system("pause");
                system("cls");
            }
            else{
                if(contarMaterias() < 21){
                    cout << endl << "---- ERROR: PLAN DE ESTUDIOS INCOMPLETO, " << 21 - contarMaterias() << " MATERIAS RESTANTES POR CARGAR ----" << endl << endl;
                    cout << endl << endl;
                    system("pause");
                    system("cls");
                }
                else{
                    asignarProfesores();
                }
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
            cout << "Opción no válida." << endl;
    }
}

int contarMaterias() {
    FILE *pMat;
    int cantMaterias = 0;

    if(!(pMat = fopen("materias.dat", "ab"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return -1;
    }

    fseek(pMat, 0, SEEK_END);
    cantMaterias += ftell(pMat) / sizeof(Materia);
    fseek(pMat, 0, SEEK_SET);
    fclose(pMat);

    return cantMaterias;
}

void asignarProfesores() {
    int legajoProfesor;

    FILE *pMat;
    Materia materiaObj;

    Profesor profesorObj;
    FILE *pProfesor;

    if (!(pMat = fopen("materias.dat", "rb+"))) {
        cout << endl << "--- NO SE ENCONTRARON REGISTROS DE MATERIAS ----" << endl;
        return;
    }

    while (fread(&materiaObj, sizeof(Materia), 1, pMat)) {
        if (materiaObj.getLegajoProfesor() != -1) {
            continue;
        }

        bool valido = false;

        while (!valido) {
            if (!(pProfesor = fopen("profesores.dat", "rb"))) {
                system("cls");
                cout << endl << "---- ERROR AL ABRIR EL ARCHIVO DE PROFESORES ----" << endl;
                fclose(pMat);
                return;
            }

            cout << endl << "\t - Legajo Profesor: ";
            cin >> legajoProfesor;

            while (fread(&profesorObj, sizeof(Profesor), 1, pProfesor)) {
                if (profesorObj.getLegajo() == legajoProfesor) {
                    valido = true;
                    break;
                }
            }
            fclose(pProfesor);

            if (!valido) {
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



///--- MENÚ PROFESOR ---\\

void menuProfesor() {
    int opcion;

    cout << "----------------------------------------------------"<< endl;
    cout << "                   MENÚ PROFESOR                    "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "1. CARGAR NOTAS                                     "<< endl;
    cout << "2. MODIFICAR NOTAS                                  "<< endl;
    cout << "3. CARGAR FECHA DE EXAMEN                           "<< endl;
    cout << "4. VER MATERIAS ASIGNADAS                           "<< endl;
    cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "             - SELECCIONE UNA OPCION: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 48){
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "----------------------------------------------------"<< endl;
        cout << "                   MENÚ PROFESOR                    "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "1. CARGAR NOTAS                                     "<< endl;
        cout << "2. MODIFICAR NOTAS                                  "<< endl;
        cout << "3. CARGAR FECHA DE EXAMEN                           "<< endl;
        cout << "4. VER MATERIAS ASIGNADAS                           "<< endl;
        cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "             - SELECCIONE UNA OPCIÓN: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();

    }

    switch(opcion) {
        case 49:
            system("cls");
            ///-- >> FUNCION CARGA DE NOTAS
            break;
        case 50:
            system("cls");
            ///-- >> FUNCION MODIFICACION DE NOTAS
            break;
        case 51:
            system("cls");
            ///-- >> FUNCION CARGA FECHA DE EXAMEN
            break;
        case 52:
            system("cls");
            ///-- >> FUNCION DE LISTADO DE MATERIAS ASIGNADAS
            break;
        case 48:
            system("cls");
            cout << "VOLVIENDO AL MENÚ PRINCIPAL..." << endl;
            Sleep(2000);
            system("cls");
            menuPrincipal();
            break;
        default:
            cout << "Opción no válida." << endl;
    }
}

///--- MENÚ ALUMNO ---\\

void menuAlumno() {
    int opcion;

    cout << "----------------------------------------------------"<< endl;
    cout << "                    MENÚ ALUMNO                     "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "1. GESTIÓN MATERIAS                                 "<< endl;
    cout << "2. GESTIÓN EXÁMENES                                 "<< endl;
    cout << "3. CAMBIAR CONTRASEÑA                               "<< endl;
    cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
    cout << "----------------------------------------------------"<< endl;
    cout << "             - SELECCIONE UNA OPCION: -             "<< endl;
    cout << "----------------------------------------------------"<< endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 48){
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "----------------------------------------------------"<< endl;
        cout << "                    MENÚ ALUMNO                     "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "1. GESTIÓN MATERIAS                                 "<< endl;
        cout << "2. GESTIÓN EXÁMENES                                 "<< endl;
        cout << "3. CAMBIAR CONTRASEÑA                               "<< endl;
        cout << "0. VOLVER AL MENÚ PRINCIPAL                         "<< endl;
        cout << "----------------------------------------------------"<< endl;
        cout << "             - SELECCIONE UNA OPCION: -             "<< endl;
        cout << "----------------------------------------------------"<< endl;

        opcion = _getch();

    }

    switch(opcion) {
        case 49:
            system("cls");
            ///-- >> FUNCION / MENÚ GESTIÓN MATERIAS
            break;
        case 50:
            system("cls");
            ///-- >> FUNCION / MENÚ GESTIÓN EXÁMENES
            break;
        case 51:
            system("cls");
            ///-- >> FUNCION CAMBIAR CONTRASEÑA
            break;
        case 48:
            system("cls");
            cout << "VOLVIENDO AL MENÚ PRINCIPAL..." << endl;
            Sleep(2000);
            system("cls");
            menuPrincipal();
            break;
        default:
            cout << "Opción no válida." << endl;
    }
}

void validarLegajo(int legajo) {

    while(legajo < 0 || cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "\t---- ERROR : LEGAJO INVÁLIDO ----" << endl;
        cout << endl << "\t - Legajo: ";
        cin >> legajo;
    }
}
