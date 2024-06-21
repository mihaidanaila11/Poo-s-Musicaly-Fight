#include <filesystem>
#include <fstream>
#include "Scene.hpp"
#include "../../Exceptions/GraphicExceptions.hpp"

bool Scene::exists(const std::string &path) { return std::ifstream(path).good(); }

bool Scene::isImageSupported(const std::string &path) {
    std::vector<std::string> supportedExtensions{
        "jpg","png","gif","bmp","pnm","tga","psd","hdr","pic"};

    std::string extension;
    for(int i=3; i>0; i--){
        extension += *(path.end() - i*sizeof(char));
    }

    std::transform(extension.begin(), extension.end(), extension.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    return isInVector(supportedExtensions, extension);
}

Scene::Scene(sf::RenderWindow*& renderWindow, const std::vector<std::string> &image_paths, const std::string& fontPath):
        window(renderWindow),
        event(),
        textureManager(image_paths), font() {
    window->setVerticalSyncEnabled(true);

    if(!font.loadFromFile(fontPath)){
        std::cout << "Error loading font from file";
    }

}



Scene::~Scene(){
    std::cout << "Scene destructor\n";
}



Scene::Scene(const Scene &other) : window(other.window),
                                event(other.event), textures(other.textures),
                                textureManager(other.textureManager){}

std::ostream &operator<<(std::ostream &os, const Scene &scene_) {
    os << "Window size: " << scene_.window->getSize().x << "x" << scene_.window->getSize().y<< "\n";

    return os;
}

bool Scene::isOpen() { return window->isOpen(); }

void Scene::clear() { window->clear(); }


void Scene::display() { window->display(); }

void Scene::close() { window->close(); }

bool Scene::pollEvent() { return window->pollEvent(event); }

sf::Event& Scene::getEvent() { return event; }

sf::Vector2u Scene::getWindowSize() const { return window->getSize(); }

Scene &Scene::operator=(const Scene &other) {
    window = other.window;
    event = other.event;
    textures = other.textures;

    return *this;
}

const sf::Font& Scene::getFont() const { return font; }

