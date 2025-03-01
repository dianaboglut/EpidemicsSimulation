# EpidemicsSimulation
This project involves implementing and parallelizing a simplified epidemic simulation in C. The simulation models the spread of an infectious disease within a population that moves within a rectangular area. Each person moves in a fixed direction with a defined amplitude, reversing at borders. Infection occurs only when individuals remain at the same location during a simulation step. Individuals transition through states: **susceptible, infected, and immune**, with fixed durations for infection and immunity. The goal is to predict disease spread over time using parallel computing to enhance simulation performance.

## Features
- Simulates the spread of an infectious disease
- Models movement, infection, and immunity cycles
- Supports parallelization for improved performance

## Installation & Setup
### Requirements
- C Compiler (e.g., GCC)
- OpenMP for parallel execution

### Compilation
#### Without debugging
```
make
```

#### With debugging
```
make debug
```
#### Running the Program
```
./test <TOTAL_SIMULATION_TIME> <InputFileName> <ThreadNumber>
```
#### For a test with 100 simulation time, 500k people and 8 threads
![image](https://github.com/user-attachments/assets/c804abf8-3007-4f00-9194-1bacf6d32290)
