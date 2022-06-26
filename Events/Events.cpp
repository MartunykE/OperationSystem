#include <iostream>
#include <windows.h>

HANDLE printEvent1;
HANDLE printEvent2;

HANDLE threads[2];

DWORD WINAPI PrintJob(LPVOID lpParam) {
	int id = *static_cast<int*>(lpParam);

	printf("Thread %d is waiting\n", GetCurrentThreadId());

	DWORD waiter = WaitForSingleObject(
		printEvent1,
		INFINITE);

	if (id == 1) {
		waiter = WaitForSingleObject(
			printEvent2,
			INFINITE);
	}

	if (waiter == WAIT_OBJECT_0) {
		for (size_t i = 0; i < 10; i++)
		{
			printf("Thread %d is working\n", GetCurrentThreadId());
			Sleep(500);
		}
	}

	if (id == 0) {
		//Run Next thread
		SetEvent(printEvent2);
	}

	return 1;
}

extern "C"
{
	int __declspec(dllexport) __stdcall EventsEntryPoint()
	{
		printEvent1 = CreateEvent(
			NULL,
			TRUE,
			FALSE,
			TEXT("printEvent1")
		);
		printEvent2 = CreateEvent(
			NULL,
			TRUE,
			FALSE,
			TEXT("printEvent2")
		);


		DWORD dwThreadID;

		printf("Creating threads \n");
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

		SetEvent(printEvent1);

		DWORD waitForThreads = WaitForMultipleObjects(
			2,
			threads,
			TRUE,
			INFINITE);
		return 0;
	}
}



