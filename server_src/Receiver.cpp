//
// Created by gabriel on 30/05/23.
//

#include "Receiver.h"

Receiver::Receiver(ServerProtocol &protocol, Match &match) : protocol(protocol),
                                                             match(match) {
}

void Receiver::run() {
    while (not match.is_finished()) {
        std::shared_ptr<Action> action = protocol.receive_action();
        if (protocol.closed()) {
            match.finish();
            return;
        }
        match.send_action(action);
    }
}
