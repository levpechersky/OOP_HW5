//
// Created by Omer on 9/21/2017.
//

#ifndef PART1_OOP5EVENTEXCEPTION_H
#define PART1_OOP5EVENTEXCEPTION_H

#include <exception>

class BaseException : public std::exception {};

class ObserverUnknownToSubject : public BaseException {};

class ObserverAlreadyKnownToSubject : public BaseException {};

#endif //PART1_OOP5EVENTEXCEPTION_H
