#include "InscripcionMateria.h"
#include <cstdlib>  // Para std::system
#include <iomanip>
#include <limits>  // Para std::numeric_limits
#include "Alumno.h"
#include "Funciones.h"
#include "Materia.h"

using namespace std;

///---- CONSTRUCTOR ----///
InscripcionMateria::InscripcionMateria(){

    _numMaterias=0;

    for (int i = 0; i < 7; ++i) {

        _estadoMaterias[i] = false;
    }
}


///---- SETTERS ----\\\

void InscripcionMateria::setAlumno(int aux)

 {
     _alumno = aux;


}

void InscripcionMateria::setMaterias(int aux, int pos) {
  if (pos >= 0 && pos < 7) {
    _materias[pos] = aux;
  }
}

void InscripcionMateria::setEstadoMaterias(bool aux, int pos) {
  _estadoMaterias[pos] = aux;


}

void InscripcionMateria::setNumMaterias(bool sumar) {
  if (sumar) {
    _numMaterias++;
  }
  else {
    _numMaterias--;
  }
}
///---- GETTERS ----\\\

int InscripcionMateria::getAlumno() { return _alumno; }

int* InscripcionMateria::getMaterias() {
  return _materias;  // Devuelve un puntero al arreglo de materias
}

int InscripcionMateria::getMaterias2(int pos) const {
  return _materias[pos];
}

bool InscripcionMateria::getEstadoMaterias(int pos) {

  return _estadoMaterias[pos];

}

int InscripcionMateria::getNumMaterias() { return _numMaterias; }

///---- MÉTODOS ----\\\

int InscripcionMateria::cargarInscripcionMateria(Alumno& alumno,const Materia& materia,int Legajo) {
    reset();
    InscripcionMateria aux;
    int posicion=0;
    bool bandera=false;

    while (aux.leerEnDiscoInscripcionMateriaPorPosicion(posicion)) {
        if (aux.getAlumno() == Legajo) {
            aux.setAlumno(alumno.getLegajo());
            aux.setMaterias(materia.getId(),aux.getNumMaterias());
            aux.setEstadoMaterias(true,aux.getNumMaterias());
            aux.setNumMaterias(true);
            aux.ModificarEnDiscoInscripcionMateria(posicion);
            bandera=true;
            return -3;
        }

       posicion++;
    }
    if (bandera==false)
    {

        return -1;
    }


}

void InscripcionMateria::inscribirseMateria(int legajo) {
  Alumno legAux;
  Materia matAux;
  int idMateria = 0, opcion = 0;
  bool continuar = true;
  InscripcionMateria inscMat;

  inscMat.reset();

  while (continuar) {
    std::system("cls");

    mostrarPlanEstudio();
    std::cout << "-----------------------------" << std::endl;
    std::cout << "    INSCRIPCIÓN DE MATERIA    " << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Ingrese el ID de la materia (ID Materia 0 para salir): ";

    if (!leerEntrada(idMateria)) {
      std::cout << "Entrada inválida. Por favor, ingrese un número válido."
                << std::endl;
      continue;
    }

    if (idMateria == 0) {
      return;
    }

    if (!validarMateria(idMateria)) {
      system("cls");
      std::cout << "El ID ingresado no existe" << std::endl;
      if (!preguntarContinuar("¿Quiere volver a ingresar el ID?")) {
        return;
      }
      continue;
    }

    if (estaAlumnoInscritoEnMateria(legajo, idMateria)) {
      system("cls");
      std::cout << "Ya se inscribió en esta materia previamente " << std::endl;
      if (!preguntarContinuar("¿Quiere inscribirse en otra materia?")) {
        return;
      }
      continue;
    }

    legAux = buscarAlumno(legajo);
    matAux = buscarMateria(idMateria);
    int posicionDeInscripcion = inscMat.cargarInscripcionMateria(legAux, matAux, legajo);

    if (posicionDeInscripcion == -1) {
        _alumno=legAux.getLegajo();
        _materias[0]=matAux.getId();
        _estadoMaterias[0]=true;
        _numMaterias=1;
        grabarEnDiscoInscripcionMateria();
        cout << endl << endl << "---- INSCRIPCIÓN REALIZADA CON ÉXITO ----" << endl;
        system("Pause");
        continuar = false;

    }
    else if (posicionDeInscripcion == -2) {

      return;
    }
    else {
      cout << endl << endl << "---- INSCRIPCIÓN REALIZADA CON ÉXITO ----" << endl;
      system("Pause");
      continuar = false;
    }

  }
}

