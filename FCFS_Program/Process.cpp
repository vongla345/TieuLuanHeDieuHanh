#pragma once
#include "Process.h"

Process::Process()
{
    id = 0;
    cpu = 0;
    arrival = 0;
    io = -1;
    ioStart = -1;
    haveIO = false;
}
Process::Process(int _id, int _cpu, int _arrival, int _io, int _ioTime, bool _haveIO)
{
    id = _id;
    cpu = _cpu;
    arrival = _arrival;
    haveIO = _haveIO;
    if (haveIO) 
    {
        io = _io;
        ioStart = _ioTime;
    }
    else 
    {
        io = -1;
        ioStart = -1;
    }
}
void Process::printGantt(Process p[], int n, bool IO, int x, int y)
{
    Process process[100];
    vector<Process> CPU; // CPU run
    vector<Process> ioRun; // IO run
    vector<Process> cpuQueue, ioQueue; // CPU queue | IO queue
    char cpu[100][50], io[100][50];
    int currTime = 0;
    int cnt = 0;
    int wt[100];

    // set up the array
    for (int i = 0; i < n; i++) {
        wt[i] = 0;
        for (int j = 0; j < 50; j++) {
            cpu[i][j] = '-';
            io[i][j] = '-';
        }
    }

    for (int i = 0; i < n; i++)
        process[i] = p[i];

    // browse each colume with current time = 0
    for (currTime = 0; cnt < n || !CPU.empty() || !cpuQueue.empty() || !ioRun.empty() || !ioQueue.empty(); currTime++) {
        // if arrive at current time
        for (int i = 0; i < n; i++) {
            if (p[i].arrival == currTime) {
                cpuQueue.push_back(p[i]);
                cnt++;
            }
        }
        // CPU doesn't have any process, push process from cpu queue to run
        while (!cpuQueue.empty() && CPU.empty()) {
            CPU.push_back(cpuQueue[0]);
            if (CPU[0].arrival + CPU[0].ioStart == currTime) {
                ioQueue.push_back(CPU[0]);
                CPU.clear();
            }
            cpuQueue.erase(cpuQueue.begin());
        }

        if (!CPU.empty()) {
            if (CPU[0].arrival + CPU[0].ioStart == currTime) {
                ioQueue.push_back(CPU[0]);
                CPU.clear();
            }
        }

        if (!ioRun.empty()) {
            if (ioRun[0].arrival + ioRun[0].ioStart + ioRun[0].io == currTime) {

                ioRun[0].cpu += ioRun[0].io;
                cpuQueue.push_back(ioRun[0]);
                ioRun.clear();
            }
        }

        if (ioRun.empty()) {
            if (!ioQueue.empty()) {
                //cout<<ioQueue[0].arrival<<'\n';
                ioRun.push_back(ioQueue[0]);
                ioQueue.erase(ioQueue.begin());
            }
        }
        if (!ioRun.empty()) {
            if (!ioQueue.empty()) {
                for (int i = 0; i < ioQueue.size(); i++) {
                    ioQueue[i].io++;
                }
            }
        }
        if (!CPU.empty()) {
            if (CPU[0].arrival + CPU[0].cpu == currTime) {
                CPU.clear();
            }
        }

        // CPU doesn't have any process, push process from cpu queue to run
        if (!cpuQueue.empty() && CPU.empty()) {
            CPU.push_back(cpuQueue[0]);
            cpuQueue.erase(cpuQueue.begin());
        }

        // 1 process take CPU and other processes in CPU queue
        if (!cpuQueue.empty() && !CPU.empty()) {
            for (int i = 0; i < cpuQueue.size(); i++) {
                cpuQueue[i].arrival++;
            }
        }
        if (!CPU.empty()) {
            if (CPU[0].arrival + CPU[0].cpu == currTime) {
                CPU.clear();
            }
        }
        if (CPU.empty()) {
            if (cpuQueue.empty()) {
                for (int i = 0; i < n; i++) {
                    cpu[i][currTime] = '|';
                }
            }
        }
        if (!CPU.empty()) {
            cpu[CPU[0].id - 1][currTime] = '#';
        }
        if (ioRun.empty()) {
            if (ioQueue.empty())
                for (int i = 0; i < n; i++) {
                    io[i][currTime] = '|';
                }
        }

        if (!ioRun.empty()) {
            io[ioRun[0].id - 1][currTime] = '#';
        }

        if (!cpuQueue.empty()) {
            for (int i = 0; i < cpuQueue.size(); i++) {
                wt[cpuQueue[i].id - 1]++;
            }
        }
    }
    y++;
    GoToXY(x, ++y);
    cout << "CPU: ";
    for (int i = 0; i < n; i++) 
    {
        GoToXY(x, ++y);
        cout << "Process " << i + 1 << ": ";
        for (int j = 0; j < currTime; j++) {
            cout << cpu[i][j];
        }
    }
    if (IO)
    {
        GoToXY(x, ++y);
        cout << "IO: ";
        for (int i = 0; i < n; i++) 
        {
            GoToXY(x, ++y);
            cout << "Process " << i + 1 << ": ";
            for (int j = 0; j < currTime; j++) 
            {
                cout << io[i][j];
            }
        }
    }
    double waitingTime = 0;
    double turnAround = 0;
    double CPUusage = 0;
    double response = 0;
    for (int i = 0; i < currTime - 1; i++) {
        if (cpu[0][i] != '|')
            CPUusage++;
    }
    for (int i = 0; i < n; i++) {
        int tmp = 0;
        for (int j = 0; j < currTime - 1; j++) {
            if (cpu[i][j] == '#') {
                tmp = j;
                break;
            }
        }
        response += tmp - process[i].arrival;
    }
    for (int i = 0; i < n; i++)
        waitingTime += double(wt[i]);
    for (int i = 0; i < n; i++) {
        int tmp = 0;
        for (int j = 0; j < currTime; j++) {
            if (cpu[i][j] == '#') {
                tmp = j + 1;
            }
        }
        turnAround += tmp - process[i].arrival;
    }
    y++;
    GoToXY(x, ++y);
    cout << "CPU usage: " << CPUusage * 100 / (currTime - 1) << "%";
    GoToXY(x, ++y);
    cout << "Average response time: " << response / n;
    GoToXY(x, ++y);
    cout << "Average waiting time: " << waitingTime / n;
    GoToXY(x, ++y);
    cout << "Average turn-around time: " << double(turnAround) / n;
}   
void GoToXY(int x, int y) {
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x - 1,y - 1 };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}