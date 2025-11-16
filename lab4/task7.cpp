#include <iostream>
#include <string>
using namespace std;

// Task structure
struct Task {
    int taskId;
    string taskName;
    int resourceId;  // Required resource ID (-1 if no resource needed)
    int arrivalTime;
    Task* next;
};

class TaskQueue
{
    Task* front;
    Task* rear;
    int taskCount;
    
    public:
    TaskQueue(){
        front = NULL;
        rear = NULL;
        taskCount = 0;
    }
    
    bool isEmp(){
        if (front == NULL)
            return true;
        else 
            return false;
    }
    
    void enqueue(int id, string name, int resource, int arrival){
        Task* newTask = new Task;
        newTask->taskId = id;
        newTask->taskName = name;
        newTask->resourceId = resource;
        newTask->arrivalTime = arrival;
        newTask->next = NULL;
        
        if (isEmp()){
            front = rear = newTask;
        }
        else {
            rear->next = newTask;
            rear = newTask;
        }
        taskCount++;
    }
    
    Task* dequeue(){
        Task* task = NULL;
        if (!isEmp()){
            task = new Task;
            task->taskId = front->taskId;
            task->taskName = front->taskName;
            task->resourceId = front->resourceId;
            task->arrivalTime = front->arrivalTime;
            task->next = NULL;
            
            Task* temp = front;
            front = front->next;
            if (front == NULL){
                rear = NULL;
            }
            delete temp;
            taskCount--;
        }
        return task;
    }
    
    void display(string queueName){
        if (isEmp()){
            cout << queueName << " is empty" << endl;
        }
        else {
            cout << "\n--- " << queueName << " ---\n";
            Task* temp = front;
            int position = 1;
            while (temp != NULL){
                cout << position << ". Task ID: " << temp->taskId << ", Name: " << temp->taskName;
                if (temp->resourceId != -1)
                    cout << ", Resource: " << temp->resourceId;
                cout << ", Arrival: " << temp->arrivalTime << endl;
                temp = temp->next;
                position++;
            }
            cout << "Total tasks: " << taskCount << endl;
        }
    }
    
    int getCount(){
        return taskCount;
    }
    
    ~TaskQueue(){
        while (!isEmp()){
            Task* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

class OSScheduler
{
    TaskQueue mainQueue;
    TaskQueue waitingQueue;
    bool resources[10];  // Resource availability (true = free, false = busy)
    int currentTime;
    
    public:
    OSScheduler(){
        for (int i = 0; i < 10; i++){
            resources[i] = true;  // All resources free initially
        }
        currentTime = 0;
    }
    
    void addTask(int id, string name, int resourceId){
        mainQueue.enqueue(id, name, resourceId, currentTime);
        cout << "Task " << id << " (" << name << ") added to main queue";
        if (resourceId != -1)
            cout << " requiring resource " << resourceId;
        cout << endl;
        currentTime++;
    }
    
    void processTask(){
        if (mainQueue.isEmp()){
            cout << "Main queue is empty, no tasks to process!" << endl;
            return;
        }
        
        Task* task = mainQueue.dequeue();
        
        // Check if task needs a resource
        if (task->resourceId != -1){
            // Check if resource is available
            if (resources[task->resourceId]){
                // Resource available, process task
                resources[task->resourceId] = false;  // Mark resource as busy
                cout << "\n--- Processing Task ---\n";
                cout << "Task ID: " << task->taskId << endl;
                cout << "Task Name: " << task->taskName << endl;
                cout << "Resource " << task->resourceId << " acquired" << endl;
                cout << "Task processed successfully!\n";
                
                // Free the resource after processing
                resources[task->resourceId] = true;
                delete task;
            }
            else {
                // Resource not available, move to waiting queue
                cout << "Resource " << task->resourceId << " is busy. Task " << task->taskId 
                     << " moved to waiting queue.\n";
                waitingQueue.enqueue(task->taskId, task->taskName, task->resourceId, task->arrivalTime);
                delete task;
            }
        }
        else {
            // No resource needed, process directly
            cout << "\n--- Processing Task ---\n";
            cout << "Task ID: " << task->taskId << endl;
            cout << "Task Name: " << task->taskName << endl;
            cout << "No resource required" << endl;
            cout << "Task processed successfully!\n";
            delete task;
        }
        currentTime++;
    }
    
    void checkWaitingQueue(){
        if (waitingQueue.isEmp()){
            cout << "No tasks in waiting queue\n";
            return;
        }
        
        // Try to move waiting tasks back to main queue if resources are free
        int count = waitingQueue.getCount();
        cout << "Checking waiting queue for available resources...\n";
        
        for (int i = 0; i < count; i++){
            Task* task = waitingQueue.dequeue();
            if (task != NULL){
                if (resources[task->resourceId]){
                    cout << "Resource " << task->resourceId << " is now free. Moving task " 
                         << task->taskId << " back to main queue.\n";
                    mainQueue.enqueue(task->taskId, task->taskName, task->resourceId, task->arrivalTime);
                }
                else {
                    // Still waiting, add back to waiting queue
                    waitingQueue.enqueue(task->taskId, task->taskName, task->resourceId, task->arrivalTime);
                }
                delete task;
            }
        }
    }
    
    void displayQueues(){
        mainQueue.display("Main Task Queue");
        waitingQueue.display("Waiting Queue");
    }
    
    void displayResources(){
        cout << "\n--- Resource Status ---\n";
        for (int i = 0; i < 10; i++){
            cout << "Resource " << i << ": " << (resources[i] ? "Free" : "Busy") << endl;
        }
    }
    
    void setResourceStatus(int resourceId, bool status){
        if (resourceId >= 0 && resourceId < 10){
            resources[resourceId] = status;
            cout << "Resource " << resourceId << " set to " << (status ? "Free" : "Busy") << endl;
        }
        else {
            cout << "Invalid resource ID! Valid range: 0-9\n";
        }
    }
};

int main(){
    cout << "Welcome to the world of problem solving 2 with umar usmani sap: 60199\n";
    cout << "Task 7: Operating System Task Scheduler\n\n";
    
    OSScheduler scheduler;
    int choice, taskId, resourceId;
    string taskName;
    
    do {
        cout << "\n--- OS Task Scheduler Menu ---\n";
        cout << "1. Add task to queue\n";
        cout << "2. Process next task\n";
        cout << "3. Display all queues\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice){
            case 1:
                cout << "Enter task ID: ";
                cin >> taskId;
                cin.ignore();
                cout << "Enter task name: ";
                getline(cin, taskName);
                cout << "Enter required resource ID (-1 for no resource, 0-9 for specific resource): ";
                cin >> resourceId;
                scheduler.addTask(taskId, taskName, resourceId);
                break;
            case 2:
                scheduler.processTask();
                break;
            case 3:
                scheduler.displayQueues();
                break;
            case 4:
                cout << "Exiting OS Task Scheduler. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 4);
    
    return 0;
}
