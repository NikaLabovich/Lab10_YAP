#include "stdafx.h"
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;

	cout << "----- тест функций -----" << endl << endl;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		In::IN in = In::getin(parm.in);
		cout << in.text << endl;
		cout << "Всего символов: " << in.size << endl;
		cout << "Всего строк: " << in.lines << endl;
		cout << "Всего пропущено: " << in.ignor << endl;
		Log::WriteLine(log, "Тест:", "без ошибок ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
		cout << "Найдены ошибки!" << endl;
		cout << "Код ошибки: " << e.id << endl;
		cout << "Название ошибки: " << e.message << endl;
		cout << "Строка с ошибкой: " << e.inext.line << endl;
		cout << "Позиция ошибки: " << e.inext.col << endl;
	}

	system("pause");
	return 0;
}

