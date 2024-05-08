#include "linea.h"
#include "estacion.h"
#include <iostream>
using namespace std;

linea::linea() {
    capacidad = 1;
    contador = 0;
    capacidad_transfe = 0;
    arreglo_lineas = new string[capacidad];
    arreglo_estaciones = new estacion**[capacidad];
    nombres_estaciones_unicas = new string*[capacidad];
    nombres_estaciones_transferencia = new string[capacidad_transfe];
    contador_estaciones = new int[capacidad];
}

linea::~linea() {
    delete[] arreglo_lineas;
    delete[] contador_estaciones;
    delete[] nombres_estaciones_unicas;
    for (int i = 0; i < contador; i++) {
        delete[] arreglo_estaciones[i];
    }
    delete[] arreglo_estaciones;
    delete[] nombres_estaciones_transferencia;
}

int linea::getNumeroTotalDeEstaciones() {
    int total_estaciones = 0;
    for (int i = 0; i < contador; ++i) {
        for (int j = 0; j < contador_estaciones[i]; ++j) {
            // Verificar si la estación actual es de transferencia
            if (!arreglo_estaciones[i][j]->getEsTransferencia()) {
                ++total_estaciones;
            }
        }
    }
    total_estaciones+=capacidad_transfe;
    return total_estaciones;
}

int linea::getNumeroTotalDeLineas() {
    return contador;
}

int linea::getNumeroDeEstaciones(string nombre_linea) {
    int indice_linea=0;
    bool ban=false;
    for (int i = 0; i < contador; ++i) {
        if (arreglo_lineas[i] == nombre_linea) {
            indice_linea=i;
            ban=true;
        }
    }
    if (ban == false) {
        return -1;
    }
    return contador_estaciones[indice_linea];
}

string linea::getTiempoDespues(string nombre_estacion) {
    for (int i = 0; i < contador; i++) {
        for (int j = 0; j < contador_estaciones[i]; j++) {
            if (arreglo_estaciones[i][j]->getNombre() == nombre_estacion) {
                return arreglo_estaciones[i][j]->getTiempoDespues();
            }
        }
    }
    return "hola";
}

string linea::getTiempoAntes(string nombre_estacion) {
    for (int i = 0; i < contador; i++) {
        for (int j = 0; j < contador_estaciones[i]; j++) {
            if (arreglo_estaciones[i][j]->getNombre() == nombre_estacion) {
                return arreglo_estaciones[i][j]->getTiempoAntes();
            }
        }
    }
    return "hola";
}

bool linea::consultarEstacion(string nombre_linea, string nombre_estacion) {
    string nombre_estacion_transf;
    bool ban = false;
    nombre_estacion_transf = nombre_estacion+"-"+nombre_linea;
    for (int i = 0; i < contador; i++) {
        if (arreglo_lineas[i] == nombre_linea) {
            ban = true;
        }
    }
    for (int i = 0; i < contador; i++) {
        if (arreglo_lineas[i] == nombre_linea) {
            for (int j = 0; j < contador_estaciones[i]; j++) {
                if (arreglo_estaciones[i][j]->getNombre() == nombre_estacion || arreglo_estaciones[i][j]->getNombre() == nombre_estacion_transf) {
                    return 1;
                }
            }
        }
    }
    for (int i = 0; i < contador; i++) {
        nombre_estacion_transf = nombre_estacion+"-"+arreglo_lineas[i];
        for (int j = 0; j < contador_estaciones[i]; j++) {
            if(nombre_estacion == nombres_estaciones_unicas[i][j] || nombre_estacion_transf == nombres_estaciones_unicas[i][j]){
                if(ban == false){
                    cout << endl << "  *La linea '" << nombre_linea << "' no existe." << " Pero la estacion '" << nombre_estacion << "' existe en la linea '" << arreglo_lineas[i] << "'.*" << endl;
                    return 0;
                }
                cout << endl << "  *La estacion '" << nombre_estacion << "' no existe en la linea '" << nombre_linea << "'. Pero existe en la linea '" << arreglo_lineas[i] << "'.*" << endl;
                return 0;
            }
        }
    }
    cout << endl << "  *La estacion '" << nombre_estacion << "' no existe en ninguna linea.*" << endl;
    return 0;
}



