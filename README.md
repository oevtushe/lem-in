# lem-in
Lem-in project in School 42

Main goal of this project is to help ants get from `start` room to `end` one in the shortest way.

## Key words
  1. `Ant farm` -> set of rooms connected with each other by links so that
                 there is a `path` or paths between start and end.
  2. `Path` -> list of rooms which ants need to pass through to get
             from start to end.
## What do we have ?
  1. Ants
  2. Rooms
  3. Links
  4. Comments

#### Properties of **Ants**.
`What they do ?` Moving from start room to finish one by one room in a time.

`What they can't do ?` Move twice in one move, move in the room which already is busy
with other ant, dance a breakdance.

Every ant will get own order number. So that first started ant will have a number 1,
second will get 2, etc..

#### Properties of **Rooms**
 1. Room has a name
 2. Room has coordinates (x,y)
 
`Names` are needed later when the path and ant movement
will be printed in stdout.

`Coordinates` by now doesn't have sense, it may be used
in future for visual representation of ant farm.

#### Properties of **Links**
Just a link between two rooms.

#### Properties of **Comments**
Simple unuseful comment ... ;)

## Input format

  1. Number of ants
  2. Room declarations
  3. Links

Format has stright order as declared above. I mean for example you can't
declare room in first line, because first program expects `Number of ants`. And you can't
declare some rooms, then link, and than again declare room, etc.. Just follow the order above.
Room declarations and link declarations may be broken by `comments`.

**1. Number of ants**: 

    positive integer, not zero.

**2. Room declaration**:

    Format: <room_name> <x coordinate> <y coordinate>
    
    Example: room1 20 10
               room2 30 40
               ...
**3. Link**:

    Format: <room_name 1>-<room_name 2>
    
    Example: room1-room2
               room3-room4
               ...

**2/3. Comments**:

    Format:
        #<text here>
        
    Example:
        #this is a simple comment
        # Another one
        
### Example of input
```
3
##start
r1 1 1
r2 2 2
r3 3 3
r4 4 4
r5 5 5
# another one
r6 6 6
r7 7 7
##end
r8 8 8
r9 9 9
r10 10 10
r11 11 11
r1-r2
r1-r3
r1-r4
# comment
r2-r5
r3-r6
r4-r7
r5-r8
r6-r9
r7-r10
r9-r8
r10-r11
r11-r8
```

### Example of output
With quiet mode on (-q option).
```
L1-r2 L2-r3
L1-r5 L2-r6 L3-r2
L1-r8 L2-r9 L3-r5
L3-r8 L2-r8
```

## Understanding the output

    Format:
        L<ant number>-<room name>
    Example:
        L1-r2
        
`L1-r2` shows that ant with number `1` moved to room with name `r2`.

## How to install
```
git clone --recurse-submodules https://github.com/oevtushe/lem-in.git && cd lem-in && make
```

## How to launch
```
./lem-in
```
Or to see available program options
```
./lem-in -
```
