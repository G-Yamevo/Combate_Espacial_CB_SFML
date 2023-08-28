#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


class Game{
    private:
        sf::RenderWindow *ventana;
        int estadoJuego; /// 1: Menu; 2: Juego; 3: Puntuaciones;
        sf::Time *tiempo1;
        sf::Clock *reloj;
        int fps;
        sf::Texture *texturaFondo;
        sf::Sprite *spriteFondo;
        int puntuacion;
        Fecha fecha;


//        Puntuacion puntos;

        Menu *menu;
        Interfaz *datos;
        Nave *nav;
        vector<Enemigo*> enem;
        int tiempoAparicion;

    public:
        Game();
        ~Game();

        /// Gets y sets
        int getEstadoJuego(){return estadoJuego;}
        void setEstadoJuego(int e){estadoJuego=e;}

        /// Funciones
        void menuPrincipal();
        void jugando();
        void puntuaciones();

        int controlDeEventosMenu();
        int controlDeEventosJuego();
        int controlDeEventosPuntuaciones();

        void gameLoop();
        void updates();
            void updateEnemigo();
            void deteccionColisiones();
        void gameOver(sf::Time temporizador, int puntos);

        void dibujar();
            void dibujarDisparo();
            void dibujarEnemigo();



};

Game::Game(){
    ventana = new sf::RenderWindow(sf::VideoMode(1000, 500), "Combate Espacial");

    fps=60;

    ventana->setFramerateLimit(fps);

    tiempo1 = new sf::Time;

    reloj = new sf::Clock;

    setEstadoJuego(1);

    texturaFondo = new sf::Texture;

    texturaFondo->loadFromFile("Imagenes/Fondo.png");

    spriteFondo = new sf::Sprite(*texturaFondo);

    puntuacion=0;

    tiempoAparicion=0;

}

Game::~Game(){
    delete ventana;
    delete texturaFondo;
    delete spriteFondo;
    delete nav;
    delete menu;
    delete datos;
    delete tiempo1;
    delete reloj;
}

void Game::gameLoop(){
    while(ventana->isOpen()){
        if(getEstadoJuego()==1){
            menuPrincipal();
        }
        if(getEstadoJuego()==2){
            jugando();
        }
        if(getEstadoJuego()==3){
            puntuaciones();
        }
    }
}
int Game::controlDeEventosMenu(){
    sf::Event evento;
    while(ventana->pollEvent(evento)){

        switch(evento.type){

            case sf::Event::KeyPressed:

                if(evento.key.code==sf::Keyboard::Escape){
                    ventana->close();
                }
                if(evento.key.code==sf::Keyboard::W){
                    menu->moverArriba();
                }
                if(evento.key.code==sf::Keyboard::S){
                    menu->moverAbajo();
                }

                if(evento.key.code==sf::Keyboard::Return){
                    if(menu->getSeleccion()==0){
                        setEstadoJuego(2);
                        break;
                    }
                    if(menu->getSeleccion()==1){
                        setEstadoJuego(3);
                        break;
                    }
                    if(menu->getSeleccion()==2){
                        ventana->close();
                    }

                }
                break;
            case sf::Event::Closed:
                ventana->close();
                break;

            default:
                break;

        }
    }
    return getEstadoJuego();
}
void Game::menuPrincipal(){
    menu = new Menu(ventana->getSize().x , ventana->getSize().y);
    while(ventana->isOpen()){

        if(controlDeEventosMenu()!=1){break;}

        ventana->clear();

        menu->draw(*ventana);

        ventana->display();

    }
}

