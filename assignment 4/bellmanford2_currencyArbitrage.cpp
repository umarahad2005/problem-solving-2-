/*
 * Bellman-Ford Algorithm - Problem 2
 * Currency Arbitrage Detection (HackerRank/Interview Problem)
 * 
 * Problem: Given exchange rates between currencies, detect if there's an 
 * arbitrage opportunity (a cycle where you can profit by converting currencies).
 * This is solved by converting exchange rates to logarithms and finding negative cycles.
 */

#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<climits>
using namespace std;

struct CurrencyEdge {
    int from, to;
    double rate;
    double logRate; // -log(rate) for Bellman-Ford
    
    CurrencyEdge(int f, int t, double r) : from(f), to(t), rate(r) {
        logRate = -log(r); // Convert to additive (negative for Bellman-Ford)
    }
};

class CurrencyArbitrage {
    vector<string> currencies;
    vector<CurrencyEdge> edges;
    int numCurrencies;
    
public:
    CurrencyArbitrage() : numCurrencies(0) {}
    
    void addCurrency(string name) {
        currencies.push_back(name);
        numCurrencies++;
    }
    
    void addExchangeRate(int from, int to, double rate) {
        edges.push_back(CurrencyEdge(from, to, rate));
    }
    
    // Bellman-Ford to detect negative cycle (arbitrage opportunity)
    bool detectArbitrage(vector<int>& arbitrageCycle) {
        vector<double> dist(numCurrencies, 0); // Start with 0 for all
        vector<int> parent(numCurrencies, -1);
        
        // Relax all edges V-1 times
        for(int i = 0; i < numCurrencies - 1; i++) {
            for(int j = 0; j < edges.size(); j++) {
                int u = edges[j].from;
                int v = edges[j].to;
                double w = edges[j].logRate;
                
                if(dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                }
            }
        }
        
        // Check for negative cycle (arbitrage)
        for(int j = 0; j < edges.size(); j++) {
            int u = edges[j].from;
            int v = edges[j].to;
            double w = edges[j].logRate;
            
            if(dist[u] + w < dist[v]) {
                // Found negative cycle - trace it
                vector<bool> visited(numCurrencies, false);
                int current = v;
                
                // Go back to find a vertex in the cycle
                for(int k = 0; k < numCurrencies; k++) {
                    current = parent[current];
                }
                
                // Trace the cycle
                int cycleStart = current;
                arbitrageCycle.push_back(current);
                current = parent[current];
                
                while(current != cycleStart && arbitrageCycle.size() < numCurrencies) {
                    arbitrageCycle.push_back(current);
                    current = parent[current];
                }
                arbitrageCycle.push_back(cycleStart); // Complete the cycle
                
                return true; // Arbitrage found
            }
        }
        
        return false; // No arbitrage
    }
    
    void analyzeMarket() {
        cout << "\n=== CURRENCY ARBITRAGE ANALYSIS ===" << endl;
        cout << "Currencies in market: ";
        for(int i = 0; i < numCurrencies; i++) {
            cout << currencies[i];
            if(i < numCurrencies - 1) cout << ", ";
        }
        cout << endl;
        
        cout << "\nExchange rates:" << endl;
        for(int i = 0; i < edges.size(); i++) {
            cout << "  " << currencies[edges[i].from] << " -> " 
                 << currencies[edges[i].to] << ": " << edges[i].rate << endl;
        }
        
        vector<int> cycle;
        bool hasArbitrage = detectArbitrage(cycle);
        
        if(hasArbitrage) {
            cout << "\n*** ARBITRAGE OPPORTUNITY DETECTED! ***" << endl;
            cout << "Profitable cycle found:" << endl;
            
            if(!cycle.empty()) {
                cout << "  ";
                double totalMultiplier = 1.0;
                
                for(int i = cycle.size() - 1; i >= 0; i--) {
                    cout << currencies[cycle[i]];
                    if(i > 0) {
                        cout << " -> ";
                        // Find the exchange rate
                        for(int j = 0; j < edges.size(); j++) {
                            if(edges[j].from == cycle[i] && edges[j].to == cycle[i-1]) {
                                totalMultiplier *= edges[j].rate;
                                break;
                            }
                        }
                    }
                }
                cout << endl;
                
                cout << "\nStarting with 1000 " << currencies[cycle[cycle.size()-1]] << ":" << endl;
                cout << "After complete cycle: " << (1000 * totalMultiplier) << " " 
                     << currencies[cycle[cycle.size()-1]] << endl;
                cout << "Profit: " << ((totalMultiplier - 1) * 100) << "%" << endl;
            }
        } else {
            cout << "\nNo arbitrage opportunity found." << endl;
            cout << "Market is arbitrage-free." << endl;
        }
    }
    
