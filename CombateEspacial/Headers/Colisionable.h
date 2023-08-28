#ifndef COLISIONABLE_H_INCLUDED
#define COLISIONABLE_H_INCLUDED

class Colisionable{

    public:
        virtual sf::FloatRect getBounds() const = 0;
        bool isColision(Colisionable& obj) const;
};

bool Colisionable::isColision(Colisionable& obj) const{
    return getBounds().intersects(obj.getBounds());
}

#endif // COLISIONABLE_H_INCLUDED
