#include "Funciones.h"

#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <windows.h>

#include <iomanip>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <string>
#include <vector>


#include "Administrador.h"
#include "Alumno.h"
#include "Aviso.h"
#include "Director.h"
#include "Evaluacion.h"
#include "InscripcionEvaluacion.h"
#include "InscripcionMateria.h"
#include "Materia.h"
#include "Profesor.h"

using namespace std;

const int CANTIDADOBJETOS = 4;

// ARCHIVOS
FILE *pAdm;
FILE *pDirectivo;
FILE *pProfesor;
FILE *pAlumno;

// VECTORES ARCHIVOS
const char *vecNombresFiles[CANTIDADOBJETOS] = {
    "administradores.dat", "directores.dat", "profesores.dat", "alumnos.dat"};
int vecTamObjetos[CANTIDADOBJETOS] = {sizeof(Administrador), sizeof(Director),
                                      sizeof(Profesor), sizeof(Alumno)};
string vecNombresRoles[CANTIDADOBJETOS] = {"ADMINISTRADOR", "DIRECTOR",
                                           "PROFESOR", "ALUMNO"};

// OBJETOS
Administrador administradorObj;
Director directorObj;
Profesor profesorObj;
Alumno alumnoObj;
InscripcionMateria inscripcionMateriaObj;
InscripcionEvaluacion inscripcionEvaluacionObj;

// VARIABLES GLOBALES
int rol;
int x;
int legajo;
int clave;


