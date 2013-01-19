#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;

const BYTE THR_COUNT	= 15;	//counnt of threads
const BYTE COUNT_CH		= 26;
const BYTE STR_SIZE		= 4;	//size of a name of an event

HANDLE hEv[THR_COUNT];	//events

DWORD WINAPI ThFunc(LPVOID id)
{
	int i = *(int*)id;
	WaitForSingleObject(hEv[i], INFINITE);
	cout<<"\nThread : "<<i;
	return NULL;
}

void RandInt(int* arr)	//random integer digits
{
	srand((UINT)time(NULL));
	int iRandVal;
	int iFlag;
	for ( int i= 0; i<THR_COUNT; i++ ) 
	{
		for ( ; ; ) 
		{
			iRandVal = 0 + rand() % THR_COUNT;
			iFlag= 0;
			for (int  j= 0; j<i; j++ ) 
			{
				if ( iRandVal == arr[j] ) 
				{ 
					iFlag = 1; break; 
				}
			}
			if ( !iFlag ) 
			{ 
				break; 
			}
		}
		arr[i]= iRandVal;
	}
}

void RandStr(LPSTR* pNames)	//random string - uses for events name
{
	char res[STR_SIZE];
	int t;

	int i = 0, j = 0;
	while(i < THR_COUNT)
	{
		///
		memset(res, '\0', STR_SIZE);
		j = 0;
		while ( j < (STR_SIZE - 1))
		{
			res[j] = (t = rand() % (COUNT_CH * 2)) >= COUNT_CH ? 'a' + t % COUNT_CH : 'A' + t;
			++j;
		}
		///
		pNames[i] = new char[STR_SIZE];
		memcpy(pNames[i],res, sizeof(char) * STR_SIZE);
		++i;
	}
}

void ShowArr(int* arr)
{
	cout<<"\nArray: ";
	for(int i = 0; i < THR_COUNT; i++)
	{
		cout<<arr[i]<<", ";
	}
}

#endif /*THREAD_H*/
