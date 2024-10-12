#include "File.hpp"
#include "Folder.hpp"
#include "iostream"

void MyTests(bool condition, const std::string& name){
    if(condition) {
        std::cout << "Test " << name << " passed" << std::endl;
    } else {
        std::cout << "Test " << name << " failed" << std::endl;
    }
}
int main() {
    File f1("file1.txt", "C1");
    File f2("file2.txt", "C2");
    f2 = f1; // Test Copy assignment
    MyTests(f2.getName() == "file1.txt" && f2.getContents() == "C1", "Copy Operator");

    File f3 = f1; // Test Copy constructor
    MyTests(f3.getName() == "file1.txt" && f3.getContents() == "C1", "Copy Constructor");


    File f4("file4.txt", "Content 4");
    f4 = std::move(f1); // Move assignment
   MyTests(f4.getName() == "file1.txt" && f4.getContents() == "C1", "Move Operator");

    File f5 = std::move(f2); // Move constructor
    MyTests(f5.getName() == "file1.txt" && f5.getContents() == "C1", "Move Constructor");

    // Test Invalid Filename Exception
    try {
        File invalidFile("invalid/name.txt", "Invalid content files");
        MyTests(false, "File Naming Exception");
    }
    catch (const InvalidFormatException&) {
        MyTests(true, "File Naming Exception");
    }

    // Test Add, Remove File in Folder and Folder Size
    Folder fol("TestFolder");
    fol.addFile(f4);
    fol.addFile(f5);
    MyTests(fol.getSize() == f4.getSize() + f5.getSize(), "Folder Get Size");
    MyTests(fol.removeFile("file1.txt"), "Remove File");
    MyTests(!fol.removeFile("nonexistent.txt"), "Remove File");
    Folder fol2("Folder2");
    fol.addFile(f4); 
    MyTests(fol.copyFileTo("file1.txt", fol2), "Copy File To");
    MyTests(fol.moveFileTo("file1.txt", fol2), "Move File To");

    std::cout << "All tests done!" << std::endl;

    return 0; 
}