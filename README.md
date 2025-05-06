# BRPG - Battlestar RPG

## Overview

Battlestar RPG is a terminal-based, turn-based game implemented in C++ using object-oriented principles and modular class design. This project simulates a role-playing battle system with difficulty scaling, inventory management, and user interaction via text I/O.

It was built collaboratively as a capstone for a software construction course at UC Riverside. Emphasis was placed on applying SOLID design principles, writing clean and extensible code, and working in a multi-member GitHub environment with version control, code reviews, and feature-based branching.

**Note:** This project reflects collective team contributions. For solo projects and individual development work, please refer to my other repositories.

---

## Authors

- [Jameel Simjee](https://github.com/JSimjee)
- [Matthew Acosta](https://github.com/macos052)
- [Jessy Garcia](https://github.com/jgarc826)
- [Arya Mohammadi](https://github.com/aryamohammadi)
- [Ryan Jourdain](https://github.com/RJourdain)

---

## Project Description

- This project helped us deepen our understanding of C++ concepts such as object-oriented programming, data structures, and algorithms.
- Our goal was to simulate a realistic development workflow, reinforce best practices, and gain experience in collaborative programming.
- The scope of the project allowed us to design systems that apply core software engineering principles.

---

## Technologies Used

- **Language:** C++
- **Tools:** Git, GitHub, CMake, GoogleTest, VS Code, Terminal
- **Paradigms:** OOP, SOLID Principles, Modular Design, Unit Testing

---

## Game Features

- **Text-based combat system** with attack, defend, and item usage mechanics.
- **Difficulty levels** that scale enemy stats, items, and challenge.
- **Player progression** through experience and stat increases.
- **Menu-driven user interface** in the terminal.

---

## SOLID Design Highlights

- **SRP:** Each class (Combat, Player, Map, etc.) has a clear, single responsibility.
- **OCP:** Components like MaxHeap are extensible and generic.
- **LSP:** Heap operations behave consistently when copied or swapped.
- **ISP:** Sorting logic is separated from inventory logic.
- **DIP:** Classes interact through abstractions, not hard dependencies.

---

## Installation & Usage

Clone and build using CMake:

```bash
git clone https://github.com/aryamohammadi/rpgGame.git
cd rpgGame
cmake .
make
./bin/Game
```

---

## Testing

We use [GoogleTest](https://github.com/google/googletest) for unit testing:

```bash
cd bin
./Tests
```

---

## Screenshots

| Main Menu | Combat | Victory | Inventory |
|-----------|--------|---------|-----------|
| ![Main Menu](Images/Screenshot_1.png) | ![Combat](Images/Screenshot_2.png) | ![Victory](Images/Screenshot_3.png) | ![Inventory](Images/Screenshot_4.png) |

---

## Diagrams

- **Navigation Diagram**  
  ![Navigation](Images/Navigation_Diagram.png)

- **Sample Output**  
  ![Output](Images/Sample_Output.png)

- **UML Class Diagram**  
  ![UML](Images/UML_Diagram.png)

- **User Interface Diagram**  
  ![UI](Images/User_Interface_Diagram.png)

---

