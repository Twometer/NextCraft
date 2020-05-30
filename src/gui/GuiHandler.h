//
// Created by twome on 30/05/2020.
//

#ifndef NEXTCRAFT_GUIHANDLER_H
#define NEXTCRAFT_GUIHANDLER_H

#include <crystal/CrystalUI.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <map>

class GuiHandler : public crystal::IGuiHandler {
private:
    std::map<std::string, crystal::Texture> textures;

    GLFWcursor *standardCursor;
    GLFWcursor *ibeamCursor;
    crystal::Cursor currentCursor = crystal::Cursor::STANDARD;

public:
    GuiHandler();

    void Initialize();

    void set_cursor(crystal::Cursor cursor) override;

    crystal::Texture *load_texture(const std::string &path) override;

    glm::vec2 get_viewport_size() override;

};

#endif //NEXTCRAFT_GUIHANDLER_H
