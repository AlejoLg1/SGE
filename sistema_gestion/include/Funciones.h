#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <string>
#include <locale.h>
#include "Alumno.h"
#include "Materia.h"
#include "Evaluacion.h"
#include "InscripcionMateria.h"
#include "InscripcionEvaluacion.h"

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

bool validarEvaluacion (int ID);

///--- BUSCAR --\\\

Alumno buscarAlumno(int);

Profesor buscarProfesor(int);

Materia buscarMateria(int);

Evaluacion buscarEvaluacion(int);

int buscarInscripcionMateria(int);

int buscarInscripcionEvaluacion(int);

bool estaAlumnoInscritoEnMateria (int, int);

bool estaAlumnoInscritoEnEvaluacion (int, int);

void BuscarEvaluacionesDeMateriasAsignadasAlumno(const InscripcionMateria& materiasInscripto);

void BuscarEvaluacionesInscritoAlumno(const InscripcionEvaluacion& evaluacionInscripto);

InscripcionMateria BuscarArchvoInscripcionMateria(int legajo);

InscripcionEvaluacion BuscarArchivoInscripcionEvaluacion(int legajo);

///--- MENÚS ROLES ---\\

void menuAdministrador();
void subMenuAdministradorClaves();

void menuDirectivo();
void subMenuDirectivoProfesor();
void subMenuDirectivoAlumno();
void subMenuDirectivoAvisos();

void subMenuDirectivoPlanEstudio();
int contarMaterias();
void asignarProfesores();
int contarAvisos();

void menuProfesor();
void subMenuProfesorGestionMaterias();

void menuAlumno();
void subMenuAlumnoPlanificacionCursada();
void opcionCambiarContrasenaAlumno(int);
bool inscriptoMaterias();
int contarEvaluaciones();
void verExamenesFinalesAlumno();
bool finalesDisponibles();
bool finalDisponible(int);
int idMateriaPorIdEvaluacion(int);

void inscribirseMateriaAlumno(int);
void inscribirseEvaluacionAlumno(int);

///---LISTADOS ---\\

void ListarEvaluaciones (int legajo);
void ListarEvaluacionesInscripto (int legajo);
bool MateriasAsignadas();
void verExamenesFinalesProfesor();
void verMateriasAsignadas();
void mostrarPlanEstudio();
void verMateriasAsignadas();

///---FUNCIONES EXTRAS ---\\

void CARGANDO();
void SALIENDO();

std::string cargaDescripcion();

#endif // FUNCIONES_H_INCLUDED
