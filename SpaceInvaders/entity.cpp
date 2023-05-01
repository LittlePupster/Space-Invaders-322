#include "entity.h"
#include <ncurses.h>
Entity::Entity(int initX, int initY){
	x = initX;
	y = initY;
}
int Entity::getX() {return x;}
int Entity::getY() {return y;}

PlayerShip::PlayerShip(int initX, int initY) : Entity(initX, initY){}	
	void PlayerShip::move(int leftRight) {
		x += leftRight;
	}
	void PlayerShip::draw() {
		mvprintw(y, x, "A");
	}
AlienShip::AlienShip(int initX, int initY) : Entity(initX, initY){}	
	void AlienShip::draw() {
		mvprintw(y, x, "V");
	}
	void AlienShip::move(int dir){
		x += dir;
	}
Bullet::Bullet(int initX, int initY) : Entity(initX, initY){}
	void Bullet::draw(){
		mvprintw(y, x, "|");
	}
	void Bullet::moveUp(){
		y--;
	}
	void Bullet::moveDown(){
		y++;
	}
Block::Block(int initX, int initY) : Entity(initX, initY){}
	void Block::draw(){
		mvprintw(y, x, "#");
	}
