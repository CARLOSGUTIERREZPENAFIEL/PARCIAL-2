#include <iostream>

using namespace std;

class estaciones {
private:
    string nombre;
    string nombre_linea;
public:
    estaciones(string _nombre, string _nombre_linea) : nombre(_nombre), nombre_linea(_nombre_linea) {}
    string getNombre() { return nombre; }
    string getNombreLinea() { return nombre_linea; }
};

class lineas {
private:
    string* arreglo_lineas;
    estaciones*** arreglo_estaciones;
    int* contador_estaciones;
    int contador;
    int capacidad;

public:
    lineas();
    ~lineas();
    void agregarLinea(string nombre);
    void agregarEstacion(string nombre_estacion, string nombre_linea);
    string getNombreLinea(int indice);
    string getNombreEstacion(int indice_linea, int indice_estacion);
    int getNumeroDeLineas();
    int getNumeroDeEstaciones(int indice_linea);
};

lineas::lineas() {
    capacidad = 1;
    contador = 0;
    arreglo_lineas = new string[capacidad];
    arreglo_estaciones = new estaciones**[capacidad];
    contador_estaciones = new int[capacidad];
}

lineas::~lineas() {
    delete[] arreglo_lineas;
    delete[] contador_estaciones;
    for (int i = 0; i < contador; i++) {
        delete[] arreglo_estaciones[i];
    }
    delete[] arreglo_estaciones;
}

void lineas::agregarLinea(string nombre) {
    capacidad++;
    string* nuevo_arreglo_lineas = new string[capacidad];
    estaciones*** nuevo_arreglo_estaciones = new estaciones**[capacidad];
    int* nuevo_contador_estaciones = new int[capacidad];

    for (int i = 0; i < contador; i++) {
        nuevo_arreglo_lineas[i] = arreglo_lineas[i];
        nuevo_arreglo_estaciones[i] = arreglo_estaciones[i];
        nuevo_contador_estaciones[i] = contador_estaciones[i];
    }

    delete[] arreglo_lineas;
    delete[] contador_estaciones;
    delete[] arreglo_estaciones;

    arreglo_lineas = nuevo_arreglo_lineas;
    arreglo_estaciones = nuevo_arreglo_estaciones;
    contador_estaciones = nuevo_contador_estaciones;

    arreglo_lineas[contador] = nombre;

    string nombre_estacion_inicial, nombre_estacion_final;
    cout << "Ingrese el nombre de la estacion inicial para la linea " << nombre << ": ";
    getline(cin, nombre_estacion_inicial);
    cout << "Ingrese el nombre de la estacion final para la linea " << nombre << ": ";
    getline(cin, nombre_estacion_final);

    // Agregar estaciones al arreglo
    arreglo_estaciones[contador] = new estaciones*[2];
    arreglo_estaciones[contador][0] = new estaciones(nombre_estacion_inicial, nombre);
    arreglo_estaciones[contador][1] = new estaciones(nombre_estacion_final, nombre);
    contador_estaciones[contador] = 2;

    contador++;
}


void lineas::agregarEstacion(string nombre_estacion, string nombre_linea) {
    bool linea_encontrada = false;
    for (int i = 0; i < contador; i++) {
        if (arreglo_lineas[i] == nombre_linea) {
            linea_encontrada = true;
            int num_estaciones = contador_estaciones[i];
            estaciones** nuevo_arreglo_estaciones = new estaciones*[num_estaciones + 1];
            for (int j = 0; j < num_estaciones; j++) {
                nuevo_arreglo_estaciones[j] = arreglo_estaciones[i][j];
            }
            delete[] arreglo_estaciones[i];
            arreglo_estaciones[i] = nuevo_arreglo_estaciones;
            arreglo_estaciones[i][num_estaciones] = new estaciones(nombre_estacion, nombre_linea);
            contador_estaciones[i]++;
            break;
        }
    }
    if (!linea_encontrada) {
        cout << "La linea especificada no existe. Por favor, ingrese una linea valida." << endl;
    }
}

string lineas::getNombreLinea(int indice) {
    return arreglo_lineas[indice];
}

string lineas::getNombreEstacion(int indice_linea, int indice_estacion) {
    return arreglo_estaciones[indice_linea][indice_estacion]->getNombre();
}

int lineas::getNumeroDeLineas() {
    return contador;
}

int lineas::getNumeroDeEstaciones(int indice_linea) {
    return contador_estaciones[indice_linea];
}

int main() {
    char opcion;
    string nombre_linea;
    string nombre_estacion;
    bool ban = true;
    lineas red_metro;

    cout << "*Bienvenido a la creacion de una RED METRO.*" << endl;

    cout << "Ingrese el nombre de la primera linea de metro: ";
    getline(cin, nombre_linea);
    red_metro.agregarLinea(nombre_linea);
    cout << "Primera linea agregada con exito." << endl;
    while (ban) {
        cout << endl << "*Ingrese la opcion deseada.*" << endl
             << "1. Agregar una linea a la red metro." << endl
             << "2. Agregar una estacion a una linea existente." << endl
             << "n. Salir." << endl << endl
             << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == '1') {
            cout << "Ingrese el nombre de la linea: ";
            getline(cin, nombre_linea);
            red_metro.agregarLinea(nombre_linea);
            cout << "Linea agregada con exito." << endl;


        } else if (opcion == '2') {
            cout << "Ingrese el nombre de la linea a la que pertenece la estacion: ";
            getline(cin, nombre_linea);
            bool ban2 = true;
            while(ban2){
                cout << "Ingrese el nombre de la estacion: ";
                getline(cin, nombre_estacion);
                red_metro.agregarEstacion(nombre_estacion, nombre_linea);
                cout << "Estacion agregada con exito." << endl;
                cout << "Desea agregar mas estaciones a esta linea? (s/n): ";
                cin >> opcion;
                cin.ignore();
                if (opcion != 's') {
                    ban2 = false;
                }
            }
        } else if (opcion == 'n') {
            ban = false;
        }
    }
    cout << "Nombres de las lineas almacenadas:" << endl;
    for (int i = 0; i < red_metro.getNumeroDeLineas(); i++) {
        cout << "Linea " << i + 1 << ": " << red_metro.getNombreLinea(i) << endl;
        cout << "Estaciones de la linea " << red_metro.getNombreLinea(i) << ":" << endl;
        for (int j = 0; j < red_metro.getNumeroDeEstaciones(i); j++) {
            cout << "  - " << red_metro.getNombreEstacion(i, j) << endl;
        }
    }

    return 0;
}
