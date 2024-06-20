#include "MainMenu.h"
#include "../../Classes/Game/Game.h"

MainMenu::MainMenu(sf::RenderWindow* renderWindow, const std::vector<std::string> &image_paths,
                   const std::string& fontPath) :
Scene(renderWindow, image_paths, fontPath), play(Scene::getTexture("Buton"), Scene::getFont(), "PLAY"),
quit(Scene::getTexture("Buton"), Scene::getFont(), "QUIT"),
returnFlag(-1){
    sf::IntRect rect{0, 0, (int) Scene::getWindowSize().x,
                     (int) Scene::getWindowSize().y};

    Scene::getTexture("Grass_blured").setRepeated(true);
    background.setTexture(Scene::getTexture("Grass_blured"));

    background.setTextureRect(rect);
}

void MainMenu::handleEvents() {
    while(Scene::pollEvent()){
        sf::Event handledEvent = Scene::getEvent();
        switch (handledEvent.type) {
            case sf::Event::Closed:
                Scene::close();
                break;

            case sf::Event::MouseButtonPressed:
                if (handledEvent.mouseButton.button == sf::Mouse::Left) {

                    if (play.clicked(Scene::getEvent().mouseButton)) {
                        returnFlag = 1;
                        return;
                    } else if (quit.clicked(Scene::getEvent().mouseButton)) {
                        Scene::close();
                        returnFlag = 0;
                        return;

                    }
                }
                break;

            default:
                break;
        }
    }
}


int MainMenu::start() {


    sf::Text title{"POO'S MUSICALY FIGHT", Scene::getFont(), 40};
    title.setFillColor(sf::Color(239, 230, 103));
    title.setOutlineThickness(1.f);
    title.setOutlineColor(sf::Color::Black);
    play.setPosition(sf::Vector2f {(float)Scene::getWindowSize().x/2 - play.getLocalBounds().width/2,
                                   (float)Scene::getWindowSize().y/2 - play.getLocalBounds().height - 20.f});

    quit.setPosition(sf::Vector2f {(float)Scene::getWindowSize().x/2 - quit.getLocalBounds().width/2,
                                   (float)Scene::getWindowSize().y/2 + quit.getLocalBounds().height + 20.f});


    sf::FloatRect localBounds = title.getLocalBounds();
    title.setPosition((float)Scene::getWindowSize().x/2 - localBounds.width/2, 20);

    Scene::clear();
    Scene::draw(background);
    Scene::draw(title);
    Scene::draw(play.getSprite());
    Scene::draw(play.getText());
    Scene::draw(quit.getSprite());
    Scene::draw(quit.getText());
    Scene::display();

    while(Scene::isOpen()){
        handleEvents();

        if(returnFlag != -1)
            return returnFlag;

    }
    return 0;
}

MainMenu &MainMenu::getMainMenu(sf::RenderWindow *renderWindow) {
    static MainMenu mainMenu{renderWindow, std::vector<std::string>{
            "Textures/Grass_blured.png",
            "Textures/Buton.png"
    }, "daydream_3/Daydream.ttf"};

    return mainMenu;
}
