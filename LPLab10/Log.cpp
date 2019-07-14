#include "stdafx.h"
#include "Log.h"
#include "Error.h"
#include "Parm.h"
#include <ctime>

namespace Log
{
	LOG getlog(wchar_t logfile[])
	{ 
		LOG tempLog = Log::INITLOG;

		tempLog.stream = new std::ofstream;
		tempLog.stream->open(logfile);

		if (!tempLog.stream)
		{
			throw ERROR_THROW(112);
		}
		return tempLog;
	}

	void WriteLine(LOG log, char* c, ...)
	{
		char **p = &c;

		while (*p != "")
		{
			(*log.stream) << *p;
			p += sizeof(**p);
		}
	}

	void WriteLine(LOG log, wchar_t* c, ...)
	{
		wchar_t **p = &c;
		char buffer[50];

		while (*p != L"")
		{
			wcstombs(buffer, *p, sizeof(buffer));
			(*log.stream) << buffer;
			p += sizeof(**p) / 2;
		}
	}

	void WriteLog(LOG log)
	{
		char buffer[PARM_MAX_SIZE];

		time_t rawtime;
		struct tm* timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, PARM_MAX_SIZE, "Дата: %d.%m.%y %H:%M:%S", timeinfo);
		(*log.stream) << "\n----- Протокол ----- " << buffer << " ----- \n";
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		char inInfo[PARM_MAX_SIZE];
		char outInfo[PARM_MAX_SIZE];
		char logInfo[PARM_MAX_SIZE];

		wcstombs(inInfo, parm.in, sizeof(inInfo));
		wcstombs(outInfo, parm.out, sizeof(outInfo));
		wcstombs(logInfo, parm.log, sizeof(logInfo));

		(*log.stream) << "----- Параметры ----- \n"
			<< " -in: " << inInfo << "\n"
			<< " -out: " << outInfo << "\n"
			<< " -log: " << logInfo << "\n";
	}

	void WriteIn(LOG log, In::IN in)
	{
		(*log.stream) << "----- Исходные данные ----- \n"
			<< "Всего символов: " << in.size << "\n"
			<< "Всего строк: " << in.lines << "\n"
			<< "Пропущено: " << in.ignor << "\n";
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		if (error.id == 100)
		{
			std::cout << "ОШИБКА " << error.id << ": " << error.message << "\n";
		}
		else
		{
			(*log.stream) << "ОШИБКА " << error.id << ": " << error.message << "\n"
				<< "Строка " << error.inext.line << ", позиция: " << error.inext.col;
		}
	}

	void Close(LOG log)
	{
		(*log.stream).close();
	}
}