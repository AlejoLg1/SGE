#include <iostream>
#include <cstring>
#include <limits>
#include "Listados.h"
#include "Director.h"

using namespace std;

void Listados::CargarDirectores()
{
Director dire;

dire.cargarDirector();
dire.grabarEnDiscoDirector();

}



int Listados::ListarDirectores()
{
Director dire;

int pos=0;

while(dire.leerEnDiscoDirector(pos)==true)
{
    dire.mostrarDirector();
    pos++;
}
return -1;
}