void linea::agregarLinea() {
    string nombre, tiempo_est;
    bool contieneSoloNumeros;
    cout << "Ingrese el nombre de la primera linea de metro: ";
    getline(cin, nombre);
    capacidad++;
    string* nuevo_arreglo_lineas = new string[capacidad];
    estacion*** nuevo_arreglo_estaciones = new estacion**[capacidad];
    string** nuevo_nombres_estaciones_unicas = new string*[capacidad];
    int* nuevo_contador_estaciones = new int[capacidad];

    for (int i = 0; i < contador; i++) {
        nuevo_arreglo_lineas[i] = arreglo_lineas[i];
        nuevo_arreglo_estaciones[i] = arreglo_estaciones[i];
        nuevo_nombres_estaciones_unicas[i] = nombres_estaciones_unicas[i];
        nuevo_contador_estaciones[i] = contador_estaciones[i];
    }

    delete[] arreglo_lineas;
    delete[] contador_estaciones;
    delete[] arreglo_estaciones;
    delete[] nombres_estaciones_unicas;

    arreglo_lineas = nuevo_arreglo_lineas;
    arreglo_estaciones = nuevo_arreglo_estaciones;
    nombres_estaciones_unicas = nuevo_nombres_estaciones_unicas;
    contador_estaciones = nuevo_contador_estaciones;

    arreglo_lineas[contador] = nombre;

    string nombre_estacion_inicial, nombre_estacion_final;
    cout << endl << "Ingrese el nombre de la estacion inicial para la linea '" << nombre << "': ";
    getline(cin, nombre_estacion_inicial);
    cout << "Ingrese el nombre de la estacion final para la linea '" << nombre << "': ";
    getline(cin, nombre_estacion_final);
    while(nombre_estacion_final==nombre_estacion_inicial){
        cout << endl << "No puede ingresar las estaciones con el mismo nombre." << endl << "Por favor ingrese otra estacion final para la linea '" << nombre << "': ";
        getline(cin, nombre_estacion_final);
    }
    do {
        cout << "Ingrese el tiempo en segundos que tarda en llegar de la estacion '" << nombre_estacion_inicial << "' a la estacion '" << nombre_estacion_final << "': ";
        getline(cin, tiempo_est);

        contieneSoloNumeros = true;
        for (char c : tiempo_est) {
            if (!(c >= '0' && c <= '9')) {
                contieneSoloNumeros = false;
                break;
            }
        }

        if (!contieneSoloNumeros) {
            cout << "***El numero ingresado contiene caracteres. Intente de nuevo.***" << endl;
        }
    } while (!contieneSoloNumeros);
    arreglo_estaciones[contador] = new estacion*[2];
    nombres_estaciones_unicas[contador] = new string[2];
    arreglo_estaciones[contador][0] = new estacion(nombre_estacion_inicial, nombre, false);
    arreglo_estaciones[contador][0]->setTiempoDespues(tiempo_est);
    arreglo_estaciones[contador][1] = new estacion(nombre_estacion_final, nombre, false);
    arreglo_estaciones[contador][1]->setTiempoAntes(tiempo_est);
    nombres_estaciones_unicas[contador][0] = nombre_estacion_inicial;
    nombres_estaciones_unicas[contador][1] = nombre_estacion_final;
    contador_estaciones[contador] = 2;
    contador++;
    cout << "  *Primera linea agregada con exito.*" << endl;
}

