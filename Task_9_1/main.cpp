#include "Threads.h"

void main(void)
{
	DWORD idThr[THR_COUNT];	//id of threads
	HANDLE hThr[THR_COUNT];	//threads

	LPSTR EvName[THR_COUNT];// events

	int arr[THR_COUNT];// array of integer digit

	RandInt(arr);		//generates random integer digits
	RandStr(EvName);	//generates random names of events
	ShowArr(arr);		//show array of integer digits

	//creates events
	BYTE i = 0;
	while(i < THR_COUNT)
	{
		hEv[i] = CreateEvent(NULL, false, false, EvName[i]); 
		++i;
	}	

	//creates threads
	i = 0;
	while(i < THR_COUNT)
	{
		hThr[i] = CreateThread(NULL, NULL, ThFunc, &arr[i], NULL, &idThr[i]);
		++i;
	}

	//check threads
	i = 0;
	while(i < THR_COUNT)
	{
		if(!hThr[i])
		{
			cout<<"\nSome of threads is not created!\n";
			system("pause");
			return;
		}
		++i;
	}
	
	i = 0;
	while(i < THR_COUNT)
	{
		Sleep(1000);
		SetEvent(hEv[arr[i]]);	
		++i;
	}

	//release memory
	i = 0;
	while(i < THR_COUNT)
	{
		CloseHandle(hThr[i]);
		CloseHandle(hEv[i]);
		++i;
	}

	system("pause");
}