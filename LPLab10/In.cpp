#include "stdafx.h"
#include "In.h"
#include "Error.h"
#include <string>

using namespace std;

namespace In
{
	IN getin(wchar_t infile[])
	{
		IN myIn;

		int position = 0;

		myIn.size = 0;
		myIn.lines = 1;
		myIn.ignor = 0;
		myIn.text = new unsigned char[IN_MAX_LEN_TEXT];

		ifstream inFile;
		inFile.open(infile);

		if (!inFile)
		{
			throw ERROR_THROW(110);
		}
		else     
		{
			unsigned char tempChar;
			while ((tempChar = inFile.get()) && !inFile.eof())
			{
				if (tempChar == IN_CODE_ENDL)
				{
					myIn.text[myIn.size] = IN_CODE_ENDL;
					myIn.lines++;
					position = 0;
				}
				else if (myIn.code[tempChar] == myIn.F)
				{
					throw ERROR_THROW_IN(111, --myIn.lines, position);
				}
				else if (myIn.code[tempChar] == myIn.T)
				{
					myIn.text[myIn.size] = tempChar;
				}
				else if (myIn.code[tempChar] == myIn.I)
				{
					myIn.ignor++;
					continue;
				}
				else
				{
					myIn.text[myIn.size] = '!';
				}
				position++;
				myIn.size++;
			}

			myIn.text[myIn.size] = '\0';
			myIn.size--;

			inFile.close();
		}

		if (myIn.size == 0)
		{
			myIn.lines = 0;
		} 
		return myIn;
	}
}
