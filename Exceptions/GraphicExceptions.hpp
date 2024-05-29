#ifndef OOP_GRAPHICEXCEPTIONS_HPP
#define OOP_GRAPHICEXCEPTIONS_HPP

#pragma once

#include <stdexcept>

class GraphicExceptions : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class inexistent_path : public GraphicExceptions{
public:
    explicit inexistent_path() : GraphicExceptions("Provided path does not exist.\n"){}
};

class unsupported_image : public GraphicExceptions{
public:
    explicit unsupported_image() : GraphicExceptions("Provided image is not supported by the SFML Library.\n"){}
};

class TextureNotFound : public GraphicExceptions{
public:
    TextureNotFound() : GraphicExceptions("Texture has not been found.") {}
};

class WindowClosed : public GraphicExceptions{
public:
    WindowClosed() : GraphicExceptions("The window has been closed."){}
};


#endif //OOP_GRAPHICEXCEPTIONS_HPP
