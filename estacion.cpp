#include "estacion.h"
#include <iostream>
using namespace std;

estacion :: estacion(string _nombre, string _nombre_linea, bool _es_transferencia )
    : nombre(_nombre), nombre_linea(_nombre_linea), es_transferencia(_es_transferencia), tiempo_antes("0"), tiempo_despues("0") {}

string estacion :: getNombre() { return nombre; }
string estacion :: getNombreLinea() { return nombre_linea; }
void estacion :: setNombre(string _nombre) { nombre = _nombre; }
void estacion :: setEsTransferencia(bool _es_transferencia) { es_transferencia = _es_transferencia; }
bool estacion :: getEsTransferencia() { return es_transferencia; }
string estacion :: getTiempoAntes() { return tiempo_antes; }
string estacion :: getTiempoDespues() { return tiempo_despues; }
void estacion :: setTiempoAntes(string _tiempo_antes) { tiempo_antes = _tiempo_antes; }
void estacion :: setTiempoDespues(string _tiempo_despues) { tiempo_despues = _tiempo_despues; }