void InscripcionMateria::mostrarInscripcionMateria() {
  // Mostrar detalles del alumno
  Alumno alu;
  Materia mat;


  alu = buscarAlumno(_alumno);
  std::cout << "----------------------------- " << std::endl;
  std::cout << "Nombre: " << alu.getNombre()<< std::endl;
  std::cout << "Apellido: " << alu.getApellido() << std::endl;
  std::cout << "Legajo: " << alu.getLegajo() << std::endl;

  // Mostrar materias inscritas y sus estados
  std::cout << "Materias inscritas:" << std::endl;
  for (int i = 0; i < 7; ++i) {
    if (_estadoMaterias[i] == true) {
            mat = buscarMateria(_materias[i]);
      std::cout << "| " << mat.getNombreMateria() << std::endl;
    }
  }
  std::cout << "----------------------------- " << std::endl << std::endl;
  system("pause");
}

void InscripcionMateria::mostrarInscripcionMateriaSinElNombreDeUsuario(
    int legajo) {
  int anchoID = 6;
  int anchoMateria = 21;

  Alumno legAux;
  Materia mat;
  int pos = 0;

  legAux = buscarAlumno(legajo);


  cout << "Materias inscritas:" << std::endl << std::endl;
  cout << left << setw(anchoID) << "ID";
  cout << "|";
  cout << left << setw(anchoMateria) << "Materia";
  cout << "|" << endl;
  cout << string(anchoID, '-') << "+" << string(anchoMateria, '-') << "+"
       << endl;

  while (leerEnDiscoInscripcionMateriaPorPosicion(pos)) {
    if (_alumno == legAux.getLegajo()) {
      for (int i = 0; i < 7; ++i) {
        if (_estadoMaterias[i] == true) {
                mat = buscarMateria(_materias[i]);
          cout << left << setw(anchoID) << mat.getId() << "|" << left
               << setw(anchoMateria) << mat.getNombreMateria() << "|"
               << endl;
        }
      }

      cout << endl << endl;
      std::cout << "----------------------------- " << std::endl;
    }

    pos++;
  }
}

void InscripcionMateria::mostrarRegistroDeIncriccionesMateria(int legajo) {
  Alumno legAux;
  int pos = 0;
  bool estaInscripto = false;

  legAux = buscarAlumno(legajo);

  while (leerEnDiscoInscripcionMateriaPorPosicion(pos)) {
    if (_alumno == legAux.getLegajo()) {
        estaInscripto = true;
        mostrarInscripcionMateria();
    }

   pos++;
  }

  if(!estaInscripto) {
    cout << endl
             << "---- ERROR : EL ALUMNO CON LEGAJO " << legajo << " NO SE ENCUENTRA INSCRIPTO A MATERIAS" <<" ----"
             << endl
             << endl;
    cout << endl << endl;
    system("pause");
  }

}

void InscripcionMateria::DarseDeBajaMateria(int legajo) {
  Alumno legAux;
  Materia matAux;
  int idMateria = 0, opcion = 0;
  bool continuar = true;

  while (continuar) {
    std::system("cls");
    mostrarInscripcionMateriaSinElNombreDeUsuario(legajo);

    std::cout << "   DARSE DE BAJA EN MATERIA  " << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Ingrese el ID de la Materia (ID Materia 0 para salir): ";

    if (!leerEntrada(idMateria))  /// chequea qe sea un numero y no otra cosa
    {
      std::cout << "Entrada inválida. Por favor, ingrese un número válido."
                << std::endl;
      continue;
    }

    if (idMateria == 0) {
      return;
    }

    if (!validarMateria(idMateria)) {
      system("cls");
      std::cout << "El ID ingresado no existe" << std::endl;
      if (!preguntarContinuar("¿Quiere volver a ingresar el ID?")) {
        return;
      }
      continue;
    }

    if (estaAlumnoInscritoEnMateria(legajo, idMateria) == false) {
      system("cls");
      std::cout << "No está inscripto en esa Materia  " << std::endl;
      if (!preguntarContinuar("¿Quiere volver a ingresar el ID?")) {
        return;
      }
      continue;
    }

    legAux = buscarAlumno(legajo);
    matAux = buscarMateria(idMateria);

    int posicionDeInscripcion = cargarBajaDeUnRegistroDeIncriccionesMateria(legAux, matAux, legajo, idMateria);

    if (posicionDeInscripcion>-1)
    {
    std::cout << endl
              << endl
              << "---- MATERIA DADA DE BAJA CON ÉXITO ----" << std::endl;
    system("Pause");
    continuar = false;
    }

        if (posicionDeInscripcion==-2)
    {
    std::cout << endl
              << endl
              << "---- MATERIA DADA DE BAJA ANTERIORMENTE ----" << std::endl;
    system("Pause");
    continuar = false;
    }

            if (posicionDeInscripcion==-1)
    {
    std::cout << endl
              << endl
              << "---- NO ESTA INSCRIPTO A LA MATERIA INGRESADA ----" << std::endl;
    system("Pause");
    continuar = false;
    }


  }
}

