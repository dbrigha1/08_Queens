//Tiles.h
//Dylan Brigham & Madison Cooley
//Dr. Bailey
//COSC 3020
//04/??/17

#ifndef TILES_H
#define TILES_H

class Tile {
private:
	int attackingQueensSize;
	bool isEmpty_;
	bool hasQueen_;
	bool hasDanger_;

public:
	Tile()
	{
		isEmpty_ = true;
		hasQueen_ = false;
		hasDanger_ = false;
		attackingQueensSize = 0;
	}
	void increaseAttackingQueensSize()
	{
		attackingQueensSize++;
	}
	void decreaseAttackingQueensSize()
	{
		attackingQueensSize--;
	}
	int queensAttackingTile()
	{
		return attackingQueensSize;
	}
	void tileIsEmpty(bool condition)
	{
		isEmpty_ = condition;
	}
	void tileHasQueen(bool condition)
	{
		hasQueen_ = condition;
	}
	bool tileHasQueen()
	{
		return hasQueen_;
	}
	void tileHasDanger(bool condition)
	{
		hasDanger_ = condition;
	}
	bool tileHasDanger()
	{
		return hasDanger_;
	}


};



#endif
