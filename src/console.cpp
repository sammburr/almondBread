#include "console.h"

#define RED   71
#define BLUE  151
#define YELLOW 103
#define GREEN 47

Console::Console(const char* _scriptName)
{

    SetConsoleOutputCP( CP_UTF8 );
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    sName = _scriptName;

}

void Console::Log(const char* _message)
{

    SetConsoleTextAttribute(hConsole, BLUE);
    std::cout << sName << " (Δ) Log :" << _message << std::endl;
    SetConsoleTextAttribute(hConsole, 7);

}

void Console::Log(float _message)
{

    SetConsoleTextAttribute(hConsole, BLUE);
    std::cout << sName <<" (Δ) Log :" << _message << std::endl;
    SetConsoleTextAttribute(hConsole, 7);

}

void Console::LogSuccsess(const char* _message)
{

    SetConsoleTextAttribute(hConsole, GREEN);
    std::cout << sName <<" (α) Succsess :" << _message << std::endl;
    SetConsoleTextAttribute(hConsole, 7);

}

void Console::LogWarning(const char* _message)
{

    SetConsoleTextAttribute(hConsole, YELLOW);
    std::cout << sName <<" (γ) Warning :" << _message << std::endl;
    SetConsoleTextAttribute(hConsole, 7);

}

void Console::LogWarning(float _message)
{

    SetConsoleTextAttribute(hConsole, YELLOW);
    std::cout <<sName << " (γ) Warning :" << _message << std::endl;
    SetConsoleTextAttribute(hConsole, 7);

}

void Console::LogError(const char* _message)
{

    SetConsoleTextAttribute(hConsole, RED);
    std::cout << sName <<" (β) Error :" << _message << std::endl;
    SetConsoleTextAttribute(hConsole, 7);

}