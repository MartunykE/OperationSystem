#include <iostream>
#include <windows.h>

HANDLE semaphore;
HANDLE threads[3];

DWORD WINAPI PrintJob(LPVOID lpParam) {
	int id = *static_cast<int*>(lpParam);

	printf("Thread %d is waiting\n", GetCurrentThreadId());

	DWORD waiter = WaitForSingleObject(
		semaphore,
		INFINITE);

	if (waiter == WAIT_OBJECT_0) {
		for (size_t i = 0; i < 10; i++)
		{
			printf("Thread %d is working\n", GetCurrentThreadId());
			Sleep(500);
		}
	}

	ReleaseSemaphore(semaphore, 1, NULL);

	return 1;
}

extern "C"
{
	int __declspec(dllexport) __stdcall SemaphoreEntryPoint()
	{
		semaphore = CreateSemaphore(
			NULL,
			2,
			2,
			NULL);

		DWORD dwThreadID;

		printf("Creating threads \n");
		for (int i = 0; i < 3; i++)
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
			3,
			threads,
			TRUE,
			INFINITE);
		return 0;
	}
}

