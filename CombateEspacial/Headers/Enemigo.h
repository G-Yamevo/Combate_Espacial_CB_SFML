#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED


class Enemigo: public Entidad{
    private:
        int tiempoAparicion;

    public:
        ///Constructores y Destructores
        Enemigo(float tamVentanaX , float tamVentanaY);
        ~Enemigo();

        ///Gets y Sets

        ///Funciones
        void mover();
};

Enemigo::Enemigo(float tamVentanaX , float tamVentanaY){
    vida=1;

    texturaEntidad = new sf::Texture;

    texturaEntidad->loadFromFile("Imagenes/Enemigo.png");

    spriteEntidad = new sf::Sprite(*texturaEntidad);

    spriteEntidad->setScale(2.5,2.5);

    tiempoAparicion=0;

    velocidad = 1;

    spriteEntidad->setPosition(tamVentanaX-spriteEntidad->getGlobalBounds().width, rand() % int(tamVentanaY - spriteEntidad->getGlobalBounds().height));


}

Enemigo::~Enemigo(){
    delete spriteEntidad;
    delete texturaEntidad;
}

void Enemigo::mover(){
    spriteEntidad->move(-velocidad,0);

}



#endif // ENEMIGO_H_INCLUDED