void linea::tiempoEstaciones(string nombre_linea, string nombre_estacion_i, string nombre_estacion_f) {
    bool est_1 = consultarEstacion(nombre_linea, nombre_estacion_i);
    bool est_2 = consultarEstacion(nombre_linea, nombre_estacion_f);
    bool contieneSoloNumeros = false;
    int hora = 0, minutos = 0, segundos = 0, segundos_viaje = 0, segundos_viaje_totales = 0, minutos_viaje_totales = 0, hora_viaje_totales = 0;
    int indice_estacion_i, indice_estacion_f;
    string input, tiempo, tiempo_final, tiempo_inicial;
    if (est_1 == 0 || est_2 == 0) {
        cout << "  *Deben ser estaciones de la misma linea, intente de nuevo.*";
        return;
    }
    cout << "Ingrese la hora actual, en el siguiente orden: hora, minutos, segundos. (ingreselos de manera separada de a dos digitos, por ejemplo '01' o '12')." << endl;
    while (!contieneSoloNumeros) {
        hora = 0; // Reinicia la variable hora
        cout << "Por favor, ingresa la HORA: ";
        getline(cin, input);

        // Verificar si el string tiene exactamente dos dígitos
        if (input.length() == 2) {
            contieneSoloNumeros = true;
            for (char c : input) {
                if (!(c >= '0' && c <= '9')) {
                    contieneSoloNumeros = false;
                    break;
                }
                hora *= 10;
                hora += c - '0';
                if (hora > 23 || hora < 0) {
                    contieneSoloNumeros = false;
                    break;
                }
            }
        } else {
            cout << "La hora debe contener dos digitos, y no ser mayor de 24 o menor de 00." << endl;
        }
    }
    contieneSoloNumeros = false;
    tiempo_inicial += input + ":";
    while (!contieneSoloNumeros) {
        minutos = 0; // Reinicia la variable minutos
        cout << "Por favor, ingresa los MINUTOS: ";
        cin >> input;

        // Verificar si el string tiene exactamente dos dígitos
        if (input.length() == 2) {
            contieneSoloNumeros = true;
            for (char c : input) {
                if (!(c >= '0' && c <= '9')) {
                    contieneSoloNumeros = false;
                    break;
                }
                minutos *= 10;
                minutos += c - '0';
                if (minutos > 59 || minutos < 0) {
                    contieneSoloNumeros = false;
                    break;
                }
            }
        } else {
            cout << "Los minutos debe contener dos digitos, y no ser mayor de 59 o menor de 00." << endl;
        }
    }
    contieneSoloNumeros = false;
    tiempo_inicial += input + ":";
    while (!contieneSoloNumeros) {
        segundos = 0; // Reinicia la variable segundos
        cout << "Por favor, ingresa los SEGUNDOS: ";
        cin >> input;

        // Verificar si el string tiene exactamente dos dígitos
        if (input.length() == 2) {
            contieneSoloNumeros = true;
            for (char c : input) {
                if (!(c >= '0' && c <= '9')) {
                    contieneSoloNumeros = false;
                    break;
                }
                segundos *= 10;
                segundos += c - '0';
                if (segundos > 59 || segundos < 0) {
                    contieneSoloNumeros = false;
                    break;
                }
            }
        } else {
            cout << "Los segundos deben contener dos digitos, y no ser mayor de 59 o menor de 00." << endl;
        }
    }
    tiempo_inicial += input;
    for (int i = 0; i < contador; i++) {
        if (arreglo_lineas[i] == nombre_linea) {
            for (int j = 0; j < contador_estaciones[i]; j++) {
                if (nombre_estacion_i == nombres_estaciones_unicas[i][j]) {
                    indice_estacion_i = j;
                }
                else if (nombre_estacion_f == nombres_estaciones_unicas[i][j]) {
                    indice_estacion_f = j;
                }
            }
        }
    }
    if(indice_estacion_f < indice_estacion_i) {
        int temp=indice_estacion_i;
        indice_estacion_i=indice_estacion_f;
        indice_estacion_f=temp;
    }
    for (int i = 0; i < contador; i++) {
        if (arreglo_lineas[i] == nombre_linea) {
            for (int j = indice_estacion_i; j <= indice_estacion_f; j++) {
                tiempo = arreglo_estaciones[i][j]->getTiempoDespues();
                segundos_viaje=0;
                for (char c : tiempo) {
                    segundos_viaje*=10;
                    segundos_viaje+=c-'0';

                }
                segundos_viaje_totales+=segundos_viaje;
                if (segundos_viaje_totales > 59) {
                    segundos_viaje_totales-=60;
                    minutos_viaje_totales+=1;
                }
                if (minutos_viaje_totales > 59) {
                    minutos_viaje_totales-=60;
                    hora_viaje_totales+=1;
                }
            }
        }
    }

    segundos_viaje_totales+=segundos;
    minutos_viaje_totales+=minutos;
    hora_viaje_totales+=hora;
    while(segundos_viaje_totales>59) {
        segundos_viaje_totales-=60;
        minutos_viaje_totales+=1;
    }
    while(minutos_viaje_totales>59) {
        minutos_viaje_totales-=60;
        hora_viaje_totales+=1;
    }
    while(hora_viaje_totales>24) {
        hora_viaje_totales-=24;
    }
    tiempo_final = to_string(hora_viaje_totales)+":"+to_string(minutos_viaje_totales)+":"+to_string(segundos_viaje_totales);
    cout << endl << "*Si inicial el viaje desde '" << nombre_estacion_i  << "' a las '" << tiempo_inicial << "' estaria llegando a '" << nombre_estacion_f << "' a las '" << tiempo_final << "'.*" << endl;
}

