# Simple Task Manager

For this project, I created a CLI tool that can manage processes on the Windows operating system. I created this project with C++ using the Windows API and Process Status API. It can display processes, relevant information about them, and terminate processes.

## Implementation

The two main functions of the program are listing various process information, and killing processes from the command line. 

Upon launching the program, all processes are listed, with the process name, PID, thread count, priority, and physical memory displayed. From there the user has 3 options: refresh processes, kill a process, or quit. If the user chooses to kill, they are prompted to enter a process name to be killed. The program will then loop through all the processes with that name and terminate all they can (Ex: chrome.exe often has multiple processes, so entering “chrome.exe” terminates all processes named “chrome.exe”). If the user chooses to quit, the program is terminated. 

I noticed while developing this project that creating a snapshot was repeating logic frequently. To combat this, I created a Snapshot struct and corresponding createSnapshot() function to clean up the code.

## Shortcomings

Initially, I planned to list CPU info and memory in the list of processes. However, I quickly came to realize that it was a bit easier said than done. Memory access for processes not owned by the user were not accessible by the Process Status API. This is because system processes were started by the kernel and the user does not have access to them. Processes that were system processes then displayed 0 KB of memory which is clearly not right. 

I decided to implement a check to display “Memory Access Denied” if variable memory was evaluated to 0 because a handle to a process was unable to be opened. CPU info was a similar issue, so I decided against displaying CPU usage.
