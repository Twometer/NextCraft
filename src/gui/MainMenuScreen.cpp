//
// Created by twome on 30/05/2020.
//

#include <crystal/io/XmlGuiLoader.h>
#include <crystal/components/Button.h>
#include <crystal/CrystalUI.h>
#include "MainMenuScreen.h"
#include "../NextCraft.h"

MainMenuScreen::MainMenuScreen() : Screen("mainMenuScreen") {
    crystal::XmlGuiLoader::load(this, "assets/screens/MainMenu.xml");

    auto joinButton = find_component<crystal::Button>("btnJoinGame");
    auto exitButton = find_component<crystal::Button>("btnExitGame");
    joinButton->set_click_listener([]() {
        crystal::CrystalUI::get_instance()->get_gui_renderer()->show_screen(nullptr);
    });
    exitButton->set_click_listener([]() {
        NextCraft::Close();
    });
}
