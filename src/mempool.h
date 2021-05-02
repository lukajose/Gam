#include <vector>
#include <iostream>
#include <queue> 
using namespace std;
class Transaction {
    private:
        string from; // account owner
        string to;  // account receiver
        long double Gam; // gam is the currency of the network
        string signature; // verify valid owner
    public:
        float fee; // miner fee
        string signTransaction();

};



class MemPool {
    private:
        priority_queue<Transaction> transactions; // highest fee transactions have priorty in the network when mining
        string publicKey; // validates incoming transactions in the network
    public:
        MemPool();
        void operator+(Transaction t); // add transaction to pool
        void broadcastTransaction(Transaction t);
        void listenTransactions();
        Transaction _GetTransaction();



         
};