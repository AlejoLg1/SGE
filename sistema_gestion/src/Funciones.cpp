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
#include "rlutil.h"

using namespace std;
using namespace rlutil;

const int CANTIDADOBJETOS = 3;
//const int CANTIDADOBJETOS = 4;

//ARCHIVOS
FILE *pAdm;
FILE *pDirectivo;
FILE *pProfesor;
FILE *pAlumno;

//VECTORES ARCHIVOS
FILE* vecPFiles[CANTIDADOBJETOS] = {pAdm, pDirectivo, pAlumno};
const char* vecNombresFiles[CANTIDADOBJETOS] = {"administradores.dat", "Director.dat", "alumnos.dat"};
int vecTamObjetos[CANTIDADOBJETOS] = {sizeof(Administrador), sizeof(Director), sizeof(Alumno)};
string vecNombresRoles[CANTIDADOBJETOS] = {"ADMINISTRADOR", "DIRECTOR", "ALUMNO"};

//DESCOMENTAR CUANDO ESTÉ CREADA LA CLASE PROFESOR Y BORRAR LO DE ARRIBA
//FILE* vecPFiles[CANTIDADOBJETOS] = {pAdm, pDirectivo, pProfesor, pAlumno};
//string vecNombresFiles[CANTIDADOBJETOS] = {"administradores.dat", "Director.dat", "profesor.dat", "alumnos.dat"};
//int vecTamObjetos[CANTIDADOBJETOS] = {sizeof(Administrador), sizeof(Directivo), sizeof(Profesor), sizeof(Alumno)};
//string vecNombresRoles[CANTIDADOBJETOS] = {"ADMINISTRADOR", "DIRECTOR", "PROFESOR", "ALUMNO"};


//OBJETOS
Administrador administradorObj;
Director directorObj;
//Profesor profesorObj;
Alumno alumnoObj;

//VARIABLES GLOBALES
int rol;
int x;
int legajo;
int clave;

void marco(int y, int x, int ancho, int alto, int color)
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
}

