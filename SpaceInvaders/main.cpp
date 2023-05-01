#include <ncurses.h>
#include "entity.h"
#include <stdlib.h>
#include <iostream>
#include <curses.h>
#include <vector>
#include <unistd.h>
#include <time.h>
#include <chrono>
#include <random>
#include "mainMenu.h"
using namespace std;
using namespace chrono;
int score = 0;
int level = 1;
int lives = 3;
int leftMost = 30;
int rightMost = 80;
int changeDir = 1;
//TODO:
//Prevent spacebar spam
//Make aliens bigger/add hitbox
void resetGlobals(){
	score = 0;
	level = 1;
	lives = 3;
	leftMost = 30;
	rightMost = 80;
	changeDir = 1;
}
vector<AlienShip> fillShips(vector<AlienShip>& ships){		
        int j = 42;				//starting at x= 40
	for(int i = 0; i < 10; i++){		//add a ship to the ship vector at position j,i
		ships.push_back(AlienShip(j,2));
		ships.push_back(AlienShip(j,3));
		ships.push_back(AlienShip(j,4));
		ships.push_back(AlienShip(j,5));
		ships.push_back(AlienShip(j,6));
		ships.push_back(AlienShip(j,7));
		j += 3;
	}
	return ships;

}
vector<Block> fillBlocks(vector<Block>& blocks){
        int j = 35, k = 55, z = 75;
        for(int i = 0; i < 5; i++){
                blocks.push_back(Block(j,15));
                blocks.push_back(Block(j,16));
                blocks.push_back(Block(j,17));
		blocks.push_back(Block(k,15));
                blocks.push_back(Block(k,16));
                blocks.push_back(Block(k,17));
		blocks.push_back(Block(z,15));
                blocks.push_back(Block(z,16));
                blocks.push_back(Block(z,17));
                j++;
		z++;
		k++;
        }
        return blocks;

}

