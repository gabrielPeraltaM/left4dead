//
// Created by gabriel on 30/05/23.
//

#include "Commands.h"

Commands::Commands(Socket &sk, Match &match) : match(match),
                                               sender(sk, match),
                                               receiver(sk, match) {
  sender.start();
}

Commands::~Commands() {
  match.finish();
  sender.join();
}

void Commands::run() {
  receiver.run();
}
