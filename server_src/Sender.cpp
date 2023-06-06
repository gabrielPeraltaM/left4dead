//
// Created by gabriel on 30/05/23.
//

#include "Sender.h"
#include "State.h"
#include <memory>

Sender::Sender(ServerProtocol &protocol, Match &match) : protocol(protocol),
                                                         match(match) {
}

void Sender::run() {
    while (not match.is_finished()) {
        std::shared_ptr<State> state = match.receive_state();
        if (!state) {
            continue;
        }
        protocol.send_state(state);
    }
}
