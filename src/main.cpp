#include <iostream>
#include "net/McClient.h"

int main() {
    McClient client;
    client.Connect("DevClient", "localhost", 25565);

    while (true) {
        // Keep the app running
    }
    return 0;
}