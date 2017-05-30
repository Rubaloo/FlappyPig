//
//  MessageManager.cpp
//  Flapi Pig
//
//  Created by Ruben on 7/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "MessageManager.hpp"

MessageManager::MessageManager() {
    pthread_mutexattr_init(&mattr);
    pthread_mutex_init(&mutex, &mattr);
    messagesNumber = 0;
};
MessageManager::~MessageManager() {
    pthread_mutex_destroy(&mutex);
    pthread_mutexattr_destroy(&mattr);
};

void MessageManager::add(int a) {
    pthread_mutex_lock(&mutex);
    messages.push(a);
    ++messagesNumber;
    pthread_mutex_unlock(&mutex);
};

int MessageManager::remove() {
    int num = -1;
    pthread_mutex_lock(&mutex);
    if(!messages.empty()) {
        num = messages.front();
        messages.pop();
        --messagesNumber;
    }
    pthread_mutex_unlock(&mutex);
    return num;
};

int MessageManager::getMessagesNumber() {
    int numMessages = -1;
    pthread_mutex_lock(&mutex);
    numMessages = messagesNumber;
    pthread_mutex_unlock(&mutex);
    return numMessages;
};