int InscripcionMateria::cargarBajaDeUnRegistroDeIncriccionesMateria(Alumno& alumno, const Materia& materia, int Legajo,int idMateriaBaja)
{
      reset();
    InscripcionMateria aux;
    int posicion=0;
    bool bandera=false;

    while (aux.leerEnDiscoInscripcionMateriaPorPosicion(posicion))
    {
        if (aux.getAlumno()== Legajo)
        {
            for (int i=0;i<7;i++)
            {
                if(aux.getMaterias2(i)==idMateriaBaja)
                {
                    if (aux.getEstadoMaterias(i)==true)
                    {
                        aux.setEstadoMaterias(false,i);
                        aux.ModificarEnDiscoInscripcionMateria(posicion);
                        bandera=true;
                        return posicion;
                    }
                    else
                        {
                        bandera=true;
                        return-2;

                        }
                        bandera=true;
                }
            }
        }

        posicion++;
    }

       if (bandera==false)
    {

        return -1;
    }

}

void InscripcionMateria::grabarEnDiscoInscripcionMateria() {
  FILE* p;
    p = fopen("InscripcionMateria.dat", "ab");
if (p==NULL){cout<<"El ARCHIVO NO SE PUDO CREAR O ABRIR"<<endl;}

  fwrite(this, sizeof(InscripcionMateria), 1, p);

  fclose(p);
}

void InscripcionMateria::ModificarEnDiscoInscripcionMateria(int pos) {
  FILE* p;

  p = fopen("InscripcionMateria.dat", "rb+");
  if (p == NULL) {
    cout << "NO SE PUDO ABRIR/CREAR EL ARCHIVO" << endl;
  }

  fseek(p, sizeof(InscripcionMateria) * pos, 0);

  fwrite(this, sizeof(InscripcionMateria), 1, p);

  fclose(p);
}

void InscripcionMateria::leerEnDiscoInscripcionMateria() {
  FILE* p;

  if (!(p = fopen("InscripcionMateria.dat", "rb"))) {
    cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
    return;
  }

  cout << "MOSTRANDO INSCRIPCIONES:" << endl;
  while (fread(this, sizeof(InscripcionMateria), 1, p)) {
    this->mostrarInscripcionMateria();
  };

  fclose(p);
}

bool InscripcionMateria::leerEnDiscoInscripcionMateriaPorPosicion(int pos) {
  FILE* p;
  bool Leyo;

  p = fopen("InscripcionMateria.dat", "rb");
  if (p == NULL) {
    return false;
  }

  fseek(p, sizeof(InscripcionMateria) * pos, 0);

  Leyo = fread(this, sizeof(InscripcionMateria), 1, p);

  fclose(p);
  return Leyo;
}

bool InscripcionMateria::leerEntrada(int& entrada) {
  std::cin >> entrada;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  }
  return true;
}

bool InscripcionMateria::preguntarContinuar(const std::string& mensaje) {
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

void InscripcionMateria::MostrarTodosLosRegistrosIncripcionMateria() {
    Materia mat;

    FILE* p = fopen("InscripcionMateria.dat", "rb");
    if (!p) {
        cout << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    InscripcionMateria inscripcion;
    while (fread(&inscripcion, sizeof(InscripcionMateria), 1, p)) {
        cout << "--------------------------------------" << endl;
        cout << "Legajo del Alumno: " << inscripcion.getAlumno()<< endl;
        cout << "Número de Materias Inscritas: " << inscripcion.getNumMaterias() << endl;
        cout << "Materias Inscritas:" << endl;

        for (int i = 0; i < 7; i++) {
            if (inscripcion.getEstadoMaterias(i)==true) {
                    mat = buscarMateria(inscripcion.getMaterias2(i));
                cout << "  Legajo de la Materia: " << mat.getId() << endl;
                system("pause");
            }
        }

        cout << "--------------------------------------" << endl;
    }

    fclose(p);
}

// Método para resetear la clase
    void InscripcionMateria::reset() {
       _alumno = 0;
        for (int i = 0; i < 7; ++i) {
            _materias[i] = 0;
            _estadoMaterias[i] = false;  // Establece todos los estados de materias a false
        }
        _numMaterias = 0;  // Reinicia el contador de materias
    }

