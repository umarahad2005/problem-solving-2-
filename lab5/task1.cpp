#include<iostream>
#include<string>
using namespace std;

class Song {
public:
    string title;
    string artist;
    int duration; // in seconds
    Song* next;
    
    Song(string t, string a, int d) {
        title = t;
        artist = a;
        duration = d;
        next = NULL;
    }
};

class Playlist {
    Song* head;
    
public:
    Playlist() {
        head = NULL;
    }
    
    // Add song to end of playlist
    void addSong(string title, string artist, int duration) {
        Song* newSong = new Song(title, artist, duration);
        
        if(head == NULL) {
            head = newSong;
            cout << "Added '" << title << "' by " << artist << " to playlist" << endl;
            return;
        }
        
        Song* temp = head;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newSong;
        cout << "Added '" << title << "' by " << artist << " to playlist" << endl;
    }
    
    // Remove song by title
    void removeSong(string title) {
        if(head == NULL) {
            cout << "Playlist is empty" << endl;
            return;
        }
        
        // If head contains the song
        if(head->title == title) {
            Song* temp = head;
            head = head->next;
            cout << "Removed '" << title << "' from playlist" << endl;
            delete temp;
            return;
        }
        
        // Search for song
        Song* temp = head;
        while(temp->next != NULL && temp->next->title != title) {
            temp = temp->next;
        }
        
        if(temp->next == NULL) {
            cout << "Song '" << title << "' not found" << endl;
            return;
        }
        
        Song* toDelete = temp->next;
        temp->next = temp->next->next;
        cout << "Removed '" << title << "' from playlist" << endl;
        delete toDelete;
    }
    
    // Search songs by artist
    void searchByArtist(string artist) {
        if(head == NULL) {
            cout << "Playlist is empty" << endl;
            return;
        }
        
        Song* temp = head;
        bool found = false;
        
        cout << "\nSongs by " << artist << ":" << endl;
        while(temp != NULL) {
            if(temp->artist == artist) {
                cout << "- " << temp->title << " (" << temp->duration << "s)" << endl;
                found = true;
            }
            temp = temp->next;
        }
        
        if(!found) {
            cout << "No songs found by " << artist << endl;
        }
    }
    
    // Calculate total duration
    int getTotalDuration() {
        int total = 0;
        Song* temp = head;
        
        while(temp != NULL) {
            total += temp->duration;
            temp = temp->next;
        }
        
        return total;
    }
    
    // Reverse playlist
    void reversePlaylist() {
        if(head == NULL || head->next == NULL) {
            return;
        }
        
        Song* prev = NULL;
        Song* current = head;
        Song* next = NULL;
        
        while(current != NULL) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        head = prev;
        cout << "Playlist reversed" << endl;
    }
    
    // Display playlist
    void display() {
        if(head == NULL) {
            cout << "Playlist is empty" << endl;
            return;
        }
        
        cout << "\n=== Current Playlist ===" << endl;
        Song* temp = head;
        int count = 1;
        
        while(temp != NULL) {
            cout << count++ << ". " << temp->title << " - " << temp->artist 
                 << " (" << temp->duration << "s)" << endl;
            temp = temp->next;
        }
        
        int total = getTotalDuration();
        cout << "Total Duration: " << total << " seconds (" 
             << total/60 << "m " << total%60 << "s)" << endl;
    }
};

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    
    Playlist myPlaylist;
    int choice;
    
    while(true) {
        cout << "\n=== Music Playlist Manager ===" << endl;
        cout << "1. Add Song" << endl;
        cout << "2. Remove Song" << endl;
        cout << "3. Search by Artist" << endl;
        cout << "4. Show Total Duration" << endl;
        cout << "5. Reverse Playlist" << endl;
        cout << "6. Display Playlist" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            string title, artist;
            int duration;
            cout << "Enter song title: ";
            getline(cin, title);
            cout << "Enter artist name: ";
            getline(cin, artist);
            cout << "Enter duration (seconds): ";
            cin >> duration;
            myPlaylist.addSong(title, artist, duration);
        }
        else if(choice == 2) {
            string title;
            cout << "Enter song title to remove: ";
            getline(cin, title);
            myPlaylist.removeSong(title);
        }
        else if(choice == 3) {
            string artist;
            cout << "Enter artist name: ";
            getline(cin, artist);
            myPlaylist.searchByArtist(artist);
        }
        else if(choice == 4) {
            int total = myPlaylist.getTotalDuration();
            cout << "Total Playlist Duration: " << total << " seconds (" 
                 << total/60 << "m " << total%60 << "s)" << endl;
        }
        else if(choice == 5) {
            myPlaylist.reversePlaylist();
        }
        else if(choice == 6) {
            myPlaylist.display();
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
