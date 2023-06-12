//
// Created by ignacio on 6/11/23.
//

#include "PlayerRenderer.h"

PlayerRenderer::PlayerRenderer(std::vector<Character> &characters,
                               Renderer &renderer)
    : characters(characters), renderer(renderer) {
  loadTextures();
}

void PlayerRenderer::loadTextures() {
  // Load players textures
  std::string actions[] = {"Attack", "Dead",   "Hurt",   "Idle", "Recharge",
                           "Run",    "Shot_1", "Shot_2", "Walk"};
  std::string character_types[] = {"IDF", "P90", "Scout"};

  for (auto &character_type : character_types) {
    for (auto &action : actions) {
      std::string path =
          RESOURCE_PATH "/" + character_type + "/" + action + ".png";
      auto *texture = new Texture(renderer, path);
      textures[character_type + action] = texture;
    }
  }

  // Load zombies textures
  std::string zombies[] = {"Jumper", "Spear", "Venom", "Witch", "Zombie"};
  std::string zombie_actions[] = {"Attack_1", "Dead", "Hurt",
                                  "Idle",     "Run",  "Walk"};

  for (auto &zombie : zombies) {
    for (auto &action : zombie_actions) {
      std::string path = RESOURCE_PATH "/" + zombie + "/" + action + ".png";
      auto *texture = new Texture(renderer, path);
      textures[zombie + action] = texture;
    }
  }
}

void PlayerRenderer::render(int it) {
  for (auto &character : characters) {
    int x = character.getCameraX();
    int y = character.getCameraY();

    std::string character_type = character.getType();
    std::string action = character.getAction();
    Texture *texture = textures[character_type + action];

    int n = texture->GetWidth() / 128;
    int frame = it % n;
    int frameSize = character.getFrameSize();

    Rect srcRect = {frame * frameSize, 0, frameSize, frameSize};
    Rect dstRect = {x, y, frameSize, frameSize};

    renderer.Copy(*texture, srcRect, dstRect, 0, NullOpt, character.getFlip());
  }
}
PlayerRenderer::~PlayerRenderer() {
  for (auto &texture : textures) {
    delete texture.second;
  }
}
