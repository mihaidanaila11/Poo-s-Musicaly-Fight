#include "TextureManager.h"
#include "../../Exceptions/GraphicExceptions.hpp"
#include <fstream>
#include <iostream>

std::unordered_map<std::string, sf::Texture> TextureManager::textures;

std::unordered_map<sf::Sprite*, sf::Texture*> TextureManager::usedTextures;


bool TextureManager::exists(const std::string &path) { return std::ifstream(path).good(); }

bool TextureManager::isImageSupported(const std::string &path) {
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

void TextureManager::loadFromFiles(const std::vector<std::string> &image_paths) {
    for (const auto &path: image_paths) {
        loadFromFile(path);
    }
}

void TextureManager::loadFromFile(const std::string &image_path) {
    if(!exists(image_path)){
        throw inexistent_path();
    }

    if(!isImageSupported(image_path)) {
        throw unsupported_image();
    }

    std::string name;
    for(int i = image_path.size() - 5; i>=0; i--){
        if(image_path[i] == '/'){
            break;
        }
        name += image_path[i];
    }
    std::reverse(name.begin(), name.end());

    sf::Image image;
    image.loadFromFile(image_path);

    sf::Texture texture;
    texture.loadFromImage(image);

    textures[name] = texture;
}

sf::Texture TextureManager::getTexture(const std::string& key) const{
    auto it = textures.find(key);
    if(it == textures.end())
        throw TextureNotFound();
    std::cout << it->first << " textura gasita\n";
    return it->second;
}

TextureManager::TextureManager(const std::vector<std::string> &image_paths){
    loadFromFiles(image_paths);
}

sf::Texture &TextureManager::useTexture(const std::string& texture_name, sf::Sprite& sprite) {
    auto* newTexture = new sf::Texture(textures[texture_name]);
    usedTextures[&sprite] = newTexture;
    sprite.setTexture(*newTexture);

    return *newTexture;
}

sf::Texture &TextureManager::useTexture(const sf::Sprite& other, sf::Sprite &sprite){

    // Nu stiu cum sa fac altfel pt ca nu pot sa folosesc .find() sau .at() sau .contains()
    // Pt ca it would drop const qualifier
    bool returnFlag = true;
    std::pair<sf::Sprite *, sf::Texture *> texturePair;
    for(const auto& pair : usedTextures){
        if(pair.first == &other){
            texturePair = pair;
            std::cout << "Gasit\n";
            returnFlag = false;
            break;
        }
    }
    if(returnFlag)
        throw std::runtime_error("Texture not found");

    auto* newTexture = new sf::Texture(*texturePair.second);
    usedTextures[&sprite] = newTexture;
    sprite.setTexture(*newTexture);

    return *newTexture;
}
