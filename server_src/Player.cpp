//
// Created by gabriel on 18/05/23.
//

#include "Player.h"

#include "server_src/actions/ActionStart.h"

Player::Player(ActionQueue &actions, StateQueue *states, int player_id,
               bool host)
    : actions(actions),
      states(states),
      finished(false),
      player_id(player_id),
      host(host) {}

void Player::send_action(const std::shared_ptr<Action> &action) {
  actions.push(action);
}

void Player::send_start() { actions.push(std::make_shared<ActionStart>()); }

std::shared_ptr<State> Player::receive_state() { return states->pop(); }

void Player::finish() {
  finished = true;
  states->close();
}

bool Player::is_finished() { return finished; }

int Player::get_player_id() const { return player_id; }

bool Player::is_host() const { return host; }
void Player::set_character_type(int type) { character_type = type; }
int Player::get_character_type() const { return character_type; }
void Player::set_map_selected(int map) { map_selected = map; }
int Player::get_map_selected() const { return map_selected; }
