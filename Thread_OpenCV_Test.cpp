// Thread_OpenCV_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <thread>
#include <Windows.h>
#include <mutex>
#include <deque>

using namespace std;
int generateNumber(int x);
void loopingData(int x);
void getSizeandValue(int x);

std::mutex g_mutex1;
CRITICAL_SECTION g_cs1;
std::deque<int> g_dque;
int main()
{
	InitializeCriticalSection(&g_cs1);
	thread t1(loopingData, 5);
	thread t2(getSizeandValue,5);
	/*thread t3(loopingData, 5);
	thread t4(loopingData, 5);
	thread t5(loopingData, 5);
	thread t6(loopingData, 5);
	thread t7(loopingData, 5);
	thread t8(loopingData, 5);*/
	//SetThreadPriority(t1.native_handle(), THREAD_PRIORITY_HIGHEST);
	//SetThreadPriority(t1.native_handle(), THREAD_PRIORITY_HIGHEST);
	/*SetThreadPriority(t1.native_handle(), THREAD_PRIORITY_HIGHEST);
	SetThreadPriority(t2.native_handle(), THREAD_PRIORITY_HIGHEST);
	SetThreadPriority(t3.native_handle(), THREAD_PRIORITY_HIGHEST);
	SetThreadPriority(t4.native_handle(), THREAD_PRIORITY_HIGHEST);
	SetThreadPriority(t5.native_handle(), THREAD_PRIORITY_HIGHEST);
	SetThreadPriority(t6.native_handle(), THREAD_PRIORITY_HIGHEST);
	SetThreadPriority(t7.native_handle(), THREAD_PRIORITY_HIGHEST);
	SetThreadPriority(t8.native_handle(), THREAD_PRIORITY_HIGHEST);*/
//	t1.join();
	t1.detach();
	t2.join();
	//printf("Finished");
	/*t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();*/
	DeleteCriticalSection(&g_cs1);
	return 0;
}

void loopingData(int x)
{
	while (x > 0)
	{
		
		printf("Thread for pushback\n");
		if (TryEnterCriticalSection(&g_cs1))
		{
		
			
			g_dque.push_back(generateNumber(rand()));
		
			LeaveCriticalSection(&g_cs1);
			::Sleep(50);
			x--;
		}
	}
}


int generateNumber(int x)
{
	double x1 = rand();
	x1 = x1*x;
	x = x1;
	printf("\n x:%d",x);
	return (int)x1;
}

void getSizeandValue(int x)
{
	int a = 0;
	while (1)
	{
	//	printf("Thread for popfront\n");
		if (TryEnterCriticalSection(&g_cs1))
		{
			if (g_dque.size() > 0)
			{
				printf("\ndeque Size is : %d", g_dque.size());
				printf("\n Top elemet is : %d", g_dque.front());
				g_dque.pop_front();
				a++;
				::Sleep(50);
			}
			LeaveCriticalSection(&g_cs1);
		}
		if (a == x)
			break;
	}
}
