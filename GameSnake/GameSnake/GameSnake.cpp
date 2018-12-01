// GameSnake.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "util.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include<time.h>
using namespace std;
const int width = 25;
const int height = 15;
// Управление клавишами
const int SettingW = 230;
const int SettingA = 228;
const int SettingS = 235;
const int SettingD = 162;
const int SettingStop = 231;
// Начальные позиции
int positionH = height / 2;
int positionW = width / 2;
int positionFruitH = rand() % height;
int positionFruitW = rand() % width;
int oldPosition;
// Начальное положение конечной игры
bool IsGameOver = true;
enum Direction {
	LEFT, RIGHT, UP, DOWN, STOP
};
Direction position;
class Data{
	public:
		int score,level,speed;

};
void CreateWindowSnake() {
	system("cls");
	for (int i = 0; i <= width;i++)
		cout << "#";	
	cout << "\n";	
	for (int i = 0; i <= height; i++) {
		for (int j = 0; j <= width; j++) {
			if (j == 0 || j == width - 1) 
				cout << "#";
			if (j == positionH && i == positionW)
				cout << "*";
			else if (j == positionFruitW && i == positionFruitH)
				cout << "@";
			else
			cout << " ";
		}
		cout << "\n";
	}
	for (int i = 0; i <= width; i++)
		cout << "#";
}

void UpdateKeyBind() {	
	if (_kbhit()) {
		cout << _getch() << " KeyBind";
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
void UpdatePosition() {
	cout << position << " Position";
	switch (position)
	{
		case UP: {
			positionW--;
			break;
		}	
		case DOWN: {
			positionW++;
			break;
		}	
		case RIGHT: {
			positionH++; 
			break;
		}	
		case LEFT: {
			positionH--;
			break;
		}	
		case STOP: {
			break;
		}
		default:
			break;
	}
	// Стоп гейм,если ушли за границу "карты"
	if (positionW >= width+1 || positionH >= height+1)
		IsGameOver = false;
}
int main()
{
	while (IsGameOver){
		UpdateKeyBind();
		UpdatePosition();
		CreateWindowSnake();
	}
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
