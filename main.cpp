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
    string** nombres_estaciones_unicas;
    int* contador_estaciones;
    int contador;
    int capacidad;

public:
    lineas();
    ~lineas();
    void agregarLinea(string nombre);
    void agregarEstacion(string nombre_estacion, string nombre_linea);
    void imprimirEstacionesDisponibles();
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
    nombres_estaciones_unicas = new string*[capacidad];
    contador_estaciones = new int[capacidad];
}

lineas::~lineas() {
    delete[] arreglo_lineas;
    delete[] contador_estaciones;
    delete[] nombres_estaciones_unicas;
    for (int i = 0; i < contador; i++) {
        delete[] arreglo_estaciones[i];
    }
    delete[] arreglo_estaciones;
}

void lineas::agregarLinea(string nombre) {
    bool linea_repetida = false;
    for (int i = 0; i < contador; i++) {
        if (arreglo_lineas[i] == nombre) {
            linea_repetida = true;
            break;
        }
    }
    if (linea_repetida) {
        cout << "La linea ya existe. Por favor, ingrese un nombre de linea diferente." << endl;
        return;
    }

    capacidad++;
    string* nuevo_arreglo_lineas = new string[capacidad];
    estaciones*** nuevo_arreglo_estaciones = new estaciones**[capacidad];
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
    cout << "Ingrese el nombre de la estacion inicial para la linea " << nombre << ": ";
    getline(cin, nombre_estacion_inicial);
    cout << "Ingrese el nombre de la estacion final para la linea " << nombre << ": ";
    getline(cin, nombre_estacion_final);

    arreglo_estaciones[contador] = new estaciones*[2];
    nombres_estaciones_unicas[contador] = new string[2];
    arreglo_estaciones[contador][0] = new estaciones(nombre_estacion_inicial, nombre);
    arreglo_estaciones[contador][1] = new estaciones(nombre_estacion_final, nombre);
    nombres_estaciones_unicas[contador][0] = nombre_estacion_inicial;
    nombres_estaciones_unicas[contador][1] = nombre_estacion_final;
    contador_estaciones[contador] = 2;
    contador++;
    cout << "Linea agregada con exito." << endl;
}


void lineas::agregarEstacion(string nombre_estacion, string nombre_linea) {
    bool linea_encontrada = false;
    for (int i = 0; i < contador; i++) {
        if (arreglo_lineas[i] == nombre_linea) {
            linea_encontrada = true;
            cout << "Estaciones disponibles en la linea '" << nombre_linea << "':" << endl;
            for (int j = 0; j < contador_estaciones[i] - 1; j++) {
                cout << j + 1 << ". " << nombres_estaciones_unicas[i][j] << " - " << nombres_estaciones_unicas[i][j + 1] << endl;
            }

            int posicion;
            do {
                cout << "Seleccione la posicion donde desea agregar la estacion '" << nombre_estacion << "' (Ingrese un numero entre 1 y " << contador_estaciones[i]-1 << "): ";
                cin >> posicion;
                cin.ignore();
            } while (posicion < 1 || posicion > contador_estaciones[i]-1);

            if (nombre_estacion == nombres_estaciones_unicas[i][posicion - 1] || nombre_estacion == nombres_estaciones_unicas[i][posicion]) {
                cout << "La estacion ya existe entre las estaciones consecutivas. Por favor, ingrese una estacion nueva." << endl;
                return;
            }

            int num_estaciones = contador_estaciones[i];
            estaciones** nuevo_arreglo_estaciones = new estaciones*[num_estaciones + 1];
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

            nuevo_arreglo_estaciones[posicion] = new estaciones(nombre_estacion, nombre_linea);
            nuevo_nombres_estaciones_unicas[posicion] = nombre_estacion;

            delete[] arreglo_estaciones[i];
            delete[] nombres_estaciones_unicas[i];
            arreglo_estaciones[i] = nuevo_arreglo_estaciones;
            nombres_estaciones_unicas[i] = nuevo_nombres_estaciones_unicas;
            contador_estaciones[i]++;
            cout << "Estacion agregada con exito entre '" << nombres_estaciones_unicas[i][posicion - 1] << "' y '" << nombres_estaciones_unicas[i][posicion+1] << "'." << endl;
            break;
        }
    }
    if (!linea_encontrada) {
        cout << "La linea especificada no existe. Por favor, ingrese una linea valida." << endl;
    }
}



void lineas::imprimirEstacionesDisponibles() {
    cout << endl << "Estaciones disponibles:" << endl;
    for (int i = 0; i < contador; i++) {
        cout << "Estaciones de la linea '" << arreglo_lineas[i] << "':" << endl;
        for (int j = 0; j < contador_estaciones[i]; j++) {
            cout << "  - " << nombres_estaciones_unicas[i][j] << endl;
        }
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

        } else if (opcion == '2') {
            red_metro.imprimirEstacionesDisponibles();
            cout << "Ingrese el nombre de la linea a la que pertenece la estacion: ";
            getline(cin, nombre_linea);
            cout << "Ingrese el nombre de la estacion: ";
            getline(cin, nombre_estacion);
            red_metro.agregarEstacion(nombre_estacion, nombre_linea);

        } else if (opcion == 'n') {
            ban = false;
        }
    }
    cout << "Nombres de las lineas almacenadas:" << endl;
    for (int i = 0; i < red_metro.getNumeroDeLineas(); i++) {
        cout << "Estaciones de la linea '" << red_metro.getNombreLinea(i) << "':" << endl;
        for (int j = 0; j < red_metro.getNumeroDeEstaciones(i); j++) {
            cout << "  - " << red_metro.getNombreEstacion(i, j) << endl;
        }
    }

    return 0;
}
