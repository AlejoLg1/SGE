#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "Alumno.h"
#include "Materia.h"
#include "InscripcionMateria.h"
#include <string>

//void marco(int, int, int, int, int);

void menuPrincipal();

int seleccionarRol(int);

///--- SETTEAR LEGAJO AUTOMÁTICO ---\\

int contarLegajos(const char* [], int []);

int settearNuevoLegajo();

///--- VALIDAR EXISTENCIA DE USUARIOS ---\\

bool usuariosCargados();

bool usuariosEspecificosCargados(std::string, const char* [], int [], std::string []);

void mensajeUsuariosNoEncontrados(std::string);


///--- LOGIN ROLES ---\\

void login(int, std::string);

///--- VALIDAR CREDENCIALES LOGIN ---\\

bool usuarioValido(std::string, int, const char* [], int [], std::string []);

bool claveValida(std::string, int, int, const char* [], int [], std::string []);

bool estadoValido(std::string, int, const char* [], int [], std::string []);

void validarLegajo(int legajo);

bool validarMateria(int ID);

///--- BUSCAR --\\\

Alumno buscarAlumno(int);

Materia buscarMateria(int);

int buscarInscripcionMateria(int);

bool estaAlumnoInscritoEnMateria (int, int);

///--- MENÚS ROLES ---\\

void menuAdministrador();

void menuDirectivo();
void subMenuDirectivoProfesor();
void subMenuDirectivoAlumno();

void subMenuDirectivoPlanEstudio();
int contarMaterias();
void asignarProfesores();
void mostrarPlanEstudio();

void menuProfesor();
void subMenuProfesorGestionMaterias();
void verMateriasAsignadas();
void verExamenesFinalesProfesor();


void menuAlumno();
void subMenuAlumnoPlanificacionCursada();
void opcionCambiarContrasenaAlumno(int);

///---FUNCIONES EXTRAS ---\\

void CARGANDO();

#endif // FUNCIONES_H_INCLUDED
