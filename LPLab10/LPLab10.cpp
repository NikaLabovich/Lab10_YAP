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

	cout << "----- ���� ������� -----" << endl << endl;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		In::IN in = In::getin(parm.in);
		cout << in.text << endl;
		cout << "����� ��������: " << in.size << endl;
		cout << "����� �����: " << in.lines << endl;
		cout << "����� ���������: " << in.ignor << endl;
		Log::WriteLine(log, "����:", "��� ������ ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);
		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
		cout << "������� ������!" << endl;
		cout << "��� ������: " << e.id << endl;
		cout << "�������� ������: " << e.message << endl;
		cout << "������ � �������: " << e.inext.line << endl;
		cout << "������� ������: " << e.inext.col << endl;
	}

	system("pause");
	return 0;
}

