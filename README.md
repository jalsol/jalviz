# CS162 (and CS202?) Project: VisuAlgo clone

Author: 22125113 - Nguyen Quang Truong

This is an application that tries to replicate what [VisuAlgo.net](https://visualgo.net)
does, with basic data structures.

Initially, this was a project for the course CS162 - Introduction to Programming
II. However, as I become more ambitious (or even delusional? who cares!), I also
want to pass the lab of CS202 - Programming Systems with this project, despite
it being a future course and not yet available to me - a freshman.

## Features

It currently supports the following data structures:
- Array
- Dynamic Array (similar to `std::vector`)
- Linked List
- Doubly Linked List
- Circular Linked List
- Stack
- Queue

Notable features include:
- Visualization of initialization and CRUD operations of different data structures
- Step-by-step code highlight
- Super customizable color settings (with presets included)
- ... and more to come!

## Demonstration

[Here is the demonstration on YouTube.](https://youtu.be/9E_ZE9IUF1Q)

## Dependencies

### Application

- C++20 (GNU GCC 11.3.0)
- CMake 3.22 or above
- [Raylib](https://github.com/raysan5/raylib) and [Raygui](https://github.com/raysan5/raygui)
(modified)
- [tiny file dialogs](https://sourceforge.net/projects/tinyfiledialogs/)

### Documentation

- [Doxygen](https://www.doxygen.nl/)
- [PlantUML](https://plantuml.com/)
- [clang-uml](https://github.com/bkryza/clang-uml)

## Building

- Clone this repository
- `cmake -S. -Bbuild`
- `make -Cbuild`
- The executable `visualgo_cpp` will appear.

### Extra building notes

- If CMake does not choose the correct build system generator, please read the
manual by running `cmake -h` and read the options for the `-G` flag;
- You can use the `-j` flag for Make to enable multithreaded compiling (for example,
my laptop has 4 cores, so I usually run `make -Cbuild -j4`).

## Releases

Prebuilt executables should be moved to the root of the repo before running.

## License

This project is licensed under the GNU GPL v3.0 License.

## Documentation

### User manual

[To be updated]

### Program structure

For the LaTeX version, please refer to `docs/latex/refman.pdf`.

For the HTML version, please generate with Doxygen using `Doxyfile` as the
configuration. The generated HTML is located at `docs/html/`

## Modeling structures overview

![core](docs/diagrams/core.png)

![gui](docs/diagrams/gui.png)

![scene](docs/diagrams/scene.png)

![component](docs/diagrams/component.png)

