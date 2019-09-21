#include <iostream>
#include "net/McClient.h"

int main() {
    McClient client;
    client.Connect("DevClient", "localhost", 25565);
    return 0;
}