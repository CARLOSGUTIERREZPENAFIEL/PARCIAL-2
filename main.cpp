#include <iostream>

using namespace std;

class lineas {
private:
    string* arreglo_lineas;
    int contador;
    int capacidad;

public:
    lineas();
    ~lineas();
    void agregarLinea(string nombre);
    string getNombreLinea(int indice);
    int getNumeroDeLineas();
};

lineas::lineas() {
    capacidad = 1;
    contador = 0;
    arreglo_lineas = new string[capacidad];
}

lineas::~lineas() {
    delete[] arreglo_lineas;
}

void lineas::agregarLinea(string nombre) {
    capacidad++;
    string* nuevo_arreglo = new string[capacidad];
    for (int i = 0; i < contador; i++) {
        nuevo_arreglo[i] = arreglo_lineas[i];
    }
    delete[] arreglo_lineas;
    arreglo_lineas = nuevo_arreglo;
    arreglo_lineas[contador] = nombre;
    contador++;
}

string lineas::getNombreLinea(int indice) {
    if (indice >= 0 && indice < contador) {
        return arreglo_lineas[indice];
    }
    return "";
}

int lineas::getNumeroDeLineas() {
    return contador;
}

int main() {
    char opcion;
    string nombre_linea;
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
             << "n. Salir." << endl << endl
             << "Opcion: ";
        cin >> opcion;

        if (opcion == '1') {
            cout << "Ingrese el nombre de la linea: ";
            cin.ignore();
            getline(cin, nombre_linea);
            red_metro.agregarLinea(nombre_linea);
            cout << "Linea agregada con exito." << endl;
        } else if (opcion == 'n') {
            ban = false;
        }
    }

    cout << "Nombres de las lineas almacenadas:" << endl;
    for (int i = 0; i < red_metro.getNumeroDeLineas(); i++) {
        cout << "Linea " << i + 1 << ": " << red_metro.getNombreLinea(i) << endl;
    }

    return 0;
}

