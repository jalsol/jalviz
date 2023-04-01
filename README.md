# CS162 Project: VisuAlgo clone

Author: 22125113 - Nguyen Quang Truong

## Requirements

- C++20 (GNU GCC 11.3.0)
- CMake 3.22 or above
- [Raylib](https://github.com/raysan5/raylib) and [Raygui](https://github.com/raysan5/raygui)

## Building

- Clone this repository
- `cmake -S. -Bbuild`
- `make -Cbuild`
- The executable `visualgo_cpp` will appear.

## Prebuilt executables

Executables inside `release` should be moved to the root of the repo before running.

## Features

- Visualize different operations of different data structures
(initialization and CRUD operations)
- Highlight lines of codes corresponding to each action
- [WIP] Color and size customization

## License

This project is licensed under the GNU GPL v3.0 License.

## Documentation

### User manual

[To be updated]

### Program structure

Please refer to `docs/latex/refman.pdf`.

To see the HTML version, please generate with Doxygen, using `Doxyfile` as the
configuration.

## Modeling structures overview

![core](docs/diagrams/core.png)

![gui](docs/diagrams/gui.png)

![scene](docs/diagrams/scene.png)

![component](docs/diagrams/component.png)

