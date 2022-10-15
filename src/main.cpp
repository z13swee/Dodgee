#include <iostream>

#include "Game.hpp"

/*
  INTRO:
    This game was inspired by a game name Dodge, and seemed like a good opportunity
    to practice programming, game dev and aim for a more polished result.


  TODO:
    Change difficulty ramp, should be easier at the begining and ramp up
    Make it playable with gamepad?

    Add sound effect on the buttons
    Add persinten highscore (including ability to input name)
    Add top 5? names on the gameover screen
    Add circular collision for more accurate representation
    Add texture 'cache', avoid creating same texture mutiple times


  GAMEPLAY IDES:
    Have color coded enimies, and player switch color with right and left mouse button.
    Color Red and Blue for example, only take damage from the same color ..

    Sometimes enemies collide and leaves powerups,
      * Slow down time
      * Invinsible
      * Player shoot out shockwave or projectile destroying/moving enemys
    Blackholes wich is pulling everything twords it

    Bosses?
*/

int main(int, char**){


  Game myGame = Game();

  if(myGame.Initialize()) {
    std::cerr << "Failed to Initialize!" << std::endl;
    return 1;
  }

  // If initializeing went well, start the Game!
  myGame.Run();

	return 0;
}
