//
// Created by ignacio on 6/11/23.
//
#include "PlayerRenderer.h"

#include <filesystem>
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

PlayerRenderer::PlayerRenderer(std::vector<Character> &characters,
                               Renderer &renderer)
    : characters(characters), renderer(renderer) {
  loadTextures();
}

void PlayerRenderer::loadTextures() {
  std::string texturesPath = RESOURCE_PATH "/characters";

  for (const auto &characterEntry : std::filesystem::directory_iterator(texturesPath)) {
    std::string character_type = characterEntry.path().filename();
    for (const auto &actionEntry : std::filesystem::directory_iterator(texturesPath + "/" + character_type)) {
      std::string action = actionEntry.path().stem();
      std::string path =
          RESOURCE_PATH "/characters/" + character_type + "/" + action +".png";
      auto *texture = new Texture(renderer, path);
      textures[character_type + action] = texture;
    }
  }
}

void PlayerRenderer::render(int it) {
  for (auto &character : characters) {
    int x = character.getCameraX();

    // Check if character is out of screen
    if (x < -character.getFrameSize() || x > SCREEN_WIDTH) {
      continue;
    }

    int y = character.getCameraY();

    std::string character_type = character.getType();
    std::string action = character.getAction();
    Texture *texture = textures[character_type + action];

    int frameSize = character.getFrameSize();
    int n = texture->GetWidth() / frameSize;
    int frame = it % n;
    if (action == "Dead" && frame == n - 1) {
      character.kill();
    }
    if (character.isDead()) {
      frame = n - 1;
    }

    Rect srcRect = {frame * frameSize, 0, frameSize, frameSize};
    Rect dstRect = {x, y, frameSize * SCREEN_WIDTH / 1920,
                    frameSize * SCREEN_HEIGHT / 1080};

    renderer.Copy(*texture, srcRect, dstRect, 0, NullOpt, character.getFlip());
  }
}
PlayerRenderer::~PlayerRenderer() {
  for (auto &texture : textures) {
    delete texture.second;
  }
}
