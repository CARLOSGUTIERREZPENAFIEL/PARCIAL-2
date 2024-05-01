#include <iostream>

using namespace std;

class RedMetro{
    private:
        string NombreLineaA;
        string NombreEstacionA1;
        string NombreEstacionA2;
    public:
        RedMetro(string,string,string);
    
};

RedMetro :: RedMetro(string _NombreLineaA, string _NombreEstacionA1, string _NombreEstacionA2){
    NombreLineaA = _NombreLineaA;
    NombreEstacionA1 = _NombreEstacionA1;
    NombreEstacionA2 = _NombreEstacionA2;
}

class lineas{
    private:
        string NombreLinea;
    public:
    	void setNombreLinea(string nombre); //Método Set
        string getNombreLinea(void); 
        
    
};

void lineas::setNombreLinea(string nombre)
{
	NombreLinea = nombre;
}
string lineas::getNombreLinea(void)
{
	return NombreLinea;
}

class estaciones{
    private:
        string NombreEstaciones;
        
};

int main() {
    const int MAX_LINEAS = 5; // Tamaño máximo del arreglo
    int contador = 1;
    bool ban=1;
    string lineaA, estacion1,estacion2;
    char opcion;
    int cont_linea=0;
    int capacidad = 1; // Tamaño inicial del arreglo
    lineas* arreglo_lineas = new lineas[capacidad]; // Arreglo dinámico de objetos lineas
    cout << "*Bienvenido a la creacion de una RED METRO.*" << endl;
    cout << "-Ingrese su primer linea: ";
    cin >> lineaA;
    cout << "ingrese al menos dos estaciones." << endl << "Estacion 1: ";
    cin >> estacion1;
    cout << "Estacion 2: ";
    cin >> estacion2;
    RedMetro Primerlinea = RedMetro(lineaA,estacion1,estacion2);
    arreglo_lineas[0].setNombreLinea(lineaA);
    while(ban==1){   
        cout << endl <<"*Ingrese la opcion deseada.*" << endl << "1. Agregar estación a una linea." << endl << "2. Eliminar una estación de una linea." << endl << "3. Numero de lineas de la red." << endl << "4. Numero de estaciones de x linea." << endl << "5. Saber la linea de x estacion." << endl << "6. Agregar una linea a la red metro." << endl << "7. Eliminar una linea de la red metro." << endl << "8. Numero de estaciones de TODA la red metro." << endl << "n. Salir." << endl << endl <<"Opcion: ";
        cin >> opcion;
        if (opcion == '6'){
            // Aumentar el tamaño del arreglo en 1 en cada ciclo
            capacidad++;
            lineas* nuevo_arreglo = new lineas[capacidad]; // Nuevo arreglo con el tamaño aumentado
            // Copiar elementos del arreglo anterior al nuevo arreglo
            for (int i = 0; i < contador; i++) {
                nuevo_arreglo[i] = arreglo_lineas[i];
            }
            // Liberar memoria del arreglo anterior
            delete[] arreglo_lineas;
            // Asignar el nuevo arreglo al puntero arreglo_lineas
            arreglo_lineas = nuevo_arreglo;
            cout << "Ingrese el nombre de la línea " << contador + 1 << ": ";
            string nomline;
            cin >> nomline;
            arreglo_lineas[contador].setNombreLinea(nomline);
            contador++;
            cout << "ESTACION AGREGADA CON EXITO" << endl;

            
        }
        else if (opcion == 'n'){
            ban=0;
        }
    }

    // Mostrar los nombres de las líneas almacenadas en el arreglo
    cout << "Nombres de las líneas almacenadas:" << endl;
    for (int i = 0; i < contador; i++) {
        cout << "Línea " << i + 1 << ": " << arreglo_lineas[i].getNombreLinea() << endl;
    }
    // Liberar memoria del arreglo dinámico
    delete[] arreglo_lineas;
    return 0;
}
