#include <iostream>
#include <windows.h>

HANDLE mutex;
HANDLE threads[2];

DWORD WINAPI PrintJob(LPVOID lpParam) {
	int id = *static_cast<int*>(lpParam);

	printf("Thread %d is waiting\n", GetCurrentThreadId());

	DWORD waiter = WaitForSingleObject(
		mutex,
		INFINITE);

	if (waiter == WAIT_OBJECT_0) {
		for (size_t i = 0; i < 10; i++)
		{
			printf("Thread %d is working\n", GetCurrentThreadId());
			Sleep(500);
		}
	}

	ReleaseMutex(mutex);

	return 1;
}

extern "C"
{
	int __declspec(dllexport) __stdcall MutexEntryPoint()
	{
		mutex = CreateMutex(
			NULL,
			FALSE,
			NULL);


		DWORD dwThreadID;

		printf("Creating threads  \n");
		for (int i = 0; i < 2; i++)
		{
			int* id = new int(i);
			threads[i] = CreateThread(
				NULL,
				0,
				PrintJob,
				id,
				0,
				&dwThreadID);
		}


		DWORD waitForThreads = WaitForMultipleObjects(
			2,
			threads,
			TRUE,
			INFINITE);
		return 0;
	}
}
