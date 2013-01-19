#include "Threads.h"

void main(void)
{
	DWORD idThr[THR_COUNT];
	HANDLE hThr[THR_COUNT];

	LPCSTR EvNames[THR_COUNT] = {"Ev_1", "Ev_2", "Ev_3", "Ev_4"};

	BYTE bReg = 1;	//region for calculation

	BYTE i = 0;
	while(i < THR_COUNT)
	{
		hEv[i] = CreateEvent(NULL, false, false, EvNames[i]);
		++i;
	}

	//creates threads
	hThr[0] = CreateThread(NULL, NULL, AddFirst, &bReg, NULL, &idThr[0]);
	hThr[1] = CreateThread(NULL, NULL, AddSecond, &bReg, NULL, &idThr[1]);
	hThr[2] = CreateThread(NULL, NULL, CmpDivAndShow, &bReg, NULL, &idThr[2]);
	hThr[3] = CreateThread(NULL, NULL, Vanish, &bReg, NULL, &idThr[3]);


	i = 0;
	while(i < THR_COUNT)
	{
		if(!hThr[i])
		{
			cout<<"\nInvalid thread!\n";
			system("pause");
			return;
		}
		++i;
	}

	SetEvent(hEv[0]);

	WaitForMultipleObjects(4, hThr, true, INFINITE);


	//release memory
	i = 0;
	while(i < THR_COUNT)
	{
		CloseHandle(hThr[i]);
		++i;
	}

	system("pause");
}