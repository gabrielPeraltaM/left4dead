//
// Created by gabriel on 30/05/23.
//

#include "Commands.h"

Commands::Commands(ServerProtocol &protocol, Match &match) : match(match),
                                                             sender(protocol, match),
                                                             receiver(protocol, match) {
    sender.start();
}

Commands::~Commands() {
    match.finish();
    sender.join();
}

void Commands::run() {
    receiver.run();
}
