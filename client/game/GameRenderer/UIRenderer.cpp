//
// Created by ignacio on 6/10/23.
//

#include "UIRenderer.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

UIRenderer::UIRenderer(Renderer &renderer, int health, int ammo, int score, int stamina) : renderer(renderer), health(health), ammo(ammo), score(score), stamina(stamina) {}

void UIRenderer::render() {
    int gapX = SCREEN_WIDTH * 0.05;
    int gapY = SCREEN_HEIGHT * 0.05;
    Uint8 alpha = 100;
    int frameWidth = 12.5 * (SCREEN_WIDTH / 100);
    int frameHeight = 4 * (SCREEN_HEIGHT / 150);

    // Render a red rectangle representing the health at top left corner
    renderer.SetDrawColor(255, 0, 0, alpha);
    renderer.FillRect(Rect(gapX, gapY, frameWidth, frameHeight));
    // Render a black border around the health bar
    renderer.SetDrawColor(0, 0, 0, alpha);
    renderer.DrawRect(Rect(gapX, gapY, frameWidth, frameHeight));

    // Render a blue rectangle representing the stamina below the health bar
    renderer.SetDrawColor(0, 0, 255, alpha);
    renderer.FillRect(
            Rect(gapX, gapY + 1.5 * frameHeight, frameWidth, frameHeight));
    // Render a black border around the stamina bar
    renderer.SetDrawColor(0, 0, 0, alpha);
    renderer.DrawRect(
            Rect(gapX, gapY + 1.5 * frameHeight, frameWidth, frameHeight));

    // Render a green rectangle representing the ammo below the stamina bar
    renderer.SetDrawColor(0, 255, 0, alpha);
    renderer.FillRect(
            Rect(gapX, gapY + 3 * frameHeight, frameWidth, frameHeight));
    // Render a black border around the ammo bar
    renderer.SetDrawColor(0, 0, 0, alpha);
    renderer.DrawRect(
            Rect(gapX, gapY + 3 * frameHeight, frameWidth, frameHeight));

}