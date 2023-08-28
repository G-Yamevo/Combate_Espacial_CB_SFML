#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

class Fecha{
     private:
        int dia;
        int mes;
        int anio;
    public:
        Fecha();
        int getDia(){return dia;}
        int getMes(){return mes;}
        int getAnio(){return anio;}
        void setDia(int d){dia=d;}
        void setMes(int m){mes=m;};
        void setAnio(int a){anio=a;}
        string devolverFecha();
};

Fecha::Fecha(){
    time_t tiempo;
    struct tm *tmPtr;
    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);
    anio=tmPtr->tm_year+1900;
    mes=tmPtr->tm_mon+1;
    dia=tmPtr->tm_mday;
}

string Fecha::devolverFecha(){

    return to_string(dia)+"/"+to_string(mes)+"/"+to_string(anio);
}

#endif // FECHA_H_INCLUDED
