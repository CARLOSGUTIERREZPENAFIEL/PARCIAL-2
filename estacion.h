#ifndef ESTACION_H
#define ESTACION_H
#include <iostream>
using namespace std;


class estacion
{
private:
    string nombre;
    string nombre_linea;
    bool es_transferencia;
    string tiempo_antes;
    string tiempo_despues;
public:
    estacion(string _nombre, string _nombre_linea, bool _es_transferencia = false);
    string getNombre();
    string getNombreLinea() ;
    void setNombre(string _nombre);
    void setEsTransferencia(bool _es_transferencia);
    bool getEsTransferencia() ;
    string getTiempoAntes() ;
    string getTiempoDespues();
    void setTiempoAntes(string _tiempo_antes);
    void setTiempoDespues(string _tiempo_despues);
};

#endif // ESTACION_H