int Game::controlDeEventosJuego(){
    sf::Event evento;
    while(ventana->pollEvent(evento)){

        switch(evento.type){

            case sf::Event::KeyPressed:
                if(evento.key.code==sf::Keyboard::Escape){
                    setEstadoJuego(1);
                }
                break;
            case sf::Event::Closed:
                ventana->close();
                break;

            default:
                break;

        }
    }
    return getEstadoJuego();
}
void Game::jugando(){
    nav = new Nave;
    datos = new Interfaz(ventana->getSize().x,ventana->getSize().y);

    datos->setPuntuacion(puntuacion);
    datos->setVida(nav->getVida());

    reloj->restart();
    while(ventana->isOpen()){

        if(controlDeEventosJuego()!=2){break;}
        if(nav->getVida()>0){

            updates();
            datos->update();

            /// Elementos de la interfaz
            datos->setPuntuacion(puntuacion);
            datos->setVida(nav->getVida());
            datos->setTemporizador(reloj->getElapsedTime());

            dibujar();
        }
        else{
            gameOver(reloj->getElapsedTime(),puntuacion);
        }

    }

}
int Game::controlDeEventosPuntuaciones(){
    sf::Event evento;
    while(ventana->pollEvent(evento)){

    switch(evento.type){
        case sf::Event::KeyPressed:
            if(evento.key.code==sf::Keyboard::Escape){
                 setEstadoJuego(1);
            }
            break;
        case sf::Event::Closed:
            ventana->close();
            break;

        default:
            break;

    }
    }
    return getEstadoJuego();

}
void Game::puntuaciones(){
    int pos=0;
    sf::Text titulo;
    sf::Font letra;
    Puntuacion puntos[5], auxP;

    letra.loadFromFile("Vermin.ttf");

    /// Titulo Principal
    titulo.setFont(letra);
    titulo.setFillColor(sf::Color::Red);
    titulo.setString("Tabla de Puntuaciones");
    titulo.setCharacterSize(35);
    titulo.setPosition(ventana->getSize().x/2 - titulo.getGlobalBounds().width/2 , 0);



    while(ventana->isOpen()){
        if(controlDeEventosPuntuaciones()!=3){break;}

        for(int i=0; i<5;i++){
                pos=0;
                /// Da la ubicacion de la tabla de puntuaciones en pantalla
                if(i==0){
                    puntos[i].controlTextos(ventana->getSize().x , (titulo.getPosition().y + titulo.getGlobalBounds().height));
                }else{
                    puntos[i].controlTextos(ventana->getSize().x , puntos[i-1].getUbicacionUltimoElemento()+5);
                }
            /// Compara las puntuaciones del archivo Puntuaciones para los datos ordenados en la tabla
            while(auxP.leerDeDisco(pos++)){
                if(i==0){
                    if(auxP.getPuntuacion()>puntos[i].getPuntuacion()){
                        puntos[i].setPosicion(i+1);
                        puntos[i].setNombreJugador(auxP.getNombreJugador());
                        puntos[i].setPuntuacion(auxP.getPuntuacion());
                        puntos[i].setTiempoTranscurrido(auxP.getTiempoTranscurrido());
                        puntos[i].setFechaPartida(auxP.getFechaPartida());
                    }
                }else if(puntos[i-1].getPuntuacion()>auxP.getPuntuacion() && puntos[i].getPuntuacion()<auxP.getPuntuacion()){
                        puntos[i].setPosicion(i+1);
                        puntos[i].setNombreJugador(auxP.getNombreJugador());
                        puntos[i].setPuntuacion(auxP.getPuntuacion());
                        puntos[i].setTiempoTranscurrido(auxP.getTiempoTranscurrido());
                        puntos[i].setFechaPartida(auxP.getFechaPartida());
                }

            }


        }

        ventana->clear();
        for(int j=0; j<5;j++){
            puntos[j].draw(*ventana);
        }
        ventana->draw(titulo);
        ventana->display();
    }
}


void Game::updates(){
    nav->updateNave(ventana->getSize().x);
    updateEnemigo();
    deteccionColisiones();
}
void Game::dibujar(){
    ///Limpia la pantalla
    ventana->clear();

    ventana->draw(*spriteFondo);
    ///Dibuja la Nave y los disparos de la misma en pantalla
    ventana->draw(nav->getSprite());
    dibujarDisparo();
    /// Dibuja los enemigos en pantalla
    dibujarEnemigo();

    ///Dibuja los datos del jugador
    datos->draw(*ventana);

    ///Muestra lo dibujado en pantalla
    ventana->display();

}

void Game::updateEnemigo(){
    ///Controla el tiempo en el que aparecen los enemigos
    tiempoAparicion++;
    if(tiempoAparicion>=50){
        enem.push_back(new Enemigo(ventana->getSize().x,ventana->getSize().y));
        tiempoAparicion=0;
    }
    for(size_t i=0;i<enem.size();i++){
        enem[i]->mover();
        ///Detecta si el enemigo sale por el lado izquierdo de la pantalla y resta 1 vida
        if(enem[i]->getSprite().getPosition().x < 0-enem[i]->getSprite().getGlobalBounds().width){
            enem.erase(enem.begin()+i);
            nav->setVida(nav->getVida()-1);
        }
    }

}
void Game::dibujarEnemigo(){
    for(size_t i=0; i<enem.size();i++){
        ventana->draw(enem[i]->getSprite());
    }

}

