#ifndef NAVE_H_INCLUDED
#define NAVE_H_INCLUDED


class Nave: public Entidad{
    private:

        bool estaDisparando;
        int tempProyectiles;
        vector<Proyectil*> balas;
        int contadorProyectiles;

    public:

        ///Constructores y Destructores
        Nave();
        ~Nave();

        ///Gets y Sets
        bool getEstadisparando(){return estaDisparando;}
        int getContadorProyectiles(){return contadorProyectiles;}
        vector<Proyectil*>& getBalas(){return balas;}


        void setEstaDisparando(bool d){estaDisparando=d;}
        void setContadorProyectiles(int cp){contadorProyectiles=cp;}

        ///Funciones
        void updateNave(float tamVentanX);
        void moverNave();
        void disparar(float tamVentanaX);
};

Nave::Nave(){
    vida=3; ///Cambiar para que el jugador inicie el juego con tres vidas

    velocidad = 5;

    texturaEntidad = new sf::Texture;

    texturaEntidad->loadFromFile("Imagenes/Nave.png");

    spriteEntidad = new sf::Sprite(*texturaEntidad);

    spriteEntidad->setScale(2.5,2.5);

    spriteEntidad->setPosition(0, 250 - spriteEntidad->getGlobalBounds().height/2);

    contadorProyectiles=0;

    estaDisparando = false;

    tempProyectiles=10;

}

Nave::~Nave(){
    delete spriteEntidad;
    delete texturaEntidad;
}

void Nave::updateNave(float tamVentanaX){
    moverNave();
    disparar(tamVentanaX);
}

void Nave::moverNave(){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            spriteEntidad->move(0 , -velocidad);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            spriteEntidad->move(-velocidad , 0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            spriteEntidad->move(0 , velocidad);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            spriteEntidad->move(velocidad , 0);
        }

        if(spriteEntidad->getPosition().x<0){   ///Hace que la nave no pueda irse de la pantalla por el lado izquierda
            spriteEntidad->setPosition(0, spriteEntidad->getPosition().y);
        }
        if(spriteEntidad->getPosition().x>1000-spriteEntidad->getGlobalBounds().width){   ///Hace que la nave no pueda irse de la pantalla por el lado derecho
            spriteEntidad->setPosition(1000-spriteEntidad->getGlobalBounds().height, spriteEntidad->getPosition().y);
        }

        ///Hace que cuando la nave cruza el borde inferior de la pantalla aparezca arriba y viceversa

        if(spriteEntidad->getPosition().y<0){ ///Si la nave se va por el borde superior de la pantalla hace que aparezca por el borde inferior de la pantalla
            spriteEntidad->setPosition(spriteEntidad->getPosition().x , 500-spriteEntidad->getGlobalBounds().height);
        }
        if(spriteEntidad->getPosition().y>500-spriteEntidad->getGlobalBounds().height){ ///Si la nave se va por el borde inferior de la pantalla hace que aparezca por el borde superior de la pantalla
            spriteEntidad->setPosition(spriteEntidad->getPosition().x , 0);
        }
}
void Nave::disparar(float tamVentanaX){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && tempProyectiles>=10){
        tempProyectiles=0;
        balas.push_back(new Proyectil(spriteEntidad->getPosition().x , spriteEntidad->getPosition().y + spriteEntidad->getGlobalBounds().height/2));
    }
    for(size_t i=0; i < balas.size() ; i++){
        balas[i]->mover();
        if(balas[i]->getSprite().getPosition().x > tamVentanaX){
            balas.erase(balas.begin()+i);
        }

    }
    tempProyectiles++;
}

#endif // NAVE_H_INCLUDED
