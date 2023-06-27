#include "Sender.h"

#include "common_src/actions.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

Sender::Sender(Socket &socket, bool &running)
    : socket(socket), running(running) {}

void Sender::run() {
  bool was_closed = false;
  SDL_Event event;

  while (running) {
    SDL_Delay(1000 / 60);
    action = keyboardHandler.getAction();

    /* Tendriamos que hacer asi, que cada vez que se presione una tecla
     * se envie la accion correspondiente, y que el server
     * se encargue de actualizar el estado del personaje.
     * También mandaría el IDLE, para que el server sepa que el cliente
     * no esta haciendo nada.
     *
     * LO QUE PUSO EL PROFE
     * okay, tiene sentido en este hilo
     * podrían cambiar la lectura del state por poll_event (y sacar el otro
    poll_event de main)
     * para no floodear la red, trackeen que keys ya apretaron (cosa de no
    volver a enviarlas)

    if (action && action != previous_action) {
  previous_action = action;
  socket.sendall(&action, sizeof(action), &was_closed);
  if (was_closed) {
    running = false;
    break;
  }

    }
     */


    if (action) {
      socket.sendall(&action, sizeof(action), &was_closed);
      if (was_closed) {
        running = false;
        break;
      }
    }

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_WINDOWEVENT) {
        switch (event.window.event) {
          case SDL_WINDOWEVENT_RESIZED:
            SCREEN_WIDTH = event.window.data1;
            SCREEN_HEIGHT = event.window.data2;
            break;
          case SDL_WINDOWEVENT_CLOSE:
            running = false;
            break;
        }
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          running = false;
          break;
        }
        keyboardHandler.setPressed(event.key.keysym.sym);
      } else if (event.type == SDL_KEYUP) {
        keyboardHandler.setReleased(event.key.keysym.sym);
      }
    }
  }
}