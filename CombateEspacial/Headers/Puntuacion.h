#ifndef PUNTUACION_H_INCLUDED
#define PUNTUACION_H_INCLUDED

#define NUMERO_ITEMS_PUNTUACION 5

class Puntuacion{
    private:
        int posicion;
        char nombreJugador[30];
        int puntuacion;
        sf::Time tiempoPartida;
        Fecha fechaPartida;

        sf::Font letra;
        sf::Text vElementosP[NUMERO_ITEMS_PUNTUACION]; /// 0:Posicion, 1:NombreJugador, 2:Puntuacion, 3:TiempoPartida, 4:FechaPartida
    public:
        Puntuacion(int pos, int punt, const char *n);
        ~Puntuacion(){};

        /// Gets y Sets
        int getPosicion(){return posicion;}
        const char *getNombreJugador(){return nombreJugador;}
        int getPuntuacion(){return puntuacion;}
        sf::Time getTiempoTranscurrido(){return tiempoPartida;}
        Fecha getFechaPartida(){return fechaPartida;}

        void setPosicion(int pos){posicion=pos;}
        void setNombreJugador(const char *nj){strcpy(nombreJugador,nj);}
        void setPuntuacion(int p){puntuacion=p;}
        void setTiempoTranscurrido(sf::Time c){tiempoPartida=c;}
        void setFechaPartida(Fecha f){fechaPartida=f;}

        /// Funciones
        void draw(sf::RenderWindow &window);
        void controlTextos(float x, float y);
        float getUbicacionUltimoElemento(){return vElementosP[4].getPosition().y+vElementosP[4].getGlobalBounds().height;}
        string tiempoMinutosSegundos(float segundos);

        bool leerDeDisco(int pos);
        bool grabarDeDisco();

};

Puntuacion::Puntuacion(int pos=0,int punt=-1, const char *n={"No Hay Nombre"}){
    sf::Time t;
    Fecha f;

    f.setAnio(0);
    f.setDia(0);
    f.setMes(0);

    setPosicion(pos);
    setPuntuacion(punt);
    setNombreJugador(n);
    setPuntuacion(punt);
    setTiempoTranscurrido(t.Zero);
    setFechaPartida(f);

    if(!letra.loadFromFile("Vermin.ttf")){
        cout<< "Error al cargar la letra"<<endl;
    }

    for(int i=0;i<NUMERO_ITEMS_PUNTUACION;i++){
        vElementosP[i].setFont(letra);
        vElementosP[i].setFillColor(sf::Color::White);
        vElementosP[i].setCharacterSize(20);
    }


}

void Puntuacion::draw(sf::RenderWindow &window){
    for(int i=0;i<NUMERO_ITEMS_PUNTUACION;i++){
        window.draw(vElementosP[i]);
    }
}

void Puntuacion::controlTextos(float x, float y){
    if(getPuntuacion()==-1){
        /// Posicion del Jugador
        vElementosP[0].setString("N: "+to_string(getPosicion()));
        ///Nombre del Jugador
        vElementosP[1].setString("Nombre: ---------------");
        /// Puntuacion del jugador
        vElementosP[2].setString("Puntuacion: ---------------");
        /// Tiempo de juego
        vElementosP[3].setString("Tiempo de juego: ---------------");
        /// Fecha de la Partida
        vElementosP[4].setString("Fecha: ---------------");

    }else{
        /// Posicion del Jugador
        vElementosP[0].setString("N: "+to_string(getPosicion()));
        ///Nombre del Jugador
        string s=getNombreJugador();
        vElementosP[1].setString("Nombre: "+s);
        /// Puntuacion del jugador
        vElementosP[2].setString("Puntuacion: "+to_string(getPuntuacion()));
        /// Tiempo de juego
        vElementosP[3].setString("Tiempo de juego: "+tiempoMinutosSegundos(getTiempoTranscurrido().asSeconds()));
        /// Fecha de la Partida
        vElementosP[4].setString("Fecha: "+getFechaPartida().devolverFecha());
    }

    for(int i=0;i<NUMERO_ITEMS_PUNTUACION;i++){
        if(i==0){
            vElementosP[i].setPosition(x/2 - vElementosP[3].getGlobalBounds().width/2 , (y+5));
        }else{
            vElementosP[i].setPosition(vElementosP[i-1].getPosition().x , (vElementosP[i-1].getGlobalBounds().height + vElementosP[i-1].getPosition().y)+1);
        }
    }

}
string Puntuacion::tiempoMinutosSegundos(float segundos){
    int segundero, minutero;

    segundero = (int)segundos%60;
	minutero = (segundos - segundero)/60;

    return to_string(minutero)+":"+to_string(segundero);

}

bool Puntuacion::leerDeDisco(int pos){
    FILE *p;
        bool leer;
        p=fopen("Puntuaciones.dat", "rb");
        if(p==NULL){
            cout<< "NO SE PUDO ABRIR EL ARCHIVO"<<endl;
            return false;
        }
        fseek(p, sizeof *this *pos,0);

        leer=fread(this,sizeof *this,1,p);
        fclose(p);
        return leer;
}

bool Puntuacion::grabarDeDisco(){
    FILE *p;
        bool grabar;
        p=fopen("Puntuaciones.dat", "ab");
        if(p==NULL){
            cout<< "ERROR";
            return false;
        }

        grabar=fwrite(this,sizeof *this,1, p);
        fclose(p);
        return grabar;
}

#endif // PUNTUACION_H_INCLUDED
