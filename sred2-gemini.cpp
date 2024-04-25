	/*
	Here are two ways to write a function that copies the contents of one file to another file in C++:
	1. Using C++17 std::filesystem::copy:
	
	C++
	*/
	#include <iostream>
	#include <filesystem>
	
	bool copy_file(const std::string& source, const std::string& destination) {
		try {
			std::filesystem::copy(source, destination);
			return true;
		} catch (const std::filesystem::filesystem_error& e) {
			std::cerr << "Error copying file: " << e.what() << std::endl;
			return false;
		}
	}
	
	int main() {
		if (copy_file("source.txt", "copy.txt")) {
			std::cout << "File copied successfully!" << std::endl;
		}
		return 0;
	}
	
	/*
	This approach uses the std::filesystem::copy function introduced in C++17. It provides a simple and efficient way to copy files. The function throws an exception if an error occurs during the copy process. The main function demonstrates how to use the copy_file function.
	2. Using traditional file streams:
	
	C++
	*/
	#include <iostream>
	#include <fstream>
	
	bool copy_file(const std::string& source, const std::string& destination) {
		std::ifstream source_file(source, std::ios::binary);
		std::ofstream destination_file(destination, std::ios::binary);
		
		if (!source_file.is_open() || !destination_file.is_open()) {
			std::cerr << "Error opening files!" << std::endl;
			return false;
		}
		
		char byte;
		while (source_file.get(byte)) {
			destination_file.put(byte);
		}
		
		source_file.close();
		destination_file.close();
		
		return true;
	}
	
	int main() {
		if (copy_file("source.txt", "copy.txt")) {
			std::cout << "File copied successfully!" << std::endl;
		}
		return 0;
	}
	
	
	This approach uses traditional file streams (std::ifstream and std::ofstream) to read from the source file and write to the destination file. It iterates through the source file character by character and writes it to the destination file. This method works for both text and binary files.
	Both methods achieve the same result of copying a file. The C++17 std::filesystem::copy function is generally preferred for its simplicity and exception handling. The traditional file stream approach offers more control over the copy process but requires more manual error checking.
