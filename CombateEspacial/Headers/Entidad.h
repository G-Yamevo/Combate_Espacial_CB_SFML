#ifndef ENTIDAD_H_INCLUDED
#define ENTIDAD_H_INCLUDED



/// Declaracion de la Clase

class Entidad: public sf::Drawable{
    protected:
        sf::Texture *texturaEntidad;
        sf::Sprite *spriteEntidad;
        float velocidad;
        int vida;

    public:
        /// Constructores y Destructores
        Entidad();
        ~Entidad();

        /// Gests y Sets
        sf::Sprite getSprite(){return *spriteEntidad;};
        sf::Texture getTextura(){return *texturaEntidad;};
        float getVelocidad(){return velocidad;};
        int getVida(){return vida;}

        void setVelocidad(float vel){velocidad=vel;}
        void setVida(int vid){vida=vid;};
        void setPosicion(float x,float y){spriteEntidad->setPosition(x,y);}


        ///Funciones de la clase Entidad
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


/// Constructores y Destructores

Entidad::Entidad(){


}

Entidad::~Entidad()
{

}

///Gets y Sets

/// Declaracion de las Funciones


void Entidad::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(*spriteEntidad, states);
}

#endif // ENTIDAD_H_INCLUDED
