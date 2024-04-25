/*
User
In c++ Write a function that copies the contents of one file to another file.
ChatGPT
Sure, here's a simple C++ function that copies the contents of one file to another file:

```cpp
*/
#include <iostream>
#include <fstream>

void copyFile(const std::string& sourceFileName, const std::string& destinationFileName) {
    std::ifstream sourceFile(sourceFileName, std::ios::binary);
    std::ofstream destinationFile(destinationFileName, std::ios::binary);

    if (!sourceFile.is_open()) {
        std::cerr << "Error opening source file: " << sourceFileName << std::endl;
        return;
    }

    if (!destinationFile.is_open()) {
        std::cerr << "Error opening destination file: " << destinationFileName << std::endl;
        return;
    }

    destinationFile << sourceFile.rdbuf();

    sourceFile.close();
    destinationFile.close();

    std::cout << "File copied successfully from " << sourceFileName << " to " << destinationFileName << std::endl;
}

int main() {
    std::string sourceFileName = "source.txt";
    std::string destinationFileName = "destination.txt";

    copyFile(sourceFileName, destinationFileName);

    return 0;
}
/*
```

This function `copyFile` takes two parameters: the source file name and the destination file name. It opens the source file for reading and the destination file for writing in binary mode. Then it copies the contents of the source file to the destination file using `rdbuf()` function which reads the entire content of the source file and writes it to the destination file. Finally, it closes both files and prints a message indicating successful copying.
*/

```

In this example, you can see that the build succeeded and the time taken for the build process is shown as "Time Elapsed". This will give you an indication of how long the compilation process took.
