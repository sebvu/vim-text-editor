learning ncurses by creating a tui vim editor

## how do u run

- clone project
- cd into proj root director
- run this command

```
make
```

- cd into bin/ and run the provided binary

it is 100% vim motions so that's the tutorial to use it

## dev roadmap

```
- [x] be able to type text
- [x] add number lines
- [x] be able to do normal functions on a normal text editor
  - [x] enter to go to a line below, back 
  - [x] backspace to delete 
  - [x] arrows to go left right up down (only on spaces filled up, including the space key) 
- [] implement seamless scrolling logic
- [] be able to save
- [] be able to edit current files
- [] be able to edit files WITH text editor

- [] if normal mode
  - [x] h j k l
  - [] ctrl d, ctrl u
  - [] dd (delete line)
  - [] diw (delete word on)
- [] if insert mode
  - [x] normal editing rules for a text editor
  - [x] escape to go back to normal mode
```
