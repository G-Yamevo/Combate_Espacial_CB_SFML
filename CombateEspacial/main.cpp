#include<iostream>
#include<cstdlib>
#include<cstring>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


using namespace std;

#include "Headers/Interfaz.h"
#include "Headers/Fecha.h"
#include "Headers/Puntuacion.h"
#include "Headers/Entidad.h"
#include "Headers/Enemigo.h"
#include "Headers/Proyectil.h"
#include "Headers/Nave.h"
#include "Headers/Menu.h"
#include "Headers/Game.h"


int main()
{
    Game juego;
    juego.gameLoop();

    return 0;
}
