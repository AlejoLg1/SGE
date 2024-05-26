#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include "Materia.h"
#include "Evaluacion.h"

using namespace std;

Evaluacion::Evaluacion()
{
    _id = 0;
    _idProfesor = 0;
    _idMateria = 0;
    _fecha = Fecha();
    _estado = false;
}

///SETTERS

void Evaluacion::setId(){
    _id = generarId();
}

void Evaluacion::setIdProfesor(int idProfesor){
    _idProfesor = idProfesor;
}

bool Evaluacion::setIdMateria(int idMateria){
    FILE *pMat;
    Materia materiaObj;
    bool exito = false;

    if(validarExistenciaFinal(idMateria)){
        cout << endl << "\t ---- ERROR : LA MATERIA ESPECIFICADA YA CUENTA CON UN EXÁMEN FINAL GENERADO ----" << endl << endl;
        Sleep(1500);
        system("cls");

        return false;
    }

    if(idMateria <= 0 || idMateria > 21){
        cout << endl << "\t ---- ERROR : ID DE MATERIA INEXISTENTE "  << endl << endl;
        Sleep(1500);
        system("cls");

        return false;
    }


    if(!(pMat = fopen("materias.dat", "rb"))) {
        cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        return false;
    }
    while(fread(&materiaObj, sizeof(Materia), 1, pMat)) {

        if(materiaObj.getId() == idMateria){
            if(materiaObj.getLegajoProfesor() == getIdProfesor()){ //Esto va a cambiar por (materiaObj.getProfesor()).getLegajo()
                exito = true;
                _idMateria = idMateria;
                break;
            }
        }
    }
    if(!exito) {
        cout << endl << "\t ---- ERROR : LA MATERIA CON ID " << idMateria << " NO CORRESPONDE AL PROFESOR CON LEGAJO " << materiaObj.getLegajoProfesor() << endl << endl;
        Sleep(1500);
        system("cls");

        return false;
    }

    cout << endl;

    fclose(pMat);

    return true;
}

void Evaluacion::setFecha(Fecha fecha){
    _fecha = fecha;
}

void Evaluacion::setEstado(bool estado){
    _estado = estado;
}

///GEETERS

int Evaluacion::getId(){
    return _id;
}

int Evaluacion::getIdProfesor(){
    return _idProfesor;
}

int Evaluacion::getIdMateria(){
    return _idMateria;
}

Fecha Evaluacion::getFecha(){
    return _fecha;
}

bool Evaluacion::getEstado(){
    return _estado;
}

bool Evaluacion::cargarEvaluacion(int legajoProfesor){
    int idMateria;
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    time_t currentTime = mktime(now);

    cout << "CREANDO EXÁMEN FINAL" << endl << endl;

    setId();
    cout << "\t - ID Final: ";
    cout << getId() << endl << endl;

    cout << "\t - Legajo Profesor: ";
    setIdProfesor(legajoProfesor);
    cout << getIdProfesor() << endl << endl;

    cout << "\t - ID Materia: ";
    cin >> idMateria;

    while(!setIdMateria(idMateria)){
        cout << "CREANDO EXÁMEN FINAL" << endl << endl;

        setId();
        cout << "\t - ID Final: ";
        cout << getId() << endl << endl;

        cout << "\t - Legajo Profesor: ";
        cout << getIdProfesor() << endl << endl;

        cout << "\t - ID Materia: ";
        cin >> idMateria;
    }

    cout << "\t - Fecha: " << endl;
    _fecha.CargarFechaEvaluacion(getId(), getIdProfesor(), getIdMateria());

    tm specificDate = createDate(_fecha.getDia(), _fecha.getMes(), _fecha.getAnio());
    time_t specificTime = mktime(&specificDate);

    while(difftime(specificTime, currentTime) < 0 || difftime(specificTime, currentTime) == 0){
        cout << "\t ---- ERROR : LA FECHA ESPECIFICADA ES ANTERIOR O IGUAL A LA FECHA ACTUAL ----" << endl << endl;
        Sleep(1000);
        system("cls");

        cout << "CREANDO EXÁMEN FINAL" << endl << endl;

        setId();
        cout << "\t - ID Final: ";
        cout << getId() << endl << endl;

        cout << "\t - Legajo Profesor: ";
        cout << getIdProfesor() << endl << endl;

        cout << "\t - ID Materia: ";
        cout << getIdMateria() << endl << endl;

        cout << "\t - Fecha: " << endl;

        _fecha.CargarFechaEvaluacion(getId(), getIdProfesor(), getIdMateria());
        specificDate = createDate(_fecha.getDia(), _fecha.getMes(), _fecha.getAnio());
        specificTime = mktime(&specificDate);
    }

    cout << endl << "¡EXAMEN FINAL CREADO CON ÉXITO!" << endl << endl;
    return true;

    setEstado(true);
}

void Evaluacion::mostrarEvaluacion(){
    cout << "\t - ID Final: ";
    cout << getId() << endl << endl;

    cout << "\t - Legajo Profesor: ";
    cout << getIdProfesor() << endl << endl;
    cout << "\t - ID Materia: ";
    cout << getIdMateria() << endl << endl;
    cout << "\t - Fecha: ";
    cout << getFecha().toString("DD/MM/YYYY") << endl << endl;

    cout << endl;
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
        if(generarId() == 1){
            cout << endl <<"---- NO HAY EXAMENES FINALES CARGADOS ----" << endl << endl;
        }
        else{
            cout << endl << "---- ERROR AL ABRIR EL ARCHIVO ----" << endl;
        }
        return;
    }


    while(fread(this,sizeof(Evaluacion),1, pEvaluacion)){
        this->mostrarEvaluacion();
    };

     if(generarId() == 1){
        cout << endl <<"---- NO HAY EXAMENES FINALES CARGADOS ----" << endl << endl;
    }

    fclose(pEvaluacion);
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
    fseek(pEval, 0, SEEK_SET);
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
        if(this->getIdMateria() == idMateria){
            fclose(pEvaluacion);
            return true;
        }
    }

    fclose(pEvaluacion);
    return false;
}