void detectCollisions(vector<Bullet>& bullets,vector<AlienShip>& aliens) {
	for (auto bullet = bullets.begin(); bullet != bullets.end(); bullet++) {		//starting at bullet[0] to the last bullet
        	for (auto alien = aliens.begin(); alien != aliens.end(); alien++) {		//starting at ship[0] to the last ship
            		if (bullet->getX() == alien->getX() && bullet->getY() == alien->getY()) {	//if a bullet has the same x & y coordinates as the ship
                		bullets.erase(bullet);							//erase the bullet and ship from their list and add 100 to the score
                		aliens.erase(alien);
				score += 100;
                		return;
			}
        	}
    	}
}
void detectCollisionsBlocks(vector<Bullet>& bullets,vector<Block>& blocks) {	//same as above but for the blocks
	for (auto bullet = bullets.begin(); bullet != bullets.end(); bullet++) {            
		for (auto block = blocks.begin(); block != blocks.end(); block++) {             
			if (bullet->getX() == block->getX() && bullet->getY() == block->getY()) {   
				bullets.erase(bullet);                                                  
				blocks.erase(block);
                		return;
            		}
        	}
    	}
}
void detectCollisionsPlayer(vector<Bullet>& bullets, PlayerShip player){
	for(auto bullet = bullets.begin(); bullet != bullets.end(); bullet++){
		if(bullet->getX() == player.getX() && bullet->getY() == 20){
			bullets.erase(bullet);
			lives--;
			return;
		}
	}
}
int getDir(){
	if(leftMost == 0){             
		changeDir = 1;
                leftMost++;
	}
        if(rightMost == 110){           //if ships hit right side of screen, change dir
                changeDir = -1;
                rightMost--;
        }
        if(changeDir == 1){             //if were going right, increment variables right
        	leftMost++;
                rightMost++;
        }
        if(changeDir == -1){            //if were going left, increment varialbes left
                leftMost--;
                rightMost--;
        }


	return changeDir;
}
int main() {
	int endGame = 0;
	while(endGame == 0){
		resetGlobals();
	int display = displayMenu();
	if(display == -1){
		endGame = 1;
		break;
	}
	initscr();
	cbreak();
	noecho();
	curs_set(0);
    	WINDOW* mainwin = newwin(21, 111,0,0);
	mainwin = initscr();
	nodelay(mainwin, TRUE);		//non blocking mode
	refresh();
    	keypad(mainwin, TRUE);		//initialize ncurses and screen
	
	PlayerShip player(56, 20);
	vector<AlienShip> ships;
	vector<Bullet> bullets;
	vector<Block> blocks;
	vector<Bullet> alienBullet;
	fillShips(ships);
	fillBlocks(blocks);
									//initialize vectors and objects
	mt19937 rng(system_clock::now().time_since_epoch().count());	//code from stack overflow for a better version of rand();
	uniform_int_distribution<int> dist(0, 500);	
	
	int flag = 0,dir;						//for alien movement
	auto fps_30 = milliseconds(33);					//how often our game updates and refreshes(30 times per second)
  	auto lastUpdate = steady_clock::now(); 				//initialize last update
	
	while (lives > 0) {							//game loop while lives > 0		
        	auto currentTime = steady_clock::now();				//start the time
    		if(currentTime - lastUpdate >= fps_30) {			//if more than 33 milliseconds have passed
			flag++;							//ships will move every 5 frames
			if(flag == 11){
				flag = 0;
			}
			clear();
			mvprintw(25,0,"Instructions:\nQ:Quit\nP:Pause\nSpace:Shoot\nLeft/Right:Move");	
			mvprintw(0,0,"Score: %d\t\t\tLevel: %d\t\t\tLives: %d",score,level,lives);
			if(ships.empty()){				//if we destroy all ships, increase level, refill ships, clear blocks, and fill blocks.
				fillShips(ships);
				level++;
				blocks.clear();
				fillBlocks(blocks);
				leftMost = 30;
				rightMost = 80;

			}
			player.draw();	
			if(flag == 10){					//on the 5th entry of the if statement (33 milliseconds * 5) we call getdir
				dir = getDir();
			}
			for(unsigned int i = 0; i < ships.size(); i++){		//update and draw ships
				if(flag == 10){
					ships[i].move(dir);			//move the ship in direction
				}
				ships[i].draw();		
				if(dist(rng) == 0){
					alienBullet.insert(alienBullet.begin(), Bullet(ships[i].getX(),ships[i].getY() + 1));	
				}						//randomly add bullets to alienBullet vector
			}
			for(unsigned int i = 0; i < blocks.size(); i++){
				blocks[i].draw();
			}
			if(!bullets.empty()){					//if we have bullets in the bullet vector:
				for(unsigned int i = 0; i < bullets.size(); i++){
					bullets[i].draw();			//draw/update/check collisions/delete after off screen
					bullets[i].moveUp();
					detectCollisions(bullets,ships);
					detectCollisionsBlocks(bullets,blocks);
					if(bullets[i].getY() < 0){
						bullets.erase(bullets.begin() + i);
						i--;
					}
				}
			}
			if(!alienBullet.empty()){				//if we have alien bullets in alien bullet vector
				for(unsigned int i = 0; i < alienBullet.size(); i++){
					alienBullet[i].draw();			//draw/update/check collisions/delete after off screen
					alienBullet[i].moveDown();
					detectCollisionsBlocks(alienBullet,blocks);
					detectCollisionsPlayer(alienBullet, player);
					if(alienBullet[i].getY() > 30){
						alienBullet.erase(alienBullet.begin() + i);
						i--;
					}
				}

			}
			lastUpdate = currentTime;	//update lastUpdate variable to reset it back to current time(aka 0)
		}
						//get user input
		int ch = getch();
		switch(ch){
        	case 'q':
                	endwin();
                	return 0;
        	case KEY_LEFT:
			nodelay(mainwin, TRUE);
                	if(player.getX() - 1 > 0){
                        	player.move(-1);
                	}
                	break;
        	case KEY_RIGHT:
			nodelay(mainwin, TRUE);
                	if(player.getX() + 1 < 111){
                       	 	player.move(1);
                	}
                	break;
		case ' ':
			nodelay(mainwin, TRUE);
			bullets.insert(bullets.begin(), Bullet(player.getX(),player.getY() -1));
			break;
		case 'p':
			nodelay(mainwin, FALSE);
			mvprintw(10,60,"GAME PAUSED");
			mvprintw(11,52,"Press any key to continue.");
		default:
			break;
		}
				//getch will not wait for user input because of nodelay(). Jump back to top of loop
	}
	clear();
	endMenu(score);
	clear();
	endwin();
	}
	return 0;
}
