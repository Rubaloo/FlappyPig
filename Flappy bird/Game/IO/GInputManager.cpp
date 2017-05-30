//
//  GInputManager.cpp
//  Flapi Pig
//
//  Created by Ruben on 7/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#include "GInputManager.hpp"

GInputManager::GInputManager() {
    pthread_mutexattr_init(&mattr);
    pthread_mutex_init(&mutex, &mattr);
    messagesNumber = 0;
};
GInputManager::~GInputManager() {
    pthread_mutex_destroy(&mutex);
    pthread_mutexattr_destroy(&mattr);
};

void GInputManager::addInput(int a) {
    pthread_mutex_lock(&mutex);
    messages.push(a);
    ++messagesNumber;
    pthread_mutex_unlock(&mutex);
};

int GInputManager::remove() {
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

int GInputManager::getInputsNumber() {
    int numMessages = -1;
    pthread_mutex_lock(&mutex);
    numMessages = messagesNumber;
    pthread_mutex_unlock(&mutex);
    return numMessages;
};
