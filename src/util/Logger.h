//
// Created by twome on 26/01/2020.
//

#ifndef NEXTCRAFT_LOGGER_H
#define NEXTCRAFT_LOGGER_H

#include <string>

#define DEBUG

#ifdef DEBUG
#define glCheckErrors() \
            {int i = glGetError(); \
            if (i != GL_NO_ERROR) \
                printf("GL ERROR: %s:%i: %d\n", __FILE__, __LINE__, i);}
#else
#define glCheckErrors()
#endif

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
