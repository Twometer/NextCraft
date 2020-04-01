//
// Created by twome on 26/01/2020.
//

#include "Logger.h"

#include <iostream>

void Logger::Print(const std::string &prefix, const std::string &message) {
    std::cout << prefix << ": " << message << std::endl;
}

void Logger::Error(const std::string &message) {
    Print("Error", message);
}

void Logger::Warning(const std::string &message) {
    Print("Warning", message);
}

void Logger::Info(const std::string &message) {
    Print("Info", message);
}

void Logger::Debug(const std::string &message) {
    Print("Debug", message);
}