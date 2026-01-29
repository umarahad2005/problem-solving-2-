#include<iostream>
#include<string>
#include<ctime>
using namespace std;

// Hashtag structure with trending score
struct Hashtag {
    string tag;
    double points;
    int lastUpdateHour;
    
    Hashtag() : tag(""), points(0), lastUpdateHour(0) {}
    Hashtag(string t, double p, int h) : tag(t), points(p), lastUpdateHour(h) {}
};

class TrendingHashtagsHeap {
    Hashtag heap[10000];
    int size;
    int currentHour;
    
    // Find hashtag by name
    int findHashtag(string tag) {
        for(int i = 0; i < size; i++) {
            if(heap[i].tag == tag) return i;
        }
        return -1;
    }
    
    void heapifyUp(int index) {
        while(index > 0) {
            int parent = (index - 1) / 2;
            if(heap[index].points > heap[parent].points) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else break;
        }
    }
    
    void heapifyDown(int index) {
        while(true) {
            int largest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            
            if(left < size && heap[left].points > heap[largest].points)
                largest = left;
            if(right < size && heap[right].points > heap[largest].points)
                largest = right;
            
            if(largest == index) break;
            swap(heap[index], heap[largest]);
            index = largest;
        }
    }
    
    // Apply decay to a hashtag based on hours passed
    void applyDecay(int index) {
        int hoursPassed = currentHour - heap[index].lastUpdateHour;
        if(hoursPassed > 0) {
            for(int i = 0; i < hoursPassed; i++) {
                heap[index].points *= 0.9; // 10% decay per hour
            }
            heap[index].lastUpdateHour = currentHour;
        }
    }
    
public:
    TrendingHashtagsHeap() : size(0), currentHour(0) {}
    
    void advanceHour() {
        currentHour++;
        // Apply decay to all hashtags
        for(int i = 0; i < size; i++) {
            applyDecay(i);
        }
        // Rebuild heap after decay
        for(int i = size / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
        cout << "Time advanced. Decay applied to all hashtags." << endl;
    }
    
    void addTweet(string hashtag, bool isVerified) {
        int points = 1;
        if(isVerified) points += 2;
        
        int index = findHashtag(hashtag);
        
        if(index != -1) {
            applyDecay(index);
            heap[index].points += points;
            heap[index].lastUpdateHour = currentHour;
            // Reposition in heap
            heapifyUp(index);
            heapifyDown(index);
        } else {
            heap[size] = Hashtag(hashtag, points, currentHour);
            heapifyUp(size);
            size++;
        }
        
        cout << "Tweet with #" << hashtag << " (" << (isVerified ? "Verified" : "Regular") 
             << " user) - +" << points << " points" << endl;
    }
    
    void displayTop10() {
        cout << "\n=== TOP 10 TRENDING HASHTAGS ===" << endl;
        cout << "Current Hour: " << currentHour << endl;
        
        if(size == 0) {
            cout << "No hashtags yet!" << endl;
            return;
        }
        
        // Create temporary array for sorting
        Hashtag temp[10000];
        for(int i = 0; i < size; i++) {
            temp[i] = heap[i];
            // Apply decay for display
            int hoursPassed = currentHour - temp[i].lastUpdateHour;
            for(int j = 0; j < hoursPassed; j++) {
                temp[i].points *= 0.9;
            }
        }
        
        // Simple sort for top 10
        for(int i = 0; i < min(10, size); i++) {
            int maxIdx = i;
            for(int j = i + 1; j < size; j++) {
                if(temp[j].points > temp[maxIdx].points)
                    maxIdx = j;
            }
            swap(temp[i], temp[maxIdx]);
        }
        
        int count = min(10, size);
        for(int i = 0; i < count; i++) {
            cout << (i + 1) << ". #" << temp[i].tag 
                 << " - " << (int)temp[i].points << " points" << endl;
        }
    }
    
    int getSize() { return size; }
};

int main() {
    cout << "welcome to world of programming with umar usmani sap : 60199" << endl;
    cout << "Lab 12 Task 3: Twitter Trending Hashtags System" << endl;
    cout << "================================================" << endl;
    
    TrendingHashtagsHeap trending;
    int choice;
    
    while(true) {
        cout << "\n1. Add Tweet with Hashtag" << endl;
        cout << "2. Display Top 10 Trending" << endl;
        cout << "3. Advance Time (1 hour - apply decay)" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            string hashtag;
            char verified;
            cout << "Enter hashtag (without #): ";
            getline(cin, hashtag);
            cout << "Is verified user? (y/n): ";
            cin >> verified;
            trending.addTweet(hashtag, (verified == 'y' || verified == 'Y'));
        }
        else if(choice == 2) {
            trending.displayTop10();
        }
        else if(choice == 3) {
            trending.advanceHour();
        }
        else if(choice == 4) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