void linea::agregarLinea(string nombre) {
    bool linea_repetida = false, ban = false, ban2 = true, contieneSoloNumeros;
    string tiempo_est;
    for (int i = 0; i < contador; i++) {
        if (arreglo_lineas[i] == nombre) {
            linea_repetida = true;
            break;
        }
    }
    if (linea_repetida) {
        cout << "  *La linea ya existe. Por favor, ingrese un nombre de linea diferente.*" << endl;
        return;
    }

    capacidad++;
    string* nuevo_arreglo_lineas = new string[capacidad];
    estacion*** nuevo_arreglo_estaciones = new estacion**[capacidad];
    string** nuevo_nombres_estaciones_unicas = new string*[capacidad];
    int* nuevo_contador_estaciones = new int[capacidad];

    for (int i = 0; i < contador; i++) {
        nuevo_arreglo_lineas[i] = arreglo_lineas[i];
        nuevo_arreglo_estaciones[i] = arreglo_estaciones[i];
        nuevo_nombres_estaciones_unicas[i] = nombres_estaciones_unicas[i];
        nuevo_contador_estaciones[i] = contador_estaciones[i];
    }

    delete[] arreglo_lineas;
    delete[] contador_estaciones;
    delete[] arreglo_estaciones;
    delete[] nombres_estaciones_unicas;

    arreglo_lineas = nuevo_arreglo_lineas;
    arreglo_estaciones = nuevo_arreglo_estaciones;
    nombres_estaciones_unicas = nuevo_nombres_estaciones_unicas;
    contador_estaciones = nuevo_contador_estaciones;

    arreglo_lineas[contador] = nombre;
    string nombre_estacion_transferencia, nombre_estacion_final, nombre_base;
    imprimirEstacionesDisponibles();
    do {
        cout << endl << "Ingrese el nombre de la estacion de trasnferencia (que se encuentre en una de las lineas anteriores) para la linea '" << nombre << "': ";
        getline(cin, nombre_estacion_transferencia);
        for(int i=0;i<capacidad_transfe;i++){
            if(nombre_estacion_transferencia==nombres_estaciones_transferencia[i]){
                nombre_estacion_transferencia+="-"+nombre;
                ban=true;
            }
        }
        for (int i = 0; i < contador; i++) {
            for (int j = 0; j < contador_estaciones[i]; j++) {
                if(nombre_estacion_transferencia == nombres_estaciones_unicas[i][j]){
                    string nuevo_nombre;
                    nombre_base=nombre_estacion_transferencia;
                    nuevo_nombre=nombre_estacion_transferencia+"-"+arreglo_lineas[i];
                    arreglo_estaciones[i][j]->setNombre(nuevo_nombre);
                    nombres_estaciones_unicas[i][j] = nuevo_nombre;
                    nombre_estacion_transferencia+="-"+nombre;
                    string* nuevo_nombres_estaciones_transferencia = new string[capacidad_transfe + 1];
                    for (int k = 0; k < capacidad_transfe; ++k) {
                        nuevo_nombres_estaciones_transferencia[k] = nombres_estaciones_transferencia[k];
                    }
                    nuevo_nombres_estaciones_transferencia[capacidad_transfe] = nombre_base;
                    delete[] nombres_estaciones_transferencia;
                    nombres_estaciones_transferencia = nuevo_nombres_estaciones_transferencia;
                    capacidad_transfe++;
                    arreglo_estaciones[i][j]->setEsTransferencia(true);
                    ban=true;
                }
            }
        }
        if(ban==false){
            cout << endl << "***La estacion '" << nombre_estacion_transferencia << "' no existe en ninguna linea. Por favor, intente de nuevo con una estacion de transferencia valida.***" << endl;
        }
    } while(ban==false);
    do{
        ban2=true;

        cout << "Ingrese el nombre de la estacion final para la linea '" << nombre << "': ";
        getline(cin, nombre_estacion_final);
        for(int i=0;i<capacidad_transfe;i++){
            nombre_base = nombres_estaciones_transferencia[i];
            if(nombre_base==nombre_estacion_final){
                cout << endl << "***La estacion '" << nombre_estacion_final << "' es una estacion de transferencia, por favor ingrese otro nombre o generaria un bucle.***" << endl << endl;
                ban2=false;
            }
        }

        for (int i = 0; i < contador; i++) {
            for (int j = 0; j < contador_estaciones[i]; j++) {
                if(nombre_estacion_final == nombres_estaciones_unicas[i][j]){
                    cout << endl << "***La estacion '" << nombre_estacion_final << "' existe en la linea '" << arreglo_lineas[i] << "'. Por favor, intente de nuevo.***" << endl << endl;
                    ban2=false;
                }
            }
        }
    }while(ban2==false);
    do {
        cout << "Ingrese el tiempo en segundos que tarda en llegar de la estacion '" << nombre_estacion_transferencia << "' a la estacion '" << nombre_estacion_final << "': ";
        getline(cin, tiempo_est);

        contieneSoloNumeros = true;
        for (char c : tiempo_est) {
            if (!(c >= '0' && c <= '9')) {
                contieneSoloNumeros = false;
                break;
            }
        }

        if (!contieneSoloNumeros) {
            cout << endl << "***El numero ingresado contiene caracteres. Intente de nuevo.***" << endl << endl;
        }
    } while (!contieneSoloNumeros);
    arreglo_estaciones[contador] = new estacion*[2];
    nombres_estaciones_unicas[contador] = new string[2];
    arreglo_estaciones[contador][0] = new estacion(nombre_estacion_transferencia, nombre, true);
    arreglo_estaciones[contador][0]->setTiempoDespues(tiempo_est);
    arreglo_estaciones[contador][1] = new estacion(nombre_estacion_final, nombre, false);
    arreglo_estaciones[contador][1]->setTiempoAntes(tiempo_est);
    nombres_estaciones_unicas[contador][0] = nombre_estacion_transferencia;
    nombres_estaciones_unicas[contador][1] = nombre_estacion_final;
    contador_estaciones[contador] = 2;
    contador++;
    cout << "  *Linea agregada con exito.*" << endl;
}


