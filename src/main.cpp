#include <iostream>
#include "net/McClient.h"
#include "model/Section.h"

int main() {
    McClient client;
    client.Connect("DevClient", "localhost", 25565);
    return 0;
}