#include "Header.h"


int main()
{
	try
	{
		LPCWSTR pipeName = TEXT(PIPE_NAME);		
		HANDLE hPipe;
		if ((hPipe = CreateFile(pipeName, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL)) == INVALID_HANDLE_VALUE)
			throw ERROR_CREATEFILE;

		DWORD dwMode = PIPE_READMODE_MESSAGE;
		SetNamedPipeHandleState(hPipe, &dwMode, NULL, NULL);  

		char inBuff[BUF_SIZE],
			outBuff[BUF_SIZE] = "hello server";
		DWORD nBytesRead;
		if (!TransactNamedPipe(hPipe, outBuff, sizeof(inBuff), inBuff, sizeof(inBuff), &nBytesRead, NULL))
			throw ERROR_TRANSACTNAMEDPIPE;

		cout << "Server response: " << inBuff << endl;

		CloseHandle(hPipe);
	}
	catch (const char* err)
	{
		cout << GetLastError() << endl;
		cout << err << endl;
	}

	system("pause");
	return 0;
}
