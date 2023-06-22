#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

void moveFile(const string& sourcePath, const string& destinationPath) {
    if (!CreateDirectoryA(destinationPath.c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
        cerr << "> Error trying to create directory: " << GetLastError() << endl;
        return;
    }

    string destinationFile = destinationPath + "\\" + sourcePath.substr(sourcePath.find_last_of("\\/") + 1);
    if (!MoveFileA(sourcePath.c_str(), destinationFile.c_str())) {
        cerr << "> Error trying to move file: " << GetLastError() << endl;
    }
}

int main(int argc, char* argv[]) {
    string sourcePath;

    cout << "> Path: ";
    cin >> sourcePath;

    string searchPath = sourcePath + "\\*";

    WIN32_FIND_DATAA fileData;
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &fileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                string filePath = sourcePath + "\\" + fileData.cFileName;
                string fileName = fileData.cFileName;
                string fileExtension = fileName.substr(fileName.find_last_of('.') + 1);

                if (!fileExtension.empty()) {
                    string destinationPath = sourcePath + "\\" + fileExtension;
                    moveFile(filePath, destinationPath);
                }
            }
        } while (FindNextFileA(hFind, &fileData) != 0);
    }

    return 0;
}