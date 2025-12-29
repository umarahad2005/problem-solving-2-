#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct FormStep {
    string stepName;
    string data;
    bool validated;
    FormStep* prev;
    FormStep* next;
};

class FormWizard {
    FormStep* head;
    FormStep* current;
    string filename;

public:
    FormWizard(string file) {
        head = nullptr;
        current = nullptr;
        filename = file;
    }

    void addStep(string name) {
        FormStep* newStep = new FormStep();
        newStep->stepName = name;
        newStep->data = "";
        newStep->validated = false;
        newStep->prev = nullptr;
        newStep->next = nullptr;

        if(head == nullptr) {
            head = newStep;
            current = head;
        } else {
            FormStep* temp = head;
            while(temp->next != nullptr)
                temp = temp->next;
            temp->next = newStep;
            newStep->prev = temp;
        }
    }

    void fillCurrentStep(string data) {
        if(current != nullptr) {
            current->data = data;
            cout << "Data saved for: " << current->stepName << endl;
            autoSave();
        }
    }

    bool validateCurrentStep() {
        if(current != nullptr && current->data != "") {
            current->validated = true;
            cout << current->stepName << " validated!" << endl;
            return true;
        }
        cout << "Please fill in data before proceeding!" << endl;
        return false;
    }

    void nextStep() {
        if(current != nullptr && validateCurrentStep()) {
            if(current->next != nullptr) {
                current = current->next;
                cout << "Moved to: " << current->stepName << endl;
            } else {
                cout << "This is the last step!" << endl;
            }
        }
    }

    void previousStep() {
        if(current != nullptr && current->prev != nullptr) {
            current = current->prev;
            cout << "Went back to: " << current->stepName << endl;
            cout << "Saved data: " << current->data << endl;
        } else {
            cout << "This is the first step!" << endl;
        }
    }

    void autoSave() {
        ofstream file(filename);
        FormStep* temp = head;
        while(temp != nullptr) {
            file << temp->stepName << "|" << temp->data << "|" << temp->validated << endl;
            temp = temp->next;
        }
        file.close();
        cout << "(Progress auto-saved)" << endl;
    }

    void loadSavedProgress() {
        ifstream file(filename);
        if(!file.is_open()) {
            cout << "No saved progress found" << endl;
            return;
        }
        
        string line;
        FormStep* temp = head;
        while(getline(file, line) && temp != nullptr) {
            int pos1 = line.find("|");
            int pos2 = line.find("|", pos1+1);
            temp->data = line.substr(pos1+1, pos2-pos1-1);
            temp->validated = (line.substr(pos2+1) == "1");
            temp = temp->next;
        }
        file.close();
        cout << "Progress restored!" << endl;
    }

    void displayCurrentStep() {
        if(current != nullptr) {
            cout << "\n--- Current Step: " << current->stepName << " ---" << endl;
            cout << "Data: " << (current->data == "" ? "(empty)" : current->data) << endl;
            cout << "Status: " << (current->validated ? "Validated" : "Not validated") << endl;
        }
    }

    void displayAllSteps() {
        cout << "\n--- Form Progress ---" << endl;
        FormStep* temp = head;
        int stepNum = 1;
        while(temp != nullptr) {
            cout << stepNum << ". " << temp->stepName;
            cout << " [" << (temp->validated ? "DONE" : "PENDING") << "]";
            if(temp == current) cout << " <-- Current";
            cout << endl;
            temp = temp->next;
            stepNum++;
        }
    }

    void submitForm() {
        FormStep* temp = head;
        while(temp != nullptr) {
            if(!temp->validated) {
                cout << "Cannot submit! " << temp->stepName << " not completed." << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "\nForm submitted successfully!" << endl;
    }
};

int main() {
    FormWizard form("insurance_form.txt");
    
    form.addStep("Personal Information");
    form.addStep("Contact Details");
    form.addStep("Employment Info");
    form.addStep("Insurance Type");
    form.addStep("Payment Details");
    
    form.displayAllSteps();
    
    form.displayCurrentStep();
    form.fillCurrentStep("Name: Ali, Age: 25");
    form.nextStep();
    
    form.displayCurrentStep();
    form.fillCurrentStep("Phone: 123456789");
    form.nextStep();
    
    form.previousStep();
    form.displayCurrentStep();
    
    form.nextStep();
    form.fillCurrentStep("Company: TechCorp");
    form.nextStep();
    
    form.displayAllSteps();
    
    form.submitForm();
    
    return 0;
}
