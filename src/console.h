#ifndef __CONSOLE__
#define __CONSOLE__

#include <Windows.h>
#include <iostream>

class Console
{
private:
    HANDLE hConsole;
    const char* sName;

public:
    Console(const char* _scriptName);
    void Log(const char* _message);
    void Log(float _message);
    void LogSuccsess(const char* _message);
    void LogWarning(const char* _message);
    void LogWarning(float _message);
    void LogError(const char* _message);

};

#endif