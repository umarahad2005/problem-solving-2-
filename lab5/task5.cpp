#include<iostream>
#include<string>
using namespace std;

class Player {
public:
    string name;
    bool inPenalty;
    Player* next;
    
    Player(string n) {
        name = n;
        inPenalty = false;
        next = NULL;
    }
};

class TurnSystem {
    Player* head;
    Player* current;
    bool clockwise;
    
public:
    TurnSystem() {
        head = NULL;
        current = NULL;
        clockwise = true;
    }
    
    // Add new player
    void addPlayer(string name) {
        Player* newPlayer = new Player(name);
        
        if(head == NULL) {
            head = newPlayer;
            newPlayer->next = newPlayer; // Circular
            current = newPlayer;
            cout << name << " joined the game" << endl;
            return;
        }
        
        // Find last player
        Player* temp = head;
        while(temp->next != head) {
            temp = temp->next;
        }
        
        temp->next = newPlayer;
        newPlayer->next = head;
        cout << name << " joined the game" << endl;
    }
    
    // Remove player who quit
    void removePlayer(string name) {
        if(head == NULL) {
            cout << "No players in game" << endl;
            return;
        }
        
        // If only one player
        if(head->next == head && head->name == name) {
            delete head;
            head = NULL;
            current = NULL;
            cout << name << " left the game" << endl;
            return;
        }
        
        // If head is to be removed
        if(head->name == name) {
            Player* temp = head;
            while(temp->next != head) {
                temp = temp->next;
            }
            
            Player* toDelete = head;
            temp->next = head->next;
            
            if(current == head) {
                current = head->next;
            }
            
            head = head->next;
            delete toDelete;
            cout << name << " left the game" << endl;
            return;
        }
        
        // Search for player
        Player* temp = head;
        while(temp->next != head && temp->next->name != name) {
            temp = temp->next;
        }
        
        if(temp->next == head) {
            cout << "Player not found" << endl;
            return;
        }
        
        Player* toDelete = temp->next;
        
        if(current == toDelete) {
            current = toDelete->next;
        }
        
        temp->next = temp->next->next;
        delete toDelete;
        cout << name << " left the game" << endl;
    }
    
    // Set penalty for player
    void setPenalty(string name, bool penalty) {
        if(head == NULL) {
            cout << "No players in game" << endl;
            return;
        }
        
        Player* temp = head;
        do {
            if(temp->name == name) {
                temp->inPenalty = penalty;
                if(penalty) {
                    cout << name << " is now in penalty" << endl;
                } else {
                    cout << name << " penalty removed" << endl;
                }
                return;
            }
            temp = temp->next;
        } while(temp != head);
        
        cout << "Player not found" << endl;
    }
    
    // Next turn (skip players in penalty)
    void nextTurn() {
        if(current == NULL) {
            cout << "No players in game" << endl;
            return;
        }
        
        int maxTries = 100; // Prevent infinite loop
        int tries = 0;
        
        do {
            if(clockwise) {
                current = current->next;
            } else {
                // Find previous player for counter-clockwise
                Player* temp = head;
                while(temp->next != current) {
                    temp = temp->next;
                }
                current = temp;
            }
            tries++;
        } while(current->inPenalty && tries < maxTries);
        
        if(current->inPenalty) {
            cout << "All players are in penalty!" << endl;
        } else {
            cout << "Current turn: " << current->name << endl;
        }
    }
    
    // Reverse direction
    void reverseDirection() {
        clockwise = !clockwise;
        cout << "Turn direction reversed! Now going " 
             << (clockwise ? "clockwise" : "counter-clockwise") << endl;
    }
    
    // Display all players
    void displayPlayers() {
        if(head == NULL) {
            cout << "No players in game" << endl;
            return;
        }
        
        cout << "\n=== Players ===" << endl;
        cout << "Direction: " << (clockwise ? "Clockwise" : "Counter-clockwise") << endl;
        
        Player* temp = head;
        int count = 1;
        do {
            string status = "";
            if(temp == current) status += " <- CURRENT TURN";
            if(temp->inPenalty) status += " [PENALTY]";
            
            cout << count++ << ". " << temp->name << status << endl;
            temp = temp->next;
        } while(temp != head);
    }
};

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    
    TurnSystem game;
    int choice;
    
    while(true) {
        cout << "\n=== Multi-Player Turn System ===" << endl;
        cout << "1. Add Player" << endl;
        cout << "2. Remove Player" << endl;
        cout << "3. Set Penalty" << endl;
        cout << "4. Remove Penalty" << endl;
        cout << "5. Next Turn" << endl;
        cout << "6. Reverse Direction" << endl;
        cout << "7. Display Players" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            string name;
            cout << "Enter player name: ";
            getline(cin, name);
            game.addPlayer(name);
        }
        else if(choice == 2) {
            string name;
            cout << "Enter player name to remove: ";
            getline(cin, name);
            game.removePlayer(name);
        }
        else if(choice == 3) {
            string name;
            cout << "Enter player name for penalty: ";
            getline(cin, name);
            game.setPenalty(name, true);
        }
        else if(choice == 4) {
            string name;
            cout << "Enter player name to remove penalty: ";
            getline(cin, name);
            game.setPenalty(name, false);
        }
        else if(choice == 5) {
            game.nextTurn();
        }
        else if(choice == 6) {
            game.reverseDirection();
        }
        else if(choice == 7) {
            game.displayPlayers();
        }
        else if(choice == 8) {
            cout << "Exiting game..." << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
