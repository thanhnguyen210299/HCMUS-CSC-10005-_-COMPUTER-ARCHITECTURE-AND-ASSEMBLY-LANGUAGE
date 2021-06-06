#pragma once

#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13

#define red 12
#define blue 11
#define white 15
#define gray 7
#define selected 14
#define noti 9
#define error 12

void textcolor(int x); //Ham to mau - Text Color
void gotoxy(int x, int y); //Tu dinh nghia ham dich chuyen con tro den vi tri x, y
void hidepointedmouse(); //ham an con tro chuot tren console
void showpointedmouse(); //hien con tro khi moi bat dau man hinh login


int TypeOfData();
int Base1(bool);
int Action(bool, int);
int Base2(int);
string Oper(bool);
bool End(int);