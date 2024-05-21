#include "Scene.h"

Scene::Scene(const unsigned int windowWidth, const unsigned int windowHeight, const std::vector<std::string> &image_paths):
        window(sf::VideoMode{windowWidth, windowHeight}, GAME_TITLE, sf::Style::Default),
        event() {
    window.setVerticalSyncEnabled(true);
    for (const auto &path: image_paths) {

        std::string name;
        for(int i = path.size() - 5; i>=0; i--){
            if(path[i] == '/'){
                break;
            }
            name += path[i];
        }
        std::reverse(name.begin(), name.end());

        sf::Image image;
        if (!image.loadFromFile(path)) {
            std::cout << "Trouble at loading Image File\n";
            continue;
        }

        sf::Texture texture;
        if(!texture.loadFromImage(image)){
            std::cout << "Trouble at loading Texture\n";
            continue;
        }

        textures[name] = texture;
    }
}



Scene::~Scene() = default;



Scene::Scene(const Scene &other) : window(sf::VideoMode{other.window.getSize().x,
                                                 other.window.getSize().y},
                                   GAME_TITLE, sf::Style::Default),
                            event(other.event), textures(other.textures) {}

std::ostream &operator<<(std::ostream &os, const Scene &scene_) {
    os << "Window size: " << scene_.window.getSize().x << "x" << scene_.window.getSize().y<< "\n";

    return os;
}

sf::Texture& Scene::getTexture(std::string key) { return textures[key]; }

sf::Event Scene::getEvent() const { return event; }

bool Scene::isOpen() { return window.isOpen(); }

void Scene::clear() { window.clear(); }


void Scene::display() { window.display(); }

void Scene::close() { window.close(); }

bool Scene::pollEvent() { return window.pollEvent(event); }

sf::Event& Scene::getEvent() { return event; }

sf::Vector2u Scene::getWindowSize() const { return window.getSize(); }

Scene &Scene::operator=(const Scene &other) {
    event = other.event;
    textures = other.textures;

    return *this;
}
