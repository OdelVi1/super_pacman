#pragma once
#include "GameStatus.h"

GameStatus::GameStatus(int& life, int& score, int& level) :m_winOrLoseSprite(), m_gameOver(false),
    m_menuRectangle(sf::RectangleShape(sf::Vector2f(500, 80))),
    m_font(sf::Font()), m_levelText(), m_lifeSprite(), m_gameStarted(false),
    m_level(level), m_score(score), m_life(life), m_title()
{
    if (!m_font.loadFromFile("ARIAL.TTF"))
    {
        std::cerr << "Could not find ARIAL.TTF font." << std::endl;
    }

    float window_center_x = (Graphics::getInstance().getWindow().getSize().x / float(2));

    sf::Vector2f position(sf::Vector2f(window_center_x - (m_title.getGlobalBounds().width / 2), 20));
    sf::Color border = sf::Color().Green;

    m_menuRectangle.setPosition(sf::Vector2f(window_center_x - (STATUS_WIDTH / 2), position.y + m_title.getGlobalBounds().height));
    m_menuRectangle.setFillColor(sf::Color().Transparent);
    m_menuRectangle.setOutlineThickness(1);
    m_menuRectangle.setOutlineColor(sf::Color().Green);
    
    m_lifeSprite.setTexture(Graphics::getInstance().getTexture(GameTextures::LIFE));
    setText();
}

void GameStatus::setText()
{
    sf::Color textNormal = sf::Color(sf::Color().Yellow);
    float rectWidth = 80;
    float rectHeight = 30;
    float y_pos = m_menuRectangle.getGlobalBounds().top + (m_menuRectangle.getGlobalBounds().height / 2) - (rectHeight / 4);
    float x_pos = m_menuRectangle.getGlobalBounds().left + 50;

    sf::RectangleShape textLevelRect(sf::Vector2f(rectWidth, rectHeight));
    sf::RectangleShape textScoreRect(sf::Vector2f(rectWidth, rectHeight));
    sf::RectangleShape textLifeRect(sf::Vector2f(rectWidth, rectHeight));
    sf::RectangleShape textTimeRect(sf::Vector2f(rectWidth, rectHeight));
    
    textLevelRect.setPosition(x_pos, y_pos);

    textScoreRect.setPosition(textLevelRect.getGlobalBounds().left + rectWidth + STATUS_SPACE, y_pos);

    textLifeRect.setPosition(textScoreRect.getGlobalBounds().left + rectWidth + STATUS_SPACE, y_pos);

    m_lifeSprite.setPosition(sf::Vector2f(textLifeRect.getGlobalBounds().left, textLifeRect.getGlobalBounds().top));
    m_lifeSprite.setScale(0.1f, 0.1f);

    textTimeRect.setPosition(textLifeRect.getGlobalBounds().left + rectWidth + STATUS_SPACE, y_pos);

    m_levelText.setFont(m_font);
    m_levelText.setCharacterSize(15);
    m_levelText.setStyle(sf::Text::Bold);
    m_levelText.setFillColor(textNormal);

    m_lifeText = m_timeText = m_scoreText = m_levelText;

    m_levelText.setPosition(sf::Vector2f(textLevelRect.getGlobalBounds().left, textLevelRect.getGlobalBounds().top));
    m_scoreText.setPosition(sf::Vector2f(textScoreRect.getGlobalBounds().left, textScoreRect.getGlobalBounds().top));
    m_lifeText.setPosition(sf::Vector2f(textLifeRect.getGlobalBounds().left + m_lifeSprite.getGlobalBounds().width,
        textLifeRect.getGlobalBounds().top));
    m_timeText.setPosition(sf::Vector2f(textTimeRect.getGlobalBounds().left, textTimeRect.getGlobalBounds().top));
}

void GameStatus::drawGameStatus()
{
    const std::string level = "LEVEL: " + std::to_string(m_level);
    const std::string life = ": " + std::to_string(m_life);
    const std::string score = "SCORE: " + std::to_string(m_score);

    float time_in_seconds = TimeClock::getInstance().getClock().getElapsedTime().asSeconds();
    if (TimeClock::getInstance().getCountDownSeconds() > 0)
    {
        time_in_seconds = TimeClock::getInstance().getCountDownSeconds() - time_in_seconds;
    }

    int minutes = int(time_in_seconds) / 60;
    int seconds = int(time_in_seconds) % 60;

    std::string minute_string = minutes >= 10 ? std::to_string(minutes) : "0" + std::to_string(minutes);
    std::string second_string = seconds >= 10 ? std::to_string(seconds) : "0" + std::to_string(seconds);
    const std::string time = "TIME: " + minute_string + ":" + second_string;
    
    m_levelText.setString(level);
    m_scoreText.setString(score);
    m_lifeText.setString(life);
    m_timeText.setString(time);

    Graphics::getInstance().getWindow().draw(m_levelText);
    Graphics::getInstance().getWindow().draw(m_lifeSprite);
    Graphics::getInstance().getWindow().draw(m_lifeText);

    Graphics::getInstance().getWindow().draw(m_scoreText);
    Graphics::getInstance().getWindow().draw(m_timeText);
}

void GameStatus::setGameOver()
{
    m_winOrLoseSprite.setTexture(Graphics::getInstance().getTexture(GameTextures::GAME_OVER));
    m_gameOver = true;
    m_gameStarted = false;
}

void GameStatus::setGameWon()
{
    m_winOrLoseSprite.setTexture(Graphics::getInstance().getTexture(GameTextures::GAME_WON));
    m_gameOver = true;
    m_gameStarted = false;
}

void GameStatus::draw()
{
    m_title.draw();
    drawGameStatus();
    
    if (m_gameOver)
    {
        float window_center_x = (Graphics::getInstance().getWindow().getSize().x / float(2));
        m_winOrLoseSprite.setPosition(sf::Vector2f(window_center_x - (m_winOrLoseSprite.getGlobalBounds().width / 2),
            m_menuRectangle.getGlobalBounds().top + m_menuRectangle.getGlobalBounds().height));
        Graphics::getInstance().getWindow().draw(m_winOrLoseSprite);
    }
}