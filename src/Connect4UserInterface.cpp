//
// Created by Lukasz-Lap on 19.05.2020.
//

#include "Connect4UserInterface.h"

Connect4UserInterface::Connect4UserInterface(Connect4AI &game, sf::RenderWindow &window) :
        _game(game),
        _window(window) {

    std::cout << window.getSize().x << window.getSize().y << std::endl;
    _player_color = sf::Color::Red;
    _ai_color = sf::Color::Yellow;

    _coin_radius = window.getSize().x / 3 / 7;
    _background_color = sf::Color(170, 196, 239);
    _border_color = sf::Color(2, 37, 94);

    sf::CircleShape coin(_coin_radius);
    coin.setFillColor(_background_color);
    coin.setOrigin(_coin_radius, _coin_radius);
    coin.setOutlineThickness(5);
    coin.setOutlineColor(_border_color);

    for (auto &i: _coins) {
        std::fill(i.begin(), i.end(), coin);
    }

    _board_height = window.getSize().y - 3 * _coin_radius;
    _board_picture.setSize(sf::Vector2f(window.getSize().x, _board_height));
    _board_picture.setFillColor(sf::Color::Blue);
    _board_picture.setPosition(0, 3 * _coin_radius);

}

/**
 * @brief Game loop
 */
void Connect4UserInterface::Run() {
    Start();


    Start();
    while (_window.isOpen()) {
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::EventType::Closed) { _window.close(); }
           // TakeTurn();
           //UpdateCoinsColors();

            DisplayGame();

            if (_game.HaveWinner()) { return; }
            if (_game.IsTie()) { return; }
        }

    }

    End();
}

void Connect4UserInterface::Start() {

}

void Connect4UserInterface::End() {

}


void Connect4UserInterface::DisplayGame() {
    _window.clear(_background_color);


    _window.draw(_board_picture);
    float current_x = _board_picture.getPosition().x + 1.5 * _coin_radius;
    float current_y = _board_picture.getPosition().y + 1.5 * _coin_radius;

    for (int i = 0; i < _game.GetColumnNumber(); ++i) {
        _coins[i][0].setPosition(current_x, current_y);
        _window.draw(_coins[i][0]);
        for (int j = 0; j < _game.GetRowNumber(); ++j) {
            current_x += 3 * _coin_radius;
            _coins[i][j].setPosition(current_x, current_y);
            _window.draw(_coins[i][j]);
        }
        current_y += 3 * _coin_radius;
        current_x = _board_picture.getPosition().x + 1.5 * _coin_radius;
    }


    _window.display();
}

void Connect4UserInterface::TakeTurn() {
    if (_game.GetCurrentPlayer() == BoardPositionState::PLAYER) {
        int column = 0;
        std::cin >> column;
        _game.DropCoin(column, BoardPositionState::PLAYER);

        _game.ChangeCurrentPlayer();
        return;
    }

    if (_game.GetCurrentPlayer() == BoardPositionState::AI) {
        auto column = _game.FindBestMove();
        _game.DropCoin(column, BoardPositionState::AI);


        _game.ChangeCurrentPlayer();
        return;
    }
}

void Connect4UserInterface::UpdateCoinsColors() {
    auto last_move = _game.GetLastMove();

    if (last_move.state == BoardPositionState::AI) {
        _coins[last_move.column][last_move.row].setFillColor(_ai_color);
    }
    if (last_move.state == BoardPositionState::PLAYER) {
        _coins[last_move.column][last_move.row].setFillColor(_player_color);
    }
}

