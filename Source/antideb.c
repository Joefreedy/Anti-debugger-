#include <windows.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
	unsigned char buffer[5];
	unsigned char patchbytes[] = { 0x6A, 0x08, 0x68, 0x60, 0x1E };
	DWORD pid = atoi (argv[1]);
	
	HANDLE hProc = OpenProcess (PROCESS_ALL_ACCESS, FALSE, pid);
	
	if (!hProc)
	{
		printf ("open failed\n");
		return -1;
	}
	
	ReadProcessMemory (hProc, (void*)0x7C951E13, buffer, 5, NULL);
	printf ("before: %02x %02x %02x %02x %02x \n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

	WriteProcessMemory (hProc, (void*)0x7C951E13, patchbytes, 5, NULL);
	
	FlushInstructionCache (hProc, NULL, 0);
	
	ReadProcessMemory (hProc, (void*)0x7C951E13, buffer, 5, NULL);
	printf ("after: %02x %02x %02x %02x %02x \n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

	CloseHandle (hProc);
	
	return 0;
}