void menuPrincipal() {
  setlocale(LC_ALL, "Spanish");

  rol = seleccionarRol(rol);

  while (true) {
    switch (rol) {
      cout << endl << "ROL: " << rol << endl;
      system("pause");
      case 49:  // ADMINISTRADOR
        system("cls");
        if (usuariosCargados()) {  // Si devuelve true, existen usuarios
          system("cls");
          login(rol, "ADMINISTRADOR");
        }
        else {
          cout << endl << "---- ERROR : NO SE ENCONTRARON USUARIOS CON ROL 'ADMINISTRADOR' CARGADOS ----" << endl << endl;
          cout << endl << endl;
          system("pause");
          system("cls");
          administradorObj.grabarEnDiscoAdministrador();
          system("cls");
          rol = seleccionarRol(rol);
        }
        break;
      case 50:  // DIRECTOR
        system("cls");
        if (usuariosCargados()) {
          if (!usuariosEspecificosCargados("DIRECTOR", vecNombresFiles, vecTamObjetos, vecNombresRoles)) {
            mensajeUsuariosNoEncontrados("DIRECTOR");
          }
          else {
            system("cls");
            login(rol, "DIRECTOR");
          }
        }
        else {
          mensajeUsuariosNoEncontrados("DIRECTOR");
        }
        break;
      case 51:  // PROFESOR
        system("cls");
        if (usuariosCargados()) {
          if (!usuariosEspecificosCargados("PROFESOR", vecNombresFiles, vecTamObjetos, vecNombresRoles)) {
            mensajeUsuariosNoEncontrados("PROFESOR");
          }
          else {
            system("cls");
            login(rol, "PROFESOR");
          }
        }
        else {
          mensajeUsuariosNoEncontrados("PROFESOR");
        }
        break;
      case 52:  // ALUMNO
        system("cls");
        if (usuariosCargados()) {
          if (!usuariosEspecificosCargados("ALUMNO", vecNombresFiles, vecTamObjetos, vecNombresRoles)) {
            mensajeUsuariosNoEncontrados("ALUMNO");
          }
          else {
            system("cls");
            login(rol, "ALUMNO");
          }
        }
        else {
          mensajeUsuariosNoEncontrados("ALUMNO");
        }
        break;
      case 48:  // SALIR
        SALIENDO();
        exit(0);
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

  // CARGANDO();

  cout << "----------------------------------------------------" << endl;
  cout << "                     MENÚ ROLES                     " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "1. ADMINISTRADOR                                    " << endl;
  cout << "2. DIRECTOR                                         " << endl;
  cout << "3. PROFESOR                                         " << endl;
  cout << "4. ALUMNO                                           " << endl;
  cout << "0. SALIR                                            " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "       - SELECCIONE SU ROL CORRESPONDIENTE: -       " << endl;
  cout << "----------------------------------------------------" << endl;

  rol = _getch();

  while (rol != 49 && rol != 50 && rol != 51 && rol != 52 && rol != 48) {
    cout << "---- ERROR : OPCIÓN INVÁLIDA ----" << endl;
    Sleep(500);
    system("cls");

    cout << "----------------------------------------------------" << endl;
    cout << "                     MENÚ ROLES                     " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "1. ADMINISTRADOR                                    " << endl;
    cout << "2. DIRECTOR                                         " << endl;
    cout << "3. PROFESOR                                         " << endl;
    cout << "4. ALUMNO                                           " << endl;
    cout << "0. SALIR                                            " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "       - SELECCIONE SU ROL CORRESPONDIENTE: -       " << endl;
    cout << "----------------------------------------------------" << endl;

    rol = _getch();
  }

  return rol;
}

///--- SETTEAR LEGAJO AUTOMÁTICO ---\\

int settearNuevoLegajo() {
  int nuevoLegajo = 0;

  nuevoLegajo = contarLegajos(vecNombresFiles, vecTamObjetos) + 1;

  return nuevoLegajo;
}

int contarLegajos(const char *vecNombresFiles[], int vecTamObjetos[]) {
  int legajosTotales = 0;
  FILE *pFile = nullptr;

  for (x = 0; x < CANTIDADOBJETOS; x++) { // recorrer los archivos .dat de admin, director, prof y alumno

    if (!(pFile = fopen(vecNombresFiles[x], "rb+"))) {
      if (!(pFile = fopen(vecNombresFiles[x], "wb+"))) {
        cout << endl << "---- ERROR AL ABRIR O CREAR EL ARCHIVO ----" << endl;
        return 0;
      }
    }

    fseek(pFile, 0, SEEK_END);
    legajosTotales += ftell(pFile) / vecTamObjetos[x];  // sumamos cantidad de objetos que se encuentran dentro de cada archivo
    fseek(pFile, 0, SEEK_SET);
    fclose(pFile);
  }

  return legajosTotales;
}

///--- VALIDAR EXISTENCIA DE USUARIOS ---\\

bool usuariosCargados() {
  return contarLegajos(vecNombresFiles, vecTamObjetos) == 0 ? false : true;
}

bool usuariosEspecificosCargados(string Rol, const char *vecNombresFiles[], int vecTamObjetos[], string vecNombresRoles[]) {
  int usuariosEspecificos = 0;
  bool existe = true;
  FILE *pFile = nullptr;

  for (x = 0; x < CANTIDADOBJETOS; x++) {
    if (Rol == vecNombresRoles[x]) {
      if (!(pFile = fopen(vecNombresFiles[x], "rb+"))) {
        cout << endl << "No encontrÓ el archivo" << endl;
        if (!(pFile = fopen(vecNombresFiles[x], "wb+"))) {
          cout << endl << "---- ERROR AL ABRIR O CREAR EL ARCHIVO ----" << endl;
          return false;
        }
      }

      fseek(pFile, 0, SEEK_END);
      usuariosEspecificos += ftell(pFile) / vecTamObjetos[x];
      fseek(pFile, 0, SEEK_SET);
      fclose(pFile);

      if (usuariosEspecificos == 0) {
        existe = false;
        return existe;
      }

      return existe;
    }
  }
}

void mensajeUsuariosNoEncontrados(string Rol) {
  cout << endl
       << "---- ERROR : NO SE ENCONTRARON USUARIOS CON ROL '" << Rol<< "' CARGADOS EN EL SISTEMA ----" << endl << endl;
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

  if (legajo == 0) {
    system("cls");
    menuPrincipal();
  }
  if (!usuarioValido(Rol, legajo, vecNombresFiles, vecTamObjetos, vecNombresRoles)) {
    cout << endl
         << "---- ERROR : NO SE ENCONTRÓ UN USUARIO " << Rol << " CON LEGAJO '"
         << legajo << "' CARGADO EN EL SISTEMA ----" << endl
         << endl;
    cout << endl << endl;
    system("pause");
    system("cls");
    login(rol, Rol);
  }

  cout << endl << "\t - Contraseña (numérica): ";
  cin >> clave;
  if (!claveValida(Rol, legajo, clave, vecNombresFiles, vecTamObjetos, vecNombresRoles)) {
    cout << endl << "---- ERROR : CONTRASEÑA INCORRECTA ----" << endl << endl;
    cout << endl << endl;
    system("pause");
    system("cls");
    login(rol, Rol);
  }

  if (!estadoValido(Rol, legajo, vecNombresFiles, vecTamObjetos, vecNombresRoles)) {
    cout << endl << "---- ERROR : USUARIO INACTIVO ----" << endl << endl;
    cout << endl << endl;
    system("pause");
    system("cls");
    login(rol, Rol);
  }

  switch (rol) {
    case 49:  // ADMINISTRADOR
      system("cls");
      menuAdministrador();
      break;
    case 50:  // DIRECTOR
      system("cls");
      menuDirectivo();
      break;
    case 51:  // PROFESOR
      system("cls");
      menuProfesor();
      break;
    case 52:  // ALUMNO
      system("cls");
      menuAlumno();
      break;
    default:
      cout << "Opcion invalida." << endl;
      break;
  }
}

///--- VALIDAR CREDENCIALES LOGIN ---\\

bool usuarioValido(string Rol, int legajo, const char *vecNombresFiles[], int vecTamObjetos[], string vecNombresRoles[]) {
  bool valido = false;
  FILE *pFile = nullptr;

  for (x = 0; x < CANTIDADOBJETOS; x++) {
    if (Rol == vecNombresRoles[x]) {
      if (!(pFile = fopen(vecNombresFiles[x], "rb+"))) {
        if (!(pFile = fopen(vecNombresFiles[x], "wb+"))) {
          cout << endl << "---- ERROR AL ABRIR O CREAR EL ARCHIVO ----" << endl;
          return false;
        }
      }

      if (Rol == "ADMINISTRADOR") {
        Administrador obj;
        while (fread(&obj, vecTamObjetos[x], 1, pFile)) {
          if (obj.getId() == legajo) {
            valido = true;
            return valido;
          }
        }
      } else if (Rol == "DIRECTOR") {
        Director obj;
        while (fread(&obj, vecTamObjetos[x], 1, pFile)) {
          if (obj.getLegajo() == legajo) {
            valido = true;
            return valido;
          }
        }
      } else if (Rol == "PROFESOR") {
        Profesor obj;
        while (fread(&obj, vecTamObjetos[x], 1, pFile)) {
          if (obj.getLegajo() == legajo) {
            valido = true;
            return valido;
          }
        }
      }
      else {
        Alumno obj;
        while (fread(&obj, vecTamObjetos[x], 1, pFile)) {
          if (obj.getLegajo() == legajo) {
            valido = true;
            return valido;
          }
        }
      }
    }
  }

  return valido;
}

bool claveValida(string Rol, int legajo, int clave, const char *vecNombresFiles[], int vecTamObjetos[], string vecNombresRoles[]) {
  bool valida = false;
  FILE *pFile = nullptr;

  for (x = 0; x < CANTIDADOBJETOS; x++) {
    if (Rol == vecNombresRoles[x]) {
      if (!(pFile = fopen(vecNombresFiles[x], "rb+"))) {
        if (!(pFile = fopen(vecNombresFiles[x], "wb+"))) {
          cout << endl << "---- ERROR AL ABRIR O CREAR EL ARCHIVO ----" << endl;
          return false;
        }
      }

      if (Rol == "ADMINISTRADOR") {
        Administrador obj;
        while (fread(&obj, vecTamObjetos[x], 1, pFile)) {
          if (obj.getId() == legajo) {
            if (obj.getClave() == clave) {
              valida = true;
              return valida;
            }
          }
        }
      } else if (Rol == "DIRECTOR") {
        Director obj;
        while (fread(&obj, vecTamObjetos[x], 1, pFile)) {
          if (obj.getLegajo() == legajo) {
            if (obj.getClave() == clave) {
              valida = true;
              return valida;
            }
          }
        }
      } else if (Rol == "PROFESOR") {
        Profesor obj;
        while (fread(&obj, vecTamObjetos[x], 1, pFile)) {
          if (obj.getLegajo() == legajo) {
            if (obj.getClave() == clave) {
              valida = true;
              return valida;
            }
          }
        }
      }
      else {
        Alumno obj;
        while (fread(&obj, vecTamObjetos[x], 1, pFile)) {
          if (obj.getLegajo() == legajo) {
            if (obj.getClave() == clave) {
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

bool estadoValido(string Rol, int legajo, const char *vecNombresFiles[],
                  int vecTamObjetos[], string vecNombresRoles[]) {
  bool valido = false;
  FILE *pFile = nullptr;

  for (x = 0; x < CANTIDADOBJETOS; x++) {
    if (Rol == vecNombresRoles[x]) {
      if (!(pFile = fopen(vecNombresFiles[x], "rb+"))) {
        if (!(pFile = fopen(vecNombresFiles[x], "wb+"))) {
          cout << endl << "---- ERROR AL ABRIR O CREAR EL ARCHIVO ----" << endl;
          return false;
        }
      }

      if (Rol == "ADMINISTRADOR") {
        Administrador obj;
        while (fread(&obj, vecTamObjetos[x], 1, pFile)) {
          if (obj.getId() == legajo)
            valido = true;
          return valido;
        }
      } else if (Rol == "DIRECTOR") {
        Director obj;
        while (fread(&obj, vecTamObjetos[x], 1, pFile)) {
          if (obj.getLegajo() == legajo) {
            if (obj.getEstado() == true) {
              valido = true;
              return valido;
            }
          }
        }
      } else if (Rol == "PROFESOR") {
        Profesor obj;
        while (fread(&obj, vecTamObjetos[x], 1, pFile)) {
          if (obj.getLegajo() == legajo) {
            if (obj.getEstado() == true) {
              valido = true;
              return valido;
            }
          }
        }
      }
      else {
        Alumno obj;
        while (fread(&obj, vecTamObjetos[x], 1, pFile)) {
          if (obj.getLegajo() == legajo) {
            if (obj.getEstado() == true) {
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

Alumno buscarAlumno(int ID) {
  Alumno aux;
  int pos = 0;

  while (aux.leerEnDiscoAlumnoPorPosicion(pos)) {
    if (aux.getLegajo() == ID) {
      return aux;
    }
    pos++;
  }
}

Profesor buscarProfesor(int ID) {
  Profesor aux;
  int pos = 0;

  while (aux.leerEnDiscoProfesorPorPosicion(pos)) {
    if (aux.getLegajo() == ID) {
      return aux;
    }
    pos++;
  }
}

Materia buscarMateria(int ID) {
  Materia aux;
  int pos = 0;

  while (aux.leerEnDiscoMateriaPorPosicion(pos)) {
    if (aux.getId() == ID) {
      return aux;
    }
    pos++;
  }
}

Evaluacion buscarEvaluacion(int ID) {
  Evaluacion aux;
  int pos = 0;

  while (aux.leerEnDiscoEvaluacionPorPosicion(pos)) {
    if (aux.getId() == ID) {
      return aux;
    }
    pos++;
  }
}

int buscarInscripcionMateria(int Legajo) {
  InscripcionMateria aux;
  int pos = 0;

  while (aux.leerEnDiscoInscripcionMateriaPorPosicion(pos)) {
    if (aux.getAlumno().getLegajo() == Legajo) {
      return pos;
    }
    pos++;
  }
  return -1;
}

int buscarInscripcionEvaluacion(int Legajo) {
  InscripcionEvaluacion aux;
  int pos = 0;

  while (aux.leerEnDiscoInscripcionEvaluacionPorPosicion(pos)) {
    if (aux.getAlumno().getLegajo() == Legajo) {
      return pos;
    }
    pos++;
  }

  return -1;
}

bool estaAlumnoInscritoEnMateria(int legAlumno, int idMateria) {
  InscripcionMateria aux;
  int pos = 0;

  while (aux.leerEnDiscoInscripcionMateriaPorPosicion(pos)) {
    if (aux.getAlumno().getLegajo() == legAlumno) {
      Materia *materias = aux.getMaterias();  // Obtener el puntero al arreglo de materias
      for (int i = 0; i < 7; i++) {
        if (materias[i].getId() == idMateria) {
          return true;
        }
      }
    }
    pos++;
  }

  return false;
}

bool estaAlumnoInscritoEnEvaluacion(int legAlumno, int idEvaluacion) {
  InscripcionEvaluacion inscEvaluacionObj;
  int pos = 0;

  while (inscEvaluacionObj.leerEnDiscoInscripcionEvaluacionPorPosicion(pos)) {
    if (inscEvaluacionObj.getAlumno().getLegajo() == legAlumno) {
      Materia *materias = inscEvaluacionObj.getMaterias();
      for (int i = 0; i < 7; i++) {
        if (materias[i].getId() == idMateriaPorIdEvaluacion(idEvaluacion)) {
          return true;
        }
      }
    }
    pos++;
  }

  return false;
}

int idMateriaPorIdEvaluacion(int idEvaluacion) {
  FILE *pEvaluacion;
  Evaluacion evaluacionObj;

  if (!(pEvaluacion = fopen("evaluaciones.dat", "rb"))) {
    cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
    return -1;
  }

  while (fread(&evaluacionObj, sizeof(Evaluacion), 1, pEvaluacion)) {
    if (evaluacionObj.getId() == idEvaluacion) {
      return evaluacionObj.getIdMateria();
    }
  }
}

void inscribirseMateriaAlumno (int legajo) {
    InscripcionMateria aux;

    if(contarMateriasInscripto() < 7){
        aux.inscribirseMateria(legajo);
    }
    else{
        cout << endl << "---- ERROR : LÍMITE DE INSCRIPCIONES ALCANZADO ----" << endl << endl << endl;
        system("pause");
    }
}

void inscribirseEvaluacionAlumno(int legajo) {
    InscripcionEvaluacion aux;

    aux.inscribirseEvaluacion(legajo);
}

///--- MENÚS ROLES ---\\

///--- MENÚ ADMINISTRADOR ---\\

void menuAdministrador() {
  int opcion;
  int legajoDirector;
  int nuevaClave;

  // CARGANDO();
  cout << "----------------------------------------------------" << endl;
  cout << "                 MENÚ ADMINISTRADOR                 " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "1. CREAR PERFIL DIRECTOR                            " << endl;
  cout << "2. ACTIVAR PERFIL DIRECTOR                          " << endl;
  cout << "3. DESACTIVAR PERFIL DIRECTOR                       " << endl;
  cout << "4. GESTIÓN CONTRASEÑAS                              " << endl;
  cout << "5. CAMBIAR CONTRASEÑA                               " << endl;
  cout << "0. VOLVER AL MENÚ PRINCIPAL                         " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
  cout << "----------------------------------------------------" << endl;

  opcion = _getch();

  while (opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 53 && opcion != 48) {
    cout << "---- ERROR : OPCIÓN INVÁLIDA ----" << endl;
    Sleep(500);
    system("cls");

    cout << "----------------------------------------------------" << endl;
    cout << "                 MENÚ ADMINISTRADOR                 " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "1. CREAR PERFIL DIRECTOR                            " << endl;
    cout << "2. ACTIVAR PERFIL DIRECTOR                          " << endl;
    cout << "3. DESACTIVAR PERFIL DIRECTOR                       " << endl;
    cout << "4. GESTIÓN CONTRASEÑAS                              " << endl;
    cout << "5. CAMBIAR CONTRASEÑA                               " << endl;
    cout << "0. VOLVER AL MENÚ PRINCIPAL                         " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
    cout << "----------------------------------------------------" << endl;

    opcion = _getch();
  }

  switch (opcion) {
    case 49:
      system("cls");
      directorObj.grabarEnDiscoDirector();
      system("cls");
      menuAdministrador();
      break;
    case 50:
      system("cls");
      cout << "ACTIVANDO PERFIL DIRECTOR" << endl;

      cout << endl << "\t- Legajo (Nro. de Legajo 0 para salir): ";
      cin >> legajoDirector;
      validarLegajo(legajoDirector);

      directorObj.activarDirector(legajoDirector);

      system("cls");
      menuAdministrador();
      break;
    case 51:
      system("cls");
      cout << "DESACTIVANDO PERFIL DIRECTOR" << endl;

      cout << endl << "\t- Legajo (Nro. de Legajo 0 para salir): ";
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
      cout << endl << "\t - Contraseña nueva (numérica / Contraseña 0 para salir): ";
      cin >> nuevaClave;

      administradorObj.cambiarClave(legajo, nuevaClave);

      if(nuevaClave != 0){
        clave = nuevaClave;
      }

      system("cls");
      menuAdministrador();
      break;
    case 48:
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

  // CARGANDO();
  cout << "----------------------------------------------------" << endl;
  cout << "                  MENÚ CONTRASEÑAS                  " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "1. BLANQUEAR CONTRASEÑA DIRECTOR                    " << endl;
  cout << "2. BLANQUEAR CONTRASEÑA PROFESOR                    " << endl;
  cout << "3. BLANQUEAR CONTRASEÑA ALUMNO                      " << endl;
  cout << "0. VOLVER AL MENÚ ADMINISTRADOR                     " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
  cout << "----------------------------------------------------" << endl;

  opcion = _getch();

  while (opcion != 49 && opcion != 50 && opcion != 51 && opcion != 48) {
    cout << "---- ERROR : OPCIÓN INVÁLIDA ----" << endl;
    Sleep(500);
    system("cls");

    cout << "----------------------------------------------------" << endl;
    cout << "                  MENÚ CONTRASEÑAS                  " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "1. BLANQUEAR CONTRASEÑA DIRECTOR                    " << endl;
    cout << "2. BLANQUEAR CONTRASEÑA PROFESOR                    " << endl;
    cout << "3. BLANQUEAR CONTRASEÑA ALUMNO                      " << endl;
    cout << "0. VOLVER AL MENÚ ADMINISTRADOR                     " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
    cout << "----------------------------------------------------" << endl;

    opcion = _getch();
  }

  switch (opcion) {
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
      menuAdministrador();
      break;
    default:
      cout << "OPCIÓN no válida." << endl;
  }
}

///--- MENÚ DIRECTIVO ---\\

void menuDirectivo() {
  int opcion;
  int legajoDirector;
  int nuevaClave;

  // CARGANDO();
  cout << "----------------------------------------------------" << endl;
  cout << "                   MENÚ DIRECTIVO                   " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "1. GESTIÓN PERFIL PROFESOR                          " << endl;
  cout << "2. GESTIÓN PERFIL ALUMNO                            " << endl;
  cout << "3. GESTIÓN PLAN DE ESTUDIO                          " << endl;
  cout << "4. GESTIÓN AVISOS                                   " << endl;
  cout << "5. CAMBIAR CONTRASEÑA                               " << endl;
  cout << "0. VOLVER AL MENÚ PRINCIPAL                         " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
  cout << "----------------------------------------------------" << endl;

  opcion = _getch();

  while (opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 53 && opcion != 48) {
    cout << "---- ERROR : OPCIÓN INVÁLIDA ----" << endl;
    Sleep(500);
    system("cls");

    cout << "----------------------------------------------------" << endl;
    cout << "                   MENÚ DIRECTIVO                   " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "1. GESTIÓN PERFIL PROFESOR                          " << endl;
    cout << "2. GESTIÓN PERFIL ALUMNO                            " << endl;
    cout << "3. GESTIÓN PLAN DE ESTUDIO                          " << endl;
    cout << "4. GESTIÓN AVISOS                                   " << endl;
    cout << "5. CAMBIAR CONTRASEÑA                               " << endl;
    cout << "0. VOLVER AL MENÚ PRINCIPAL                         " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
    cout << "----------------------------------------------------" << endl;

    opcion = _getch();
  }

  switch (opcion) {
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
      subMenuDirectivoAvisos();
      break;
    case 53:
      system("cls");
      cout << "CAMBIANDO CONTRASEÑA" << endl;

      cout << endl << "\t - Contraseña anterior: " << clave << endl;
      cout << endl << "\t - Contraseña nueva (numérica / Contraseña 0 para salir): ";
      cin >> nuevaClave;

      directorObj.cambiarClave(legajo, nuevaClave);

      if(nuevaClave != 0){
        clave = nuevaClave;
      }

      system("cls");
      menuDirectivo();
      break;
    case 48:
      system("cls");
      menuPrincipal();
      break;
    default:
      cout << "OPCIÓN no válida." << endl;
  }
}

void subMenuDirectivoProfesor() {
  int opcion;
  int legajoProfesor;
  int nuevaClave;

  // CARGANDO();
  cout << "----------------------------------------------------" << endl;
  cout << "                  GESTIÓN PROFESOR                  " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "1. CREAR PERFIL PROFESOR                            " << endl;
  cout << "2. ACTIVAR PERFIL PROFESOR                          " << endl;
  cout << "3. DESACTIVAR PERFIL PROFESOR                       " << endl;
  cout << "0. VOLVER AL MENÚ DIRECTIVO                         " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
  cout << "----------------------------------------------------" << endl;

  opcion = _getch();

  while (opcion != 49 && opcion != 50 && opcion != 51 && opcion != 48) {
    cout << "---- ERROR : OPCIÓN INVÁLIDA ----" << endl;
    Sleep(500);
    system("cls");

    cout << "----------------------------------------------------" << endl;
    cout << "                  GESTIÓN PROFESOR                  " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "1. CREAR PERFIL PROFESOR                            " << endl;
    cout << "2. ACTIVAR PERFIL PROFESOR                          " << endl;
    cout << "3. DESACTIVAR PERFIL PROFESOR                       " << endl;
    cout << "0. VOLVER AL MENÚ DIRECTIVO                         " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
    cout << "----------------------------------------------------" << endl;

    opcion = _getch();
  }

  switch (opcion) {
    case 49:
      system("cls");
      profesorObj.grabarEnDiscoProfesor();
      system("cls");
      subMenuDirectivoProfesor();
      break;
    case 50:
      system("cls");
      cout << "ACTIVANDO PERFIL PROFESOR" << endl;

      cout << endl << "\t- Legajo (Nro. de Legajo 0 para salir): ";
      cin >> legajoProfesor;
      validarLegajo(legajoProfesor);

      profesorObj.activarProfesor(legajoProfesor);

      system("cls");
      subMenuDirectivoProfesor();
      break;
    case 51:
      system("cls");
      cout << "DESACTIVANDO PERFIL PROFESOR" << endl;

      cout << endl << "\t- Legajo (Nro. de Legajo 0 para salir): ";
      cin >> legajoProfesor;
      validarLegajo(legajoProfesor);

      profesorObj.desactivarProfesor(legajoProfesor);

      system("cls");
      subMenuDirectivoProfesor();
      break;
    case 48:
      system("cls");
      menuDirectivo();
      break;
    default:
      cout << "OPCIÓN no válida." << endl;
  }
}

void subMenuDirectivoAlumno() {
  int opcion;
  int legajoAlumno;
  int nuevaClave;

  // CARGANDO();
  cout << "----------------------------------------------------" << endl;
  cout << "                   GESTIÓN ALUMNO                   " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "1. CREAR PERFIL ALUMNO                              " << endl;
  cout << "2. ACTIVAR PERFIL ALUMNO                            " << endl;
  cout << "3. DESACTIVAR PERFIL ALUMNO                         " << endl;
  cout << "0. VOLVER AL MENÚ DIRECTIVO                         " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
  cout << "----------------------------------------------------" << endl;

  opcion = _getch();

  while (opcion != 49 && opcion != 50 && opcion != 51 && opcion != 48) {
    cout << "---- ERROR : OPCIÓN INVÁLIDA ----" << endl;
    Sleep(500);
    system("cls");

    cout << "----------------------------------------------------" << endl;
    cout << "                   GESTIÓN ALUMNO                   " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "1. CREAR PERFIL ALUMNO                              " << endl;
    cout << "2. ACTIVAR PERFIL ALUMNO                            " << endl;
    cout << "3. DESACTIVAR PERFIL ALUMNO                         " << endl;
    cout << "0. VOLVER AL MENÚ DIRECTIVO                         " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
    cout << "----------------------------------------------------" << endl;

    opcion = _getch();
  }

  switch (opcion) {
    case 49:
      system("cls");
      alumnoObj.grabarEnDiscoAlumno();
      system("cls");
      subMenuDirectivoAlumno();
      break;
    case 50:
      system("cls");
      cout << "ACTIVANDO PERFIL ALUMNO" << endl;

      cout << endl << "\t- Legajo (Nro. de Legajo 0 para salir): ";
      cin >> legajoAlumno;
      validarLegajo(legajoAlumno);

      alumnoObj.activarAlumno(legajoAlumno);

      system("cls");
      subMenuDirectivoAlumno();
      break;
    case 51:
      system("cls");
      cout << "DESACTIVANDO PERFIL ALUMNO" << endl;

      cout << endl << "\t- Legajo (Nro. de Legajo 0 para salir):: ";
      cin >> legajoAlumno;
      validarLegajo(legajoAlumno);

      alumnoObj.desactivarAlumno(legajoAlumno);

      system("cls");
      subMenuDirectivoAlumno();
      break;
    case 48:
      system("cls");
      menuDirectivo();
      break;
    default:
      cout << "OPCIÓN no válida." << endl;
  }
}

void subMenuDirectivoAvisos() {
  int opcion;
  int legajoAlumno;
  int nuevaClave;
  Aviso AvisoObj;

  // CARGANDO();
  cout << "----------------------------------------------------" << endl;
  cout << "                   GESTIÓN AVISOS                   " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "1. CREAR AVISO                                      " << endl;
  cout << "2. VER AVISOS                                       " << endl;
  cout << "0. VOLVER AL MENÚ DIRECTIVO                         " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
  cout << "----------------------------------------------------" << endl;

  opcion = _getch();

  while (opcion != 49 && opcion != 50 && opcion != 48) {
    cout << "---- ERROR : OPCIÓN INVÁLIDA ----" << endl;
    Sleep(500);
    system("cls");

    cout << "----------------------------------------------------" << endl;
    cout << "                   GESTIÓN AVISOS                   " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "1. CREAR AVISO                                      " << endl;
    cout << "2. VER AVISOS                                       " << endl;
    cout << "0. VOLVER AL MENÚ DIRECTIVO                         " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
    cout << "----------------------------------------------------" << endl;

    opcion = _getch();
  }

  switch (opcion) {
    case 49:
      system("cls");

      AvisoObj.grabarEnDisco();

      system("cls");
      subMenuDirectivoAvisos();
      break;
    case 50:
      system("cls");

      if (contarAvisos() > 0) {
        AvisoObj.leerEnDisco();
      }
      else {
        cout << endl
             << "---- ERROR : NO SE ENCONTRARON AVISOS CARGADOS EN EL SISTEMA ----"
             << endl
             << endl;
        cout << endl << endl;
      }

      system("pause");
      system("cls");
      subMenuDirectivoAvisos();
      break;
    case 48:
      system("cls");
      menuDirectivo();
      break;
    default:
      cout << "OPCIÓN no válida." << endl;
  }
}

void subMenuDirectivoPlanEstudio() {
  int opcion;
  int cantMaterias;
  Materia materiaObj;

  // CARGANDO();
  cout << "----------------------------------------------------" << endl;
  cout << "               GESTIÓN PLAN DE ESTUDIO              " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "1. CARGAR MATERIAS                                  " << endl;
  cout << "2. ASIGNAR PROFESORES                               " << endl;
  cout << "3. VER PLAN DE ESTUDIO                              " << endl;
  cout << "0. VOLVER AL MENÚ DIRECTIVO                         " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
  cout << "----------------------------------------------------" << endl;

  opcion = _getch();

  while (opcion != 49 && opcion != 50 && opcion != 51 && opcion != 48) {
    cout << "---- ERROR : OPCIÓN INVÁLIDA ----" << endl;
    Sleep(500);
    system("cls");

    cout << "----------------------------------------------------" << endl;
    cout << "               GESTIÓN PLAN DE ESTUDIO              " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "1. CARGAR MATERIAS                                  " << endl;
    cout << "2. ASIGNAR PROFESORES                               " << endl;
    cout << "3. VER PLAN DE ESTUDIO                              " << endl;
    cout << "0. VOLVER AL MENÚ DIRECTIVO                         " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
    cout << "----------------------------------------------------" << endl;

    opcion = _getch();
  }

  switch (opcion) {
    case 49:
      system("cls");

      cout << "CARGANDO MATERIAS - PLAN DE ESTUDIO 2003 (Cant. materias 0 para salir)" << endl;

      if (contarMaterias() < 21) {
        cout << endl << "\t- Cantidad de materias a cargar: ";
        cin >> cantMaterias;

        if (cantMaterias == 0) {
          system("cls");
          subMenuDirectivoPlanEstudio();
          break;
        }

        while (cantMaterias > 21 || cantMaterias > (21 - contarMaterias()) ||
               cantMaterias < 0) {
          cout << endl
               << "---- ERROR : CANTIDAD DISPONIBLE: "
               << (21 - contarMaterias()) << " ----" << endl;
          Sleep(1500);
          system("cls");

          cout << "CARGANDO MATERIAS - PLAN DE ESTUDIO 2003" << endl;

          cout << endl << "\t- Cantidad de materias a cargar: ";
          cin >> cantMaterias;
        }

        for (int x = 0; x < cantMaterias; x++) {
          system("cls");
          cout << "CARGANDO MATERIAS - PLAN DE ESTUDIO 2003" << endl;
          materiaObj.grabarEnDiscoMateria();
        }

      }
      else {
        cout << endl << "---- LÍMITE DE MATERIAS CARGADAS ALCANZADO ----" << endl;
        cout << endl << endl;
        system("pause");
      }

      system("cls");
      subMenuDirectivoPlanEstudio();
      break;
    case 50:
      system("cls");

      cout << "ASIGNANDO PROFESORES - PLAN DE ESTUDIO 2003" << endl;

      if (!usuariosEspecificosCargados("PROFESOR", vecNombresFiles, vecTamObjetos, vecNombresRoles)) {
        cout << endl
             << "---- ERROR : NO SE ENCONTRARON USUARIOS CON ROL 'PROFESOR' CARGADOS EN EL SISTEMA ----"
             << endl
             << endl;
        cout << endl << endl;
        system("pause");
        system("cls");
      }
      else {
        if (contarMaterias() < 21) {
          cout << endl
               << "---- ERROR : PLAN DE ESTUDIOS INCOMPLETO, "
               << 21 - contarMaterias() << " MATERIAS RESTANTES POR CARGAR ----"
               << endl
               << endl;
          cout << endl << endl;
          system("pause");
          system("cls");
        }
else {
          asignarProfesores();
        }
      }

      system("cls");
      subMenuDirectivoPlanEstudio();
      break;
    case 51:
      system("cls");

      cout << "PLAN DE ESTUDIO 2003" << endl << endl;
      if (contarMaterias() > 0) {
        mostrarPlanEstudio();
        system("pause");
      }
      else {
        cout << endl
             << "---- ERROR : NO SE ENCONTRARON MATERIAS CARGADAS EN EL SISTEMA ----"
             << endl
             << endl;
        cout << endl << endl;
        system("pause");
        system("cls");
      }

      system("cls");
      subMenuDirectivoPlanEstudio();
      break;
    case 48:
      system("cls");
      menuDirectivo();
      break;
    default:
      cout << "OPCIÓN no válida." << endl;
  }
}

int contarMaterias() {
  FILE *pMat;
  int cantMaterias = 0;

  if (!(pMat = fopen("materias.dat", "ab"))) {
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
    if (materiaObj.getProfesor().getLegajo() != 0) {
      continue;
    }

    bool valido = false;
    bool activo = false;

    while (!valido || !activo) {
      if (!(pProfesor = fopen("profesores.dat", "rb"))) {
        system("cls");
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO DE PROFESORES ----" << endl;
        fclose(pMat);
        return;
      }

      system("cls");
      cout << "ASIGNANDO PROFESORES - PLAN DE ESTUDIO 2003 (Nro. de Legajo 0 para salir)" << endl;

      cout << endl << "\t - Materia: " << materiaObj.getNombreMateria() << endl;
      cout << endl << "\t - Legajo Profesor: ";
      cin >> legajoProfesor;

      if (legajoProfesor == 0) {
        fclose(pProfesor);
        fclose(pMat);
        return;
      }

      while (fread(&profesorObj, sizeof(Profesor), 1, pProfesor)) {
        if (profesorObj.getLegajo() == legajoProfesor) {
          valido = true;
          if (profesorObj.getEstado()) {
            activo = true;
          }
          break;
        }
      }
      fclose(pProfesor);

      if (!valido) {
        cout << endl
             << "---- ERROR : NO SE ENCONTRÓ UN PROFESOR CON LEGAJO '"
             << legajoProfesor << "' CARGADO EN EL SISTEMA ----" << endl
             << endl;
        system("pause");
      }

      if (valido && !activo) {
        cout << endl
             << "---- ERROR : EL PROFESOR CON LEGAJO '" << legajoProfesor << "' SE ENCUENTRA INACTIVO ----" << endl
             << endl;
        valido = false;
        system("pause");
      }
    }

    materiaObj.setProfesor(legajoProfesor);
    long offset = ftell(pMat) - sizeof(Materia);
    fseek(pMat, offset, SEEK_SET);
    fwrite(&materiaObj, sizeof(Materia), 1, pMat);
    fflush(pMat);

    fseek(pMat, offset + sizeof(Materia), SEEK_SET);
  }

  fclose(pMat);
  cout << endl << "¡PLAN DE ESTUDIO CARGADO CON ÉXITO!" << endl << endl;
  system("pause");
}

void mostrarPlanEstudio() {
  FILE *pMat;
  Materia materiaObj;
  int anchoID = 6;
  int anchoMateria = 21;
  int anchoProfesor = 16;

  if (!(pMat = fopen("materias.dat", "rb"))) {
    cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
    return;
  }

  cout << left << setw(anchoID) << "ID";
  cout << "|";
  cout << left << setw(anchoMateria) << "Materia";
  cout << "|";
  cout << left << setw(anchoProfesor) << "Profesor" << endl;

  cout << string(anchoID, '-') << "+" << string(anchoMateria, '-') << "+"
       << string(anchoProfesor, '-') << endl;

  while (fread(&materiaObj, sizeof(Materia), 1, pMat)) {
    cout << left << setw(anchoID) << materiaObj.getId() << "|" << left
         << setw(anchoMateria) << materiaObj.getNombreMateria() << "|";

    if (materiaObj.getProfesor().getLegajo() == 0) {
      cout << left << setw(anchoProfesor) << "No Asignado";
    }
    else {
      string nombreCompleto = string(materiaObj.getProfesor().getNombre()) +
                              " " +
                              string(materiaObj.getProfesor().getApellido());
      cout << left << setw(anchoProfesor) << nombreCompleto;
    }
    cout << endl;
  }

  cout << endl << endl;

  fclose(pMat);
}

///--- MENÚ PROFESOR ---\\

void menuProfesor() {
  int opcion;
  int nuevaClave;
  Aviso AvisoObj;

  // CARGANDO();
  cout << "----------------------------------------------------" << endl;
  cout << "                   MENÚ PROFESOR                    " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "1. GESTIÓN MATERIAS                                 " << endl;
  cout << "2. VER AVISOS                                       " << endl;
  cout << "3. CAMBIAR CONTRASEÑA                               " << endl;
  cout << "0. VOLVER AL MENÚ PRINCIPAL                         " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
  cout << "----------------------------------------------------" << endl;

  opcion = _getch();

  while (opcion != 49 && opcion != 50 && opcion != 51 && opcion != 48) {
    cout << "---- ERROR : OPCIÓN INVÁLIDA ----" << endl;
    Sleep(500);
    system("cls");

    cout << "----------------------------------------------------" << endl;
    cout << "                   MENÚ PROFESOR                    " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "1. GESTIÓN MATERIAS                                 " << endl;
    cout << "2. VER AVISOS                                       " << endl;
    cout << "3. CAMBIAR CONTRASEÑA                               " << endl;
    cout << "0. VOLVER AL MENÚ PRINCIPAL                         " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
    cout << "----------------------------------------------------" << endl;

    opcion = _getch();
  }

  switch (opcion) {
    case 49:
      system("cls");
      ///-- >> SUB MENÚ GESTIÓN MATERIAS
      subMenuProfesorGestionMaterias();
      break;
    case 50:
      system("cls");

      if (contarAvisos() > 0) {
        AvisoObj.leerEnDisco();
      }
      else {
        cout << endl
             << "---- ERROR : NO SE ENCONTRARON AVISOS CARGADOS EN EL SISTEMA ----"
             << endl
             << endl;
        cout << endl << endl;
      }

      system("pause");
      system("cls");
      menuProfesor();
      break;
    case 51:
      system("cls");
      cout << "CAMBIANDO CONTRASEÑA" << endl;

      cout << endl << "\t - Contraseña anterior: " << clave << endl;
      cout << endl << "\t - Contraseña nueva (numérica / Contraseña 0 para salir): ";
      cin >> nuevaClave;

      profesorObj.cambiarClave(legajo, nuevaClave);

      if(nuevaClave != 0){
        clave = nuevaClave;
      }

      system("cls");
      menuProfesor();
      break;
    case 48:
      system("cls");
      menuPrincipal();
      break;
    default:
      cout << "OPCIÓN no válida." << endl;
  }
}

void subMenuProfesorGestionMaterias() {
  int opcion;
  Evaluacion evaluacionObj;

  // CARGANDO();
  cout << "----------------------------------------------------" << endl;
  cout << "                  GESTIÓN MATERIAS                  " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "1. VER MATERIAS ASIGNADAS                           " << endl;
  cout << "2. CREAR EXAMEN FINAL                               " << endl;
  cout << "3. VER EXAMENES FINALES                             " << endl;
  cout << "4. CARGAR NOTAS                                     " << endl;
  cout << "0. VOLVER AL MENÚ PROFESOR                          " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
  cout << "----------------------------------------------------" << endl;

  opcion = _getch();

  while (opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 48) {
    cout << "---- ERROR : OPCIÓN INVÁLIDA ----" << endl;
    Sleep(500);
    system("cls");

    cout << "----------------------------------------------------" << endl;
    cout << "                  GESTIÓN MATERIAS                  " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "1. VER MATERIAS ASIGNADAS                           " << endl;
    cout << "2. CREAR EXAMEN FINAL                               " << endl;
    cout << "3. VER EXAMENES FINALES                             " << endl;
    cout << "4. CARGAR NOTAS                                     " << endl;
    cout << "0. VOLVER AL MENÚ PROFESOR                          " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
    cout << "----------------------------------------------------" << endl;

    opcion = _getch();
  }

  switch (opcion) {
    case 49:
      system("cls");

      cout << "MOSTRANDO MATERIAS ASIGNADAS - PLAN DE ESTUDIO 2003" << endl
           << endl;

      verMateriasAsignadas();
      system("pause");

      system("cls");
      subMenuProfesorGestionMaterias();
      break;
    case 50:
      system("cls");

      if (MateriasAsignadas()) {
        evaluacionObj.grabarEnDisco(legajo);
      }

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
      if (contarInscipcionEvaluaciones() > 0) {
            cargarNotas();
      }
      else {
        cout << endl
             << "---- ERROR : NO SE ENCONTRARON INSCRIPCIONES A EXÁMENES FINALES CARGADAS EN EL SISTEMA ----"
             << endl
             << endl;
        cout << endl << endl;
      }

      system("pause");
      system("cls");
      subMenuProfesorGestionMaterias();
      break;
    case 48:
      system("cls");
      menuProfesor();
      break;
    default:
      cout << "OPCIÓN no válida." << endl;
  }
}

bool MateriasAsignadas() {
  FILE *pMat;
  Materia materiaObj;

  if (!(pMat = fopen("materias.dat", "rb"))) {
    cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
    return false;
  }

  while (fread(&materiaObj, sizeof(Materia), 1, pMat)) {
    if (materiaObj.getProfesor().getLegajo() == legajo) {
      return true;
    }
  }

  fclose(pMat);
  cout << endl
       << "---- ERROR : EL PROFESOR CON LEGAJO " << legajo
       << " NO POSEE MATERIAS ASIGNADAS PARA CREAR EXAMENES FINALES ----"
       << endl
       << endl;

  system("pause");
  return false;
}

void verMateriasAsignadas() {
  FILE *pMat;
  Materia materiaObj;
  int anchoID = 6;
  int anchoMateria = 16;

  if (!(pMat = fopen("materias.dat", "rb"))) {
    cout << endl
         << "---- NO SE ENCONTRARON REGISTROS DE MATERIAS ASIGNADAS ----"
         << endl
         << endl;
    return;
  }

  cout << left << setw(anchoID) << "ID";
  cout << "|";
  cout << left << setw(anchoMateria) << "Materia" << endl;

  cout << string(anchoID, '-') << "+" << string(anchoMateria, '-') << endl;

  while (fread(&materiaObj, sizeof(Materia), 1, pMat)) {
    if (materiaObj.getProfesor().getLegajo() == legajo) {
      cout << left << setw(anchoID) << materiaObj.getId() << "|" << left
           << setw(anchoMateria) << materiaObj.getNombreMateria() << endl;
    }
  }

  cout << endl << endl;

  fclose(pMat);
}

void BuscarEvaluacionesDeMateriasAsignadasAlumno(const InscripcionMateria &materiasInscripto) {
  int pos = 0;
  Evaluacion evaluaciones;

  cout << "--------------------------------------" << endl;
  cout << "-     EVALUACIONES DISPONIBLES        " << endl;
  while (evaluaciones.leerEnDiscoEvaluacionPorPosicion(pos)) {
    for (int i = 0; i < 7; i++) {
      if (evaluaciones.getIdMateria() == materiasInscripto.getMaterias2(i)) {
        evaluaciones.mostrarEvaluacion();
      }
    }

    pos++;
  }
}

void BuscarEvaluacionesInscritoAlumno(const InscripcionEvaluacion &evaluacionInscripto) {
  bool hayInscripciones = false;
  int pos = 0;
  Evaluacion evaluaciones;

  cout << "-------------------------------------" << endl;
  cout << "    INCRIPCIONES EXAMENES FINALES    " << endl;
  while (evaluaciones.leerEnDiscoEvaluacionPorPosicion(pos)) {
    for (int i = 0; i < 7; i++) {
      if (evaluaciones.getIdMateria() == evaluacionInscripto.getMaterias2(i)) {
        hayInscripciones = true;
        evaluaciones.mostrarEvaluacion();
      }
    }

    pos++;
  }

  if (!hayInscripciones) {
    system("cls");
    cout << endl
         << "---- NO SE ENCONTRARON INSCRIPCIONES A EXÁMENES FINALES ----"
         << endl
         << endl;
    return;
  }

  cout << endl << endl;
}

InscripcionMateria BuscarArchvoInscripcionMateria(int legajo) {
  InscripcionMateria archivoInscripcionMateria;
  int pos = 0;

  while (archivoInscripcionMateria.leerEnDiscoInscripcionMateriaPorPosicion(pos)) {
    if (archivoInscripcionMateria.getAlumno().getLegajo() == legajo) {
      return archivoInscripcionMateria;
    }

    pos++;
  }
}

InscripcionEvaluacion BuscarArchivoInscripcionEvaluacion(int legajo) {
  InscripcionEvaluacion archivoInscripcionEvaluacion;
  int pos = 0;

  while (archivoInscripcionEvaluacion.leerEnDiscoInscripcionEvaluacionPorPosicion(pos)) {
    if (archivoInscripcionEvaluacion.getAlumno().getLegajo() == legajo) {
        return archivoInscripcionEvaluacion;
    }
    pos++;
  }
}

void ListarEvaluaciones(int legajo) {
  BuscarEvaluacionesDeMateriasAsignadasAlumno(
      BuscarArchvoInscripcionMateria(legajo));
}

void ListarEvaluacionesInscripto(int legajo) {
    InscripcionEvaluacion archivoInscripcionEvaluacion;

    BuscarEvaluacionesInscritoAlumno(BuscarArchivoInscripcionEvaluacion(legajo));
}

void verExamenesFinalesProfesor() {
  FILE *pEval;
  Evaluacion evaluacionObj;

  FILE *pMat;
  Materia materiaObj;

  time_t t = time(nullptr);
  tm *now = localtime(&t);
  time_t currentTime = mktime(now);

  int anchoID = 9;
  int anchoMateria = 15;
  int anchoFecha = 12;

  if (!(pEval = fopen("evaluaciones.dat", "rb"))) {
    cout << endl
         << "---- NO SE ENCONTRARON REGISTROS DE EXAMENES FINALES ----" << endl
         << endl;
    return;
  }

  cout << left << setw(anchoFecha) << "Fecha";
  cout << "|";
  cout << left << setw(anchoID) << "ID Final";
  cout << "|";
  cout << left << setw(anchoMateria) << "Materia" << endl;

  cout << string(anchoFecha, '-') << "+" << string(anchoID, '-') << "+"
       << string(anchoMateria, '-') << endl;

  while (fread(&evaluacionObj, sizeof(Evaluacion), 1, pEval)) {
    if (!(pMat = fopen("materias.dat", "rb"))) {
      cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
      return;
    }
    while (fread(&materiaObj, sizeof(Materia), 1, pMat)) {
      if (materiaObj.getProfesor().getLegajo() == legajo &&
          evaluacionObj.getIdMateria() == materiaObj.getId()) {
        break;
      }
    }

    tm specificDate = evaluacionObj.createDate(
        evaluacionObj.getFecha().getDia(), evaluacionObj.getFecha().getMes(),
        evaluacionObj.getFecha().getAnio());
    time_t specificTime = mktime(&specificDate);

    if (difftime(specificTime, currentTime) > 0) {
      if (evaluacionObj.getIdProfesor() == legajo) {
        cout << left << setw(anchoFecha)
             << evaluacionObj.getFecha().toString("DD/MM/YYYY") << "|" << left
             << setw(anchoID) << evaluacionObj.getId() << "|" << left
             << setw(anchoMateria) << materiaObj.getNombreMateria() << endl;
      }
    }
    fclose(pMat);
  }

  cout << endl << endl;

  fclose(pEval);
}

void cargarNotas() {
    FILE *pInscEvaluacion;
    InscripcionEvaluacion inscEvaluacionObj;

    int idFinal;
    int idMateria;
    float nota;
    bool flag = true, cargarNotas = false;

    if (!(pInscEvaluacion = fopen("InscripcionEvaluacion.dat", "rb+"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    cout << endl << "Ingrese el ID del examen final (ID examen final 0 para salir): ";
    cin >> idFinal;
    cout << endl;

    if (idFinal == 0) {
        fclose(pInscEvaluacion);
        cout << endl;
        return;
    }

    if (!validarExistenciaEvaluacion(idFinal)) {
        cout << endl << "---- ERROR : ID DE FINAL INEXISTENTE ----" << endl << endl;
        fclose(pInscEvaluacion);
        return;
    }

    idMateria = obtenerIdMateriaEvaluacion(idFinal);

    if(!validarProfesorAsignado(idMateria, legajo)) {
        cout << endl << "\t ---- ERROR : LA CARGA DE NOTAS DEL EXAMEN FINAL NO CORRESPONDE AL PROFESOR CON LEGAJO " << legajo << " ----" << endl << endl << endl;
        return;
    }

    while (fread(&inscEvaluacionObj, sizeof(InscripcionEvaluacion), 1, pInscEvaluacion)) {
        for (int x = 0; x < 7; x++) {
            if (inscEvaluacionObj.getMaterias()[x].getId() == idMateria) {
                if(inscEvaluacionObj.getMateriasNotas()[x] != 0){
                    ;
                }
                else{
                    if(flag){
                        cargarNotas = true;
                        flag = false;
                    }
                    system("cls");
                    cout << endl << "Ingrese el ID del examen final (ID examen final 0 para salir): " << idFinal << endl;
                    cout << endl << "\t - Legajo Alumno: " << inscEvaluacionObj.getAlumno().getLegajo() << endl;
                    cout << endl << "\t - Nota (1 a 10): ";
                    cin >> nota;

                    while (nota <= 0 || nota > 10) {
                        cout << endl << "---- ERROR : NOTA INVÁLIDA ---- " << endl << endl;
                        system("pause");
                        system("cls");
                        cout << endl << "Ingrese el ID del examen final (ID examen final 0 para salir): " << idFinal << endl;
                        cout << endl << "\t - Legajo Alumno: " << inscEvaluacionObj.getAlumno().getLegajo() << endl;
                        cout << endl << "\t - Nota (1 a 10): ";
                        cin >> nota;
                    }

                    inscEvaluacionObj.setMateriasNotas(nota, x);
                    long offset = ftell(pInscEvaluacion) - sizeof(InscripcionEvaluacion);
                    fseek(pInscEvaluacion, offset, SEEK_SET);
                    fwrite(&inscEvaluacionObj, sizeof(InscripcionEvaluacion), 1, pInscEvaluacion);
                    fseek(pInscEvaluacion, 0, SEEK_CUR);

                    break;
                }
            }
        }
    }

    if(!cargarNotas){
        cout << "\t ---- ERROR : NO SE ENCONTRARON NOTAS DISPONIBLES PARA CARGAR ----" << endl;
    }

    cout << endl << endl;
    fclose(pInscEvaluacion);
}


int contarInscipcionEvaluaciones() {
  FILE *pInscEvaluacion;
  int cantInscEvals = 0;

  if (!(pInscEvaluacion = fopen("InscripcionEvaluacion.dat", "ab"))) {
    cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
    return -1;
  }

  fseek(pInscEvaluacion, 0, SEEK_END);
  cantInscEvals += ftell(pInscEvaluacion) / sizeof(InscripcionEvaluacion);
  fseek(pInscEvaluacion, 0, SEEK_SET);
  fclose(pInscEvaluacion);

  return cantInscEvals;
}

bool validarExistenciaEvaluacion(int idFinal) {
    FILE *pEvaluacion;
    Evaluacion evaluacionObj;
    bool existe = false;

    if(!(pEvaluacion = fopen("evaluaciones.dat", "rb"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        system("pause");
        return false;
    }

    while(fread(&evaluacionObj, sizeof(Evaluacion), 1, pEvaluacion)) {
        if(evaluacionObj.getId() == idFinal) {
            existe = true;
            break;
        }
    };

    fclose(pEvaluacion);

    return existe;
}

int obtenerIdMateriaEvaluacion(int idFinal) {
    FILE *pEvaluacion;
    Evaluacion evaluacionObj;
    bool existe = false;
    int idMateria = 0;

    if(!(pEvaluacion = fopen("evaluaciones.dat", "rb"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return false;
    }

    while(fread(&evaluacionObj, sizeof(Evaluacion), 1, pEvaluacion)) {
        if(evaluacionObj.getId() == idFinal) {
            idMateria = evaluacionObj.getIdMateria();
            break;

        }
    };

    fclose(pEvaluacion);

    return idMateria;
}

bool validarProfesorAsignado(int idMateria, int legajo) {
    FILE *pMat;
    Materia materiaObj;
    bool exito = false;

    if(!(pMat = fopen("materias.dat", "rb"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return false;
    }

    while(fread(&materiaObj, sizeof(Materia), 1, pMat)) {
        if(materiaObj.getId() == idMateria) {
            if(materiaObj.getProfesor().getLegajo() == legajo) {
                exito = true;
                break;
            }
        }
    }

    fclose(pMat);

    if(!exito) {
        return false;
    }

    return true;
}
///--- MENÚ ALUMNO ---\\

void menuAlumno() {
  int opcion;
  int nuevaClave;
  Aviso AvisoObj;

  // CARGANDO();
  cout << "----------------------------------------------------" << endl;
  cout << "                    MENÚ ALUMNO                     " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "1. GESTIÓN CURSADA                                  " << endl;
  cout << "2. VER PLAN DE ESTUDIO                              " << endl;
  cout << "3. VER AVISOS                                       " << endl;
  cout << "4. CAMBIAR CONTRASEÑA                               " << endl;
  cout << "0. VOLVER AL MENÚ PRINCIPAL                         " << endl;
  cout << "----------------------------------------------------" << endl;
  cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
  cout << "----------------------------------------------------" << endl;

  opcion = _getch();

  while (opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 &&
         opcion != 48) {
    cout << "---- ERROR : OPCIÓN INVÁLIDA ----" << endl;
    Sleep(500);
    system("cls");

    cout << "----------------------------------------------------" << endl;
    cout << "                    MENÚ ALUMNO                     " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "1. GESTIÓN CURSADA                                  " << endl;
    cout << "2. VER PLAN DE ESTUDIO                              " << endl;
    cout << "3. VER AVISOS                                       " << endl;
    cout << "4. CAMBIAR CONTRASEÑA                               " << endl;
    cout << "0. VOLVER AL MENÚ PRINCIPAL                         " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -             " << endl;
    cout << "----------------------------------------------------" << endl;

    opcion = _getch();
  }

  switch (opcion) {
    case 49:
      system("cls");
      subMenuAlumnoPlanificacionCursada();
      menuAlumno();
      break;
    case 50:
      system("cls");
      if (contarMaterias() > 0) {
        cout << "PLAN DE ESTUDIO 2003" << endl << endl;
        mostrarPlanEstudio();
        system("pause");
      }
      else {
        cout << endl
             << "---- ERROR : NO SE ENCONTRARON MATERIAS CARGADAS EN EL SISTEMA ----"
             << endl
             << endl;
        cout << endl << endl;
        system("pause");
      }

      system("cls");
      menuAlumno();
      break;
    case 51:
      system("cls");

      if (contarAvisos() > 0) {
        AvisoObj.leerEnDisco();
      }
      else {
        cout << endl
             << "---- ERROR : NO SE ENCONTRARON AVISOS CARGADOS EN EL SISTEMA ----"
             << endl
             << endl;
        cout << endl << endl;
      }

      system("pause");
      system("cls");
      menuAlumno();
      break;
    case 52:
      system("cls");
      cout << "CAMBIANDO CONTRASEÑA" << endl;

      cout << endl << "\t - Contraseña anterior: " << clave << endl;
      cout << endl << "\t - Contraseña nueva (numérica / Contraseña 0 para salir): ";
      cin >> nuevaClave;

      alumnoObj.cambiarClave(legajo, nuevaClave);

      if(nuevaClave != 0){
        clave = nuevaClave;
      }

      menuAlumno();
      break;
    case 48:
      system("cls");
      menuPrincipal();
      break;
    default:
      cout << "OPCIÓN no válida." << endl;
  }
}

void validarLegajo(int &legajo) {
  while (legajo < 0 || cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl << "\t---- ERROR : LEGAJO INVÁLIDO ----" << endl;
    cout << endl << "\t - Legajo (Nro. de Legajo 0 para salir): ";
    cin >> legajo;
  }
}

bool validarMateria(int ID) {
  Materia aux;
  int posicion = 0;

  while (aux.leerEnDiscoMateriaPorPosicion(posicion)) {
    if (aux.getId() == ID) {
      return true;
    }
    posicion++;
  }

  return false;
}

bool validarEvaluacion(int ID) {
  Evaluacion aux;
  int posicion = 0;

  while (aux.leerEnDiscoEvaluacionPorPosicion(posicion)) {
    if (aux.getId() == ID) {
      return true;
    }
    posicion++;
  }

  return false;
}

void subMenuAlumnoPlanificacionCursada() {
  int opcion;
  Evaluacion EvaluacionObj;
  FILE *pEval;

  // CARGANDO();
  cout << "-----------------------------------------------------" << endl;
  cout << "                MENÚ GESTIÓN CURSADA                 " << endl;
  cout << "-----------------------------------------------------" << endl;
  cout << "1. VER PLANIFICACION                                 " << endl;
  cout << "2. ANOTARSE A MATERIAS                               " << endl;
  cout << "3. DARSE DE BAJA A MATERIAS                          " << endl;
  cout << "4. ANOTARSE A EXAMEN FINAL                           " << endl;
  cout << "5. VER EXAMENES FINALES                              " << endl;
  cout << "6. VER EXAMENES FINALES INSCRIPTO                    " << endl;
  cout << "0. VOLVER AL MENÚ ALUMNO                             " << endl;
  cout << "-----------------------------------------------------" << endl;
  cout << "             - SELECCIONE UNA OPCIÓN: -              " << endl;
  cout << "-----------------------------------------------------" << endl;

  opcion = _getch();

  while (opcion != 49 && opcion != 50 && opcion != 51 && opcion != 52 && opcion != 53 && opcion != 54 && opcion != 48) {
    cout << "---- ERROR : OPCIÓN INVÁLIDA ----" << endl;
    Sleep(500);
    system("cls");

    cout << "-----------------------------------------------------" << endl;
    cout << "                MENÚ GESTIÓN CURSADA                 " << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "1. VER PLANIFICACION                                 " << endl;
    cout << "2. ANOTARSE A MATERIAS                               " << endl;
    cout << "3. DARSE DE BAJA A MATERIAS                          " << endl;
    cout << "4. ANOTARSE A EXAMEN FINAL                           " << endl;
    cout << "5. VER EXAMENES FINALES                              " << endl;
    cout << "6. VER EXAMENES FINALES INSCRIPTO                    " << endl;
    cout << "0. VOLVER AL MENÚ ALUMNO                             " << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "             - SELECCIONE UNA OPCIÓN: -              " << endl;
    cout << "-----------------------------------------------------" << endl;

    opcion = _getch();
  }

  switch (opcion) {
    case 49:  /// VER PLANIF
      system("cls");
      inscripcionMateriaObj.mostrarRegistroDeIncriccionesMateria(legajo);

      system("cls");
      subMenuAlumnoPlanificacionCursada();
      break;
    case 50:  /// ANOTARSE A MATERIAS
      system("cls");
      inscribirseMateriaAlumno(legajo);

      system("cls");
      subMenuAlumnoPlanificacionCursada();
      break;
    case 51:  /// DARSE DE BAJA A MATERIAS
      system("cls");

      if (inscriptoMaterias()) {
            inscripcionMateriaObj.DarseDeBajaMateria(legajo);
      }
      else {
        cout << endl
             << "---- ERROR : EL ALUMNO CON LEGAJO " << legajo
             << " NO SE ENCUENTRA INSCRIPTO A MATERIAS ----" << endl
             << endl;
        cout << endl << endl;
        system("pause");
        system("cls");
      }

      system("cls");
      subMenuAlumnoPlanificacionCursada();
      break;
    case 52:  /// INSCRIBIRSE A FINALES
      system("cls");
      inscribirseEvaluacionAlumno(legajo);

      system("cls");
      subMenuAlumnoPlanificacionCursada();
      break;
    case 53:  /// VER FINALES
      system("cls");

      if (contarEvaluaciones() > 0) {
        if (inscriptoMaterias()) {
          verExamenesFinalesAlumno();
        }
        else {
          cout << endl
               << "---- ERROR : EL ALUMNO CON LEGAJO " << legajo
               << " NO SE ENCUENTRA INSCRIPTO A MATERIAS ----" << endl
               << endl;
          cout << endl << endl;
        }
      }
      else {
        cout << endl
             << "---- ERROR : NO SE ENCONTRARON EXÁMENES FINALES CARGADOS EN EL SISTEMA ----"
             << endl
             << endl;
        cout << endl << endl;
      }

      system("pause");
      system("cls");
      subMenuAlumnoPlanificacionCursada();
      break;
    case 54:  /// VER FINALES INSCRIPTO
      system("cls");

      ListarEvaluacionesInscripto(legajo);
      system("pause");

      // LÓGICA SIMILAR A ARRIBA PERO VALIANDO CONTRA LAS MATERIAS INSCRIPTO

      system("cls");
      subMenuAlumnoPlanificacionCursada();
      break;
    case 48:
      system("cls");
      menuAlumno();
      break;
    default:
      cout << "OPCIÓN no válida." << endl;
  }
}

bool inscriptoMaterias() {
  FILE *pInscMat;
  InscripcionMateria inscripcionObj;

  if (!(pInscMat = fopen("InscripcionMateria.dat", "rb"))) {
    cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
    system("cls");
    return false;
  }

  while (fread(&inscripcionObj, sizeof(InscripcionMateria), 1, pInscMat)) {
    if (inscripcionObj.getAlumno().getLegajo() == legajo) {
      for (int x = 0; x < 7; x++) {
        if (inscripcionObj.getEstadoMaterias(x)) {
          return true;
        }
      }
    }
  }

  fclose(pInscMat);
  return false;
}

int contarMateriasInscripto() {
  FILE *pInscMat;
  InscripcionMateria inscripcionObj;
  int contMaterias = 0;

  if (!(pInscMat = fopen("InscripcionMateria.dat", "rb"))) {
    cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
    system("cls");
    return false;
  }

  while (fread(&inscripcionObj, sizeof(InscripcionMateria), 1, pInscMat)) {
    if (inscripcionObj.getAlumno().getLegajo() == legajo) {
      for (int x = 0; x < 7; x++) {
        if (inscripcionObj.getEstadoMaterias(x)) {
          contMaterias++;
        }
      }
    }
  }

  fclose(pInscMat);
  return contMaterias;
}

bool finalesDisponibles() {
  FILE *pEval;
  Evaluacion evaluacionObj;

  FILE *pInscMat;
  InscripcionMateria inscMatObj;

  if (!(pEval = fopen("evaluaciones.dat", "rb"))) {
    cout << endl
         << "---- NO SE ENCONTRARON REGISTROS DE EXÁMENES FINALES ----" << endl
         << endl;
    return false;
  }

  while (fread(&evaluacionObj, sizeof(Evaluacion), 1, pEval)) {
    if (!(pInscMat = fopen("InscripcionMateria.dat", "rb"))) {
      cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
      return false;
    }

    while (fread(&inscMatObj, sizeof(InscripcionMateria), 1, pInscMat)) {
      if (inscMatObj.getAlumno().getLegajo() == legajo) {
        for (int x = 0; x < 7; x++) {
          if (evaluacionObj.getIdMateria() == inscMatObj.getMaterias2(x) && inscMatObj.getEstadoMaterias(x)== true) {
            fclose(pInscMat);
            fclose(pEval);
            return true;
          }
        }
      }
    }

    fclose(pInscMat);
  }

  fclose(pEval);

  return false;
}

bool finalDisponible(int idEvaluacion) {
  FILE *pEval;
  Evaluacion evaluacionObj;

  FILE *pInscMat;
  InscripcionMateria inscMatObj;

  if (!(pEval = fopen("evaluaciones.dat", "rb"))) {
    cout << endl
         << "---- NO SE ENCONTRARON REGISTROS DE EXÁMENES FINALES ----" << endl
         << endl;
    return false;
  }

  while (fread(&evaluacionObj, sizeof(Evaluacion), 1, pEval)) {
    if (!(pInscMat = fopen("InscripcionMateria.dat", "rb"))) {
      cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
      return false;
    }

    while (fread(&inscMatObj, sizeof(InscripcionMateria), 1, pInscMat)) {
      if (inscMatObj.getAlumno().getLegajo() == legajo) {
        for (int x = 0; x < 7; x++) {
          if (evaluacionObj.getIdMateria() ==
                  inscMatObj.getMaterias()[x].getId() &&
              inscMatObj.getEstadoMaterias(x)) {
            if (evaluacionObj.getId() == idEvaluacion) {
              fclose(pInscMat);
              fclose(pEval);
              return true;
            }
          }
        }
      }
    }

    fclose(pInscMat);
  }

  fclose(pEval);

  return false;
}

void CARGANDO() {
  system("cls");
  cout << "CARGANDO";
  Sleep(300);
  cout << ".";
  Sleep(300);
  cout << ".";
  Sleep(300);
  cout << ".";
  Sleep(300);
  cout << ".";
  system("cls");
}

void SALIENDO() {
  system("cls");
  cout << "SALIENDO";
  Sleep(300);
  cout << ".";
  Sleep(300);
  cout << ".";
  Sleep(300);
  cout << ".";
  Sleep(300);
  cout << ".";
  cout << endl;
}

string cargaDescripcion() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  std::cout << "             --- ** Escribe tu mensaje. Presiona Ctrl+G para terminar. ** ---\n"
            << endl
            << endl;

  char ch;
  std::string input;

  while ((ch = _getch()) != 7) {
    if (ch == 8) {
      if (!input.empty()) {
        input.pop_back();
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        COORD cursorPosition = consoleInfo.dwCursorPosition;
        cursorPosition.X--;
        SetConsoleCursorPosition(hConsole, cursorPosition);
        cout << ' ';
        SetConsoleCursorPosition(hConsole, cursorPosition);
      }
    }
    else {
      input.push_back(ch);
      cout << ch;
    }

    if (ch == 13) {
      input.push_back('\n');
      cout << "\n";
    }
  }

  return input;
}

int contarAvisos() {
  FILE *pAvi;
  int cantAvisos = 0;

  if (!(pAvi = fopen("avisos.dat", "ab"))) {
    cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
    return -1;
  }

  fseek(pAvi, 0, SEEK_END);
  cantAvisos += ftell(pAvi) / sizeof(Aviso);
  fseek(pAvi, 0, SEEK_SET);
  fclose(pAvi);

  return cantAvisos;
}

int contarEvaluaciones() {
  FILE *pEval;
  int cantEvals = 0;

  if (!(pEval = fopen("evaluaciones.dat", "ab"))) {
    cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
    return -1;
  }

  fseek(pEval, 0, SEEK_END);
  cantEvals += ftell(pEval) / sizeof(Evaluacion);
  fseek(pEval, 0, SEEK_SET);
  fclose(pEval);

  return cantEvals;
}

void verExamenesFinalesAlumno() {
  FILE *pEval;
  Evaluacion evaluacionObj;

  FILE *pInscMat;
  InscripcionMateria inscMatObj;

  time_t t = time(nullptr);
  tm *now = localtime(&t);
  time_t currentTime = mktime(now);

  int anchoID = 9;
  int anchoMateria = 15;
  int anchoFecha = 12;

  bool hayFinales = false;

  if (!(pEval = fopen("evaluaciones.dat", "rb"))) {
    cout << endl
         << "---- NO SE ENCONTRARON REGISTROS DE EXAMENES FINALES ----" << endl
         << endl;
    return;
  }

  cout << left << setw(anchoFecha) << "Fecha";
  cout << "|";
  cout << left << setw(anchoID) << "ID Final";
  cout << "|";
  cout << left << setw(anchoMateria) << "Materia" << endl;

  cout << string(anchoFecha, '-') << "+" << string(anchoID, '-') << "+"
       << string(anchoMateria, '-') << endl;

  while (fread(&evaluacionObj, sizeof(Evaluacion), 1, pEval)) {
    tm specificDate = evaluacionObj.createDate(
        evaluacionObj.getFecha().getDia(), evaluacionObj.getFecha().getMes(),
        evaluacionObj.getFecha().getAnio());
    time_t specificTime = mktime(&specificDate);

    if (difftime(specificTime, currentTime) > 0) {
      if (!(pInscMat = fopen("InscripcionMateria.dat", "rb"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
      }

      while (fread(&inscMatObj, sizeof(InscripcionMateria), 1, pInscMat)) {
        if (inscMatObj.getAlumno().getLegajo() == legajo) {
          for (int x = 0; x < 7; x++) {
            if (evaluacionObj.getIdMateria() ==
                    inscMatObj.getMaterias2(x) &&
                inscMatObj.getEstadoMaterias(x)) {
              cout << left << setw(anchoFecha)
                   << evaluacionObj.getFecha().toString("DD/MM/YYYY") << "|"
                   << left << setw(anchoID) << evaluacionObj.getId() << "|"
                   << left << setw(anchoMateria)
                   << inscMatObj.getMaterias()[x].getNombreMateria() << endl;
              hayFinales = true;
              break;
            }
          }
        }
      }

      fclose(pInscMat);
    }
  }

  if (!hayFinales) {
    system("cls");
    cout << endl
         << "---- ERROR : NO SE ENCONTRARON EXÁMENES FINALES DISPONIBLES ----"
         << endl
         << endl;
  }
  cout << endl << endl;

  fclose(pEval);
}
