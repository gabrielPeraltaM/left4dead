//
// Created by ignacio on 6/10/23.
//

#include "BackgroundRenderer.h"

extern int SCREEN_WIDTH;

BackgroundRenderer::BackgroundRenderer(Renderer &renderer,
                                       std::vector<Character> &characters,
                                       int playerId)
    : renderer(renderer), characters(characters), playerId(playerId) {}

void BackgroundRenderer::render() {
  camera.x = (characters.at(playerId).getPosX() - SCREEN_WIDTH / 2) %
             (LEVEL_WIDTH - camera.w);
  skyCamera.x = ((characters.at(playerId).getPosX() - SCREEN_WIDTH / 2) / 3) %
                (LEVEL_WIDTH - camera.w);
  housesCamera.x =
      ((characters.at(playerId).getPosX() - SCREEN_WIDTH / 2) / 3 * 2) %
      (LEVEL_WIDTH - camera.w);
  // Keep camera in bounds
  if (camera.x < 0) {
    camera.x = 0;
    skyCamera.x = 0;
    housesCamera.x = 0;
  }
  cameraOffset = characters.at(playerId).getPosX() - SCREEN_WIDTH / 2;

  if (camera.x == 0 || cameraOffset < 0) {
    cameraOffset = 0;
  }

  // Show the Background
  renderer.Copy(sky, skyCamera, NullOpt);
  renderer.Copy(houses, housesCamera, NullOpt);
  renderer.Copy(wall, camera, NullOpt);
  renderer.Copy(floor, camera, NullOpt);

  // Set the characters position relative to the camera
  for (auto &character : characters) {
    if (character.getId() == playerId) {
      character.setCameraX((character.getPosX() - camera.x) %
                           (LEVEL_WIDTH - camera.w));
    } else {
      character.setCameraX(character.getPosX() - cameraOffset);
    }
    character.setCameraY(character.getPosY());
  }
}
BackgroundRenderer::~BackgroundRenderer() {}
