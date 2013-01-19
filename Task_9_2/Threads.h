#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <Windows.h>

using namespace std;

const BYTE THR_COUNT	= 2;	//counnt of threads
const BYTE ARR_SIZE		= 12;	//size of an array of digits

CRITICAL_SECTION gCrSec;	//critical section

//debug
#define CheckPtr(ptr)						\
{											\
	if(!ptr)								\
	{										\
		cout<<"\nError! Bad pointer!\n";	\
		exit(0);							\
	}										\
}

//paired
DWORD WINAPI Pair(LPVOID arr)
{
	CheckPtr(arr);
	int *tmp = (int*)arr;	//get pointer

	BYTE i = 2;
	while(i < ARR_SIZE)
	{
		
		EnterCriticalSection(&gCrSec);

		tmp[i] = tmp[i] + tmp[i - 2];
		i += 2;

		LeaveCriticalSection(&gCrSec);
		Sleep(1);
	}
	
	return NULL;
}

//unpaired
DWORD WINAPI UnPair(LPVOID arr)
{
	CheckPtr(arr);
	int *tmp = (int*)arr;	//get pointer

	BYTE i = 3;
	while(i < ARR_SIZE)
	{
		
		EnterCriticalSection(&gCrSec);

		tmp[i] = tmp[i] + tmp[i - 2];
		i += 2;

		LeaveCriticalSection(&gCrSec);
		Sleep(1);

	}
	return NULL;
}


//useful methods
void ShowArr(int* arr)
{
	CheckPtr(arr);

	BYTE i = 0;
	cout<<"\nArray : ";
	while( i < ARR_SIZE)
	{
		cout<<arr[i]<<", ";
		++i;
	}
	cout<<'\n';
}
#endif /*THREAD_H*/