#include "Header.h"

int main()
{
	try
	{
		LPCWSTR pipeName = TEXT(PIPE_NAME);
		HANDLE hPipe;
		if ((hPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE|PIPE_WAIT, 1, NULL, NULL, INFINITE, NULL)) == INVALID_HANDLE_VALUE)
			throw ERROR_CREATENAMEDPIPE;

		if (!ConnectNamedPipe(hPipe, NULL))
			throw ERROR_CONNECTNAMEDPIPE;

		cout << "connected" << endl;

		char inBuf[BUF_SIZE];
		DWORD dwBytesRead = 0;
		if (!ReadFile(hPipe, inBuf, sizeof(inBuf), &dwBytesRead, NULL))
			throw ERROR_READFILE;

		cout << "Client message: " << inBuf << endl;

		char outBuf[BUF_SIZE] = "hello client";
		DWORD dwBytesWritten = 0;
		if (!WriteFile(hPipe, outBuf, sizeof(outBuf), &dwBytesWritten, NULL))
			throw ERROR_READFILE;		

		CloseHandle(hPipe);
	}
	catch (string err)
	{
		cout << err << endl;
	}

	system("pause");
	return 0;
}
