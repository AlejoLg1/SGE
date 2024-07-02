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

bool usuariosEspecificosCargados(string, const char* [], int [], string []);

void mensajeUsuariosNoEncontrados(string);


///--- LOGIN ROLES ---\\

void login(int, string);

///--- VALIDAR CREDENCIALES LOGIN ---\\

bool usuarioValido(string, int, const char* [], int [], string []);

bool claveValida(string, int, int, const char* [], int [], string []);

bool estadoValido(string, int, const char* [], int [], string []);

void validarLegajo(int &);

bool validarMateria(int);

bool validarEvaluacion (int);

///--- BUSCAR --\\\

Alumno buscarAlumno(int);

Profesor buscarProfesor(int);

Materia buscarMateria(int);

Evaluacion buscarEvaluacion(int);

int buscarInscripcionMateria(int);

int buscarInscripcionEvaluacion(int);

bool estaAlumnoInscritoEnMateria (int, int);

bool estaAlumnoInscritoEnEvaluacion (int, int);

void BuscarEvaluacionesDeMateriasAsignadasAlumno(const InscripcionMateria&);

void BuscarEvaluacionesDeMateriasAsignadasAlumnoListandoTodoRecto(const InscripcionMateria&);

void BuscarEvaluacionesInscritoAlumno(const InscripcionEvaluacion&);

InscripcionMateria BuscarArchvoInscripcionMateria(int);

InscripcionEvaluacion BuscarArchivoInscripcionEvaluacion(int);

///--- MENÚS ROLES ---\\

void menuAdministrador();
void subMenuAdministradorClaves();
void subMenuAdministradorCopiasSeguridad();
void subMenuAdministradorRealizarCopiasSeguridad();
void realizarBackup(const string&, const string&);
void realizarBackupGeneral();
void subMenuAdministradorRestaurarCopiasSeguridad();
void realizarRestauracion(const string&, const string&);
void realizarRestauracionGeneral();

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
int contarInscipcionEvaluaciones();
void cargarNotas();
bool validarExistenciaEvaluacion(int);
int obtenerIdMateriaEvaluacion(int);
bool validarProfesorAsignado(int, int);
void subMenuListadosEstadisticaProfesor();
void verListadosAlumnosInscriptosPorMateria();
void verListadosAlumnosAprobadosPorMateria();
void verListadosAlumnosDesaprobadosPorMateria();

void menuAlumno();
void subMenuAlumnoPlanificacionCursada();
void opcionCambiarContrasenaAlumno(int);
bool inscriptoMaterias();
int contarEvaluaciones();
void verExamenesFinalesAlumno(int);
bool finalesDisponibles();
bool finalDisponible(int);
int idMateriaPorIdEvaluacion(int);
int contarMateriasInscripto();

void inscribirseMateriaAlumno(int);
void darseDeBajaMateriaAlumno(int);
void inscribirseEvaluacionAlumno(int);

///---LISTADOS ---\\

void ListarEvaluaciones (int );
void ListarEvaluacionesTodoRecto (int);
void ListarEvaluacionesInscripto (int);
bool MateriasAsignadas();
void verExamenesFinalesProfesor();
void verMateriasAsignadas();
void mostrarPlanEstudio();
void verMateriasAsignadas();

///---FUNCIONES EXTRAS ---\\

void CARGANDO();
void SALIENDO();

string cargaDescripcion();

#endif // FUNCIONES_H_INCLUDED
