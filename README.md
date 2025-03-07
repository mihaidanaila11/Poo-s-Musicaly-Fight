# POO's Musically Fight!

## Overview
Poo's Musically Fight is a game that combines my two main passions: games and music. Built in C++ using Object-Oriented Programming (OOP) concepts, this project is designed to showcase my skills in game development and software engineering.

In this game, your mission is to fight against waves of enemies, with each hit contributing to the creation of a song. The more enemies you defeat, the more complex and interesting your musical composition becomes.

## Features
- **C++ Development**: The game is developed in C++, showcasing proficiency in a widely-used programming language.
- **Object-Oriented Programming**: Utilizes OOP concepts to create a modular and maintainable codebase.
- **Interactive Gameplay**: Players engage in combat with waves of enemies, with each action contributing to a dynamic soundtrack.
- **Music Integration**: Every hit and action in the game contributes to an evolving musical piece, making each playthrough unique.


## KeyBinds:
- **Movement**: `W`,`A`,`S`,`D` (`UP`, `LEFT`, `DOWN`, `RIGHT`)
- **Attack** *(can't spam it)*: `SPACE`
- **Pause**: `ESC`

### Important!
Aveți voie cu cod generat de modele de limbaj la care nu ați contribuit semnificativ doar în folder-ul `generated`.
Codul generat pus "ca să fie"/pe care nu îl înțelegeți se punctează doar pentru puncte bonus, doar în contextul
în care oferă funcționalități ajutătoare și doar dacă are sens.

O cerință nu se consideră îndeplinită dacă este realizată doar ca o serie de apeluri proxy către cod generate.

### Sprint 0

- [X] Project name (can be changed later)
- [X] Short description of the chosen theme, what you aim to implement

## Sprint 1

#### Tasks:
- [X] Define at least **3-4 classes** using composition with the classes you have defined
- [X] Initialization constructors
- [X] For the same (single) class: copy constructor, copy `operator=`, destructor
<!-- - [ ] For another class: move constructor, move `operator=`, destructor -->
<!-- - [ ] For another class: all five special member functions -->
- [X] `operator<<` for all classes for display (std::ostream)
- [X] As many `const` as possible (where applicable)
- [X] Implement at least 3 public member functions for functionalities specific to the chosen theme, including at least 1-2 more complex functions
  - Not just read/display or add/remove elements in/from a vector
<!-- - [ ] Usage scenario of the defined classes:
  - Create objects and call all public member functions in main
  - Only examples of keyboard input data will be added to the `tastatura.txt` file (if applicable); if you need data from files, create separate files
-->
- [X] `git` tag: for example `v0.1`
- [X] Continuous integration (CI) service; example: GitHub Actions

## Sprint 2

#### Tasks:
- [x] Separate code from classes into `.h` (or `.hpp`) and `.cpp`
- [x] Inheritance:
  - At least one base class and **3 derived classes**
  - The hierarchy must have its own base, not derived from a predefined class
  - [x] Class with an attribute of type pointer to a base class with derivatives
  - [x] Virtual (pure) functions called through base pointers from the class containing the base pointer attribute
    - At least one virtual function must be **specific to the theme** (e.g., not just simple read/display)
    - Virtual constructors (clone): necessary but not considered specific functions for the theme
  - [x] Call the base class constructor from the derived constructors
  - [ ] Smart pointers (recommended, optional)
  - [ ] `dynamic_cast`/`std::dynamic_pointer_cast` for meaningful downcasting
- [x] Override cc/op= for correct copying/assigning, copy and swap
- [x] Exceptions
  - [x] Own hierarchy based on `std::exception` or derived from `std::exception`; at least **3** classes for specific errors
  - [x] Meaningful usage: for example, `throw` in the constructor (or function returning an object), `try`/`catch` in `main`
- [x] Static functions and attributes
- [x] STL
- [x] As many `const` as possible
- [x] At the end: separate commit with the addition of a new derived class without modifying the rest of the code, **besides the already added 3 derived classes**
  - The new derived class cannot be an existing one that was deleted and added again
- [x] `git` tag: for example `v0.2`

## Sprint 3

#### Tasks:
- [x] 2 design patterns
- [x] A meaningful template class; at least **2 instantiations**
  - [x] Preferably also a meaningful template function; at least 2 instantiations
<!-- - [ ] A specialization on template function/class -->
- [ ] `git` tag: for example `v0.3` or `v1.0`
      
## Resources
- [SFML](https://github.com/SFML/SFML/tree/2.6.1) (Zlib)
