#ifndef LINEA_H
#define LINEA_H
#include <iostream>
#include "estacion.h"
using namespace std;

class linea
{
private:
    string* arreglo_lineas;
    estacion*** arreglo_estaciones;
    string** nombres_estaciones_unicas;
    string* nombres_estaciones_transferencia;
    int* contador_estaciones;
    int contador;
    int capacidad;
    int capacidad_transfe;

public:
    linea();
    ~linea();
    void agregarLinea(string nombre);
    void agregarLinea();
    void eliminarLinea(string nombre);
    void agregarEstacion(string nombre_estacion, string nombre_linea);
    void eliminarEstacion(string nombre_estacion, string nombre_linea);
    bool consultarEstacion(string nombre_linea, string nombre_estacion);
    void imprimirEstacionesDisponibles();
    string getNombreLinea(int indice);
    string getNombreEstacion(int indice_linea, int indice_estacion);
    string getTiempoDespues(string nombre_estacion);
    string getTiempoAntes(string nombre_estacion);
    void tiempoEstaciones(string nombre_linea, string nombre_estacion_i, string nombre_estacion_f);
    int getNumeroDeLineas();
    int getNumeroDeEstaciones(int indice_linea);
    int getNumeroTotalDeEstaciones();
    int getNumeroTotalDeLineas();
    int getNumeroDeEstaciones(string nombre_linea);
};

#endif // LINEA_H
