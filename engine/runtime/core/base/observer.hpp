//
// Created by xmmmmmovo on 2023/3/2.
//

#ifndef TAIXUENGINE_OBSERVER_HPP
#define TAIXUENGINE_OBSERVER_HPP

#include "noncopyable.hpp"

namespace taixu {

class IObserver : private noncopyable {
public:
    virtual void update() = 0;
};

class ISubject : private noncopyable {
public:
    virtual void attach(IObserver *observer) = 0;
    virtual void detach(IObserver *observer) = 0;
    virtual void notify()                    = 0;
};

}// namespace taixu

#endif//TAIXUENGINE_OBSERVER_HPP
