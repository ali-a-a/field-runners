# Field Runners

It is a tiny battlefield-like game in SDL2 and C++. The game is about defending your country by deploying different kinds of missiles and killing enemies trying to invade your country.

## How To Play

You can clone the repository and compile the program. All the assets are provided in this repository. To compile the program, go to the `src` directory and run `make`. A binary file called `FieldRunners.out` will be generated and you can run it to start the game. A guide for program arguments:

```bash
./FieldRunners.out
<wave-1-start-point> <wave-1-end-point> <wave-2-start-point> <wave-2-end-point>
<wave-1-enemies>
<wave-2-enemies>

# example
./FieldRunners.out
500 1000 600 1500
20
40
```

In each wave, a given number of enemies attack from the given starting point and try to invade the ending point.

## Customize The Game

You can check out the `src/defines.hpp` file and change constant values to customize the game as you want.

## Game Picture
![422437777-0903b96f-56e9-4396-bf1e-867ec53acd70](https://github.com/user-attachments/assets/b499c917-f7bd-4703-ad54-3ea1de2e70ac)



