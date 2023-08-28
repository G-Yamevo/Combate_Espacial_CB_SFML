#ifndef PROYECTIL_H_INCLUDED
#define PROYECTIL_H_INCLUDED



class Proyectil: public Entidad{
    private:
        float velocidadDisparo;
    public:
        Proyectil(float x , float y);
        ~Proyectil();

        /// Funciones  de la clase
        void mover();
};

Proyectil::Proyectil(float x , float y){
    velocidadDisparo = 20;

    texturaEntidad = new sf::Texture;

    texturaEntidad->loadFromFile("Imagenes/Proyectil.png");

    spriteEntidad = new sf::Sprite(*texturaEntidad);

    spriteEntidad->setPosition(x , y - spriteEntidad->getGlobalBounds().height/2);
}


Proyectil::~Proyectil(){
    delete texturaEntidad;
    delete spriteEntidad;

}

void Proyectil::mover(){

    spriteEntidad->move(velocidadDisparo,0);

}



#endif // PROYECTIL_H_INCLUDED