void Game::dibujarDisparo(){
    for(size_t i=0; i<nav->getBalas().size();i++){
        ventana->draw(nav->getBalas()[i]->getSprite());
    }
}

void Game::deteccionColisiones(){

    for(size_t k=0;k<enem.size();k++){
        for(size_t i=0; i<nav->getBalas().size();i++){
            /// Deteccion de colision de las balas con el enemigo
            if(enem[k]->getSprite().getGlobalBounds().intersects(nav->getBalas()[i]->getSprite().getGlobalBounds())){
                enem.erase(enem.begin()+k);
                nav->getBalas().erase(nav->getBalas().begin()+i);
                puntuacion++;
                break;
            }
        }
        ///Detecta si el enemigo colisiona con la nave
        if(enem[k]->getSprite().getGlobalBounds().intersects(nav->getSprite().getGlobalBounds())){
            nav->setVida(nav->getVida()-1);
            enem.erase(enem.begin()+k);
            break;
        }
    }
}

void Game::gameOver(sf::Time temporizador, int puntos){
    sf::Text gameOver;
    sf::Text pedirNombre;
    sf::Text nombreIngresado;
    std::string inputJugador;
    Puntuacion auxP;
    char nombre[30];

    sf::Font letra;
    sf::Event event;

    letra.loadFromFile("Vermin.ttf");

    /// Titulo fin del juego
    gameOver.setFont(letra);
    gameOver.setFillColor(sf::Color::Red);
    gameOver.setString("Fin del Juego");
    gameOver.setCharacterSize(100);
    gameOver.setPosition(ventana->getSize().x/2 - gameOver.getGlobalBounds().width/2 , 20);

    /// Texto que pide el ingreso del nombre del jugador
    pedirNombre.setFont(letra);
    pedirNombre.setFillColor(sf::Color::White);
    pedirNombre.setString("Ingrese el Nombre del Jugador");
    pedirNombre.setCharacterSize(30);
    pedirNombre.setPosition(ventana->getSize().x/2 - pedirNombre.getGlobalBounds().width/2 , gameOver.getGlobalBounds().height + 100);

    nombreIngresado.setFont(letra);
    nombreIngresado.setFillColor(sf::Color::White);
    nombreIngresado.setCharacterSize(25);


    while(ventana->isOpen()){
        if(getEstadoJuego()!=2){break;}
        while (ventana->pollEvent(event)){
            switch(event.type){
                case sf::Event::KeyPressed:
                        if(event.key.code==sf::Keyboard::Return){
                            strcpy(nombre,inputJugador.c_str());
                            setEstadoJuego(1);
                            break;
                        }
                    break;
                case sf::Event::TextEntered:
                        if(event.text.unicode == '\b'){
                            /// Borra una letra cuando se detecta que se ingreso el input del backspace o delete
                            if(inputJugador.size()>0){
                                inputJugador.erase(inputJugador.size()-1,1);
                                nombreIngresado.setString(inputJugador);
                            }
                        }else{
                            /// Maneja el input del jugador cuando ingresa su nombre por teclado y lo muestra por pantalla
                            inputJugador += static_cast<char>(event.text.unicode);
                            nombreIngresado.setString(inputJugador);
                            nombreIngresado.setPosition(ventana->getSize().x/2-nombreIngresado.getGlobalBounds().width/2 , pedirNombre.getPosition().x + pedirNombre.getGlobalBounds().height + 20);
                        }

                            break;
                default:
                    break;
                }

        }

    ventana->clear();

    ventana->draw(gameOver);
    ventana->draw(pedirNombre);
    ventana->draw(nombreIngresado);

    ventana->display();
    }


    auxP.setNombreJugador(nombre);
    auxP.setPuntuacion(puntos);
    auxP.setTiempoTranscurrido(temporizador);
    auxP.setFechaPartida(fecha);

    auxP.grabarDeDisco();

}

#endif // GAME_H_INCLUDED
