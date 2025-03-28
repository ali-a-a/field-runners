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

<img width="512" alt="Screen Shot 2022-03-09 at 2 35 15 PM" src="https://private-user-images.githubusercontent.com/68470999/422437777-0903b96f-56e9-4396-bf1e-867ec53acd70.jpg?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NDMxMjM4NjUsIm5iZiI6MTc0MzEyMzU2NSwicGF0aCI6Ii82ODQ3MDk5OS80MjI0Mzc3NzctMDkwM2I5NmYtNTZlOS00Mzk2LWJmMWUtODY3ZWM1M2FjZDcwLmpwZz9YLUFtei1BbGdvcml0aG09QVdTNC1ITUFDLVNIQTI1NiZYLUFtei1DcmVkZW50aWFsPUFLSUFWQ09EWUxTQTUzUFFLNFpBJTJGMjAyNTAzMjglMkZ1cy1lYXN0LTElMkZzMyUyRmF3czRfcmVxdWVzdCZYLUFtei1EYXRlPTIwMjUwMzI4VDAwNTkyNVomWC1BbXotRXhwaXJlcz0zMDAmWC1BbXotU2lnbmF0dXJlPWFmYmE1YmZhYWY3YmFlOTFkYzM2ZDhhMTMzZDBlYTJiYTk2MDFiNmE2MDY1MWUzYjgwZDE3Y2ZkMTZiOTViNTkmWC1BbXotU2lnbmVkSGVhZGVycz1ob3N0In0.Ael8zvDcBpTXSNfLbt78sfsZuGXjov_ufdUMQG8b1uk">
