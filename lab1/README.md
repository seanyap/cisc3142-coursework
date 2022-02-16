## Lab 1 Overview

In this lab, I was given a broken program that needs to read in values from a
CSV file and the task is to fix the program to ensure it is able to perform its
operation correctly.

I decided to use the Map data structure provided by the standard library to relate
or map the relationships between brands & category with all their prices
to provide quick lookup of all the prices for a particular brand/category instead of
iterating the separate vectors storing their values over and over again, which is
not very time efficient. Of course, this is at the expense of space, but I think
tradeoff is well worth it. I also used the Map data structure to relate the
relationships between unique years and the respective SKUs in those years for the
same reason as above, but also to take advantage of the fact that keys in Map
data structure are unique, which satisfy the condition of this assignment.

#### Program Pseudocode:

- read line by line from the csv file
- parse out values that are separated by commas
- insert values into its respective vectors
- iterate over vectors to populate map data structure to indicate relationships among two columns
- iterate map to extract insights (average brand & category price and year vs SKUs)
- generate output file

#### Data flow sketches

![data flow sketches](./dataflow-sketch.png)

### Setup Instructions

1. Clone this repository and cd into project directory

```bash
git clone https://github.com/seanyap/cisc3142-coursework.git && cd lab1
```

2. Run Makefile to compile and build the project

```bash
make lab1
```

3. Run the executable program

```bash
./lab1
```

Delete object file

```bash
make clean
```
