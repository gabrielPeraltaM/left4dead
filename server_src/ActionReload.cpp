//
// Created by gabriel on 19/06/23.
//

#include "ActionReload.h"

void ActionReload::execute(Map &map) {
    map.reload(player_id);
}
