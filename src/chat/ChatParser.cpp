//
// Created by Twometer on 21/09/2019.
//

#include "ChatParser.h"
#include <json.hpp>
#include <iostream>

using namespace nlohmann;

ChatMessage *ChatParser::Parse(const char *jsonStr) {
    json j = json::parse(jsonStr);
    auto arr = j["extra"];
    for (auto &it : arr) {
        if (it.is_string()) {
            std::cout << it.get<std::string>() << '\n';
        } else {
            // TODO modifiers: bold, italic, underlined, obfuscated, color
            std::cout << it["text"].get<std::string>() << '\n';
        }
    }
    return nullptr;
}
