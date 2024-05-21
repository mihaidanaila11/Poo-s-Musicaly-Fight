#include "Scene.hpp"


Scene::Scene(sf::RenderWindow*& renderWindow, const std::vector<std::string> &image_paths, const std::string& fontPath):
        window(renderWindow),
        event(), font() {
    std::cout << "constructor scene\n";
    window->setVerticalSyncEnabled(true);
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

    if(!font.loadFromFile(fontPath)){
        std::cout << "Error loading font from file";
    }
}



Scene::~Scene(){
    std::cout << "Scene destructor\n";
}



Scene::Scene(const Scene &other) : window(other.window),
                            event(other.event), textures(other.textures) {}

std::ostream &operator<<(std::ostream &os, const Scene &scene_) {
    os << "Window size: " << scene_.window->getSize().x << "x" << scene_.window->getSize().y<< "\n";

    return os;
}

sf::Texture& Scene::getTexture(const std::string& key) { return textures[key]; }

sf::Event Scene::getEvent() const { return event; }

bool Scene::isOpen() { return window->isOpen(); }

void Scene::clear() { window->clear(); }


void Scene::display() { window->display(); }

void Scene::close() { window->close(); }

bool Scene::pollEvent() { return window->pollEvent(event); }

sf::Event& Scene::getEvent() { return event; }

sf::Vector2u Scene::getWindowSize() const { return window->getSize(); }

Scene &Scene::operator=(const Scene &other) {
    event = other.event;
    textures = other.textures;

    return *this;
}

const sf::Font& Scene::getFont() const { return font; }