void menuPrincipal() {
    setlocale(LC_ALL, "Spanish");
    rol = seleccionarRol(rol);

    while(true) {
        marco(12, 10, 80, 48, 9);
        setColor(15);
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
                rol = seleccionarRol(rol);
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
            case 53: // SALIR
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
    marco(12, 10, 80, 48, 9);
    setColor(15);
    gotoxy(25,16);cout << "Seleccione su rol correspondiente: " << endl;
    gotoxy(25,17);cout << "1) Administrador";
    gotoxy(25,18);cout << "2) Director";
    gotoxy(25,19);cout << "3) Profesor";
    gotoxy(25,20);cout << "4) Alumno";
    gotoxy(25,21);cout << "5) Salir";
    gotoxy(25,22);cout << endl;

    rol = _getch();

    while(rol != 49 && rol != 50 && rol != 51 && rol != 52 && rol != 53){
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "Seleccione su rol correspondiente: " << endl;
        cout << endl << "1) Administrador";
        cout << endl << "2) Directivo";
        cout << endl << "3) Profesor";
        cout << endl << "4) Alumno";
        cout << endl << "5) Salir";
        cout << endl << endl;

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
                cout << endl << "No encontré el archivo" << endl;
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
            cout << "Ha seleccionado la opcion 3." << endl;
            break;
        case 52: //ALUMNO
            cout << "Ha seleccionado la opcion 4." << endl;
            system("pause");
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
                /*Profesor obj;
                while (fread(&obj, vecTamObjetos[x], 1, vecPFiles[x])) {
                    if(obj.getLegajo() == legajo){
                        valido = true;
                        return valido;
                    }
                }*/
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
                /*Profesor obj;
                while (fread(&obj, vecTamObjetos[x], 1, vecPFiles[x])) {
                    if(obj.getLegajo() == legajo){
                        if(obj.getClave() == clave){
                            valida = true;
                            return valida;
                        }
                    }
                }*/
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
                /*Profesor obj;
                while (fread(&obj, vecTamObjetos[x], 1, vecPFiles[x])) {
                    if(obj.getLegajo() == legajo){
                        if(obj.getEstado() == true){
                            valido = true;
                            return valido;
                        }
                    }
                }*/
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

    cout << "¡Bienvenido!" << endl;
    cout << "Seleccione la opción que desee: " << endl;

    cout << endl << "1) Crear perfil Director";
    cout << endl << "2) Activar perfil Director";
    cout << endl << "3) Desactivar perfil Director";
    cout << endl << "4) Cambiar contraseña";
    cout << endl << "5) Volver al Menú principal";
    cout << endl << endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 53){
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "¡Bienvenido!" << endl;
        cout << "Seleccione la opción que desee: " << endl;

        cout << endl << "1) Crear perfil Director";
        cout << endl << "2) Activar perfil Director";
        cout << endl << "3) Desactivar perfil Director";
        cout << endl << "4) Cambiar contraseña";
        cout << endl << "5) Volver al Menú principal";
        cout << endl << endl;

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

            cout << endl << "\t - Contraseña anterior: " << clave << endl;
            cout << endl << "\t - Contraseña nueva (numérica): ";
            cin >> nuevaClave;

            administradorObj.cambiarClave(legajo, nuevaClave);

            system("cls");
            menuAdministrador();
            break;
        case 53:
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

    cout << "¡Bienvenido!" << endl;
    cout << "Seleccione la opción que desee: " << endl;

    cout << endl << "1) Gestion perfil Profesor";
    cout << endl << "2) Gestion perfil Alumno";
    cout << endl << "3) Cambiar contraseña";
    cout << endl << "4) Volver al Menú principal";
    cout << endl << endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52){
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "¡Bienvenido!" << endl;
        cout << "Seleccione la opción que desee: " << endl;

        cout << endl << "1) Gestion perfil Profesor";
        cout << endl << "2) Gestion perfil Alumno";
        cout << endl << "3) Cambiar contraseña";
        cout << endl << "4) Volver al Menú principal";
        cout << endl << endl;

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
            cout << "CAMBIANDO CONTRASEÑA" << endl;

            cout << endl << "\t - Contraseña anterior: " << clave << endl;
            cout << endl << "\t - Contraseña nueva (numérica): ";
            cin >> nuevaClave;

            directorObj.cambiarClave(legajo, nuevaClave);

            system("cls");
            menuDirectivo();
            break;
        case 52:
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

    cout << "¡Bienvenido!" << endl;
    cout << "Seleccione la opción que desee: " << endl;

    cout << endl << "1) Crear perfil Profesor";
    cout << endl << "2) Activar perfil Profesor";
    cout << endl << "3) Desactivar perfil Profesor";
    cout << endl << "4) Volver al Menú Directivo";
    cout << endl << endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52){
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "¡Bienvenido!" << endl;
        cout << "Seleccione la opción que desee: " << endl;

        cout << endl << "1) Crear perfil Profesor";
        cout << endl << "2) Activar perfil Profesor";
        cout << endl << "3) Desactivar perfil Profesor";
        cout << endl << "4) Volver al Menú Directivo";
        cout << endl << endl;

        opcion = _getch();
    }

    switch(opcion) {
        case 49:
            system("cls");
            //profesorObj.grabarEnDiscoDirector();
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
        case 52:
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

    cout << "¡Bienvenido!" << endl;
    cout << "Seleccione la opción que desee: " << endl;

    cout << endl << "1) Crear perfil Alumno";
    cout << endl << "2) Activar perfil Alumno";
    cout << endl << "3) Desactivar perfil Alumno";
    cout << endl << "4) Volver al Menú Directivo";
    cout << endl << endl;

    opcion = _getch();

    while(opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52){
        cout << "---- ERROR: OPCIÓN INVÁLIDA ----" << endl;
        Sleep(500);
        system("cls");

        cout << "¡Bienvenido!" << endl;
        cout << "Seleccione la opción que desee: " << endl;

        cout << endl << "1) Crear perfil Alumno";
        cout << endl << "2) Activar perfil Alumno";
        cout << endl << "3) Desactivar perfil Alumno";
        cout << endl << "4) Volver al Menú Directivo";
        cout << endl << endl;

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
        case 52:
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

///--- MENÚ PROFESOR ---\\

void menuProfesor() {
     system("cls");
    system("title PROYECTO 2024");
    int opcion;
    do{
        marco(12, 10, 80, 48, 9);
        setColor(15);
        gotoxy(25,16);cout << "----------------------------------------------------"<< endl;
        gotoxy(25,17);cout << "                   MENU PROFESOR                    "<< endl;
        gotoxy(25,18);cout << "----------------------------------------------------"<< endl;
        gotoxy(25,20);cout << "1. CARGAR NOTAS                                     "<< endl;
        gotoxy(25,21);cout << "2. MODIFICAR NOTAS                                  "<< endl;
        gotoxy(25,22);cout << "3. CARGAR FECHA DE EXAMEN                           "<< endl;
        gotoxy(25,23);cout << "4. VER MATERIAS ASIGNADAS                           "<< endl;
        gotoxy(25,24);cout << "0. SALIR                                            "<< endl;
        gotoxy(25,25);cout << "----------------------------------------------------"<< endl;
        gotoxy(25,26);cout << "- SELECCIONE UNA OPCION: -    "<< endl;
        gotoxy(25,27);cout << "----------------------------------------------------"<< endl;
        gotoxy(25,28);cout << " --> ";cin>>opcion;

        switch(opcion){
            case 1:
                ///-- >> FUNCION CARGA DE NOTAS
            break;
            case 2:
                ///-- >> FUNCION MODIFICACION DE NOTAS
            break;
            case 3:
                ///-- >> FUNCION CARGA FECHA DE EXAMEN
            break;
            case 4:
                ///-- >> FUNCION DE LISTADO DE MATERIAS ASIGNADAS
            break;

            case 0:
                return;
            break;
            default:
                cout << "OPCION INCORRECTA. REINGRESE LA OPCION NUEVAMENTE.";
            break;
        }

    }while(opcion != 0);


}

///--- MENÚ ALUMNO ---\\

void menuAlumno() {

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
