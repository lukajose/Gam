#include <iostream>
#include <queue>
class Transaction {
    private:
        std::string from; // account owner
        std::string to;  // account receiver
        long double Gam; // gam is the currency of the network
        std::string signature; // verify valid owner
    public:
        float fee; // miner fee
        std::string signTransaction();

};
class MemPool {
    private:
        int maxClients;
        int * clientSockets;
        int clientIndex;
        std::priority_queue<Transaction> transactions; // highest fee transactions have priorty in the network when mining
        std::string publicKey; // validates incoming transactions in the network
    public:
        MemPool(int connSize);
        void operator+(Transaction t); // add transaction to pool
        void broadcastTransaction(Transaction t);
        int listenTransactions();
        Transaction _GetTransaction();
         
};