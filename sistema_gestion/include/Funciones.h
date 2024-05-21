#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
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

void menuAlumno();

#endif // FUNCIONES_H_INCLUDED