void linea::eliminarLinea(string nombre_linea) {
    bool banderilla = false;
    string nom_transf;
    for (int i = 0; i < contador; i++) {
        if (arreglo_lineas[i] == nombre_linea) {
            banderilla = true;
            for (int j = 0; j < contador_estaciones[i]; j++) {
                if (arreglo_estaciones[i][j]->getEsTransferencia()) {
                    cout << endl << "  *Esta linea cuenta con una estacion de transferencia, no se puede eliminar.*" << endl;
                    return;
                }
            }
        }
    }


    if (banderilla == false){
        cout << endl << "  *No existe la linea ingresada, por favor intente de nuevo.*" << endl;
        return;
    }
    int indice_eliminar = -1;
    for (int i = 0; i < contador; ++i) {
        if (arreglo_lineas[i] == nombre_linea) {
            indice_eliminar = i;
            break;
        }
    }
    for (int i = 0; i < contador_estaciones[indice_eliminar]; ++i) {
        delete arreglo_estaciones[indice_eliminar][i];
    }
    delete[] arreglo_estaciones[indice_eliminar];
    delete[] nombres_estaciones_unicas[indice_eliminar];

    for (int i = indice_eliminar; i < contador - 1; ++i) {
        arreglo_lineas[i] = arreglo_lineas[i + 1];
        arreglo_estaciones[i] = arreglo_estaciones[i + 1];
        nombres_estaciones_unicas[i] = nombres_estaciones_unicas[i + 1];
        contador_estaciones[i] = contador_estaciones[i + 1];
    }

    --contador;

    cout << "  *La linea '" << nombre_linea << "' ha sido eliminada exitosamente.*" << endl;

}



