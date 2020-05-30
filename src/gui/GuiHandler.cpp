//
// Created by twome on 30/05/2020.
//

#include "GuiHandler.h"
#include "../NextCraft.h"
#include "../gl/Loader.h"

using namespace crystal;

void GuiHandler::set_cursor(Cursor cursor) {
    if (cursor != currentCursor) {
        currentCursor = cursor;
        if (cursor == Cursor::STANDARD)
            glfwSetCursor(NextCraft::window, standardCursor);
        else if (cursor == Cursor::IBEAM)
            glfwSetCursor(NextCraft::window, ibeamCursor);
    }
}

Texture *GuiHandler::load_texture(const std::string &path) {
    if (textures.count(path)) {
        return &textures[path];
    } else {
        Texture tex = Loader::LoadTexture("assets/textures/" + path + ".png");
        textures[path] = tex;
        return &textures[path];
    }
}

glm::vec2 GuiHandler::get_viewport_size() {
    const Viewport &viewport = NextCraft::GetViewport();
    return glm::vec2(viewport.width, viewport.height);
}

GuiHandler::GuiHandler() {
    standardCursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    ibeamCursor = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
}

void GuiHandler::Initialize() {
    crystal::CrystalUI::initialize(this, "assets/fonts/nirmala");
}
