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
<img width="511" alt="423173240-bc1a648b-6ca3-4e31-a114-7467934300d0" src="https://github.com/user-attachments/assets/f64546bb-3ef9-410b-8e76-0070a306dea3" />


