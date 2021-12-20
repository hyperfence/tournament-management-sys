#include "ErrorHandler.h"

const string currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d|%X", &tstruct);
	return buf;
}

ErrorHandler::ErrorHandler()
{
	this->code = 0;
	this->line = 0;
	this->desc = "";
	this->file = "";
	this->state = "";
	this->source = "";
}

void ErrorHandler::setError(int line, int code, string source, string file, string desc, string state)
{
	this->line = line;
	this->code = code;
	this->source = source;
	this->file = file;
	this->desc = desc;
	this->state = state;
}

void ErrorHandler::logError()
{
	string dirPath = "Logs";
	string err = "[" + currentDateTime() + "][" + this->source + "][Error#" + to_string(this->code) + "][State#" + this->state + "][File:" + this->file + "][Line:" + to_string(this->line) + "]: " + this->desc + "\n";
	if (CreateDirectory(dirPath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{
		if (IS_DEBUG)
		{
			cout << "\nx-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n";
		}
		char fileName[] = "Logs/log.txt";
		fstream logFile;
		logFile.open(fileName, std::fstream::in | std::fstream::out | std::fstream::app);
		if (!logFile)
		{
			if (IS_DEBUG)
			{
				cout << "Creating the log file ...\n";
			}
			logFile.open(fileName, fstream::in | fstream::out | fstream::trunc);
			logFile << "\n";
			logFile.close();
		}
		else
		{
			if (IS_DEBUG)
			{
				cout << "This error was logged into the log.txt file.\n";
			}
			logFile << err;
			logFile.close();
		}
	}
	else
	{
		if (IS_DEBUG)
		{
			cout << "Failed to log the error! Couldn't create or find the Logs directory.\n";
		}
	}
	string err1 = "[" + this->source + "][Error#" + to_string(this->code) + "][State#" + this->state + "]\nFile: " + this->file + "\nLine: " + to_string(this->line) + "\nDetails: " + this->desc + "\n";
	if (IS_DEBUG)
	{
		cout << err1;
		cout << "x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n\n";
	}
}

ErrorHandler::~ErrorHandler()
{

}