    void clear() {
        currencies.clear();
        edges.clear();
        numCurrencies = 0;
    }
};

int main() {
    cout << "welcome to world of programming with umar usmani sap : 60199" << endl;
    cout << "Assignment 4 - Bellman-Ford Problem 2: Currency Arbitrage" << endl;
    cout << "==========================================================" << endl;
    
    CurrencyArbitrage market;
    int choice;
    
    while(true) {
        cout << "\n1. Example with Arbitrage (USD-EUR-GBP)" << endl;
        cout << "2. Example without Arbitrage" << endl;
        cout << "3. Complex Example (5 currencies)" << endl;
        cout << "4. Custom Input" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if(choice == 1) {
            market.clear();
            cout << "\nExample: Market with Arbitrage Opportunity" << endl;
            
            market.addCurrency("USD"); // 0
            market.addCurrency("EUR"); // 1
            market.addCurrency("GBP"); // 2
            
            // Arbitrage: 1 USD -> 0.9 EUR -> 0.8 GBP -> 1.5 USD = 1.08 USD
            market.addExchangeRate(0, 1, 0.9);   // USD to EUR
            market.addExchangeRate(1, 2, 0.8);   // EUR to GBP
            market.addExchangeRate(2, 0, 1.5);   // GBP to USD (creates arbitrage)
            market.addExchangeRate(1, 0, 1.1);   // EUR to USD
            market.addExchangeRate(2, 1, 1.2);   // GBP to EUR
            market.addExchangeRate(0, 2, 0.7);   // USD to GBP
            
            market.analyzeMarket();
        }
        else if(choice == 2) {
            market.clear();
            cout << "\nExample: Fair Market (No Arbitrage)" << endl;
            
            market.addCurrency("USD"); // 0
            market.addCurrency("EUR"); // 1
            market.addCurrency("JPY"); // 2
            
            // Fair rates (no arbitrage cycle)
            market.addExchangeRate(0, 1, 0.85);  // USD to EUR
            market.addExchangeRate(1, 0, 1.18);  // EUR to USD
            market.addExchangeRate(0, 2, 110);   // USD to JPY
            market.addExchangeRate(2, 0, 0.009); // JPY to USD
            market.addExchangeRate(1, 2, 130);   // EUR to JPY
            market.addExchangeRate(2, 1, 0.0077);// JPY to EUR
            
            market.analyzeMarket();
        }
        else if(choice == 3) {
            market.clear();
            cout << "\nComplex Example: 5 Currencies" << endl;
            
            market.addCurrency("USD"); // 0
            market.addCurrency("EUR"); // 1
            market.addCurrency("GBP"); // 2
            market.addCurrency("JPY"); // 3
            market.addCurrency("CHF"); // 4
            
            // Create some exchange rates with potential arbitrage
            market.addExchangeRate(0, 1, 0.92);
            market.addExchangeRate(1, 2, 0.86);
            market.addExchangeRate(2, 3, 180.0);
            market.addExchangeRate(3, 4, 0.0075);
            market.addExchangeRate(4, 0, 1.15);  // CHF to USD
            market.addExchangeRate(1, 0, 1.09);
            market.addExchangeRate(2, 1, 1.16);
            market.addExchangeRate(0, 3, 150.0);
            market.addExchangeRate(3, 0, 0.0067);
            
            market.analyzeMarket();
        }
        else if(choice == 4) {
            market.clear();
            
            int n, e;
            cout << "Enter number of currencies: ";
            cin >> n;
            cin.ignore();
            
            cout << "Enter currency names:" << endl;
            for(int i = 0; i < n; i++) {
                string name;
                cout << "Currency " << i << ": ";
                getline(cin, name);
                market.addCurrency(name);
            }
            
            cout << "Enter number of exchange rates: ";
            cin >> e;
            
            cout << "Enter exchange rates (from_index to_index rate):" << endl;
            for(int i = 0; i < e; i++) {
                int from, to;
                double rate;
                cout << "Rate " << (i+1) << ": ";
                cin >> from >> to >> rate;
                market.addExchangeRate(from, to, rate);
            }
            
            market.analyzeMarket();
        }
        else if(choice == 5) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
