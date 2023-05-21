#include <vector>
#include <iostream>
#include "../Server/Player.h"
using std::vector;

bool testMovement(){

	vector<Player> playerVector;
	
	class Player currentPlayer;
        currentPlayer.id = 1; 
        currentPlayer.positionX = 216;
        currentPlayer.positionY = 216;
        playerVector.push_back(currentPlayer);


	currentPlayer.checkMovement(1, 0, 0, &playerVector, currentPlayer.id);
	bool result = (playerVector[1].positionX == 217 && playerVector[1].positionY == 217 );

	if(result) {
		std::cout << "Test Passed!" << std::endl;
		
	}

	return result;

}
