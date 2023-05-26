#pragma once
#include "GiaoDien.h"

void LuaChon(int a, string menu[], int focus, int len)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (a)
	{
	case 1:
	{
		system("cls");
		int focus = 0;
		string menuIO[] = {
			"Khong IO",
			"IO",
			"Quay ve"
		};
		int len = sizeof(menuIO) / sizeof(menuIO[0]);
		MenuChinh();
		LuaChonIO(MenuIO(menuIO, focus, len), menuIO, focus, len);
		//nut quay ve
		GoToXY(43, 17);
		cout << "Bam ESC de quay lai";
		int ch = _getch();
		if (ch == 27)
		{
			system("cls");
			MenuChinh();
			LuaChon(Menu(menu, focus, len), menu, focus, len);
		}
		break;
	}
	case 2:
	{
		exit(EXIT_SUCCESS);
		break;
	}
	}
}
void LuaChonIO(int a, string menu[], int focus, int len)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	Process pArr[100], p;
	int n, x, cpu, arrival, io = -1, ioStart = -1;
	bool IO = false;
	int locationX = 50, locationY = 10;
	switch (a)
	{
	case 1:
	{
		system("cls");
		MenuChinh();
		bool IO = false;

		GoToXY(locationX, locationY);
		cout << "Enter number of processes: ";
		cin >> n;
		locationY += 1;
		for (int i = 0; i < n; i++) {
			GoToXY(locationX, locationY + i);
			cout << "Process: " << i + 1;
			GoToXY(locationX, locationY + i + 1);
			cout << "===> Burst time: ";
			cin >> cpu;
			GoToXY(locationX, locationY + i + 2);
			cout << "===> Arrival time: ";
			cin >> arrival;
			Process process(i + 1, cpu, arrival, io, ioStart, IO);
			pArr[i] = process;
			locationY += 3;
		}
		locationY += 2;
		p.printGantt(pArr, n, IO, locationX, locationY);
		//nut quay ve
		locationY = locationY + 9 + n;
		GoToXY(locationX, locationY);
		cout << "Bam ESC de quay lai";
		int ch = _getch();
		if (ch == 27)
		{
			system("cls");
			int focus = 0;
			string menuIO[] = {
				"Khong IO",
				"IO",
				"Quay ve"
			};
			int len = sizeof(menuIO) / sizeof(menuIO[0]);
			MenuChinh();
			LuaChonIO(MenuIO(menuIO, focus, len), menuIO, focus, len);
		}
		break;
	}
	case 2:
	{
		system("cls");
		MenuChinh();
		bool IO = true;

		GoToXY(locationX, locationY);
		cout << "Enter number of processes: ";
		cin >> n;
		locationY += 1;
		for (int i = 0; i < n; i++) {
			GoToXY(locationX, locationY + i);
			cout << "Process: " << i + 1;
			GoToXY(locationX, locationY + i + 1);
			cout << "===> Burst time: ";
			cin >> cpu;
			GoToXY(locationX, locationY + i + 2);
			cout << "===> Arrival time: ";
			cin >> arrival;
			GoToXY(locationX, locationY + i + 3);
			cout << "===> IO burst time: ";
			cin >> io;
			GoToXY(locationX, locationY + i + 4);
			cout << "===> IO start time: ";
			cin >> ioStart;
			Process process(i + 1, cpu, arrival, io, ioStart, IO);
			pArr[i] = process;
			locationY += 5;
		}
		locationY += 2;
		p.printGantt(pArr, n, IO, locationX, locationY);
		//nut quay ve
		locationY = locationY + 13 + 2 * n;
		GoToXY(locationX, locationY);
		cout << "Bam ESC de quay lai";
		int ch = _getch();
		if (ch == 27)
		{
			system("cls");
			int focus = 0;
			string menuIO[] = {
				"Khong IO",
				"IO",
				"Quay ve"
			};
			int len = sizeof(menuIO) / sizeof(menuIO[0]);
			MenuChinh();
			LuaChonIO(MenuIO(menuIO, focus, len), menuIO, focus, len);
		}
		break;
	}
	case 3:
	{
		system("cls");
		int focus = 0;
		string menu[] = {
			"Bat Dau",
			"Thoat"
		};
		int len = sizeof(menu) / sizeof(menu[0]);
		MenuChinh();
		LuaChon(Menu(menu, focus, len), menu, focus, len);
		break;
	}
	}
}
void MenuChinh() 
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 4);
	GoToXY(40, 5);
	cout << "********************************************" << endl;
	SetConsoleTextAttribute(hConsole, 4);
	GoToXY(40, 6);
	cout << "*";
	SetConsoleTextAttribute(hConsole, 3);
	cout << "   CHUONG TRINH MO PHONG THUAT TOAN FCFS   ";
	SetConsoleTextAttribute(hConsole, 4);
	cout << "*" << endl;
	SetConsoleTextAttribute(hConsole, 4);
	GoToXY(40, 7);
	cout << "********************************************";
	SetConsoleTextAttribute(hConsole, 15);
}
int Menu(string menu[], int focus, int len)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < len; i++) {
		if (i == focus) {
			SetConsoleTextAttribute(hConsole, 52);
		}
		else {
			SetConsoleTextAttribute(hConsole, 15);
		}
		GoToXY(55, 10 + i);
		cout << i + 1 << ". " << menu[i];
	}
	SetConsoleTextAttribute(hConsole, 15);
	int ch = _getch();
	if (ch == 0 || ch == 224)
	{
		char c = _getch();
		switch (c)
		{
		case 72:
		{
			if (focus == 0) {
				focus = len - 1;
			}
			else {
				focus--;
			}
			break;
		case 80:
			if (focus == len - 1) {
				focus = 0;
			}
			else {
				focus++;
			}
			break;
		}
		}
	}
	else if (ch == 13) return focus + 1;
	else if (ch == 27 && len == 3) return 27;
	Menu(menu, focus, len);
}
int MenuIO(string menu[], int focus, int len)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < len; i++) {
		if (i == focus) {
			SetConsoleTextAttribute(hConsole, 52);
		}
		else {
			SetConsoleTextAttribute(hConsole, 15);
		}
		GoToXY(55, 10 + i);
		cout << i + 1 << ". " << menu[i];
	}
	SetConsoleTextAttribute(hConsole, 15);
	int ch = _getch();
	if (ch == 0 || ch == 224)
	{
		char c = _getch();
		switch (c)
		{
		case 72:
		{
			if (focus == 0) {
				focus = len - 1;
			}
			else {
				focus--;
			}
			break;
		case 80:
			if (focus == len - 1) {
				focus = 0;
			}
			else {
				focus++;
			}
			break;
		}
		}
	}
	else if (ch == 13) return focus + 1;
	else if (ch == 27 && len == 3) return 27;
	Menu(menu, focus, len);
}