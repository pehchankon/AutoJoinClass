#include <fstream>
#include <cstdlib>
#include <string>
#include <windows.h>
#include <shellapi.h>
#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

void configure(),startClass(string duration, string link),check(),startOBS(),startZOOM();
string getCurTime(), getCurStatus();
bool Record = false;

int main()
{
	/*bool start = 0;
	cout << "Record?(0,1) :";
	cin >> Record;
	if (Record)
	{
		cout << "Start OBS?(0,1) :";
		cin >> start;
		if (start)
			startOBS();
	}*/
	configure();
	check();			
	return 0;
}

string getCurTime()					//return current system time
{
	time_t now = time(0);
   	string buffer = ctime(&now);
	string CurTime;
	for(int i=11; i<16; i++)
		CurTime.push_back(buffer.at(i));
	return CurTime;
}

string getCurStatus()				//return current system day+time				
{
	time_t now = time(0);
   	string buffer = ctime(&now);
	string CurTime;
	for(int i=0; i<16; i++)
	{
		CurTime.push_back(buffer.at(i));
		if(i==2)
			i=10;
	}
	return CurTime;
}				

void check()				//read file, check for class, call startClass fn
{
	string day{}, time{}, classlink{}, duration{}, temp{};
	ifstream TimeTable;
	TimeTable.open(".\\Assets\\timetable.csv");
	while (TimeTable)
	{
		getline(TimeTable, day, ',');
		getline(TimeTable, time, ',');
		getline(TimeTable, classlink, ',');
		getline(TimeTable, duration, '\n');
		if (getCurStatus() == (day + time))
		{
			TimeTable.close();
			startClass(duration, classlink);
			return;
		}
		cout << day+time << endl;
	}
	TimeTable.close();
	cout << "No Class at " << getCurStatus() << "." << endl;
	Sleep(600000);
	check();
}

void startClass(string duration,string link)		//start zoom, join class, record
{
	const int delay = 0;		//set to 0 for testing(in ms)
	cout << "wait for " << (float)delay / 1000 << "seconds." << endl;
	Sleep(delay);						
	startZOOM();				//to uncomment, change zoom directory in zoom.bat file
	ShellExecute(NULL, "open", link.c_str(), NULL, NULL, SW_SHOWNORMAL);
	cout << "Joined Class." << endl;
	if (Record)
	{
		cout << "Recording...";
		system("cd C:\\Program Files\\obs-studio\\OBSCommand && OBSCommand.exe/startrecording");
	}
	Sleep(stoi(duration.c_str()) * 60000 - delay);
	if (Record)
	{
		cout << "Stopping Recording...";
		system("cd C:\\Program Files\\obs-studio\\OBSCommand && OBSCommand.exe/stoprecording");
	}
	system("cd C:\\Windows\\System32&&taskkill /f /im zoom.exe");
	cout << "Exiting ZOOM...";
	check();
}

void configure()			//waits until time is multiple of 10
{
	int unit = 0;		//to change multiple of time
	char temp = 0;
	temp = getCurTime().at(4);
	cout << "Configuring...";
	while (getCurTime().at(4) == temp)
		Sleep(1000);
	temp = getCurTime().at(4);
	
	if (unit >= (temp - 48))
		Sleep(60000 * (unit - (temp - 48)));
	else
		Sleep(60000 * (10 + unit - (temp - 48)));
	
	cout << "Completed."<<endl;
}

void startOBS()			//creates an independent process
{
	//HANDLE hProcess;
	//HANDLE hThread;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD drProcessId = 0;
	DWORD dwThreadId = 0;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	BOOL bCreateProcess;
	bCreateProcess = CreateProcess(
		".\\Assets\\obs.bat",
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi);
	cout << "Started OBS." << endl;
}

void startZOOM()			//creates an independent process
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD drProcessId = 0;
	DWORD dwThreadId = 0;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	BOOL bCreateProcess;
	bCreateProcess = CreateProcess(
		".\\Assets\\zoom.bat",
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi);
	cout << "Started ZOOM." << endl;
}