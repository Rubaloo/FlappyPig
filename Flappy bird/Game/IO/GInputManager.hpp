#ifndef MessageManager_hpp
#define MessageManager_hpp

#include <queue>
#include <iostream>

class GInputManager
{
public:
    GInputManager();
    ~GInputManager();
    
    int Remove();
    int GetInputsNumber();
    
    void AddInput(int a);
private:
    pthread_mutex_t mutex;
    pthread_mutexattr_t mattr;
    std::queue<int> messages;
    
    int messagesNumber;
};

#endif /* MessageManager_hpp */
