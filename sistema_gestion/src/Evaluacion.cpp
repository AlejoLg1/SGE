#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include "Funciones.h"
#include "Materia.h"
#include "Evaluacion.h"

using namespace std;

Evaluacion::Evaluacion() {
    _id = 0;
    _idProfesor = 0;
    _idMateria = 0;
    _fecha = Fecha();
    _estado = false;
}

/// SETTERS

void Evaluacion::setId() {
    _id = generarId();
}

void Evaluacion::setIdProfesor(int idProfesor) {
    _idProfesor = idProfesor;
}

bool Evaluacion::setIdMateria(int idMateria, int legajoProfesor) {
    FILE *pMat;
    Materia materiaObj;
    bool exito = false;

    if(validarExistenciaFinal(idMateria)) {
        cout << endl << "\t ---- ERROR : LA MATERIA ESPECIFICADA YA CUENTA CON UN EXÁMEN FINAL GENERADO ----" << endl << endl;
        Sleep(1500);
        system("cls");
        return false;
    }

    if(idMateria <= 0 || idMateria > 21) {
        cout << endl << "\t ---- ERROR : ID DE MATERIA INEXISTENTE ----"  << endl << endl;
        Sleep(1500);
        system("cls");
        return false;
    }

    if(!(pMat = fopen("materias.dat", "rb"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return false;
    }

    while(fread(&materiaObj, sizeof(Materia), 1, pMat)) {
        if(materiaObj.getId() == idMateria) {
            if(materiaObj.getProfesor().getLegajo() == legajoProfesor) {
                exito = true;
                _idMateria = idMateria;
                break;
            }
        }
    }

    fclose(pMat);

    if(!exito) {
        cout << endl << "\t ---- ERROR : LA MATERIA CON ID " << idMateria << " NO CORRESPONDE AL PROFESOR CON LEGAJO " << legajoProfesor << " ----" << endl << endl;
        Sleep(1500);
        system("cls");
        return false;
    }

    return true;
}

void Evaluacion::setFecha(Fecha fecha) {
    _fecha = fecha;
}

void Evaluacion::setEstado(bool estado) {
    _estado = estado;
}

/// GETTERS

int Evaluacion::getId() {
    return _id;
}

int Evaluacion::getIdProfesor() {
    return _idProfesor;
}

int Evaluacion::getIdMateria() {
    return _idMateria;
}

Fecha Evaluacion::getFecha() {
    return _fecha;
}

bool Evaluacion::getEstado() {
    return _estado;
}

bool Evaluacion::cargarEvaluacion(int legajoProfesor) {
    int idMateria;
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    time_t currentTime = mktime(now);

    cout << "CREANDO EXÁMEN FINAL (ID Materia 0 para salir)" << endl << endl;

    setId();
    setIdProfesor(legajoProfesor);
    cout << "\t - ID Final: " << getId() << endl << endl;
    cout << "\t - Legajo Profesor: " << getIdProfesor() << endl << endl;

    cout << "\t - ID Materia: ";
    cin >> idMateria;

    if(idMateria == 0) {
        return false;
    }

    while(!setIdMateria(idMateria, legajoProfesor)) {
        cout << "CREANDO EXÁMEN FINAL (ID Materia 0 para salir)" << endl << endl;

        setId();
        setIdProfesor(legajoProfesor);
        cout << "\t - ID Final: " << getId() << endl << endl;
        cout << "\t - Legajo Profesor: " << getIdProfesor() << endl << endl;

        cout << "\t - ID Materia: ";
        cin >> idMateria;

        if(idMateria == 0) {
            return false;
        }
    }

    setId();
    setIdProfesor(legajoProfesor);

    cout << endl << "\t - Fecha: " << endl;
    _fecha.CargarFechaEvaluacion(getId(), getIdProfesor(), getIdMateria());

    tm specificDate = createDate(_fecha.getDia(), _fecha.getMes(), _fecha.getAnio());
    time_t specificTime = mktime(&specificDate);
    while(difftime(specificTime, currentTime) <= 0) {
        cout << "\t ---- ERROR : LA FECHA ESPECIFICADA ES ANTERIOR O IGUAL A LA FECHA ACTUAL ----" << endl << endl;
        Sleep(1000);
        system("cls");

        cout << "CREANDO EXÁMEN FINAL" << endl << endl;

        setId();
        setIdProfesor(legajoProfesor);
        cout << "\t - ID Final: " << getId() << endl << endl;
        cout << "\t - Legajo Profesor: " << getIdProfesor() << endl << endl;
        cout << "\t - ID Materia: " << getIdMateria() << endl << endl;
        cout << "\t - Fecha: " << endl;
        _fecha.CargarFechaEvaluacion(getId(), getIdProfesor(), getIdMateria());
        specificDate = createDate(_fecha.getDia(), _fecha.getMes(), _fecha.getAnio());
        specificTime = mktime(&specificDate);
    }

    setFecha(_fecha);
    setEstado(true);
    cout << endl << "¡EXAMEN FINAL CREADO CON ÉXITO!" << endl << endl;
    system("pause");

    return true;
}

void Evaluacion::mostrarEvaluacion() {
Materia materia = buscarMateria(getIdMateria());

    cout << "-------------------------------------"<<endl;
    cout << "\t - ID Final: " << getId() <<endl;
    cout << "\t - Profesor: " << materia.getProfesor().getNombre()<<" "<<materia.getProfesor().getApellido()<< endl;
    cout << "\t - Materia: " << materia.getNombreMateria() << endl;
    cout << "\t - Fecha: " << getFecha().toString("DD/MM/YYYY") << endl;
    cout << "-------------------------------------"<<endl;


}

void Evaluacion::mostrarEvaluacionTodoRecto()
{
    Materia materia = buscarMateria(getIdMateria());

    cout << "----------------------------------------------------------------------------------------"<<endl;
    cout << "\t - ID Final: " << getId()<< " | Profesor: " << materia.getProfesor().getNombre()<<" "<<materia.getProfesor().getApellido()<< "| Materia: " << materia.getNombreMateria()<< "| Fecha: " << getFecha().toString("DD/MM/YYYY")<<endl;
    cout << "----------------------------------------------------------------------------------------"<<endl;


}

void Evaluacion::grabarEnDisco(int legajoProfesor) {
    FILE *pEvaluacion;

    if(!(pEvaluacion = fopen("evaluaciones.dat", "ab"))) {
        system("cls");
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return;
    }

    if(this->cargarEvaluacion(legajoProfesor)) {
        fwrite(this, sizeof(Evaluacion), 1, pEvaluacion);
    }

    fclose(pEvaluacion);
}

void Evaluacion::leerEnDisco() {
    FILE *pEvaluacion;

    if(!(pEvaluacion = fopen("evaluaciones.dat", "rb"))) {
        if(generarId() == 1) {
            cout << endl <<"---- NO HAY EXAMENES FINALES CARGADOS ----" << endl << endl;
        }
        else {
            cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        }
        return;
    }

    while(fread(this, sizeof(Evaluacion), 1, pEvaluacion)) {
        this->mostrarEvaluacion();
    }

    if(generarId() == 1) {
        cout << endl <<"---- NO HAY EXAMENES FINALES CARGADOS ----" << endl << endl;
    }

    fclose(pEvaluacion);
}

bool Evaluacion::leerEnDiscoEvaluacionPorPosicion(int pos) {

 FILE *p;
    bool leyo;

    p = fopen("evaluaciones.dat", "rb");
    if (p == nullptr)
    {
        return false;
    }

    fseek(p, sizeof(Evaluacion) * pos, 0);
    leyo = fread(this, sizeof(Evaluacion), 1, p);
    fclose(p);
    return leyo;


}

int Evaluacion::generarId() {
    FILE *pEval;
    int idsTotales = 1;

    if(!(pEval = fopen("evaluaciones.dat", "ab"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return -1;
    }

    fseek(pEval, 0, SEEK_END);
    idsTotales += ftell(pEval) / sizeof(Evaluacion);
    fclose(pEval);

    return idsTotales;
}

tm Evaluacion::createDate(int day, int month, int year) {
    tm date = {};
    date.tm_mday = day;
    date.tm_mon = month - 1; // Meses en std::tm van de 0 a 11
    date.tm_year = year - 1900; // Años en std::tm se cuentan desde 1900
    return date;
}

bool Evaluacion::validarExistenciaFinal(int idMateria) {
    FILE *pEvaluacion;

    if(!(pEvaluacion = fopen("evaluaciones.dat", "rb+"))) {
        system("cls");
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return false;
    }

    while (fread(this, sizeof(Evaluacion), 1, pEvaluacion)) {
        if(this->getIdMateria() == idMateria) {
            fclose(pEvaluacion);
            return true;
        }
    }

    fclose(pEvaluacion);
    return false;
}
