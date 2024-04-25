/*
User
	In c++ Write a function that creates a new file with the specified name in the current directory.
	ChatGPT
	Sure, here's a simple C++ function that creates a new file with the specified name in the current directory:
	
	```cpp
*/
#include <iostream>
	#include <fstream>
	
	void createFile(const std::string& fileName) {
		std::ofstream file(fileName.c_str());
		if (file.is_open()) {
			std::cout << "File created successfully: " << fileName << std::endl;
			file.close();
		} else {
			std::cerr << "Error creating file: " << fileName << std::endl;
		}
	}
	
	int main() {
		std::string fileName;
		std::cout << "Enter the name of the file to create: ";
		std::cin >> fileName;
		createFile(fileName);
		return 0;
	}
/*
	```
	
	This code defines a function `createFile` that takes a `std::string` parameter `fileName` and creates a new file with that name in the current directory using `std::ofstream`. The `main` function prompts the user to enter the name of the file they want to create and then calls the `createFile` function.
*/
