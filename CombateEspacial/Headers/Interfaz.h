#ifndef Interfaz_H_INCLUDED
#define Interfaz_H_INCLUDED

#define NUMERO_ITEMS_Interfaz 3

class Interfaz{
    private:
        int puntuacion;
        int vida;
        sf::Time temporizador;

        sf::Font letra;
        sf::Text elementosInterfaz[NUMERO_ITEMS_Interfaz]; ///0:Puntuacioines, 1:Vida del Jugador, 2:Temporizador de la partida.

    public:
        Interfaz(float x, float y);
        ~Interfaz(){};

        /// Gets y Sets
        int getPuntuacion(){return puntuacion;}
        int getVida(){return vida;}
        sf::Time getTemporizador(){return temporizador;}

        void setPuntuacion(int p){puntuacion=p;}
        void setVida(int v){vida=v;}
        void setTemporizador(sf::Time t){temporizador= t;}

        /// Funciones
        void posicionPuntuacionActual(float x, float y);
        void posicionVidasJugador(float x, float y);
        void posicionTemporizadorPartida(float x, float y);
        void draw(sf::RenderWindow &window);
        void update();
        string tiempoMinutosSegundos(float segundos);



};

Interfaz::Interfaz(float x, float y){
    if(!letra.loadFromFile("Vermin.ttf")){
        cout<< "Error al cargar la letra"<<endl;
    }

    posicionPuntuacionActual(x,y);
    posicionTemporizadorPartida(x,y);
    posicionVidasJugador(x,y);
}

void Interfaz::draw(sf::RenderWindow &window){
    for(int i=0; i<NUMERO_ITEMS_Interfaz;i++){
        window.draw(elementosInterfaz[i]);

    }
}

void Interfaz::posicionPuntuacionActual(float x, float y){

    ///Establece los valores de el texto de Puntuacion
    elementosInterfaz[0].setFont(letra);
    elementosInterfaz[0].setFillColor(sf::Color::White);
    elementosInterfaz[0].setString("Puntos: "+to_string(getPuntuacion()));
    elementosInterfaz[0].setCharacterSize(30);
    elementosInterfaz[0].setPosition(10, y-30-elementosInterfaz[0].getGlobalBounds().height);
}
void Interfaz::posicionVidasJugador(float x, float y){

    ///Establece los valores de el texto de Vidas
    elementosInterfaz[1].setFont(letra);
    elementosInterfaz[1].setFillColor(sf::Color::White);
    elementosInterfaz[1].setString("Vidas: "+to_string(getVida()));
    elementosInterfaz[1].setCharacterSize(30);
    elementosInterfaz[1].setPosition(10, 10);
}
void Interfaz::posicionTemporizadorPartida(float x, float y){

    ///Establece los valores de el texto del Temporizador
    elementosInterfaz[2].setFont(letra);
    elementosInterfaz[2].setFillColor(sf::Color::White);
    elementosInterfaz[2].setString("Tiempo: "+tiempoMinutosSegundos(getTemporizador().asSeconds()));
    elementosInterfaz[2].setCharacterSize(30);
    elementosInterfaz[2].setPosition(x-20-elementosInterfaz[2].getGlobalBounds().width, 10);
}

void Interfaz::update(){
    elementosInterfaz[0].setString("Puntos: "+to_string(getPuntuacion()));
    elementosInterfaz[1].setString("Vidas: "+to_string(getVida()));
    elementosInterfaz[2].setString("Tiempo: "+tiempoMinutosSegundos(getTemporizador().asSeconds()));
}

string Interfaz::tiempoMinutosSegundos(float segundos){
    int segundero, minutero;

    segundero = (int)segundos%60;
	minutero = (segundos - segundero)/60;

    return to_string(minutero)+":"+to_string(segundero);

}

#endif // Interfaz_H_INCLUDED
