# Lem_in

Program that finds optimal routes in a graph.

![](lem-in_demo.gif)

## Description

Algorithmic project on graph theory. It's something like a logistics planner for an ant farm  :) The goal is to move a random number of ants in a labyrinth from the *Start* room to the *End* room in a minimum number of moves.

*This is the project of the Algorithms branch of the School 42 curriculum.*

**Detailed description of the task: [lem-in.en.pdf](https://github.com/dstepanets/Lem_in/blob/master/lem-in.en.pdf)**

## Usage

Compile with `make`. Then run like this:

`./lem-in [-p -c -d -s -n -a] < [map]`

#### Lem-in options:
```
-p	hide discovered paths
-c	hide moves count
-d	allow duplicate links
-s	allow self-links
-n	allow negative coordinates
-a	extend ants limit to max int (NOT RECOMMENDED)
```
Use test files in *_my_maps* directory.

Or generate random maps by the provided _**generator.dms**_. You can either generate map into a file:

```
./generator.dms --big > file
./lem-in < file
```

Or input the generator's output directly to the lem-in executable like this:

`./generator.dms --big | ./lem-in`

#### Generator options:
```
--help : to read the manual
--flow-one : generates an ant farm with distinctive path and [1] ant in it
--flow-ten : generates an ant farm with distinctive path and approximately [10] ants in it
--flow-thousand : generates an ant farm with distinctive path and approximately [100] ants in it
--big : generates a big map (approximately [1000] rooms) to test the time complexity
--big-superposition : generates a big map with overlapping paths
```

**Tested only on Mac OS X.**

## Algorithm

I find all paths from start to end that don't overlap, because any room can be occupied by only one ant at a time. For that I use BFS (Breadth First Search) with a queue. First, I find the shortest route, exclude its rooms from the next searches, and then look for the second shortest route and so on. 

When having the list of routes I move ants on them one by one, starting from the shortest path. Depending on the number of ants and routes lengths, the program choses the best rout for each ant.

## Features

