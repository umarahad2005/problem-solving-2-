/*
 * Lab 9 - Task 4: Social Network Friend Recommendations
 * Binary tree for social connections with friend recommendations
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;

struct UserNode {
    int userId;
    string name;
    int interactionScore;          // 0-100
    vector<string> commonInterests;
    UserNode* left;                // Close connection
    UserNode* right;               // Acquaintance
    
    UserNode(int id, string n, int score = 50, vector<string> interests = {})
        : userId(id), name(n), interactionScore(score), 
          commonInterests(interests), left(nullptr), right(nullptr) {}
};

class SocialNetwork {
private:
    UserNode* root;
    
    // Find user by ID
    UserNode* findUser(UserNode* node, int id) {
        if (node == nullptr) return nullptr;
        if (node->userId == id) return node;
        
        UserNode* found = findUser(node->left, id);
        if (found) return found;
        return findUser(node->right, id);
    }
    
    // Find parent of a user
    UserNode* findParent(UserNode* node, int id, UserNode* parent = nullptr) {
        if (node == nullptr) return nullptr;
        if (node->userId == id) return parent;
        
        UserNode* found = findParent(node->left, id, node);
        if (found) return found;
        return findParent(node->right, id, node);
    }
    
    // Collect all users at specific depth from a user
    void collectAtDepth(UserNode* node, int targetDepth, int currentDepth, 
                        vector<UserNode*>& result, set<int>& visited) {
        if (node == nullptr || visited.count(node->userId)) return;
        
        if (currentDepth == targetDepth) {
            result.push_back(node);
            return;
        }
        
        visited.insert(node->userId);
        collectAtDepth(node->left, targetDepth, currentDepth + 1, result, visited);
        collectAtDepth(node->right, targetDepth, currentDepth + 1, result, visited);
    }
    
    // Calculate social influence score (post-order)
    int calculateInfluence(UserNode* node, map<int, int>& scores) {
        if (node == nullptr) return 0;
        
        int leftInfluence = calculateInfluence(node->left, scores);
        int rightInfluence = calculateInfluence(node->right, scores);
        
        // Influence = own interaction score + 0.3 * (sum of connections' influence)
        int influence = node->interactionScore + (int)(0.3 * (leftInfluence + rightInfluence));
        scores[node->userId] = influence;
        
        return influence;
    }
    
    // Find path between two users (BFS)
    vector<UserNode*> findPath(UserNode* start, int targetId) {
        if (start == nullptr) return {};
        
        queue<vector<UserNode*>> pathQueue;
        set<int> visited;
        
        pathQueue.push({start});
        visited.insert(start->userId);
        
        while (!pathQueue.empty()) {
            vector<UserNode*> path = pathQueue.front();
            pathQueue.pop();
            
            UserNode* current = path.back();
            
            if (current->userId == targetId) {
                return path;
            }
            
            // Explore connections
            if (current->left && visited.find(current->left->userId) == visited.end()) {
                visited.insert(current->left->userId);
                vector<UserNode*> newPath = path;
                newPath.push_back(current->left);
                pathQueue.push(newPath);
            }
            
            if (current->right && visited.find(current->right->userId) == visited.end()) {
                visited.insert(current->right->userId);
                vector<UserNode*> newPath = path;
                newPath.push_back(current->right);
                pathQueue.push(newPath);
            }
        }
        
        return {};  // No path found
    }
    
    // Count common interests
    int countCommonInterests(const vector<string>& a, const vector<string>& b) {
        int count = 0;
        for (const string& interest : a) {
            if (find(b.begin(), b.end(), interest) != b.end()) {
                count++;
            }
        }
        return count;
    }
    
    // Pre-order traversal helper
    void preOrderDisplay(UserNode* node, int indent) {
        if (node == nullptr) return;
        
        for (int i = 0; i < indent; i++) cout << "  ";
        cout << "|- " << node->name << " (ID:" << node->userId 
             << ", Score:" << node->interactionScore << ")" << endl;
        
        preOrderDisplay(node->left, indent + 1);
        preOrderDisplay(node->right, indent + 1);
    }
    
    // Collect users by interaction score
    void collectByScore(UserNode* node, vector<pair<int, UserNode*>>& users) {
        if (node == nullptr) return;
        
        collectByScore(node->left, users);
        users.push_back({node->interactionScore, node});
        collectByScore(node->right, users);
    }
    
    // Delete tree
    void deleteTree(UserNode* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    
public:
    SocialNetwork() : root(nullptr) {}
    
    ~SocialNetwork() {
        deleteTree(root);
    }
    
    // Add root user
    void addRootUser(int id, const string& name, int score, vector<string> interests) {
        if (root == nullptr) {
            root = new UserNode(id, name, score, interests);
            cout << "Root user '" << name << "' added." << endl;
        }
    }
    
    // Add close connection (left child)
    bool addCloseConnection(int parentId, int newId, const string& name, 
                           int score, vector<string> interests) {
        UserNode* parent = findUser(root, parentId);
        if (parent == nullptr) return false;
        
        if (parent->left == nullptr) {
            parent->left = new UserNode(newId, name, score, interests);
        } else {
            // Add as acquaintance to existing close connection
            UserNode* current = parent->left;
            while (current->right != nullptr) {
                current = current->right;
            }
            current->right = new UserNode(newId, name, score, interests);
        }
        cout << name << " added as close connection to " << parent->name << endl;
        return true;
    }
    
    // Add acquaintance (right child)
    bool addAcquaintance(int parentId, int newId, const string& name,
                        int score, vector<string> interests) {
        UserNode* parent = findUser(root, parentId);
        if (parent == nullptr) return false;
        
        if (parent->right == nullptr) {
            parent->right = new UserNode(newId, name, score, interests);
        } else {
            UserNode* current = parent->right;
            while (current->right != nullptr) {
                current = current->right;
            }
            current->right = new UserNode(newId, name, score, interests);
        }
        cout << name << " added as acquaintance to " << parent->name << endl;
        return true;
    }
    
    // Find friends of friends (2nd degree connections)
    vector<UserNode*> getFriendsOfFriends(int userId) {
        UserNode* user = findUser(root, userId);
        if (user == nullptr) return {};
        
        set<int> directFriends;
        set<int> visited;
        vector<UserNode*> fof;
        
        // Collect direct friends
        if (user->left) directFriends.insert(user->left->userId);
        if (user->right) directFriends.insert(user->right->userId);
        directFriends.insert(userId);  // Include self
        
        // Get friends of each direct friend
        auto collectFOF = [&](UserNode* friendNode) {
            if (friendNode == nullptr) return;
            if (friendNode->left && directFriends.find(friendNode->left->userId) == directFriends.end()) {
                fof.push_back(friendNode->left);
            }
            if (friendNode->right && directFriends.find(friendNode->right->userId) == directFriends.end()) {
                fof.push_back(friendNode->right);
            }
        };
        
        if (user->left) collectFOF(user->left);
        if (user->right) collectFOF(user->right);
        
        return fof;
    }
    
    // Recommend connections (max 5)
    void recommendConnections(int userId) {
        UserNode* user = findUser(root, userId);
        if (user == nullptr) {
            cout << "User not found!" << endl;
            return;
        }
        
        cout << "\n=== Friend Recommendations for " << user->name << " ===" << endl;
        
        vector<UserNode*> fof = getFriendsOfFriends(userId);
        
        // Score each potential connection
        vector<pair<int, UserNode*>> scored;
        for (UserNode* candidate : fof) {
            int score = 0;
            
            // Factor 1: Common interests
            score += countCommonInterests(user->commonInterests, candidate->commonInterests) * 20;
            
            // Factor 2: Interaction score similarity
            score += (100 - abs(user->interactionScore - candidate->interactionScore));
            
            scored.push_back({score, candidate});
        }
        
        // Sort by score (descending)
        sort(scored.begin(), scored.end(), [](const auto& a, const auto& b) {
            return a.first > b.first;
        });
        
        // Display top 5
        int count = min(5, (int)scored.size());
        if (count == 0) {
            cout << "No recommendations available." << endl;
            return;
        }
        
        cout << "Top " << count << " recommendations:" << endl;
        for (int i = 0; i < count; i++) {
            cout << (i + 1) << ". " << scored[i].second->name 
                 << " (Score: " << scored[i].first << ")" << endl;
        }
    }
    
    // Find shortest path between users
    void findShortestPath(int fromId, int toId) {
        UserNode* from = findUser(root, fromId);
        if (from == nullptr) {
            cout << "Source user not found!" << endl;
            return;
        }
        
        vector<UserNode*> path = findPath(from, toId);
        
        cout << "\n=== Shortest Path ===" << endl;
        if (path.empty()) {
            cout << "No path found between users." << endl;
            return;
        }
        
        cout << "Path length (degrees of separation): " << (path.size() - 1) << endl;
        cout << "Path: ";
        for (size_t i = 0; i < path.size(); i++) {
            if (i > 0) cout << " -> ";
            cout << path[i]->name;
        }
        cout << endl;
    }
    
    // Calculate social distance from a user (average degrees)
    void calculateAverageSocialDistance(int userId) {
        UserNode* user = findUser(root, userId);
        if (user == nullptr) return;
        
        cout << "\n=== Average Social Distance from " << user->name << " ===" << endl;
        
        queue<pair<UserNode*, int>> q;
        set<int> visited;
        int totalDistance = 0;
        int userCount = 0;
        
        q.push({user, 0});
        visited.insert(user->userId);
        
        while (!q.empty()) {
            UserNode* current = q.front().first;
            int distance = q.front().second;
            q.pop();
            
            if (current != user) {
                totalDistance += distance;
                userCount++;
            }
            
            if (current->left && visited.find(current->left->userId) == visited.end()) {
                visited.insert(current->left->userId);
                q.push({current->left, distance + 1});
            }
            if (current->right && visited.find(current->right->userId) == visited.end()) {
                visited.insert(current->right->userId);
                q.push({current->right, distance + 1});
            }
        }
        
        if (userCount > 0) {
            cout << "Average distance: " << (double)totalDistance / userCount << endl;
            cout << "Total reachable users: " << userCount << endl;
        }
    }
    
    // Level-order traversal (BFS) - friends at each degree
    void displayByDegree(int userId) {
        UserNode* user = findUser(root, userId);
        if (user == nullptr) return;
        
        cout << "\n=== Level-order: Friends by Degree of Separation ===" << endl;
        
        queue<pair<UserNode*, int>> q;
        set<int> visited;
        int currentLevel = -1;
        
        q.push({user, 0});
        visited.insert(user->userId);
        
        while (!q.empty()) {
            UserNode* current = q.front().first;
            int level = q.front().second;
            q.pop();
            
            if (level != currentLevel) {
                if (currentLevel != -1) cout << endl;
                cout << "Degree " << level << ": ";
                currentLevel = level;
            } else {
                cout << ", ";
            }
            
            cout << current->name;
            
            if (current->left && visited.find(current->left->userId) == visited.end()) {
                visited.insert(current->left->userId);
                q.push({current->left, level + 1});
            }
            if (current->right && visited.find(current->right->userId) == visited.end()) {
                visited.insert(current->right->userId);
                q.push({current->right, level + 1});
            }
        }
        cout << endl;
    }
    
    // Post-order: Calculate social influence scores
    void displayInfluenceScores() {
        cout << "\n=== Post-order: Social Influence Scores ===" << endl;
        
        map<int, int> scores;
        calculateInfluence(root, scores);
        
        // Sort by influence score
        vector<pair<int, int>> sorted(scores.begin(), scores.end());
        sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
        
        cout << "Key Influencers (sorted by influence):" << endl;
        for (const auto& p : sorted) {
            UserNode* user = findUser(root, p.first);
            if (user) {
                cout << "  " << user->name << ": " << p.second << " influence points" << endl;
            }
        }
    }
    
    // Pre-order: Display social network structure
    void displayPreOrder() {
        cout << "\n=== Pre-order: Social Network Structure ===" << endl;
        preOrderDisplay(root, 0);
    }
    
    // In-order: List users by interaction score
    void displayByInteractionScore() {
        cout << "\n=== In-order: Users by Interaction Score ===" << endl;
        
        vector<pair<int, UserNode*>> users;
        collectByScore(root, users);
        
        sort(users.begin(), users.end());
        
        for (const auto& p : users) {
            cout << p.second->name << ": " << p.first << " interaction score" << endl;
        }
    }
    
    // Identify social bridges
    void identifySocialBridges() {
        cout << "\n=== Social Bridges (Connecting Different Groups) ===" << endl;
        
        // A bridge is a user who connects otherwise disconnected groups
        // Simplified: users with both left and right children
        queue<UserNode*> q;
        if (root) q.push(root);
        
        vector<UserNode*> bridges;
        
        while (!q.empty()) {
            UserNode* current = q.front();
            q.pop();
            
            if (current->left && current->right) {
                bridges.push_back(current);
            }
            
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        
        if (bridges.empty()) {
            cout << "No social bridges identified." << endl;
        } else {
            for (UserNode* bridge : bridges) {
                cout << "  " << bridge->name << " connects: " 
                     << (bridge->left ? bridge->left->name : "none") << " <-> "
                     << (bridge->right ? bridge->right->name : "none") << endl;
            }
        }
    }
    
    // Export network for analysis
    void exportNetwork() {
        cout << "\n=== Network Export (Pre-order) ===" << endl;
        cout << "Format: UserID,Name,InteractionScore,Interests" << endl;
        cout << "---" << endl;
        
        queue<UserNode*> q;
        if (root) q.push(root);
        
        while (!q.empty()) {
            UserNode* current = q.front();
            q.pop();
            
            cout << current->userId << "," << current->name << "," 
                 << current->interactionScore << ",\"";
            
            for (size_t i = 0; i < current->commonInterests.size(); i++) {
                if (i > 0) cout << ";";
                cout << current->commonInterests[i];
            }
            cout << "\"" << endl;
            
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }
};

int main() {
    SocialNetwork network;
    
    // Build the social network as specified in the example
    network.addRootUser(1, "Alice", 85, {"photography", "travel", "music"});
    
    // Alice's connections
    network.addCloseConnection(1, 2, "Bob", 75, {"gaming", "music", "sports"});
    network.addAcquaintance(1, 3, "Charlie", 60, {"travel", "cooking", "books"});
    
    // Bob's connections
    network.addCloseConnection(2, 4, "David", 90, {"photography", "gaming", "tech"});
    network.addAcquaintance(2, 5, "Eve", 45, {"music", "art", "dance"});
    
    // Charlie's connections
    network.addCloseConnection(3, 6, "Frank", 70, {"travel", "photography", "nature"});
    network.addAcquaintance(3, 7, "Grace", 55, {"cooking", "books", "yoga"});
    
    // David's connections
    network.addCloseConnection(4, 8, "Henry", 65, {"gaming", "tech", "movies"});
    
    // Frank's connections
    network.addCloseConnection(6, 9, "Ivy", 80, {"travel", "music", "photography"});
    
    // Display network structure
    network.displayPreOrder();
    
    // Friend recommendations
    network.recommendConnections(1);  // For Alice
    network.recommendConnections(2);  // For Bob
    
    // Path analysis
    network.findShortestPath(1, 9);   // Alice to Ivy
    network.findShortestPath(2, 7);   // Bob to Grace
    
    // Social distance
    network.calculateAverageSocialDistance(1);  // From Alice
    
    // Friends by degree
    network.displayByDegree(1);  // From Alice
    
    // Influence scores
    network.displayInfluenceScores();
    
    // Social bridges
    network.identifySocialBridges();
    
    // Users by interaction score
    network.displayByInteractionScore();
    
    // Export network
    network.exportNetwork();
    
    // Friends of friends
    cout << "\n=== Friends of Friends for Alice ===" << endl;
    vector<UserNode*> fof = network.getFriendsOfFriends(1);
    for (UserNode* user : fof) {
        cout << "  - " << user->name << endl;
    }
    
    return 0;
}
