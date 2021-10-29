#include "Header.h"


int main()
{
	try
	{
		LPCWSTR pipeName = TEXT(PIPE_NAME);
		HANDLE hPipe;
		if ((hPipe = CreateFile(pipeName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL)) == INVALID_HANDLE_VALUE)
			throw ERROR_CREATEFILE;

		char outBuff[BUF_SIZE] = "hello server";
		DWORD dwBytesWritten = 0;
		if (!WriteFile(hPipe, outBuff, sizeof(outBuff), &dwBytesWritten, NULL))
			throw ERROR_TRANSACTNAMEDPIPE;

		char inBuff[BUF_SIZE] = "";
		DWORD dwBytesRead = 0;
		if (!ReadFile(hPipe, inBuff, sizeof(inBuff), &dwBytesRead, NULL))
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
