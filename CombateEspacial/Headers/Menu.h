#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#define NUMERO_ITEMS_MENU 3

class Menu{
    private:
        int indice;
        sf::Font letra;
        sf::Text tituloMenu;
        sf::Text elementosMenu[NUMERO_ITEMS_MENU];
        sf::Sprite spriteFondo;
        sf::Texture texturaFondo;

    public:
        Menu(float x , float y);
        ~Menu();


        void draw(sf::RenderWindow &window);
        void moverArriba();
        void moverAbajo();
        int getSeleccion(){return indice;}


};


Menu::Menu(float x, float y){
    if(!letra.loadFromFile("Vermin.ttf")){
        cout<< "Error al cargar la letra"<<endl;
    }
    /// Titulo Principal
    tituloMenu.setFont(letra);
    tituloMenu.setFillColor(sf::Color::Red);
    tituloMenu.setString("Combate Espacial");
    tituloMenu.setCharacterSize(100);
    tituloMenu.setPosition(x/2 - tituloMenu.getGlobalBounds().width/2 , 50);

    /// Iniciar Partida
    elementosMenu[0].setFont(letra);
    elementosMenu[0].setFillColor(sf::Color::White);
    elementosMenu[0].setString("Iniciar Partida");
    elementosMenu[0].setCharacterSize(30);
    elementosMenu[0].setPosition(x/2 - elementosMenu[0].getGlobalBounds().width/2 , 300);
    /// Mostrar la tabla de Puntuaciones
    elementosMenu[1].setFont(letra);
    elementosMenu[1].setFillColor(sf::Color::White);
    elementosMenu[1].setString("Puntuaciones");
    elementosMenu[1].setCharacterSize(30);
    elementosMenu[1].setPosition(x/2 - elementosMenu[1].getGlobalBounds().width/2 , 350);
    /// Slir del Juego
    elementosMenu[2].setFont(letra);
    elementosMenu[2].setFillColor(sf::Color::White);
    elementosMenu[2].setString("Salir del Juego");
    elementosMenu[2].setCharacterSize(30);
    elementosMenu[2].setPosition(x/2 - elementosMenu[2].getGlobalBounds().width/2 , 400);

    indice = 0;
    elementosMenu[indice].setFillColor(sf::Color::Yellow);
//    texturaFondo.loadFromFile("");
//    spriteFondo.setTexture(texturaFondo);
}

Menu::~Menu(){}

void Menu::draw(sf::RenderWindow &window){
    window.draw(tituloMenu);
    for(int i=0; i<NUMERO_ITEMS_MENU;i++){
        window.draw(elementosMenu[i]);

    }
}

void Menu::moverArriba(){
    if(indice-1>=0){
        elementosMenu[indice].setFillColor(sf::Color::White);
        indice--;

        elementosMenu[indice].setFillColor(sf::Color::Yellow);
    }

}

void Menu::moverAbajo(){
    if(indice+1<NUMERO_ITEMS_MENU){
        elementosMenu[indice].setFillColor(sf::Color::White);
        indice++;
        elementosMenu[indice].setFillColor(sf::Color::Yellow);
    }

}



#endif // MENU_H_INCLUDED
