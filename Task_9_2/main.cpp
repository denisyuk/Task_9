#include "Threads.h"

void main(void)
{
	DWORD idThr[THR_COUNT];
	HANDLE hThr[THR_COUNT];

	int arr[ARR_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12};

	//initialize of critical section
		InitializeCriticalSection(&gCrSec);

	//show array
		ShowArr(arr);

	//creates threads
	hThr[0] = CreateThread(NULL, NULL, Pair,arr, NULL, &idThr[0]);
	hThr[1] = CreateThread(NULL, NULL, UnPair,arr, NULL, &idThr[1]);


	BYTE i = 0;
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

	WaitForMultipleObjects(2, hThr, true, INFINITE);

	//show result
		ShowArr(arr);

	//release memory
		DeleteCriticalSection(&gCrSec);

	i = 0;
	while(i < THR_COUNT)
	{
		CloseHandle(hThr[i]);
		++i;
	}

	system("pause");
}