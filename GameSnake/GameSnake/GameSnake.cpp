// GameSnake.cpp : First Join C++;
// Game Test,hope all works;
// Version: 0.1;
// Author: HappyFeedFriends;
// Date: 01.12.2018. 01 December 2018 year

#include "pch.h"
#include "util.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <fstream>
using namespace std;
const int width = 25; // Size Width
const int height = 10;// Size Height
// Setting Control
const int SettingW = 230; // Button Keyboard: W
const int SettingA = 228; // Button Keyboard: A
const int SettingS = 235; // Button Keyboard: S
const int SettingD = 162; // Button Keyboard: D
const int SettingStop = 231;
// Start Position
int positionH = height / 2;
int positionW = width / 2;
int positionFruitH = rand() % height;
int positionFruitW = rand() % width;
// Score 
int score = 0;
// GameInfo
bool IsGameOver = true;
int GameSpeed, IsSave, IsUsedSave,record = 0;
float speed;
enum Direction {
	LEFT, RIGHT, UP, DOWN, STOP, BONUS_MOVE
};
Direction position;
void CreateInfoPlayer() {
	for (int i = 0; i <= 10; i++) {
		if (i == 10)
			cout << "Фруктов:" << score;
		else
			cout << " ";
	}
}
void CreateInfoRecord() {
	for (int i = 0; i <= 10; i++) {
		if (i == 10 && record > 0)
			cout << "Рекорд:" << record;
		else
			cout << " ";
	}
}
void CreateInfoSpeed() {
	for (int i = 0; i <= 10; i++) {
		if (i == 10)
			cout << "Скорость: " << speed << " сек.";
		else
			cout << " ";
	}
}

void CreateInfo(int j, int i){
	if (j == width - 1 && i == 0) {
		CreateInfoPlayer();
	}
	if (j == width - 1 && i == 3 && record > 0) {
		CreateInfoRecord();
	}
	if (j == width - 1 && i == 5) {
		CreateInfoSpeed();
	}
}

void CreateWindowSnake() {
	system("cls");
	for (int i = 0; i <= width;i++)
		cout << "#";	
	cout << "\n";	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width-1) 
				cout << "#";
			if (j == positionW && i == positionH)
				cout << "*";
			else if (j == positionFruitW && i == positionFruitH)
				cout << "@";
			else
			cout << " ";
			CreateInfo(j, i);
		}
		cout << "\n";
	}
	for (int i = 0; i <= width; i++)
		cout << "#";
	if (positionW >= width - 2 || positionH >= height ||
		positionW < 0 || positionH < 0)
		IsGameOver = false;
}

void UpdateKeyBind() {	
	if (_kbhit()) {
		switch (_getch()) {
			case SettingW: {
				position = UP;
				break;
			}			
			case SettingA: {
				position = LEFT;
				break;
			}			
			case SettingS: {
				position = DOWN;
				break;
			}			
			case SettingD: {
				position = RIGHT;
				break;
			}
			case SettingStop: {
				position = STOP;
				break;
			}			
		}
	}
}
void CreateFruit() {
	positionFruitH = rand() % height;
	positionFruitW = rand() % (width-1);
}
void UpdatePosition() {
	switch (position)
	{
		case UP: {
			positionH--;
			break;
		}	
		case DOWN: {
			positionH++;
			break;
		}	
		case RIGHT: {
			positionW++;
			break;
		}	
		case LEFT: {
			positionW--;
			break;
		}	
		case STOP: {
			break;
		}		
	}
	// Game Over if position for the map	
	if (positionW == positionFruitW && positionH == positionFruitH) {
		CreateFruit();
		score++;
		if (record <= score -1)
		record = score;
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");// Russian 
	cout << "Имеется ли у вас сохранённые очки? \n 1 = Да \n 0 = Нет";
	cin >> IsUsedSave;
	ifstream records;
	records.open("records.txt");
	records >> record;
	records.close();
	// Is Save
	if (IsUsedSave == 1) {
		ifstream myfile;
		myfile.open("saves.txt");
		myfile >> score >> speed;
		myfile.close();
	}
	else {
		system("cls");
		cout << score;
		cout << " Минимальная: 0 \n Cредняя: 1 \n Быстрая: 2 \nВыберите скорость игры:";
		cin >> GameSpeed;
		switch (GameSpeed) {
		case 0: {
			speed = 1;
			break;
		}
		case 1: {
			speed = 0.5;
			break;
		}
		case 2: {
			speed = 0.3;
			break;
		}
		default: speed = 1;


		}
	}
	while (IsGameOver){
		UpdateKeyBind();
		UpdatePosition();
		CreateWindowSnake();
		Sleep(1000 * speed);
	} 
	ofstream outFile("records.txt");
	outFile << record;
	system("cls");
	cout << "\n Сохранить полученные очки? \n 1 = Да \n 0 = Нет\n";
	cin >> IsSave;
	if (IsSave == 1) {
		ofstream outFile("saves.txt");
		outFile << score << " " << speed;
	}
	return 0;
}