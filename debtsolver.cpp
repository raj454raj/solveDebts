#include<bits/stdc++.h>
using namespace std;

// ----------------------------------------------------------------------------------
int friends[100][100] = {0};
// Map name of the friend to his/her id
map<string, int> db;
// Map friend's id to his/her name
map<int, string> idToName;
// Total number of friends in all the transactions
int friendCount = 0;

// ----------------------------------------------------------------------------------
vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

// ----------------------------------------------------------------------------------
int toInt(string s) {
    int val;
    istringstream ss(s);
    ss >> val;
    return val;
}

// ----------------------------------------------------------------------------------
int getFriendId(int *amount, int op) {
    int ind = 1;
    for(int i = 2 ; i <= friendCount ; ++i) {
        if(op == 1) {
            if(amount[i] > amount[ind])
                ind = i;
        }
        else {
            if(amount[i] < amount[ind])
                ind = i;
        }
    }
    return ind;
}

// ----------------------------------------------------------------------------------
void minimumTransactions(int *amount) {

    int maxCredit = getFriendId(amount, 1);
    int maxDebit = getFriendId(amount, 2);

    // If maximum creditor and maximum debitor are done then return
    if(amount[maxCredit] == 0 && amount[maxDebit] == 0)
        return;

    // Find the absolute minimum
    int minAmount = min(-amount[maxDebit], amount[maxCredit]);

    // Maximum debtor pays minimum to maximum creditor
    amount[maxCredit] -= minAmount;
    amount[maxDebit] += minAmount;

    cout << idToName[maxDebit] << " should pay " << minAmount << " to " << idToName[maxCredit] << endl;
    
    // Recursively call until amount list becomes empty(all 0s)
    minimumTransactions(amount);

}

// ----------------------------------------------------------------------------------
int main() {

    string transaction;
    vector<string> elements;

    // Read from input until "done." is read
    while(true) {

        // Read the line in the form(without quotes, amount -> integer)
        // "friend1 owes friend2 amount"
        if(getline(cin, transaction)) {

            // Reading transactions end on a "done." note
            if(transaction == "done.")
                break;

            elements.clear();

            // Split the input transaction by spaces to parse them to friends and amount
            elements = split(transaction, ' ', elements);

            if(elements.size() != 4) {
                cout << "Invalid Input";
                break;
            }

            // If Friend not in database add him/her with an Id
            if(db.find(elements[0]) == db.end()) {
                db[elements[0]] = ++friendCount;
                idToName[friendCount] = elements[0];
            }

            // If Friend not in database add him/her with an Id
            if(db.find(elements[2]) == db.end()) {
                db[elements[2]] = ++friendCount;
                idToName[friendCount] = elements[2];
            }

            // Update the adjacency matrix of friends
            friends[db[elements[0]]][db[elements[2]]] += toInt(elements[3]);
        }

    }

    int *amount = (int *)calloc(friendCount + 1, sizeof(int));
    
    // Total amount to be paid to someone else
    // negative => You get that amount from someone else
    for(int i = 1 ; i <= friendCount ; ++i) {
        for(int j = 1 ; j <= friendCount ; ++j) {
            amount[i] += (friends[j][i] - friends[i][j]);
        }
    }

    // Find the minimum transactions required
    minimumTransactions(amount);
    
    return 0;
}

