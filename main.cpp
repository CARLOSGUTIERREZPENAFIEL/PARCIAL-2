#include <iostream>

using namespace std;
class Estacion{
private:
    string NombreEstacion;
    string NombreLinea;
    string T_EstacionAnterior;
    string T_EstacionSiguiente;
    string NombreEstacionAnterior;
    string NombreEstacionSiguiente;
    string P_Entre_Estaciones;
public:
    Estacion(string,string,string,string,string,string,string);
    void setEstacion(string _NombreEstacion,string _NombreLinea,string _T_EstacionAnterior,string _T_EstacionSiguiente,string _NombreEstacionAnterior, string _NombreEstacionSiguiente, string _P_Entre_Estaciones);
    string getEstacion(string Dato);
    void setEstacion1(string _NombreEstacionSiguiente,string _T_EstacionSiguiente);
    void setEstacion2(string _NombreEstacionAnterior, string _T_EstacionAnterior);
    ~Estacion();

};
Estacion :: Estacion(string _NombreEstacion,string _NombreLinea,string _T_EstacionAnterior,string _T_EstacionSiguiente,string _NombreEstacionAnterior, string _NombreEstacionSiguiente, string _P_Entre_Estaciones){
    NombreEstacion = _NombreEstacion;
    NombreLinea = _NombreLinea;
    T_EstacionAnterior = _T_EstacionAnterior;
    T_EstacionSiguiente = _T_EstacionSiguiente;
    NombreEstacionAnterior = _NombreEstacionAnterior;
    NombreEstacionSiguiente = _NombreEstacionSiguiente;
    P_Entre_Estaciones = _P_Entre_Estaciones;
}
void Estacion :: setEstacion(string _NombreEstacion,string _NombreLinea, string _T_EstacionAnterior,string _T_EstacionSiguiente,string _NombreEstacionAnterior, string _NombreEstacionSiguiente, string _P_Entre_Estaciones){
    NombreEstacion = _NombreEstacion;
    NombreLinea = _NombreLinea;
    T_EstacionAnterior = _T_EstacionAnterior;
    T_EstacionSiguiente = _T_EstacionSiguiente;
    NombreEstacionAnterior = _NombreEstacionAnterior;
    NombreEstacionSiguiente = _NombreEstacionSiguiente;
    P_Entre_Estaciones = _P_Entre_Estaciones;
}
void Estacion:: setEstacion1(string _NombreEstacionSiguiente,string _T_EstacionSiguiente){
    NombreEstacionSiguiente = _NombreEstacionSiguiente;
    T_EstacionSiguiente = _T_EstacionSiguiente;

}
void Estacion :: setEstacion2(string _NombreEstacionAnterior, string _T_EstacionAnterior){
    NombreEstacionAnterior = _NombreEstacionAnterior;
    T_EstacionAnterior = _T_EstacionAnterior;
}
string Estacion:: getEstacion(string Dato){
    if (Dato == "NombreEstacion"){
        return NombreEstacion;
    }
    else if (Dato == "NombreLinea"){
        return NombreLinea;
    }
    else if ( Dato == "T_EstacionAnterior"){
        return T_EstacionAnterior;
    }
    else if(Dato == "T_EstacionSiguiente"){
        return T_EstacionSiguiente;
    }
    else if(Dato == "NombreEstacionAnterior"){
        return NombreEstacionAnterior;
    }
    else if(Dato == "NombreEstacionSiguiente"){
        return NombreEstacionSiguiente;
    }
    else{
        return P_Entre_Estaciones;
    }
}

int main(){
    return 0;
}
