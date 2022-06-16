# Trainer

## How to use
- Go to Trainer root directory and execute the following command
  
  ``` $ . trenv `pwd` ```

- _startup_ command will initiate Trainer server
- Fill in solution_#.cc files in $TRAINER_HOME/solutions/solutions directory
  - Any C++ codes (i.e., .h, .cc files) in $TRAINER_HOME/solutions/solutions will be compiled
- _trainer_ command will open trainer CLI
- Use commands given in trainer CLI to build and execute your solutions

## Build
- _build_ command in trainer CLI will compile solutions with optimal mode

## Execute
- _run_ command in trainer CLI will show you the list of problems
- Choose the solution you would like to execute and trainer will execute and verify your solution
- After verification, trainer will print whether the solution produce correct results; it will also print the elapsed time

## Debug
- _debug_ command will first build your solution with debug mode
- After build is complete, the list of problems will show again
- Choose the solution you would like to debug, and trainer will attach cgdb to the chosen solution
- Set the breakpoint at the solution function (e.g., SolutionForProblem#) and run the debugger

## Coding Style
- Although it's none of my business, I recommend following Google Coding Style Guide
- https://google.github.io/styleguide/cppguide.html
