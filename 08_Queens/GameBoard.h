//GameBoard.h
//Dylan Brigham & Madison Cooley
//Dr. Bailey
//COSC 3020
//04/??/17

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include<vector>
#include "Tiles.h"

class GameBoard {
private:
	std::vector<std::vector<Tile>> board_;
	int size_;
	const char VERTICAL_WALL = '|';
	const char HORIZONTAL_WALL = '__';
	const char QUEEN_ = 'Q';
	const char DANGER_ = 'X';
	const char INVALID_ = 'I';

public:
	GameBoard(int size)
	{
		//this initializes the board to have empty tiles
		board_.resize(size, std::vector<Tile>(size, Tile()));
		size_ = size;
	}

	void insertQueenAt(int row, int column)
	{
		board_.at(row).at(column).tileHasQueen(true);
		markTileDangerous(row, column, true);
	}

	void removeQueenAt(int row, int column)
	{
		//std::cout << "Removed!" << std::endl;
		board_.at(row).at(column).tileHasQueen(false);
		markTileDangerous(row, column, false);
		//std::cout << "success" << std::endl;
	}

	//This function returns the colum pos of a queen in a certain row
	int colPosOfQueen(int row)
	{
		for (int i = 0; i < size_; i++)
		{
			if (board_.at(row).at(i).tileHasQueen())
			{
				return i;
			}
		}
	}

	//This function returns the colum pos of a queen in a certain row
	int rowPosOfQueen(int col)
	{
		for (int i = 0; i < size_; i++)
		{
			if (board_.at(col).at(i).tileHasQueen())
			{
				return i;
			}
		}
	}

	void display()
	{
		for (int i = 0; i < size_; i++)
		{
			std::cout << VERTICAL_WALL;
			for (int j = 0; j < size_; j++)
			{
				if (board_.at(i).at(j).tileHasQueen() && board_.at(i).at(j).tileHasDanger())
					std::cout << INVALID_;
				else if (board_.at(i).at(j).tileHasQueen())
					std::cout << QUEEN_;
				else if (board_.at(i).at(j).tileHasDanger())
					std::cout << DANGER_;
				else
					std::cout << ' ';
				std::cout << VERTICAL_WALL;
			}
			std::cout << std::endl;
		}

	}
	//checks if any queen is in danger from another attacking queen
	int check()
	{
		for (int i = 0; i < size_; i++)
		{
			for (int j = 0; j < size_; j++)
			{
				if (board_.at(i).at(j).tileHasQueen() && board_.at(i).at(j).tileHasDanger())
					return 0;
			}
		}
		return 1;
	}

	//returns true if position is not in danger
	bool checkPos(int row, int col)
	{
		//if (board_.at(row).at(col).tileHasQueen() && board_.at(row).at(col).tileHasDanger())
		if (board_.at(row).at(col).tileHasDanger() || board_.at(row).at(col).tileHasQueen())
			return false;
		else
			return true;
	}

	void clear()
	{
		board_.clear();
		board_.resize(size_, std::vector<Tile>(size_, Tile()));
	}

	int size()
	{
		return size_;
	}

	//the code below finds the most top left position so that I can find all 
	//positions diagonal to that.
	std::pair<int, int> setupLeftDiagonals(int row, int column)
	{
		int tempRow;
		int tempColumn;

		if (row > column)
		{
			tempRow = row - column;
			tempColumn = 0;
		}
		else if (column > row)
		{
			tempColumn = column - row;
			tempRow = 0;
		}
		else
		{
			tempRow = 0;
			tempColumn = 0;
		}
		return std::make_pair(tempRow, tempColumn);

	}
	//the code below finds the most top right position so that I can find all 
	//positions diagonal to that.
	std::pair<int, int> setupRightDiagonals(int row, int column)
	{
		int tempRow;
		int tempColumn;

		if (size_ - 1 < row + column)
		{
			tempRow = row + column - (size_ - 1);
			tempColumn = size_ - 1;
		}
		else
		{
			tempRow = 0;
			tempColumn = row + column;
		}
		return std::make_pair(tempRow, tempColumn);
	}

	//this function marks all tiles that the queen can attack
	void markTileDangerous(int row, int column, bool condition)
	{
		std::pair<int, int> topLeftCoordinates = setupLeftDiagonals(row, column);
		std::pair<int, int> topRightCoordinates = setupRightDiagonals(row, column);

		for (int i = 0; i < size_; i++)
		{
			for (int j = 0; j < size_; j++)
			{
				if (j != column) //we don't want the queen to put herself in danger
				{
					if (condition == true)
					{
						board_.at(row).at(j).tileHasDanger(condition);
						board_.at(row).at(j).increaseAttackingQueensSize();
					}
					else
					{
						if (board_.at(row).at(j).queensAttackingTile() == 1)
						{
							board_.at(row).at(j).tileHasDanger(condition);
						}
						board_.at(row).at(j).decreaseAttackingQueensSize();
					}
				}

				if (i != row)
				{
					if (condition == true)
					{
						board_.at(i).at(column).tileHasDanger(condition);
						board_.at(i).at(column).increaseAttackingQueensSize();
					}
					else
					{
						if (board_.at(i).at(column).queensAttackingTile() == 1)
						{
							board_.at(i).at(column).tileHasDanger(condition);
						}
						board_.at(i).at(column).decreaseAttackingQueensSize();
					}
				}

				if ((i == topLeftCoordinates.first && j == topLeftCoordinates.second))
				{
					if (topLeftCoordinates.first != row || topLeftCoordinates.second != column)
					{
						if (condition == true)
						{
							board_.at(i).at(j).tileHasDanger(condition);
							board_.at(i).at(j).increaseAttackingQueensSize();
						}
						else
						{
							if (board_.at(i).at(j).queensAttackingTile() == 1)
							{
								board_.at(i).at(j).tileHasDanger(condition);
							}
							board_.at(i).at(j).decreaseAttackingQueensSize();
						}
					}
					topLeftCoordinates.first++;
					topLeftCoordinates.second++;
				}
				if (i == topRightCoordinates.first && j == topRightCoordinates.second)
				{
					if (topRightCoordinates.first != row || topRightCoordinates.second != column)
					{
						if (condition == true)
						{
							board_.at(i).at(j).tileHasDanger(condition);
							board_.at(i).at(j).increaseAttackingQueensSize();
						}
						else
						{
							if (board_.at(i).at(j).queensAttackingTile() == 1)
							{
								board_.at(i).at(j).tileHasDanger(condition);
							}
							board_.at(i).at(j).decreaseAttackingQueensSize();
						}
					}
					topRightCoordinates.first++;
					topRightCoordinates.second--;
				}
			}
		}
	}

	//this function marks all tiles safe once a queen is removed
};

#endif

