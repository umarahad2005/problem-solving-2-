#include<iostream>
#include<string>
using namespace std;

struct FileNode {
    string name;
    bool isFolder;
    FileNode* next;
    FileNode* parent;
    FileNode* children;
};

class FileSystem {
    FileNode* root;
    FileNode* current;

public:
    FileSystem() {
        root = new FileNode();
        root->name = "root";
        root->isFolder = true;
        root->next = nullptr;
        root->parent = nullptr;
        root->children = nullptr;
        current = root;
    }

    void addFile(string name, bool isFolder) {
        FileNode* newFile = new FileNode();
        newFile->name = name;
        newFile->isFolder = isFolder;
        newFile->next = nullptr;
        newFile->parent = current;
        newFile->children = nullptr;

        if(current->children == nullptr)
            current->children = newFile;
        else {
            FileNode* temp = current->children;
            while(temp->next != nullptr)
                temp = temp->next;
            temp->next = newFile;
        }
    }

    void listFiles() {
        cout << "\nCurrent Directory: " << current->name << endl;
        cout << "-------------------" << endl;
        FileNode* temp = current->children;
        if(temp == nullptr) {
            cout << "(empty)" << endl;
            return;
        }
        while(temp != nullptr) {
            cout << (temp->isFolder ? "[DIR] " : "[FILE] ") << temp->name << endl;
            temp = temp->next;
        }
    }

    void navigateTo(string folderName) {
        FileNode* temp = current->children;
        while(temp != nullptr) {
            if(temp->name == folderName && temp->isFolder) {
                current = temp;
                cout << "Navigated to: " << folderName << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Folder not found!" << endl;
    }

    void goBack() {
        if(current->parent != nullptr) {
            current = current->parent;
            cout << "Returned to: " << current->name << endl;
        } else {
            cout << "Already at root!" << endl;
        }
    }

    void searchByName(string name) {
        cout << "Searching for: " << name << endl;
        FileNode* temp = current->children;
        bool found = false;
        while(temp != nullptr) {
            if(temp->name.find(name) != string::npos) {
                cout << "Found: " << temp->name << endl;
                found = true;
            }
            temp = temp->next;
        }
        if(!found) cout << "No files found!" << endl;
    }

    void searchByExtension(string ext) {
        cout << "Searching for *." << ext << endl;
        FileNode* temp = current->children;
        bool found = false;
        while(temp != nullptr) {
            if(temp->name.length() > ext.length()) {
                string fileExt = temp->name.substr(temp->name.length() - ext.length());
                if(fileExt == ext) {
                    cout << "Found: " << temp->name << endl;
                    found = true;
                }
            }
            temp = temp->next;
        }
        if(!found) cout << "No files found!" << endl;
    }

    void detectDuplicates() {
        cout << "\nChecking for duplicates..." << endl;
        FileNode* outer = current->children;
        bool found = false;
        while(outer != nullptr) {
            FileNode* inner = outer->next;
            while(inner != nullptr) {
                if(outer->name == inner->name) {
                    cout << "Duplicate found: " << outer->name << endl;
                    found = true;
                }
                inner = inner->next;
            }
            outer = outer->next;
        }
        if(!found) cout << "No duplicates found!" << endl;
    }
};

int main() {
    FileSystem fs;
    
    fs.addFile("Documents", true);
    fs.addFile("Pictures", true);
    fs.addFile("readme.txt", false);
    fs.addFile("notes.txt", false);
    fs.addFile("notes.txt", false);
    
    fs.listFiles();
    
    fs.navigateTo("Documents");
    fs.addFile("report.pdf", false);
    fs.addFile("project.cpp", false);
    fs.addFile("data.cpp", false);
    fs.listFiles();
    
    fs.searchByExtension("cpp");
    fs.searchByName("report");
    
    fs.goBack();
    fs.listFiles();
    
    fs.detectDuplicates();
    
    return 0;
}
