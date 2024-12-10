#pragma once
#include<graphics.h>
#include<easyx.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")
#define Row 16
#define Col 30
#define Num 50
#define IMGW 40
void drapmap(int mine[Row][Col], IMAGE img[]);
void Mouseoperation(int mine[Row][Col]);
void Showmine(int mine[Row][Col]);
void OpenNULL(int mine[Row][Col], int row, int col);
void Findmine(int mine[Row][Col], int row, int col);
void music();