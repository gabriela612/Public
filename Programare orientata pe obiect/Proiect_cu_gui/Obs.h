#pragma once
#include <vector>

using namespace std;

class Observer {
    //friend Observable;
public:
    virtual void update() = 0;
};



class Observable {
    //friend Observer;
private:
    std::vector<Observer*> followers;
public:
    void add_follower(Observer* observer) {
        this->followers.push_back(observer);
    }
    void notifica() {
        for (auto follower : followers) {
            follower->update();
        }
    }
};