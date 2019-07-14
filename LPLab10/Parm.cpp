#include "stdafx.h"
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"

using namespace std;

namespace Parm
{
	PARM getparm(int argc, wchar_t* argv[])
	{
		PARM myParm;

		bool myParmIn =  false;
		bool myParmOut = false;
		bool myParmLog = false;

		wchar_t *temp = NULL;

		for (int i = 1; i < argc; i++)
		{
			if (wcslen(argv[i]) < PARM_MAX_SIZE)
			{
				if (wcsstr(argv[i], PARM_IN) != 0)
				{
					temp = wcsstr(argv[i], PARM_IN) + wcslen(PARM_IN);
					wcscpy(myParm.in, temp);
					temp -= wcslen(PARM_IN);
					myParmIn = true;
				}
				if (wcsstr(argv[i], PARM_OUT) != 0)
				{
					temp = wcsstr(argv[i], PARM_OUT) + wcslen(PARM_OUT);
					wcscpy(myParm.out, temp);
					temp -= wcslen(PARM_OUT);
					myParmOut = true;
				}
				if (wcsstr(argv[i], PARM_LOG) != 0)
				{
					temp = wcsstr(argv[i], PARM_LOG) + wcslen(PARM_LOG);
					wcscpy(myParm.log, temp);
					temp -= wcslen(PARM_LOG);
					myParmLog = true;
				}
			}
			else
			{
				throw ERROR_THROW(104);
			}
		}

		if (!myParmIn)
		{
			throw ERROR_THROW(100);
		}
		if (myParmOut)
		{
			wcscpy(temp, myParm.in);
			wcsncat(temp, PARM_OUT_DEFAULT_EXT, 4);
			wcscpy(myParm.out, temp);
		}
		if (myParmLog)
		{
			wcscpy(temp, myParm.in);
			wcsncat(temp, PARM_LOG_DEFAULT_EXT, 4);
			wcscpy(myParm.log, temp);
		}

		return myParm;
	}
}