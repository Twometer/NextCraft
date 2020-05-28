//
// Created by Twometer on 21/09/2019.
//

#include "ChatParser.h"
#include <nlohmann/json.hpp>

using namespace nlohmann;

std::string ChatParser::ToString(const char *jsonStr) {
    std::string str;
    json json = json::parse(jsonStr);

    auto arr = json["extra"];
    for (auto &it : arr) {
        if (it.is_string()) {
            str += it.get<std::string>();
        } else {
            // TODO modifiers: bold, italic, underlined, obfuscated, color
            str += it["text"].get<std::string>();
        }
    }

    if (str.length() == 0 && json["translate"] != nullptr) {
        str = json["translate"].get<std::string>();
    }

    return str;
}
