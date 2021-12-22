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
#include <tchar.h>
#include <windows.h>

class ErrorHandler
{
private:
	int line;
	int code;
	std::string source;
	std::string file;
	std::string desc;
	std::string state;

public:
	ErrorHandler();
	void setError(int line, int code, std::string source, std::string file, std::string desc, std::string state);
	void logError();
	~ErrorHandler();
};