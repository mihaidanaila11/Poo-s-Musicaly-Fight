#ifndef OOP_TEXTUREMANAGER_H
#define OOP_TEXTUREMANAGER_H

#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <unordered_set>
#include "SFML/Graphics.hpp"

class TextureManager {
    static std::unordered_map<std::string, sf::Texture> textures;

    static std::unordered_map<sf::Sprite*, sf::Texture*> usedTextures;

public:
    static bool exists(const std::string& path);
    static bool isImageSupported(const std::string& path);

    template<typename T>
    static bool isInVector(const std::vector<T>& vector, const T& object){
        for(const auto& item : vector){
            if(item == object)
                return true;
        }

        return false;
    }

    explicit TextureManager(const std::vector<std::string> &image_paths);
    ~TextureManager();

    void loadFromFiles(const std::vector<std::string> &image_paths);
    void loadFromFile(const std::string &image_path);

    [[nodiscard]] sf::Texture getTexture(const std::string& key) const;

    static sf::Texture& useTexture(const std::string& texture_name, sf::Sprite& sprite);
    static sf::Texture& useTexture(const sf::Sprite& other, sf::Sprite& sprite);
    static void removeTexture(sf::Sprite& sprite);
};


#endif //OOP_TEXTUREMANAGER_H
