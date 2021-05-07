# Custom Crypto Currency

A custom crypto currency in C++. The currency uses a similar p2p protocol as bitcoin. Instead of raw tcp the currency uses grpc.
The concencus mechanism used is proof of work. More on this later.

To compile and run in the root directory do:

```
g++ -o testchain src/*.cpp  -std=c++11 -stdlib=libc++
./testchain
```