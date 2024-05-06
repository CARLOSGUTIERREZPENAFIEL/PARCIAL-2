#include <iostream>

using namespace std;
// recordar cambiar el uso de memoria de +1 en cada ciclo, a *2 al llenarse
class estaciones {
private:
    string nombre;
    string nombre_linea;
    bool es_transferencia;
public:
    estaciones(string _nombre, string _nombre_linea, bool _es_transferencia = false)
        : nombre(_nombre), nombre_linea(_nombre_linea), es_transferencia(_es_transferencia) {}
    string getNombre() { return nombre; }
    string getNombreLinea() { return nombre_linea; }
    void setNombre(string _nombre) { nombre = _nombre; }
    void setEsTransferencia(bool _es_transferencia) { es_transferencia = _es_transferencia; }
    bool getEsTransferencia() { return es_transferencia; }
};

class lineas {
private:
    string* arreglo_lineas;
    estaciones*** arreglo_estaciones;
    string** nombres_estaciones_unicas;
    string* nombres_estaciones_transferencia;
    int* contador_estaciones;
    int contador;
    int capacidad;
    int capacidad_transfe;

public:
    lineas();
    ~lineas();
    void agregarLinea(string nombre);
    void agregarLinea();
    void eliminarLinea(string nombre);
    void agregarEstacion(string nombre_estacion, string nombre_linea);
    void eliminarEstacion(string nombre_estacion, string nombre_linea);
    void consultarEstacion(string nombre_linea, string nombre_estacion);
    void imprimirEstacionesDisponibles();
    string getNombreLinea(int indice);
    string getNombreEstacion(int indice_linea, int indice_estacion);
    int getNumeroDeLineas();
    int getNumeroDeEstaciones(int indice_linea);
    int getNumeroTotalDeEstaciones();
    int getNumeroTotalDeLineas();
    int getNumeroDeEstaciones(string nombre_linea);


};

lineas::lineas() {
    capacidad = 1;
    contador = 0;
    capacidad_transfe = 0;
    arreglo_lineas = new string[capacidad];
    arreglo_estaciones = new estaciones**[capacidad];
    nombres_estaciones_unicas = new string*[capacidad];
    nombres_estaciones_transferencia = new string[capacidad_transfe];
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
    delete[] nombres_estaciones_transferencia;
}

int lineas::getNumeroTotalDeEstaciones() {
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

int lineas::getNumeroTotalDeLineas() {
    return contador;
}

int lineas::getNumeroDeEstaciones(string nombre_linea) {
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

void lineas::consultarEstacion(string nombre_linea, string nombre_estacion) {
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
                    cout << endl << "  *La estacion '" << nombre_estacion << "' si pertenece a la linea '" << nombre_linea << "'.*" << endl;
                    return;
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
                    return;
                }
                cout << endl << "  *La estacion '" << nombre_estacion << "' no existe en la linea '" << nombre_linea << "'. Pero existe en la linea '" << arreglo_lineas[i] << "'.*" << endl;
                return;
            }
        }
    }
    cout << endl << "  *La estacion '" << nombre_estacion << "' no existe en ninguna linea.*" << endl;
    return;
}



void lineas::agregarLinea() {
    string nombre;
    cout << "Ingrese el nombre de la primera linea de metro: ";
    getline(cin, nombre);
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
    cout << endl << "Ingrese el nombre de la estacion inicial para la linea '" << nombre << "': ";
    getline(cin, nombre_estacion_inicial);
    cout << "Ingrese el nombre de la estacion final para la linea '" << nombre << "': ";
    getline(cin, nombre_estacion_final);
    while(nombre_estacion_final==nombre_estacion_inicial){
        cout << endl << "No puede ingresar las estaciones con el mismo nombre." << endl << "Por favor ingrese otra estacion final para la linea '" << nombre << "': ";
        getline(cin, nombre_estacion_final);
    }
    arreglo_estaciones[contador] = new estaciones*[2];
    nombres_estaciones_unicas[contador] = new string[2];
    arreglo_estaciones[contador][0] = new estaciones(nombre_estacion_inicial, nombre, false);
    arreglo_estaciones[contador][1] = new estaciones(nombre_estacion_final, nombre, false);
    nombres_estaciones_unicas[contador][0] = nombre_estacion_inicial;
    nombres_estaciones_unicas[contador][1] = nombre_estacion_final;
    contador_estaciones[contador] = 2;
    contador++;
    cout << "  *Primera linea agregada con exito.*" << endl;
}

void lineas::agregarLinea(string nombre) {
    bool linea_repetida = false, ban = false, ban2 = true;
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
    arreglo_estaciones[contador] = new estaciones*[2];
    nombres_estaciones_unicas[contador] = new string[2];
    arreglo_estaciones[contador][0] = new estaciones(nombre_estacion_transferencia, nombre, true);
    arreglo_estaciones[contador][1] = new estaciones(nombre_estacion_final, nombre, false);
    nombres_estaciones_unicas[contador][0] = nombre_estacion_transferencia;
    nombres_estaciones_unicas[contador][1] = nombre_estacion_final;
    contador_estaciones[contador] = 2;
    contador++;
    cout << "  *Linea agregada con exito.*" << endl;
}


void lineas::eliminarLinea(string nombre_linea) {
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



void lineas::agregarEstacion(string nombre_estacion, string nombre_linea) {
    bool linea_encontrada = false;
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
            if (posicion == contador_estaciones[i]+1){
                posicion=0;
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
            if (posicion == 0) {
                cout << "  *Estacion agregada con exito en el extremo inicial.*" << endl;
                break;
            }
            else if (posicion == contador_estaciones[i]-1) {
                cout << "  *Estacion agregada con exito en el extremo final.*" << endl;
                break;
            }
            else {
                cout << "  *Estacion agregada con exito entre '" << nombres_estaciones_unicas[i][posicion - 1] << "' y '" << nombres_estaciones_unicas[i][posicion+1] << "'.*" << endl;
                break;
            }
        }
    }
    if (!linea_encontrada) {
        cout << "  *La linea especificada no existe. Por favor, ingrese una linea valida.*" << endl;
    }
}



void lineas::eliminarEstacion(string nombre_estacion, string nombre_linea) {
    bool banderilla = false, ban=false;
    string nom_transf;
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
    cout << "  *La estacion '" << nombre_estacion << "' ha sido eliminada exitosamente de la linea '" << nombre_linea << "'.*" << endl;



}



void lineas::imprimirEstacionesDisponibles() {
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
    cout << "**Bienvenido a la creacion de una RED METRO.**" << endl << endl;
    red_metro.agregarLinea();
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
             << "n. Salir." << endl << endl
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
            red_metro.consultarEstacion(nombre_linea, nombre_estacion);

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

        } else if (opcion == 'n') {
            ban = false;
        }
    }

    return 0;
}