void linea::agregarEstacion(string nombre_estacion, string nombre_linea) {
    string tiempo_est="a";
    bool linea_encontrada = false, contieneSoloNumeros = false;
    for (int i = 0; i < contador; i++) {
        for (int j = 0; j < contador_estaciones[i]; j++) {
            if(nombre_estacion == nombres_estaciones_unicas[i][j]){
                cout << "  *La estacion ya existe en la linea '" << arreglo_lineas[i] << "'. Por favor, ingrese una estacion nueva.*" << endl;
                return;
            }
        }
    }
    for (int i = 0; i < contador; i++) {
        if (arreglo_lineas[i] == nombre_linea) {
            linea_encontrada = true;
            cout << endl << "Estaciones disponibles en la linea '" << nombre_linea << "':" << endl;
            for (int j = 0; j < contador_estaciones[i] - 1; j++) {
                cout << j + 1 << ". " << nombres_estaciones_unicas[i][j] << " - " << nombres_estaciones_unicas[i][j + 1] << endl;
            }
            cout << contador_estaciones[i] << ". " << "Extremo final." << endl << contador_estaciones[i]+1 << ". " << "Extremo inicial." << endl;
            int posicion;
            do {
                cout << "Seleccione la posicion donde desea agregar la estacion '" << nombre_estacion << "' (Ingrese un numero entre 1 y " << contador_estaciones[i]+1 << "): ";
                cin >> posicion;
                if (cin.fail()) {
                    cout << "Entrada invalida. Por favor, ingrese un numero." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            } while (posicion < 1 || posicion > contador_estaciones[i]+1);
            cin.ignore();
            if (posicion == contador_estaciones[i]+1){
                posicion=0;
            }
            int num_estaciones = contador_estaciones[i];
            estacion** nuevo_arreglo_estaciones = new estacion*[num_estaciones + 1];
            string* nuevo_nombres_estaciones_unicas = new string[num_estaciones + 1];
            for (int j = 0; j < num_estaciones; j++) {
                if (j < posicion) {
                    nuevo_arreglo_estaciones[j] = arreglo_estaciones[i][j];
                    nuevo_nombres_estaciones_unicas[j] = nombres_estaciones_unicas[i][j];
                } else {
                    nuevo_arreglo_estaciones[j + 1] = arreglo_estaciones[i][j];
                    nuevo_nombres_estaciones_unicas[j + 1] = nombres_estaciones_unicas[i][j];
                }
            }

            nuevo_arreglo_estaciones[posicion] = new estacion(nombre_estacion, nombre_linea);
            nuevo_nombres_estaciones_unicas[posicion] = nombre_estacion;

            delete[] arreglo_estaciones[i];
            delete[] nombres_estaciones_unicas[i];
            arreglo_estaciones[i] = nuevo_arreglo_estaciones;
            nombres_estaciones_unicas[i] = nuevo_nombres_estaciones_unicas;
            contador_estaciones[i]++;
            cout << endl;
            if (posicion == 0) {
                do {
                    cout << "Ingrese el tiempo en segundos que tardara la estacion '" << nombres_estaciones_unicas[i][posicion] << "' en llegar hasta la estacion '" << nombres_estaciones_unicas[i][posicion+1] << "': ";
                    getline(cin, tiempo_est);

                    contieneSoloNumeros = true;
                    for (char c : tiempo_est) {
                        if (!(c >= '0' && c <= '9')) {
                            contieneSoloNumeros = false;
                            break;
                        }
                    }

                    if (!contieneSoloNumeros) {
                        cout << "***El numero ingresado contiene caracteres. Intente de nuevo.***" << endl;
                    }
                } while (!contieneSoloNumeros);
                arreglo_estaciones[i][posicion]->setTiempoDespues(tiempo_est);
                arreglo_estaciones[i][posicion+1]->setTiempoAntes(tiempo_est);
                cout << "  *Estacion agregada con exito en el extremo inicial.*" << endl;
                break;
            }
            else if (posicion == contador_estaciones[i]-1) {
                do {
                    cout << "Ingrese el tiempo en segundos que tardara la estacion '" << nombres_estaciones_unicas[i][posicion-1] << "' en llegar hasta la estacion '" << nombres_estaciones_unicas[i][posicion] << "': ";
                    getline(cin, tiempo_est);

                    contieneSoloNumeros = true;
                    for (char c : tiempo_est) {
                        if (!(c >= '0' && c <= '9')) {
                            contieneSoloNumeros = false;
                            break;
                        }
                    }

                    if (!contieneSoloNumeros) {
                        cout << "***El numero ingresado contiene caracteres. Intente de nuevo.***" << endl;
                    }
                } while (!contieneSoloNumeros);
                arreglo_estaciones[i][posicion-1]->setTiempoDespues(tiempo_est);
                arreglo_estaciones[i][posicion]->setTiempoAntes(tiempo_est);

                cout << "  *Estacion agregada con exito en el extremo final.*" << endl;
                break;
            }
            else {

                do {
                    cout << "Ingrese el tiempo en segundos que tardara la estacion '" << nombres_estaciones_unicas[i][posicion - 1] << "' en llegar hasta la estacion '" << nombres_estaciones_unicas[i][posicion] << "': ";
                    getline(cin, tiempo_est);
                    contieneSoloNumeros = true;
                    for (char c : tiempo_est) {
                        if (!(c >= '0' && c <= '9')) {
                            contieneSoloNumeros = false;
                            break;
                        }
                    }

                    if (!contieneSoloNumeros) {
                        cout << "***El numero ingresado contiene caracteres. Intente de nuevo.***" << endl;
                    }
                } while (!contieneSoloNumeros);
                arreglo_estaciones[i][posicion-1]->setTiempoDespues(tiempo_est);
                arreglo_estaciones[i][posicion]->setTiempoAntes(tiempo_est);

                do {
                    cout << "Ingrese el tiempo en segundos que tardara la estacion '" << nombres_estaciones_unicas[i][posicion] << "' en llegar hasta la estacion '" << nombres_estaciones_unicas[i][posicion+1] << "': ";
                    getline(cin, tiempo_est);
                    contieneSoloNumeros = true;
                    for (char c : tiempo_est) {
                        if (!(c >= '0' && c <= '9')) {
                            contieneSoloNumeros = false;
                            break;
                        }
                    }

                    if (!contieneSoloNumeros) {
                        cout << "***El numero ingresado contiene caracteres. Intente de nuevo.***" << endl;
                    }
                } while (!contieneSoloNumeros);
                arreglo_estaciones[i][posicion]->setTiempoDespues(tiempo_est);
                arreglo_estaciones[i][posicion+1]->setTiempoAntes(tiempo_est);
                cout << "  *Estacion agregada con exito entre '" << nombres_estaciones_unicas[i][posicion - 1] << "' y '" << nombres_estaciones_unicas[i][posicion+1] << "'.*" << endl;
                break;
            }
        }
    }
    if (!linea_encontrada) {
        cout << "  *La linea especificada no existe. Por favor, ingrese una linea valida.*" << endl;
    }
}



void linea::eliminarEstacion(string nombre_estacion, string nombre_linea) {
    bool banderilla = false, ban=false, contieneSoloNumeros = false;
    string nom_transf, tiempo_est;
    int indice_linea = 0;
    int indice_estacion = 0;
    nom_transf=nombre_estacion+"-"+nombre_linea;
    for (int i = 0; i < contador; ++i) {
        if (arreglo_lineas[i] == nombre_linea) {
            indice_linea = i;
            break;
        }
    }
    if(contador_estaciones[indice_linea] == 1) {
        cout << "  *Esta es la ultima estacion de la linea, no se puede eliminar. Intenta eliminando la linea!*" << endl;
        return;
    }
    for (int i = 0; i < contador; i++) {
        if (arreglo_lineas[i] == nombre_linea) {
            ban = true;
            for (int j = 0; j < contador_estaciones[i]; j++) {
                if (nombre_estacion == nombres_estaciones_unicas[i][j]) {
                    banderilla = true;
                    indice_estacion = j;
                    bool transf = arreglo_estaciones[i][j]->getEsTransferencia();
                    if (transf) {
                        cout << "  *Esta estacion es de transferencia, no se puede eliminar.*" << endl;
                        return;
                    }
                } else if (nom_transf == nombres_estaciones_unicas[i][j]) {
                    cout << "  *Esta estacion es de transferencia, no se puede eliminar.*" << endl;
                    return;
                }
            }
        }
    }
    if (ban == false){
        cout << "  *No existe la linea '" << nombre_linea << "'.*" << endl;
        return;
    }

    if (banderilla == false) {
        cout << "  *La estacion '" << nombre_estacion << "' no existe en la linea '" << nombre_linea << "'.*" << endl;
        char respuesta;
        do{
            cout << "Desea agregar esta estacion a la linea? (Y/N): ";
            cin >> respuesta;
            cout << endl;
            cin.ignore(); // Limpiar el buffer de entrada
            if (respuesta == 'Y' || respuesta == 'y') {
                agregarEstacion(nombre_estacion, nombre_linea);
                return;
            }
            else if (respuesta == 'N' || respuesta == 'n'){
                return;
            }
        } while(banderilla == false);
    }
    delete arreglo_estaciones[indice_linea][indice_estacion];
    for (int j = indice_estacion; j < contador_estaciones[indice_linea] - 1; ++j) {
        nombres_estaciones_unicas[indice_linea][j] = nombres_estaciones_unicas[indice_linea][j + 1];
    }
    --contador_estaciones[indice_linea];
    int est_linea = contador_estaciones[indice_linea];
    cout << "  *La estacion '" << nombre_estacion << "' ha sido eliminada exitosamente de la linea '" << nombre_linea << "'.*" << endl;
    if (indice_estacion == 0) {
        cout << "aca: " << arreglo_estaciones[indice_linea][indice_estacion+1]->getNombre();
        arreglo_estaciones[indice_linea][indice_estacion]->setTiempoAntes("0");

    } else if (indice_estacion == est_linea) {
        arreglo_estaciones[indice_linea][est_linea-1]->setTiempoDespues("0");

    } else {
        do {
            cout << "Ingrese el tiempo en segundos que tardara de la estacion '" << nombres_estaciones_unicas[indice_linea][indice_estacion-1] << "' en llegar hasta la estacion '" << nombres_estaciones_unicas[indice_linea][indice_estacion] << "': ";
            getline(cin, tiempo_est);

            contieneSoloNumeros = true;
            for (char c : tiempo_est) {
                if (!(c >= '0' && c <= '9')) {
                    contieneSoloNumeros = false;
                    break;
                }
            }

            if (!contieneSoloNumeros) {
                cout << "***El numero ingresado contiene caracteres. Intente de nuevo.***" << endl;
            }
        } while (!contieneSoloNumeros);
        arreglo_estaciones[indice_linea][indice_estacion-1]->setTiempoDespues(tiempo_est);
        arreglo_estaciones[indice_linea][indice_estacion]->setTiempoAntes(tiempo_est);
    }


}



void linea::imprimirEstacionesDisponibles() {
    cout << endl << "***************************";
    cout << endl << "Estaciones disponibles:" << endl << endl;
    for (int i = 0; i < contador; i++) {
        cout << " Estaciones de la linea '" << arreglo_lineas[i] << "':" << endl;
        for (int j = 0; j < contador_estaciones[i]; j++) {
            cout << "   - " << nombres_estaciones_unicas[i][j] << endl;
        }
    }
    cout << "***************************" << endl << endl;
}

string linea::getNombreLinea(int indice) {
    return arreglo_lineas[indice];
}

string linea::getNombreEstacion(int indice_linea, int indice_estacion) {
    return arreglo_estaciones[indice_linea][indice_estacion]->getNombre();
}

int linea::getNumeroDeLineas() {
    return contador;
}

int linea::getNumeroDeEstaciones(int indice_linea) {
    return contador_estaciones[indice_linea];
}
