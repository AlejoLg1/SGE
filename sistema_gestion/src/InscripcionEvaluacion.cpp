#include "InscripcionEvaluacion.h"

#include <iostream>
#include <limits>     // Necesario para std::numeric_limits
#include <stdexcept>  // Necesario para std::out_of_range

#include "Alumno.h"
#include "Evaluacion.h"
#include "Funciones.h"
#include "Materia.h"

InscripcionEvaluacion::InscripcionEvaluacion() {
  // ctor
}

///---- SETTERS ----\\\

void InscripcionEvaluacion::setAlumno(Alumno aux) { _alumno = aux; }

void InscripcionEvaluacion::setMaterias(const Materia& aux, int pos) {
  if (pos >= 0 && pos < 7) {
    _materias[pos] = aux;
  } 
  else {
    cout << endl << "---- ERROR : POSICIÓN FUERA DE RANGO ----" << endl << endl;
    system("pause");
  }
}

void InscripcionEvaluacion::setMateriasNotas(float nota, int pos) {
  if (pos >= 0 && pos < 7) {
    _materiasNotas[pos] = nota;
  } 
  else {
    cout << endl << "---- ERROR : POSICIÓN FUERA DE RANGO ----" << endl << endl;
    system("pause");
  }
}

void InscripcionEvaluacion::setNumMaterias(int num) { _numMaterias = num; }

///---- GETTERS ----\\\

Alumno InscripcionEvaluacion::getAlumno() { return _alumno; }

Materia* InscripcionEvaluacion::getMaterias() { return _materias; }

int InscripcionEvaluacion::getMaterias2(int pos) const {
  return _materias[pos].getId();
}

float* InscripcionEvaluacion::getMateriasNotas() { return _materiasNotas; }

int InscripcionEvaluacion::getNumMaterias() { return _numMaterias; }

///---- MÉTODOS ----\\\

int InscripcionEvaluacion::cargarInscripcionEvaluacion(const Alumno& alumno,
                                                       const Materia& materia,
                                                       int legajo) {
  if (_numMaterias >= 7) {
    throw std::runtime_error("No se pueden cargar más de 7 materias");
  } 
  else {
    if (int posicion = buscarInscripcionEvaluacion(legajo) == -1) {
      _alumno = alumno;
      _materias[_numMaterias] = materia;
      _materiasNotas[_numMaterias] = 0;  // Initializing the note
      _numMaterias++;
      return -1;
    }

    else {
      _alumno = alumno;
      _materias[_numMaterias] = materia;
      _materiasNotas[_numMaterias] = 0;  // Initializing the note
      _numMaterias++;
      return posicion;
    }
  }
  return -1;
}

void InscripcionEvaluacion::inscribirseEvaluacion(int legajo) {
  Alumno legAux;
  Evaluacion evalAux;
  Materia matAux;
  int idEvaluacion = 0;
  bool continuar = true;

  while (continuar) {
    std::system("cls");

    std::cout << "------------------------------" << std::endl;
    std::cout << "  INSCRIPCIÓN A EXAMEN FINAL  " << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << "Ingrese el ID del examen final (ID examen final 0 para salir): ";

    if (!leerEntrada(idEvaluacion)) {
      std::cout << "Entrada inválida. Por favor, ingrese un número válido."
                << std::endl;
      continue;
    }

    if (idEvaluacion == 0) {
      return;
    }

    if (!validarEvaluacion(idEvaluacion)) {
      system("cls");
      std::cout << "El ID ingresado no existe" << std::endl;
      if (!preguntarContinuar("¿Quiere volver a ingresar el ID?")) {
        return;
      }
      continue;
    }

    if (!finalDisponible(idEvaluacion)) {
      cout << endl
           << "---- ERROR : EL EXAMEN FINAL NO CORRESPONDE A LAS MATERIAS INSCRIPTAS ----"
           << endl
           << endl;
      system("pause");
      return;
    }

    if (estaAlumnoInscritoEnEvaluacion(legajo, idEvaluacion)) {
      system("cls");
      std::cout << "Ya esta inscripto en ese exámen final " << std::endl;
      if (!preguntarContinuar("¿Quiere realizar otra inscripción?")) {
        return;
      }
      continue;
    }

    legAux = buscarAlumno(legajo);
    evalAux = buscarEvaluacion(idEvaluacion);
    matAux = buscarMateria(evalAux.getIdMateria());
    int posicionDeInscripcion =
        cargarInscripcionEvaluacion(legAux, matAux, legajo);

    if (posicionDeInscripcion == -1) {
      grabarEnDiscoInscripcionEvaluacion(legAux, evalAux);
    } else {
      ModificarEnDiscoInscripcionEvaluacion(posicionDeInscripcion);
    }

    std::cout << std::endl
              << std::endl
              << "---- INSCRIPCIÓN REALIZADA CON ÉXITO ----" << std::endl;
    system("Pause");
    continuar = false;
  }
}

