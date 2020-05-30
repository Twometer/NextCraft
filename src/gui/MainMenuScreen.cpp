//
// Created by twome on 30/05/2020.
//

#include <crystal/io/XmlGuiLoader.h>
#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen() : Screen("mainMenuScreen") {
    crystal::XmlGuiLoader::load(this, "assets/screens/MainMenu.xml");
}
