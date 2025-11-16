#include<iostream>
#include<string>
using namespace std;

enum JobPriority {
    HIGH = 1,
    NORMAL = 2,
    LOW = 3
};

class PrintJob {
public:
    string username;
    string filename;
    int pages;
    JobPriority priority;
    PrintJob* next;
    
    PrintJob(string user, string file, int p, JobPriority pr) {
        username = user;
        filename = file;
        pages = p;
        priority = pr;
        next = NULL;
    }
};

class PrintSpooler {
    PrintJob* head;
    int totalJobs;
    
public:
    PrintSpooler() {
        head = NULL;
        totalJobs = 0;
    }
    
    // Add print job with priority
    void addPrintJob(string username, string filename, int pages, JobPriority priority) {
        PrintJob* newJob = new PrintJob(username, filename, pages, priority);
        totalJobs++;
        
        if(head == NULL) {
            head = newJob;
            cout << "Added print job: " << filename << " [" << getPriorityString(priority) << "]" << endl;
            return;
        }
        
        // Insert based on priority
        if(newJob->priority < head->priority) {
            newJob->next = head;
            head = newJob;
            cout << "Added print job: " << filename << " [" << getPriorityString(priority) << "]" << endl;
            return;
        }
        
        PrintJob* temp = head;
        while(temp->next != NULL && temp->next->priority <= newJob->priority) {
            temp = temp->next;
        }
        
        newJob->next = temp->next;
        temp->next = newJob;
        cout << "Added print job: " << filename << " [" << getPriorityString(priority) << "]" << endl;
    }
    
    // Process next job
    void processJob() {
        if(head == NULL) {
            cout << "No jobs in queue" << endl;
            return;
        }
        
        PrintJob* job = head;
        head = head->next;
        
        cout << "Printing: " << job->filename << " by " << job->username 
             << " (" << job->pages << " pages)" << endl;
        cout << "Job completed!" << endl;
        
        totalJobs--;
        delete job;
    }
    
    // Cancel specific job
    void cancelJob(string filename) {
        if(head == NULL) {
            cout << "No jobs in queue" << endl;
            return;
        }
        
        // If head is the job to cancel
        if(head->filename == filename) {
            PrintJob* temp = head;
            head = head->next;
            cout << "Cancelled job: " << filename << endl;
            totalJobs--;
            delete temp;
            return;
        }
        
        PrintJob* temp = head;
        while(temp->next != NULL && temp->next->filename != filename) {
            temp = temp->next;
        }
        
        if(temp->next == NULL) {
            cout << "Job not found" << endl;
            return;
        }
        
        PrintJob* toCancel = temp->next;
        temp->next = temp->next->next;
        cout << "Cancelled job: " << filename << endl;
        totalJobs--;
        delete toCancel;
    }
    
    // Requeue failed job
    void requeueJob(string username, string filename, int pages, JobPriority priority) {
        cout << "Printer error! Re-queueing job..." << endl;
        addPrintJob(username, filename, pages, priority);
    }
    
    // Count jobs per user
    int countUserJobs(string username) {
        int count = 0;
        PrintJob* temp = head;
        
        while(temp != NULL) {
            if(temp->username == username) {
                count++;
            }
            temp = temp->next;
        }
        
        return count;
    }
    
    // Fair scheduling check
    void checkFairness() {
        if(head == NULL) {
            cout << "No jobs in queue" << endl;
            return;
        }
        
        cout << "\n=== User Job Distribution ===" << endl;
        
        // Simple approach: count jobs per unique user
        PrintJob* temp = head;
        while(temp != NULL) {
            int userJobs = countUserJobs(temp->username);
            
            // Only print once per user
            bool alreadyPrinted = false;
            PrintJob* check = head;
            while(check != temp) {
                if(check->username == temp->username) {
                    alreadyPrinted = true;
                    break;
                }
                check = check->next;
            }
            
            if(!alreadyPrinted) {
                cout << temp->username << ": " << userJobs << " jobs";
                if(userJobs > 3) {
                    cout << " [WARNING: Heavy usage]";
                }
                cout << endl;
            }
            
            temp = temp->next;
        }
    }
    
    // Display queue
    void displayQueue() {
        if(head == NULL) {
            cout << "No jobs in queue" << endl;
            return;
        }
        
        cout << "\n=== Print Queue (Total: " << totalJobs << ") ===" << endl;
        
        PrintJob* temp = head;
        int position = 1;
        
        while(temp != NULL) {
            cout << position++ << ". " << temp->filename << " - " << temp->username 
                 << " (" << temp->pages << " pages) [" 
                 << getPriorityString(temp->priority) << "]" << endl;
            temp = temp->next;
        }
    }
    
private:
    string getPriorityString(JobPriority p) {
        if(p == HIGH) return "HIGH";
        if(p == NORMAL) return "NORMAL";
        return "LOW";
    }
};

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    
    PrintSpooler spooler;
    int choice;
    
    while(true) {
        cout << "\n=== Print Spooler Management ===" << endl;
        cout << "1. Add Print Job" << endl;
        cout << "2. Process Next Job" << endl;
        cout << "3. Cancel Job" << endl;
        cout << "4. Simulate Printer Error (Requeue)" << endl;
        cout << "5. Check Fair Scheduling" << endl;
        cout << "6. Display Queue" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            string username, filename;
            int pages, priorityNum;
            
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter filename: ";
            getline(cin, filename);
            cout << "Enter number of pages: ";
            cin >> pages;
            cout << "Enter priority (1=High, 2=Normal, 3=Low): ";
            cin >> priorityNum;
            
            spooler.addPrintJob(username, filename, pages, (JobPriority)priorityNum);
        }
        else if(choice == 2) {
            spooler.processJob();
        }
        else if(choice == 3) {
            string filename;
            cout << "Enter filename to cancel: ";
            getline(cin, filename);
            spooler.cancelJob(filename);
        }
        else if(choice == 4) {
            string username, filename;
            int pages, priorityNum;
            
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter filename: ";
            getline(cin, filename);
            cout << "Enter number of pages: ";
            cin >> pages;
            cout << "Enter priority (1=High, 2=Normal, 3=Low): ";
            cin >> priorityNum;
            
            spooler.requeueJob(username, filename, pages, (JobPriority)priorityNum);
        }
        else if(choice == 5) {
            spooler.checkFairness();
        }
        else if(choice == 6) {
            spooler.displayQueue();
        }
        else if(choice == 7) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
