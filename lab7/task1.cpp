#include<iostream>
#include<string>
using namespace std;

struct Post {
    int id;
    string content;
    bool pinned;
};

class NewsFeed {
    Post posts[100];
    int count;
    int displayLimit;

public:
    NewsFeed() {
        count = 0;
        displayLimit = 5;
    }

    void addPost(int id, string content) {
        for(int i = count; i > 0; i--)
            posts[i] = posts[i-1];
        posts[0].id = id;
        posts[0].content = content;
        posts[0].pinned = false;
        count++;
    }

    void removePost(int id) {
        int index = -1;
        for(int i = 0; i < count; i++) {
            if(posts[i].id == id) {
                index = i;
                break;
            }
        }
        if(index != -1) {
            for(int i = index; i < count-1; i++)
                posts[i] = posts[i+1];
            count--;
            cout << "Post " << id << " removed" << endl;
        }
    }

    void pinPost(int id) {
        int index = -1;
        for(int i = 0; i < count; i++) {
            if(posts[i].id == id) {
                index = i;
                break;
            }
        }
        if(index != -1) {
            Post temp = posts[index];
            temp.pinned = true;
            for(int i = index; i > 0; i--)
                posts[i] = posts[i-1];
            posts[0] = temp;
            cout << "Post " << id << " pinned to top" << endl;
        }
    }

    void displayFeed() {
        cout << "\n--- News Feed ---" << endl;
        int limit = (displayLimit < count) ? displayLimit : count;
        for(int i = 0; i < limit; i++) {
            cout << "[" << (posts[i].pinned ? "PINNED" : "     ") << "] ";
            cout << "ID: " << posts[i].id << " | " << posts[i].content << endl;
        }
    }

    void loadMore() {
        displayLimit += 5;
        cout << "Loading more posts..." << endl;
        displayFeed();
    }
};

int main() {
    NewsFeed feed;
    
    feed.addPost(1, "Hello World!");
    feed.addPost(2, "My first post");
    feed.addPost(3, "Learning C++");
    feed.addPost(4, "Data Structures");
    feed.addPost(5, "Arrays are fun");
    feed.addPost(6, "News Feed System");
    
    feed.displayFeed();
    
    feed.pinPost(3);
    feed.displayFeed();
    
    feed.removePost(2);
    feed.displayFeed();
    
    feed.loadMore();
    
    return 0;
}
