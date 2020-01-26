//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_LOGGER_H
#define NEXTCRAFT_LOGGER_H

#include <string>

class Logger {
private:
    static void Print(const std::string &prefix, const std::string &message);

public:
    static void Error(const std::string &message);

    static void Warning(const std::string &message);

    static void Info(const std::string &message);

    static void Debug(const std::string &message);
};


#endif //NEXTCRAFT_LOGGER_H