void InscripcionEvaluacion::mostrarInscripcionEvaluacion() {
  // Mostrar detalles del alumno
  std::cout << "----------------------------- " << std::endl;
  std::cout << "Nombre: " << _alumno.getNombre() << std::endl;
  std::cout << "Apellido: " << _alumno.getApellido() << std::endl;
  std::cout << "Legajo: " << _alumno.getLegajo() << std::endl;

  // Mostrar materias inscritas y sus notas
  std::cout << "Materias inscritas y notas:" << std::endl;
  for (int i = 0; i < _numMaterias; ++i) {
    std::cout << "| " << _materias[i].getNombreMateria() << " | Nota: " << _materiasNotas[i] << std::endl;
  }
  std::cout << "----------------------------- " << std::endl;
  system("pause");
}

void InscripcionEvaluacion::mostrarInscripcionEvaluacionSinElNombreDeUsuario(
    int legajo) {
  Alumno legAux;
  int pos = 0;

  legAux = buscarAlumno(legajo);

  while (leerEnDiscoInscripcionEvaluacionPorPosicion(pos)) {
    if (_alumno.getLegajo() == legAux.getLegajo()) {
      std::cout << "Materias inscritas y notas:" << std::endl;
      for (int i = 0; i < _numMaterias; ++i) {
        std::cout << "| ID: " << _materias[i].getId()
                  << " | Materia: " << _materias[i].getNombreMateria()
                  << " | Nota: " << _materiasNotas[i] << std::endl;
      }
      std::cout << "----------------------------- " << std::endl;
    }
    pos++;
  }
}

void InscripcionEvaluacion::mostrarRegistroDeIncriccionesEvaluacion(int legajo) {
  Alumno legAux;
  int pos = 0;

  legAux = buscarAlumno(legajo);

  while (leerEnDiscoInscripcionEvaluacionPorPosicion(pos)) {
    if (_alumno.getLegajo() == legAux.getLegajo()) {
      mostrarInscripcionEvaluacion();
    }
    pos++;
  }
}

void InscripcionEvaluacion::DarseDeBajaEvaluacion(
    int legajo)  // no vamos a permitir esto
{
  Alumno legAux;
  Materia matAux;
  int idEvaluacion = 0;
  bool continuar = true;

  while (continuar) {
    std::system("cls");
    mostrarInscripcionEvaluacionSinElNombreDeUsuario(legajo);

    std::cout << "   DARSE DE BAJA EN EVALUACION  " << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Ingrese el ID de la Evaluacion: ";

    if (!leerEntrada(idEvaluacion))  // chequea que sea un número y no otra cosa
    {
      std::cout << "Entrada inválida. Por favor, ingrese un número válido."
                << std::endl;
      continue;
    }

    if (!validarEvaluacion(idEvaluacion)) {
      system("cls");
      std::cout << "El ID ingresado no existe" << std::endl;
      if (!preguntarContinuar("¿Quiere volver a ingresar el ID?")) {
        return;
      }
      continue;
    }

    if (!estaAlumnoInscritoEnEvaluacion(legajo, idEvaluacion)) {
      system("cls");
      std::cout << "No Esta Inscripto en Esa Evaluacion" << std::endl;
      if (!preguntarContinuar("¿Quiere volver a ingresar el ID?")) {
        return;
      }
      continue;
    }

    legAux = buscarAlumno(legajo);
    matAux = buscarMateria(idEvaluacion);

    int posicionDeInscripcion = cargarBajaDeUnRegistroDeIncriccionesEvaluacion(
        legAux, matAux, legajo, idEvaluacion);

    ModificarEnDiscoInscripcionEvaluacion(posicionDeInscripcion);
    std::cout << "Evaluacion Dada de baja" << std::endl;

    system("Pause");
    continuar = false;
  }
}

