#pragma once
#include "Header.h"

class Process
{
private:
    int id; // process id
    int cpu; // cpu time burst
    int arrival; // time arrival in cpu
    int io; // I/O time burst
    int ioStart; // time start I/O
    bool haveIO;
public:
    Process();
    Process(int _id, int _cpu, int _arrival, int _io, int _ioTime, bool _haveIO);
    void printGantt(Process p[], int n, bool IO, int x, int y);
};
void GoToXY(int x, int y);