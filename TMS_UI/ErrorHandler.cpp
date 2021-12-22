#include "ErrorHandler.h"

const std::string currentDateTime() {
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

void ErrorHandler::setError(int line, int code, std::string source, std::string file, std::string desc, std::string state)
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
	std::string err = "[" + currentDateTime() + "][" + this->source + "][Error#" + std::to_string(this->code) + "][State#" + this->state + "][File:" + this->file + "][Line:" + std::to_string(this->line) + "]: " + this->desc + "\n";
	if (CreateDirectory(__T("Logs"), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{
		if (IS_DEBUG)
		{
			std::cout << "\nx-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n";
		}
		char fileName[] = "Logs/log.txt";
		std::fstream logFile;
		logFile.open(fileName, std::fstream::in | std::fstream::out | std::fstream::app);
		if (!logFile)
		{
			if (IS_DEBUG)
			{
				std::cout << "Creating the log file ...\n";
			}
			logFile.open(fileName, std::fstream::in | std::fstream::out | std::fstream::trunc);
			logFile << "\n";
			logFile.close();
		}
		else
		{
			if (IS_DEBUG)
			{
				std::cout << "This error was logged into the log.txt file.\n";
			}
			logFile << err;
			logFile.close();
		}
	}
	else
	{
		if (IS_DEBUG)
		{
			std::cout << "Failed to log the error! Couldn't create or find the Logs directory.\n";
		}
	}
	std::string err1 = "[" + this->source + "][Error#" + std::to_string(this->code) + "][State#" + this->state + "]\nFile: " + this->file + "\nLine: " + std::to_string(this->line) + "\nDetails: " + this->desc + "\n";
	if (IS_DEBUG)
	{
		std::cout << err1;
		std::cout << "x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x\n\n";
	}
}

ErrorHandler::~ErrorHandler()
{

}