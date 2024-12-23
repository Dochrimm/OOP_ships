#include <iostream>
#include <vector>
#include "Map.h"
#include "Exceptions.h"
#include "CoordinateManagement.h"
#include "Abilities.h"
#include "Factories.h"
#include "AbilityManager.h"
#include "Game.h"

int main() {

    Game game;
    try{
        game.gameStart();
    }catch(const IException& ex){
        std::cout << ex.what() << std::endl;
    }
    
    return 0;
}