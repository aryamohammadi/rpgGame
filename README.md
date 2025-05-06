# BRPG – Battlestar RPG

## Overview

Battlestar RPG is a terminal-based, turn-based combat game built in C++ with a focus on clean architecture and object-oriented design. Players engage in RPG-style battles with scalable difficulty, inventory management, and stat progression — all through a text-based interface.

This project was developed as a collaborative capstone for a Software Construction course at UC Riverside. It emphasizes SOLID principles, modular class structure, and a realistic development workflow including version control, code reviews, and feature-based branching.

> ⚠️ This is a collaborative project. For individual work, see [other repositories](https://github.com/aryamohammadi).

---

## Authors

This project was developed by a five-person team as part of a course at UC Riverside. Each contributor played a key role in design, implementation, and testing.

- [Arya Mohammadi](https://github.com/aryamohammadi)
- [Jameel Simjee](https://github.com/JSimjee)
- [Matthew Acosta](https://github.com/macos052)
- [Jessy Garcia](https://github.com/jgarc826)
- [Ryan Jourdain](https://github.com/RJourdain)

---

## Project Description

Battlestar RPG was designed to apply advanced C++ programming concepts in a collaborative setting. The project simulates a full development lifecycle—from design and planning to implementation and testing—mirroring real-world software engineering practices.

Key goals included:

- Applying object-oriented design, data structures, and algorithms in a functional game environment
- Practicing team-based development using Git, code reviews, and modular workflows
- Reinforcing software engineering fundamentals like abstraction, maintainability, and testability

---

## Technologies Used

- **Language:**  
  C++

- **Development Tools:**  
  Git, GitHub, CMake, Make, VS Code, Terminal

- **Testing Framework:**  
  GoogleTest

- **Programming Paradigms:**  
  Object-Oriented Programming (OOP), SOLID Principles, Modular Design, Unit Testing

---

## Game Features

- **Turn-based combat** with player options to attack, defend, or use items
- **Dynamic difficulty scaling** that adjusts enemy stats and challenge level
- **RPG-style progression** through experience points and stat upgrades
- **Text-driven interface** with navigable menus and in-terminal interaction


---

## SOLID Design Highlights

The architecture of Battlestar RPG follows SOLID principles to ensure maintainability, modularity, and scalability:

- **S – Single Responsibility Principle (SRP):**  
  Each class (e.g., `Combat`, `Player`, `Map`) encapsulates one well-defined responsibility.

- **O – Open/Closed Principle (OCP):**  
  Components like `MaxHeap` are open for extension (e.g., with new behaviors) but closed to direct modification.

- **L – Liskov Substitution Principle (LSP):**  
  Data structures such as heaps behave predictably when inherited, copied, or swapped.

- **I – Interface Segregation Principle (ISP):**  
  Logic for sorting, inventory, and combat is separated into purpose-specific modules.

- **D – Dependency Inversion Principle (DIP):**  
  Classes depend on abstractions (like interfaces) rather than concrete implementations.

---

## Installation & Usage

To build and run Battlestar RPG locally:

```bash
# Clone the repository
git clone https://github.com/aryamohammadi/rpgGame.git
cd rpgGame

# Build the project using CMake
cmake .
make

# Run the game
./bin/Game
```

---

## Testing

Unit tests are implemented using [GoogleTest](https://github.com/google/googletest) to verify core game functionality, including combat mechanics and data structures.

To run the test suite:

```bash
cd bin
./Tests
```

---

## Screenshots

Below are snapshots of core game interfaces in Battlestar RPG:

| Main Menu           | Combat View          | Victory Screen        | Inventory Menu         |
|---------------------|----------------------|------------------------|-------------------------|
| ![Main Menu](Images/Screenshot_1.png) | ![Combat View](Images/Screenshot_2.png) | ![Victory Screen](Images/Screenshot_3.png) | ![Inventory Menu](Images/Screenshot_4.png) |

---

## Diagrams

The following diagrams provide insight into the game’s structure, flow, and interface:

### Navigation Flow
![Navigation Diagram](Images/Navigation_Diagram.png)

### Sample Output
![Sample Output](Images/Sample_Output.png)

### UML Class Structure
![UML Class Diagram](Images/UML_Diagram.png)

### User Interface Layout
![UI Diagram](Images/User_Interface_Diagram.png)


---
## License

This project is open source and available under the terms of the [MIT License](LICENSE).

You are free to use, modify, and distribute the code, provided that proper credit is given to all contributors.

