//QueensDriver.cpp
//Dylan Brigham & Madison Cooley
//Dr. Bailey
//COSC 3020
//04/??/17

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>
#include "GameBoard.h"
#include "winTimer.h"


void shuffle(std::vector<int>& container);
void randomQueenInsert(GameBoard & gameboard, std::vector<int> container);
void randomSearch(GameBoard & gameBoard);

bool backTrackQueenInsert(GameBoard & gameBoard, int row);
void backTrack(GameBoard & gameboard);

bool random(GameBoard & gameboard, int row, std::vector<int> orderVec);
void randomBacktrack(GameBoard & gameBoard);

int main()
{
	int SIZE;
	do {

		std::cout << "Enter number of Queens: ";
		std::cin >> SIZE;
		std::cout << std::endl;


		GameBoard gameboard(SIZE);
		Timer watch;
		watch.start();
		randomSearch(gameboard);
		watch.stop();
		gameboard.display();
		std::cout << "Time: " << watch() << std::endl;

		GameBoard gameboard1(SIZE);
		Timer watch2;
		watch2.start();
		backTrack(gameboard1);
		watch2.stop();
		std::cout << std::endl;
		gameboard1.display();
		std::cout << "Time: " << watch2() << std::endl;

		GameBoard gameboard2(SIZE);
		Timer watch3;
		watch3.start();
		randomBacktrack(gameboard2);
		watch3.stop();
		std::cout << std::endl;
		gameboard2.display();
		std::cout << "Timer: " << watch3() << std::endl;
		std::cout << std::endl;
	} while (SIZE != 0);
	return 0;
}


void shuffle(std::vector<int>& container)
{
	std::random_device rd; //I need to do more research on this, found it on overstack
	std::mt19937 g(rd());
	std::shuffle(std::begin(container), std::end(container), g);
}

void randomSearch(GameBoard & gameboard)
{
	std::vector<int> queenContainer(gameboard.size());
	for (int i = 0; i < queenContainer.size(); i++)
	{
		queenContainer.at(i) = i;
	}
	do {
		randomQueenInsert(gameboard, queenContainer);
	} while (gameboard.check() == 0);
}

void randomQueenInsert(GameBoard & gameboard, std::vector<int> container)
{
	gameboard.clear();

	shuffle(container);

	for (int i = 0; i < gameboard.size(); i++)
	{
		gameboard.insertQueenAt(i, container.at(i));
	}
}

bool backTrackQueenInsert(GameBoard & gameboard, int row)
{
	//gameboard.display();
	//Sleep(500);
	//system("cls");


	if (gameboard.size() == row)
	{
		return true;
	}

	int col;
	for (col = 0; col < gameboard.size(); col++)
	{
		bool foundPos = true;

		//checks each row for a safe position
		for (int queen = 0; queen <= row; queen++)
		{
			if (!gameboard.checkPos(row, col))
			{
				foundPos = false;
				break;
			}
		}

		if (foundPos)
		{
			gameboard.insertQueenAt(row, col);

			//recursive call
			if (backTrackQueenInsert(gameboard, row + 1))
				return true;
		}
	}
	int column = gameboard.colPosOfQueen(row - 1);
	gameboard.removeQueenAt(row - 1, column);

	return false;
}

void backTrack(GameBoard & gameboard)
{
	bool found = backTrackQueenInsert(gameboard, 0);
	if (found)
	{
		//gameboard.display();
	}
}

void randomBacktrack(GameBoard & gameboard)
{
	std::vector<int> queenContainer(gameboard.size());
	int startPos = 0;
	for (int i = 0; i < queenContainer.size(); i++)
	{
		queenContainer.at(i) = i;
	}
	shuffle(queenContainer);

	std::vector<int> orderVec(gameboard.size());
	for (int i = 0; i < orderVec.size(); i++)
	{
		orderVec.at(queenContainer.at(i)) = i;

	}
	//for (int obj : orderVec)
	//	std::cout << obj << " ";
	//std::cout << std::endl;
	//gameboard.insertQueenAt(orderVec.at(0), 0);

	bool found = random(gameboard, 0, orderVec);
	if (found)
	{
		//gameboard.display();
	}
}

bool random(GameBoard & gameboard, int index, std::vector<int> orderVec)
{
	//gameboard.display();
	//Sleep(200);
	//system("cls");

	//Game is solved
	if (gameboard.size() == index)
	{
		return true;
	}

	//std::cout << "New Call" << std::endl;
	int col;
	for (col = 0; col < gameboard.size(); col++)
	{
		//std::cout << "Col " << col << std::endl;

		bool foundPos = true;

		//checks each row for a safe position
		for (int queen = 0; queen <= orderVec.at(index); queen++)
		{
			//std::cout << "Row " << orderVec.at(index) << std::endl;

			if (!gameboard.checkPos(orderVec.at(index), col))
			{
				foundPos = false;

				break;
			}
		}

		if (foundPos)
		{
			//std::cout << "Position found" << std::endl;
			//if (gameboard.checkPos(orderVec.at(index), col))
			//{
			//std::cout << "Inserted " << orderVec.at(index) << ", " << col << std::endl;
			gameboard.insertQueenAt(orderVec.at(index), col);
			//}

			//recursive call
			if (random(gameboard, index + 1, orderVec))
				return true;
		}
	}
	//std::cout << "Backtracked " << index << std::endl;
	int column = gameboard.colPosOfQueen(orderVec.at(index - 1));
	gameboard.removeQueenAt(orderVec.at(index - 1), column);

	return false;
}