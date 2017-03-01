/***************************************************************
*	        chatlogarchive.asi - made by Rebel0X               *
*                  version 1.0 ALPHA                           *
***************************************************************/



#include <iostream>
#include <Windows.h>

#include <fstream>
#include <string>
#include <time.h>

#pragma warning(disable:4996) //disables shitty warnings about time and shit who cares?

std::wstring path; //define strange shit to be used between the functions
void StartPlugin();
void EndPlugin();
HMODULE processModule;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//attaches to the game
		processModule = hModule;
		StartPlugin();
		break;
	case DLL_PROCESS_DETACH:
		//deattaches from the game
		EndPlugin();
		break;
	}
	return TRUE;
}

//costum function

BOOL DirectoryExists(LPCTSTR szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

//main functions

void StartPlugin()
{
	//read directory
	if (std::ifstream("chatlogarchiver.ini"))
	{
		//file exists, proceed to extract the path.
		WCHAR output[MAX_PATH];
		GetPrivateProfileString(L"settings", L"path", NULL, output, MAX_PATH, L".\\chatlogarchiver.ini");

		//check if the path is valid, by checking if the directory exists.
		if (DirectoryExists(output))
		{
			path = output; //path receives the value from the output.

						   //create a variable to check if the archive folder exists.
			std::wstring folder(path + L"\\archive");
			std::wcout << folder << std::endl;

			//check if the archive folder does not exists
			if (!DirectoryExists(folder.c_str()))
			{
				//makes the archive folder.
				CreateDirectory(folder.c_str(), NULL);
			}

		}
	}
	else {
		//kills the DLL
		FreeLibrary(processModule);
	}

}

void EndPlugin()
{
	//get the current time
	time_t rawTime;
	tm * timeInfo;

	time(&rawTime);
	timeInfo = localtime(&rawTime);
	//end

	//convert the current time to so it can be used as a file name.
	char filename[100];
	size_t l = strftime(filename, sizeof(filename), "%Y-%m-%d - %Hh%Mm%Ss.txt", timeInfo);
	std::wstring file(filename, filename + strlen(filename));

	//joins all together to create the destination path and source path.
	std::wstring destination(path + L"\\archive\\" + file);
	std::wstring source(path + L"\\chatlog.txt");

	//finishes up by copying the file to destination path.
	CopyFile(source.c_str(), destination.c_str(), FALSE);
}
