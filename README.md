# Snake Game

An **embedded C++ Snake Game** designed for LED matrix displays and microcontroller environments like **ESP32** or **Arduino**. This modular, lightweight game demonstrates core principles of game logic, hardware interfacing, and real-time updates.

Built for **expandability** and **hardware abstraction**, it's ideal for learning embedded game development or deploying a quick retro game on custom hardware.

## ✨ Features

- **Classic Snake Gameplay** – Move, grow, and avoid collisions in a nostalgic arcade style.
- **LED Matrix Display Support** – Renders gameplay on a low-power LED matrix screen.
- **Menu Interface** – Basic game menu for starting or resetting the game.
- **Customizable Settings** – Modify game speed, display behavior, and more.
- **Hardware Abstraction** – Supports RTC, buttons, and other hardware components.
- **PlatformIO Integration** – Easily build and deploy using the PlatformIO ecosystem.

## ⚡ Technology Stack

- **C++ (C++11 or later)** – Main language for control logic and game implementation.
- **PlatformIO** – Manages builds, libraries, and hardware targets.
- **Microcontroller Hardware** – Designed for platforms like ESP32.
- **LED Matrix** – Visual game rendering using simple pixel-based output.

## ⚙️ Build & Installation

### Prerequisites

Before building the project, ensure you have the following installed:

- **PlatformIO IDE** (or CLI)
- A compatible microcontroller board (e.g., ESP32)
- Required hardware (e.g., LED matrix, buttons, RTC)

### Build Instructions

Follow these steps to clone, build, and run the HTTP client:

```sh
# Clone the repository
git clone https://github.com/andreiv03/snake-game.git
cd snake-game

# Open in PlatformIO or build from CLI
platformio run

# Upload the firmware to your board
platformio run --target upload
```

## 🤝 Contributing

Contributions are welcome! If you'd like to enhance the project, follow these steps:

1. **Fork** the repository
2. Create a **feature branch** (`git checkout -b feature-branch`)
3. **Commit** your changes (`git commit -m "feat: add new feature"`)
4. **Push** your changes (`git push origin feature-branch`)
5. Open a **Pull Request** 🚀

For suggestions or bug reports, feel free to open an issue with the appropriate label.

⭐ **If you find this project useful, consider giving it a star!** ⭐

## 📜 License

Distributed under the **MIT License**. See `LICENSE` for details.
