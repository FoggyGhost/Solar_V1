# Solar

Solar is a command-line based RPG in which all of your choices matter. Your mission is to obtain a carboprism, an item needed by time travellers whose obligation is to prevent timeline abnormalities.

## Installation

The first thing you need to do is to download this repository. Then compile using the following commands:

```bash
gcc -Wall -c base_functions.c
gcc -Wall -c main.c
gcc -Wall -c locations.c
gcc -o solar main.o locations.o base_functions.o
```

## Gameplay & usage

Use w, a, s, d keys to move around the world when prompted.
The game is autosaved each time a chapter is completed.

## Status
This game may become more developed in the future. However, at this point it is completely playable.

## Contributing
Further development and modifications are welcome.

## License
[GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0/)
