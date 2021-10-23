#include "Header.h"


int main()
{
	try
	{		
		char inBuff[BUF_SIZE],
			outBuff[BUF_SIZE] = "hello server";
		DWORD nBytesRead;
		LPCWSTR pipeName = TEXT(PIPE_NAME);
		if (!CallNamedPipe(pipeName, outBuff, sizeof(outBuff), inBuff, sizeof(inBuff), &nBytesRead, NMPWAIT_WAIT_FOREVER))
			throw ERROR_CALLNAMEDPIPE;

		cout << "Server response: " << inBuff << endl;
	}
	catch (const char* err)
	{
		cout << GetLastError() << endl;
		cout << err << endl;
	}

	system("pause");
	return 0;
}
