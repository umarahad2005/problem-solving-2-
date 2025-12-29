#include<iostream>
#include<string>
using namespace std;

struct Task {
    int id;
    string sensorName;
    int priority;
    bool completed;
    Task* next;
};

class RoundRobinScheduler {
    Task* head;
    Task* current;
    int taskCount;

public:
    RoundRobinScheduler() {
        head = nullptr;
        current = nullptr;
        taskCount = 0;
    }

    void addTask(int id, string name, int priority) {
        Task* newTask = new Task();
        newTask->id = id;
        newTask->sensorName = name;
        newTask->priority = priority;
        newTask->completed = false;

        if(head == nullptr) {
            head = newTask;
            newTask->next = head;
            current = head;
        } else {
            Task* temp = head;
            while(temp->next != head)
                temp = temp->next;
            temp->next = newTask;
            newTask->next = head;
        }
        taskCount++;
        cout << "Task added: " << name << " (Priority: " << priority << ")" << endl;
    }

    void executeCurrentTask() {
        if(current == nullptr) {
            cout << "No tasks to execute!" << endl;
            return;
        }
        
        cout << "Executing: " << current->sensorName;
        for(int i = 0; i < current->priority; i++)
            cout << " [run " << i+1 << "]";
        cout << endl;
        
        current = current->next;
    }

    void removeTask(int id) {
        if(head == nullptr) return;

        Task* temp = head;
        Task* prev = nullptr;

        do {
            if(temp->id == id) {
                if(prev == nullptr) {
                    if(head->next == head) {
                        delete head;
                        head = nullptr;
                        current = nullptr;
                    } else {
                        Task* last = head;
                        while(last->next != head)
                            last = last->next;
                        head = head->next;
                        last->next = head;
                        if(current == temp) current = head;
                        delete temp;
                    }
                } else {
                    prev->next = temp->next;
                    if(current == temp) current = temp->next;
                    delete temp;
                }
                taskCount--;
                cout << "Task " << id << " removed" << endl;
                return;
            }
            prev = temp;
            temp = temp->next;
        } while(temp != head);
    }

    void markCompleted(int id) {
        Task* temp = head;
        if(temp == nullptr) return;
        
        do {
            if(temp->id == id) {
                temp->completed = true;
                cout << "Task " << id << " marked as completed" << endl;
                return;
            }
            temp = temp->next;
        } while(temp != head);
    }

    void displayTasks() {
        if(head == nullptr) {
            cout << "No tasks in queue" << endl;
            return;
        }
        
        cout << "\n--- Task Queue ---" << endl;
        Task* temp = head;
        do {
            cout << "ID: " << temp->id << " | " << temp->sensorName;
            cout << " | Priority: " << temp->priority;
            cout << " | " << (temp->completed ? "DONE" : "PENDING");
            if(temp == current) cout << " <-- Current";
            cout << endl;
            temp = temp->next;
        } while(temp != head);
    }

    void runCycle(int rounds) {
        cout << "\n--- Running " << rounds << " rounds ---" << endl;
        for(int i = 0; i < rounds; i++) {
            executeCurrentTask();
        }
    }
};

int main() {
    RoundRobinScheduler scheduler;
    
    scheduler.addTask(1, "Temperature Sensor", 2);
    scheduler.addTask(2, "Humidity Sensor", 1);
    scheduler.addTask(3, "Pressure Sensor", 3);
    scheduler.addTask(4, "Light Sensor", 1);
    
    scheduler.displayTasks();
    
    scheduler.runCycle(5);
    
    scheduler.markCompleted(2);
    scheduler.removeTask(2);
    
    scheduler.displayTasks();
    
    return 0;
}
