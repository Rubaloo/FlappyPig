//
//  MessageManager.hpp
//  Flapi Pig
//
//  Created by Ruben on 7/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef MessageManager_hpp
#define MessageManager_hpp

#include <queue>
#include <stdio.h>
#include <iostream>
using namespace std;

class MessageManager {
public:
    MessageManager();
    ~MessageManager();
    
    void add(int a);
    int remove();
    int getMessagesNumber();
    
private:
    pthread_mutex_t mutex;
    pthread_mutexattr_t mattr;
    queue<int> messages;
    int messagesNumber;
};

#endif /* MessageManager_hpp */
