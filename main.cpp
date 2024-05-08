#include <iostream>
#include "linea.h"
#include "estacion.h"
using namespace std;


int main() {
    char opcion;
    string nombre_linea;
    string nombre_estacion, nombre_estacion_f;
    bool ban = true;
    linea red_metro;
    cout << "**Bienvenido a la creacion de una RED METRO.**" << endl << endl;
    while (ban) {
        cout << endl << "*Ingrese la opcion deseada.*" << endl
             << "1. Agregar una estacion a una linea." << endl
             << "2. Eliminar una estacion de una linea." << endl
             << "3. Cantidad de lineas de la red." << endl
             << "4. Cantidad de estaciones de 'x' linea." << endl
             << "5. Consultar si 'x' estacion, pertenece a 'y' linea." << endl
             << "6. Agregar una linea a la red metro." << endl
             << "7. Eliminar una linea de la red metro." << endl
             << "8. Cantidad de estaciones de la red metro." << endl
             << "9. Estaciones disponibles." << endl
             << "M. Calculo del tiempo de llegada." << endl
             << "N. Salir." << endl << endl
             << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == '1') {
            red_metro.imprimirEstacionesDisponibles();
            cout << "Ingrese el nombre de la linea a la que pertenecera la estacion: ";
            getline(cin, nombre_linea);
            cout << "Ingrese el nombre de la nueva estacion: ";
            getline(cin, nombre_estacion);
            red_metro.agregarEstacion(nombre_estacion, nombre_linea);

        } else if(opcion == '2') {
            red_metro.imprimirEstacionesDisponibles();
            cout << "Ingrese el nombre de la linea a la que pertenece la estacion: ";
            getline(cin, nombre_linea);
            cout << "Ingrese el nombre de la estacion a eliminar: ";
            getline(cin, nombre_estacion);
            red_metro.eliminarEstacion(nombre_estacion, nombre_linea);

        } else if (opcion == '3') {
            red_metro.imprimirEstacionesDisponibles();
            cout << endl << "La cantidad de lineas de toda la red es de: " << red_metro.getNumeroTotalDeLineas() << endl;

        } else if (opcion == '4') {
            red_metro.imprimirEstacionesDisponibles();
            cout << "Ingrese el nombre de la linea para consultar sus estaciones: ";
            getline(cin, nombre_linea);
            int num_Est=red_metro.getNumeroDeEstaciones(nombre_linea);
            if (num_Est == -1) {
                cout << endl << "La Linea '" << nombre_linea << "' no existe." << endl;
            } else {
                cout << endl << "La cantidad de estaciones de toda la linea '" << nombre_linea << "' es de: " << num_Est << endl;
            }

        } else if (opcion == '5') {
            cout << "Ingrese la linea a la que cree que pertenece la estacion: ";
            getline(cin, nombre_linea);
            cout << "Ingrese la estacion que desea consultar: ";
            getline(cin, nombre_estacion);
            bool conEst=red_metro.consultarEstacion(nombre_linea, nombre_estacion);
            if(conEst==1){
                cout << endl << "  *La estacion '" << nombre_estacion << "' si pertenece a la linea '" << nombre_linea << "'.*" << endl;
            }

        } else if (opcion == '6') {
            if(red_metro.getNumeroDeLineas() == 0){
                red_metro.agregarLinea();
            }
            else{
                cout << "Ingrese el nombre de la nueva linea: ";
                getline(cin, nombre_linea);
                red_metro.agregarLinea(nombre_linea);
            }

        } else if (opcion == '7') {
            red_metro.imprimirEstacionesDisponibles();
            cout << "Ingrese el nombre de la linea a eliminar: ";
            getline(cin, nombre_linea);
            red_metro.eliminarLinea(nombre_linea);

        } else if (opcion == '8') {
            red_metro.imprimirEstacionesDisponibles();
            cout << endl << "La cantidad de estaciones de toda la red es de: " << red_metro.getNumeroTotalDeEstaciones() << endl;

        } else if (opcion == '9') {
            red_metro.imprimirEstacionesDisponibles();

        } else if (opcion == 'm' || opcion == 'M') {
            red_metro.imprimirEstacionesDisponibles();
            cout << "Ingrese la linea de las estaciones: ";
            getline(cin, nombre_linea);
            cout << "Ingrese la estacion inicial: ";
            getline(cin, nombre_estacion);
            cout << "Ingrese la estacion final: ";
            getline(cin, nombre_estacion_f);
            red_metro.tiempoEstaciones(nombre_linea, nombre_estacion, nombre_estacion_f);

        } else if (opcion == 'n' || opcion == 'N') {
            ban = false;
        } else if (opcion == 'a') {
            cin >> nombre_estacion;
            cout << "este: " << red_metro.getTiempoAntes(nombre_estacion);
        } else if (opcion == 'd') {
            cin >> nombre_estacion;
            cout << "este: " << red_metro.getTiempoDespues(nombre_estacion);
        }
    }

    return 0;
}
