*This project has been created as part of the 42 curriculum by nfaronia.*

# 📜 Philosophers

## 📝 Description

The Philosophers project is a concurrency and threading simulation inspired by the classic dining philosophers problem.

Each philosopher is represented by a thread that alternates between:
- thinking
- eating
- sleeping

Forks are shared resources protected by mutexes to avoid race conditions. The simulation must ensure that:
- no two philosophers use the same fork at the same time
- no data races occur
- philosophers die if they do not eat within `time_to_die`
- the program stops correctly when a philosopher dies or when a required number of meals is reached (if specified)

This project focuses on understanding:
- threads
- mutexes
- synchronization
- race conditions
- timing accuracy

---

## 📌 Instructions

### 🛠️ Compilation
Compile the project using:

```bash
make
```
Or manually:
```
cc -Wall -Wextra -Werror -pthread *.c -o philo
```

---

### 💻 Execution
Program usage:
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```
Example:
```
./philo 5 800 200 200
./philo 4 410 200 200
./philo 5 800 200 200 7
```
#### Parameters:
- number_of_philosophers: number of philosophers and forks
- time_to_die: time in ms before a philosopher dies without eating
- time_to_eat: time spent eating
- time_to_sleep: time spent sleeping
-  number_of_meals (optional): simulation stops when all philosophers eat this many times

### 🧪 Testing
It is recommended to test with:
- 1 philosopher (edge case: must die)
- 2 philosophers (timing precision test)
- 4 philosophers (basic concurrency test)
- 200 philosophers (stress test)

Use tools such as:
```
valgrind --tool=helgrind ./philo ...
valgrind --leak-check=full ./philo ...
```
---

## 🗃️ Resources

### 📚 References
- [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

- [playlist from CodeVault](https://www.youtube.com/watch?v=d9s_d28yJq0&t=3s)

- 42 Philosophers subject PDF

### 🤖 AI Usage

AI tools were used as an educational aid to find study resources, understand synchronization concepts, improve debugging strategies, write README, and clarify anomalies related to threads and synchronization. These tools were not used to create the entire project logic. 