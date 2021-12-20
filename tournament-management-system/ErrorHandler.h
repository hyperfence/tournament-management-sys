#pragma once
#ifdef _DEBUG
	#define IS_DEBUG true
#else
	#define IS_DEBUG false
#endif
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <windows.h>

using namespace std;

class ErrorHandler
{
private:
	int line;
	int code;
	string source;
	string file;
	string desc;
	string state;

public:
	ErrorHandler();
	void setError(int line, int code, string source, string file, string desc, string state);
	void logError();
	~ErrorHandler();
};