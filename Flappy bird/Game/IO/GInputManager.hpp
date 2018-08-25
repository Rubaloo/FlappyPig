#ifndef MessageManager_hpp
#define MessageManager_hpp

#include <queue>
#include <stdio.h>
#include <iostream>
using namespace std;

class GInputManager {
public:
    GInputManager();
    ~GInputManager();
    
    int remove();
    void addInput(int a);
    int getInputsNumber();
    
private:
    pthread_mutex_t mutex;
    pthread_mutexattr_t mattr;
    queue<int> messages;
    int messagesNumber;
};

#endif /* MessageManager_hpp */
