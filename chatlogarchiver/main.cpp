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
void DebugLog(std::wstring content);
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

	DebugLog(L"Starting plugin and verifying configuration file;");
	if (std::ifstream("chatlogarchiver.ini"))
	{
		DebugLog(L"Configuration file found, reading settings;");
		//file exists, proceed to extract the path.
		WCHAR output[MAX_PATH];
		GetPrivateProfileString(L"settings", L"path", NULL, output, MAX_PATH, L".\\chatlogarchiver.ini");

		DebugLog(L"Checking directory;");
		//check if the path is valid, by checking if the directory exists.
		if (DirectoryExists(output))
		{
			DebugLog(L"Directory found;");
			path = output; //path receives the value from the output.

						   //create a variable to check if the archive folder exists.
			std::wstring folder(path + L"\\archive");
			std::wcout << folder << std::endl;

			//check if the archive folder does not exists
			if (!DirectoryExists(folder.c_str()))
			{
				DebugLog(L"Creating archive folder;");
				//makes the archive folder.
				CreateDirectory(folder.c_str(), NULL);
			}

		}
		else {
			//if directory isn't valid we must kill the process.
			DebugLog(L"Directory is not valid, check the configuration file;");
			FreeLibrary(processModule);
			Beep(750, 300);
		}
	}
	else {
		//kills the DLL
		DebugLog(L"Configuration file not found, please create a \"chatlogarchiver.ini\" file;");
		FreeLibrary(processModule);
		Beep(750, 300);
	}
	
}

std::wstring getCurrentTime()
{
	time_t rawTime; tm * timeInfo;
	
	time(&rawTime); timeInfo = localtime(&rawTime);

	char output[100];
	size_t l = strftime(output, sizeof(output), "%Y-%m-%d - %Hh%Mm%Ss", timeInfo);

	return std::wstring(output, output + strlen(output));
}

void EndPlugin()
{
	DebugLog(L"Closing the plugin;");

	//joins all together to create the destination path and source path.
	std::wstring destination(path + L"\\archive\\" + getCurrentTime() + L".txt");
	std::wstring source(path + L"\\chatlog.txt");


	DebugLog(L"Copying file to destination folder;");
	//finishes up by copying the file to destination path.
	CopyFile(source.c_str(), destination.c_str(), FALSE);
}

void DebugLog(std::wstring content)
{
	std::wofstream logfile;
	logfile.open("chatlogarchiver.log", std::ios::app);
	logfile << L"[" + getCurrentTime() + L"] " + content << std::endl;
	logfile.close();
}