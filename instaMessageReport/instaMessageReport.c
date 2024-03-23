// instaMessageReport.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <string.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int userChoice = 0;
	wchar_t userFolder[260] = { '\0' }; // max size of cFileName

	printf_s("Instagram Message Report ...\n\n");
	printf_s("Please choose one of the following options:\n\n");
	printf_s("I would like to recieve a report for\n");
	printf_s("\t1) my entire messaging history\n");
	printf_s("\t2) a specific conversation\n\n");
	printf_s("Option: ");

	scanf_s("%d", &userChoice);

	if (userChoice != 1 && userChoice != 2) return 0;
	if (userChoice == 2) {
		printf_s("Please enter the folder name of the conversation (you may use the display name):\n");
		getchar(); //remove the newline character left in the buffer
		fgetws(userFolder, 259, stdin);

		HANDLE fileHandler = INVALID_HANDLE_VALUE; // initialize the file handler 
		WIN32_FIND_DATA fileInfo; // define the struct that will hold file information,
		// we will use the cFileName variable stored in this.


		fileHandler = FindFirstFile(L"D:/download 3/inbox-20240321T031829Z-001/inbox/*", &fileInfo);
		// ^ set the handler to the first file found under inbox. 

		int strSize = wcslen(userFolder)-1; // size exlcuding \n
		userFolder[strSize] = '\0'; // replace the \n character to a null terminator
		if (fileHandler == INVALID_HANDLE_VALUE) exit(-1); // before we continue, ensure such first file exists
		do {
			//fileInfo.cFileName[strSize] = '\0';
			if (wcsncmp(userFolder, fileInfo.cFileName, strSize)) continue;
			printf("%ws", fileInfo.cFileName);
			break;
		} while (FindNextFile(fileHandler, &fileInfo));
	}
	else {



		int amtFolders = 0;
		HANDLE fileHandler = INVALID_HANDLE_VALUE; // initialize the file handler 
		WIN32_FIND_DATA fileInfo; // define the struct that will hold file information,
		// we will use the cFileName variable stored in this.


		fileHandler = FindFirstFile(L"D:/download 3/inbox-20240321T031829Z-001/inbox/*", &fileInfo);
		// ^ set the handler to the first file found under inbox. 

		if (fileHandler == INVALID_HANDLE_VALUE) exit(-1); // before we continue, ensure such first file exists
		do {
			amtFolders++;
			printf("%ws\n", fileInfo.cFileName);
		} while (FindNextFile(fileHandler, &fileInfo));
	}

}

