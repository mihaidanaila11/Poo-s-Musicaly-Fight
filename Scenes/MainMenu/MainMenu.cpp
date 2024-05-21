#include "MainMenu.h"
#include "../../Classes/Button/Button.h"
#include "../../Classes/Game/Game.h"

MainMenu::MainMenu(sf::RenderWindow*& renderWindow, const std::vector<std::string> &image_paths,
                   const std::string& fontPath) :
Scene(renderWindow, image_paths, fontPath){
    sf::IntRect rect{0, 0, (int) Scene::getWindowSize().x,
                     (int) Scene::getWindowSize().y};

    Scene::getTexture("Grass_blured").setRepeated(true);
    background.setTexture(Scene::getTexture("Grass_blured"));

    background.setTextureRect(rect);
}


int MainMenu::start() {
    sf::Text title{"POO'S MUSICALY FIGHT", Scene::getFont(), 40};
    title.setFillColor(sf::Color(239, 230, 103));
    title.setOutlineThickness(1.f);
    title.setOutlineColor(sf::Color::Black);

    sf::FloatRect localBounds = title.getLocalBounds();
    title.setPosition((float)Scene::getWindowSize().x/2 - localBounds.width/2, 20);

    Button play{Scene::getTexture("Buton"), Scene::getFont(), "PLAY"};
    play.setPosition(sf::Vector2f {(float)Scene::getWindowSize().x/2 - play.getLocalBounds().width/2,
                                   (float)Scene::getWindowSize().y/2 - play.getLocalBounds().height - 20.f});

    Button quit{Scene::getTexture("Buton"), Scene::getFont(), "QUIT"};
    quit.setPosition(sf::Vector2f {(float)Scene::getWindowSize().x/2 - quit.getLocalBounds().width/2,
                                   (float)Scene::getWindowSize().y/2 + quit.getLocalBounds().height + 20.f});

    while(Scene::isOpen()){
        while(Scene::pollEvent()){
            switch (Scene::getEvent().type) {
                case sf::Event::Closed:
                    Scene::close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (Scene::getEvent().mouseButton.button == sf::Mouse::Left) {

                        if (play.clicked(Scene::getEvent().mouseButton)) {
                            return 1;
                        } else if (quit.clicked(Scene::getEvent().mouseButton)) {
                            Scene::close();
                            return 0;

                        }
                    }
                    break;

                default:
                    break;
            }
        }

        Scene::clear();
        Scene::draw(background);
        Scene::draw(title);
        Scene::draw(play.getSprite());
        Scene::draw(play.getText());
        Scene::draw(quit.getSprite());
        Scene::draw(quit.getText());
        Scene::display();
    }
    return 0;
}