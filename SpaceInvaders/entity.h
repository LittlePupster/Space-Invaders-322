#ifndef ENTITY_H
#define ENTITY_H

class Entity {
protected:
	int x;
	int y;
public:
	Entity(int initX, int initY);
	int getX();
	int getY();
};
class PlayerShip : public Entity {
public:
	PlayerShip(int initX, int initY);
	void move(int leftRight);
	void draw();
};
class AlienShip : public Entity{
public:
	AlienShip(int initX, int initY);
	void draw();
	void move(int dir);
};
class Bullet : public Entity{
public:
	Bullet(int initX, int initY);
	void draw();
	void moveUp();
	void moveDown();
};
class Block : public Entity{
public:
	Block(int initX, int initY);
	void draw();
};
#endif // ENTITY_H
