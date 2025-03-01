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

#### For a test with 10 simulation time, 10 people and 2 threads, with debug
![image](https://github.com/user-attachments/assets/91b91932-59da-4c80-96e1-d492db2b2de8)
![image](https://github.com/user-attachments/assets/6b091080-7818-45b1-9a6c-421d9a999e97)
![image](https://github.com/user-attachments/assets/f6f10a50-2ec3-4ed0-817c-8d5c24039576)
![image](https://github.com/user-attachments/assets/089212ef-95f1-40d6-91ec-cf7d186e1382)
![image](https://github.com/user-attachments/assets/8d8ba5a5-d5b3-4963-9f98-4051d8f5ae1d)
![image](https://github.com/user-attachments/assets/1f7ebd4a-68fd-40dd-b0a9-419a48ff7d94)
![image](https://github.com/user-attachments/assets/eee68be5-3832-4f8f-93e5-c408fb8317ac)
![image](https://github.com/user-attachments/assets/9e125501-7d61-4c7f-b6a2-e7e4dffdfe51)
![image](https://github.com/user-attachments/assets/3562c2d5-6cd1-4163-aecd-845c1bbd2573)
![image](https://github.com/user-attachments/assets/488c5058-c127-4653-94fc-f1bdb064547a)
![image](https://github.com/user-attachments/assets/43917142-cf94-46df-9ca7-3c7c7bd9e7bd)


