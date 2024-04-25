/*
User
In c++ Write a program that invokes a specific system command, for example by running the program from the command line or executing a script.
ChatGPT
Sure, here's a simple C++ program that invokes a specific system command using the `system()` function:

```cpp
*/
#include <cstdlib> // for system()

int main() {
	// Replace "your_command_here" with the command you want to execute
	// For example, "ls -l" to list files in the current directory
	const char* command = "your_command_here";
	
	// Execute the command
	int returnCode = system(command);
	
	// Check if the command was executed successfully
	if (returnCode == 0) {
		std::cout << "Command executed successfully.\n";
	} else {
		std::cerr << "Command failed to execute.\n";
	}
	
	return 0;
}
/*
```

Replace `"your_command_here"` with the actual command you want to execute. For example, `"ls -l"` to list files in the current directory. Compile and run this program, and it will execute the specified command.
*/