int InscripcionEvaluacion::cargarBajaDeUnRegistroDeIncriccionesEvaluacion(
    const Alumno& alumno, const Materia& materia, int Legajo,
    int idEvaluacionBaja) {
  int posicion = buscarInscripcionEvaluacion(
      Legajo);  // Assuming there's a function to find the enrollment position

  _alumno = alumno;
  for (int i = 0; i < 7; i++) {
    if (_materias[i].getId() == idEvaluacionBaja) {
      _materiasNotas[i] = -1;  // Set a flag value to indicate the evaluation is dropped
      return posicion;
    }
  }
  return posicion;
}

void InscripcionEvaluacion::grabarEnDiscoInscripcionEvaluacion(const Alumno& alumno, const Evaluacion& evaluacion) {
  FILE* p;

  if (!(p = fopen("InscripcionEvaluacion.dat", "ab"))) {
    std::cout << "---- ERROR AL ABRIR EL ARCHIVO ----" << std::endl;
    return;
  }

  fwrite(this, sizeof(InscripcionEvaluacion), 1, p);
  fclose(p);
}

void InscripcionEvaluacion::ModificarEnDiscoInscripcionEvaluacion(int pos) {
  FILE* p;

  p = fopen("InscripcionEvaluacion.dat", "rb+");
  if (p == nullptr) {
    std::cout << "NO SE PUDO ABRIR/CREAR EL ARCHIVO" << std::endl;
    return;
  }

  fseek(p, sizeof(InscripcionEvaluacion) * pos, 0);
  fwrite(this, sizeof(InscripcionEvaluacion), 1, p);
  fclose(p);
}

void InscripcionEvaluacion::leerEnDiscoInscripcionEvaluacion() {
  FILE* p;

  if (!(p = fopen("InscripcionEvaluacion.dat", "rb"))) {
    std::cout << "---- ERROR AL ABRIR EL ARCHIVO ----" << std::endl;
    return;
  }

  std::cout << "MOSTRANDO INSCRIPCIONES:" << std::endl;
  while (fread(this, sizeof(InscripcionEvaluacion), 1, p)) {
    this->mostrarInscripcionEvaluacion();
  }
  fclose(p);
}

bool InscripcionEvaluacion::leerEnDiscoInscripcionEvaluacionPorPosicion(
    int pos) {
  FILE* p;
  bool leyo;

  p = fopen("InscripcionEvaluacion.dat", "rb");
  if (p == nullptr) {
    return false;
  }

  fseek(p, sizeof(InscripcionEvaluacion) * pos, 0);
  leyo = fread(this, sizeof(InscripcionEvaluacion), 1, p);
  fclose(p);
  return leyo;
}

bool InscripcionEvaluacion::leerEntrada(int& entrada) {
  std::cin >> entrada;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  }
  return true;
}

bool InscripcionEvaluacion::preguntarContinuar(const std::string& mensaje) {
  int opcion = 0;
  std::cout << mensaje << std::endl;
  std::cout << "SI = 1      NO = 0" << std::endl << std::endl;

  std::cout << "> ";
  if (!leerEntrada(opcion)) {
    std::cout << "Opción inválida. Intente de nuevo." << std::endl;
    return false;
  }
  return opcion == 1;
}
