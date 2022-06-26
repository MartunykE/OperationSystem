
#include <iostream>
#include <windows.h> 
#include <stdio.h> 

typedef int(__stdcall* MutexEntryPoint)();
typedef int(__stdcall* EventsEntryPoint)();
typedef int(__stdcall* SemaphoreEntryPoint)();

void Mutex() {
	printf("Mutex Start \n");

	HMODULE mutexDll = LoadLibraryA("Mutex.dll");

	MutexEntryPoint mutexEntryPoint = (MutexEntryPoint)GetProcAddress(mutexDll, "MutexEntryPoint");
	mutexEntryPoint();

	printf("Mutex End \n");
	printf("----------------------------------- \n \n");
}

void Events() {
	printf("Events Start \n");

	HMODULE eventsDll = LoadLibraryA("Events.dll");

	EventsEntryPoint eventsEntryPoint = (EventsEntryPoint)GetProcAddress(eventsDll, "EventsEntryPoint");
	eventsEntryPoint();

	printf("Events End \n");
	printf("----------------------------------- \n \n");
}


void Semaphore() {
	printf("Semaphore Start \n");

	HMODULE semaphoreDll = LoadLibraryA("Semaphore.dll");

	SemaphoreEntryPoint semaphoreEntryPoint = (SemaphoreEntryPoint)GetProcAddress(semaphoreDll, "SemaphoreEntryPoint");
	semaphoreEntryPoint();

	printf("Semaphore End \n");
	printf("----------------------------------- \n \n");
}

int main()
{
	Mutex();
	Events();
	Semaphore();
	
	return 0;
}