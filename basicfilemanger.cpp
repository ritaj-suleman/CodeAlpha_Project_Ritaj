//Basic File Manager

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;
namespace fs = std::filesystem;

void listDirectory(const std::string& path) {
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            cout << (entry.is_directory() ? "[DIR]  " : "[FILE] ")
                 << entry.path().filename().string() << '\n';
        }
    } catch (const fs::filesystem_error& e) {
        cerr << "Error: " << e.what() << '\n';
    }
}

void createDirectory(const std::string& path) {
    try {
        if (fs::create_directory(path)) {
            cout << "Directory created: " << path << '\n';
        } else {
            cerr << "Failed to create directory." << '\n';
        }
    } catch (const fs::filesystem_error& e) {
        cerr << "Error: " << e.what() << '\n';
    }
}

void viewFile(const std::string& path) {
    try {
        ifstream file(path);
        if (!file.is_open()) {
            cerr << "Error opening file." << '\n';
            return;
        }

        string line;
        while (getline(file, line)) {
            cout << line << '\n';
        }

        file.close();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
    }
}

void copyFile(const std::string& source, const std::string& destination) {
    try {
        fs::copy(source, destination);
        cout << "File copied to: " << destination << '\n';
    } catch (const fs::filesystem_error& e) {
        cerr << "Error: " << e.what() << '\n';
    }
}

void moveFile(const std::string& source, const std::string& destination) {
    try {
        fs::rename(source, destination);
        cout << "File moved to: " << destination << '\n';
    } catch (const fs::filesystem_error& e) {
        cerr << "Error: " << e.what() << '\n';
    }
}

int main() {
    string currentPath = fs::current_path().string();
    cout << "Welcome to the Command-Line File Manager" << '\n';

    while (true) {
        cout << "\nCurrent Directory: " << currentPath << '\n';
        cout << "Options: " << '\n';
        cout << "1. List directory contents" << '\n';
        cout << "2. Create directory" << '\n';
        cout << "3. View file" << '\n';
        cout << "4. Copy file" << '\n';
        cout << "5. Move file" << '\n';
        cout << "6. Change directory" << '\n';
        cout << "7. Exit" << '\n';
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            listDirectory(currentPath);
            break;
        case 2: {
            string dirName;
            cout << "Enter directory name: ";
            getline(cin, dirName);
            createDirectory(currentPath + "/" + dirName);
            break;
        }
        case 3: {
            string fileName;
            cout << "Enter file name: ";
            getline(cin, fileName);
            viewFile(currentPath + "/" + fileName);
            break;
        }
        case 4: {
            string source, destination;
            cout << "Enter source file: ";
            getline(cin, source);
            cout << "Enter destination path: ";
            getline(cin, destination);
            copyFile(currentPath + "/" + source, currentPath + "/" + destination);
            break;
        }
        case 5: {
            string source, destination;
            cout << "Enter source file: ";
            getline(cin, source);
            cout << "Enter destination path: ";
            getline(cin, destination);
            moveFile(currentPath + "/" + source, currentPath + "/" + destination);
            break;
        }
        case 6: {
            string newPath;
            cout << "Enter path to change directory: ";
            getline(cin, newPath);
            if (fs::exists(newPath) && fs::is_directory(newPath)) {
                currentPath = newPath;
                cout << "Changed directory to: " << currentPath << '\n';
            } else {
                cerr << "Invalid directory." << '\n';
            }
            break;
        }
        case 7:
            cout << "Exiting. Goodbye!" << '\n';
            return 0;
        default:
            cerr << "Invalid choice. Please try again." << '\n';
        }
    }
}

