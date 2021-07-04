
//
// Created by tobey on 7/4/2021.
//

#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

int find_pid_win10(char * process_name)
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    int process_pid;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (stricmp(entry.szExeFile, process_name) == 0)
            {
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

                process_pid = entry.th32ProcessID;
                CloseHandle(hProcess);
            }
        }
    }

    CloseHandle(snapshot);
    return process_pid;
}


int main(void)
{
    char name[] = "clion64.exe";

    int pid = find_pid_win10(name);

    printf("%i\n", pid);
    return 0;
}