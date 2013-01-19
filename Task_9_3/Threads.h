#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <Windows.h>

using namespace std;

const BYTE THR_COUNT	= 4;	//counnt of threads
const BYTE ARR_SIZE		= 12;	//size of an array of digits
const BYTE WAIT_TIME	= 50;	//waiting time
const BYTE MAX_VALUE	= 241;	//maximum value that will be vanished

HANDLE hEv[THR_COUNT];	//events

//debug
#define CheckPtr(ptr)						\
{											\
	if(!ptr)								\
	{										\
		cout<<"\nError! Bad pointer!\n";	\
		exit(0);							\
	}										\
}

//adds 3
DWORD WINAPI AddFirst(LPVOID bReg)
{
	CheckPtr(bReg);
	BYTE *tmp = (BYTE*)bReg;	//get pointer

	while(1)
	{
		WaitForSingleObject(hEv[0], INFINITE);
		ResetEvent(hEv[0]);

		*tmp += 3;

		Sleep(50);
		SetEvent(hEv[2]);
	}

	return NULL;
}

//adds 5
DWORD WINAPI AddSecond(LPVOID bReg)
{
	CheckPtr(bReg);
	BYTE *tmp = (BYTE*)bReg;	//get pointer

	while(1)
	{
		WaitForSingleObject(hEv[1], INFINITE);
		ResetEvent(hEv[1]);

		*tmp += 5;

		Sleep(WAIT_TIME);
		SetEvent(hEv[3]);
	}

	return NULL;
}

//compare dividing for 12
DWORD WINAPI CmpDivAndShow(LPVOID bReg)
{
	CheckPtr(bReg);
	BYTE *tmp = (BYTE*)bReg;	//get pointer

	while(1)
	{
		WaitForSingleObject(hEv[2], INFINITE);
		ResetEvent(hEv[2]);

		if(*tmp % 12 == 0)
		{
			cout<<"\n"<<(int)*tmp;
		}

		Sleep(WAIT_TIME);
		SetEvent(hEv[1]);
	}

	return NULL;
}


//vanish
DWORD WINAPI Vanish(LPVOID bReg)
{
	CheckPtr(bReg);
	BYTE *tmp = (BYTE*)bReg;	//get pointer

	while(1)
	{
		WaitForSingleObject(hEv[3], INFINITE);
		ResetEvent(hEv[3]);

		if(*tmp > MAX_VALUE)
		{
			cout<<"\nVanish value..."<<(int)*tmp;
			*tmp = 1;
		}

		Sleep(WAIT_TIME);
		SetEvent(hEv[0]);
	}

	return NULL;
}

#endif /*THREAD_H*/