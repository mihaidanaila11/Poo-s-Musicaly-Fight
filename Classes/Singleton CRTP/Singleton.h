#ifndef OOP_SINGLETON_H
#define OOP_SINGLETON_H

#include <SFML/Graphics/RenderWindow.hpp>

template<typename Derived>
class Singleton {
protected:
    Singleton() = default;

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    template<class... Args>
    static Derived& getInstance(Args&&... args){
        static Derived instance(std::forward<Args>(args)...);
        return instance;
    }

private:
    class DerivatedInstance : public Derived{
    public:
        template<class... Args>
        explicit DerivatedInstance(Args&&... args) : Derived(std::forward<Args>(args)...){}
    };
};


#endif //OOP_SINGLETON_H
