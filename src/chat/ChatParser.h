//
// Created by Twometer on 21/09/2019.
//

#ifndef NEXTCRAFT_CHATPARSER_H
#define NEXTCRAFT_CHATPARSER_H

#include "ChatMessage.h"

class ChatParser {
public:
    static ChatMessage *Parse(const char *json);

};


#endif //NEXTCRAFT_CHATPARSER_H
