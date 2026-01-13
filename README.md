# Philosophers

Short Description
-----------------
A POSIX C implementation of the Dining Philosophers problem with two modes:
- a threads-based implementation using pthreads and mutexes (primary)
- a process-based implementation using POSIX semaphores (bonus)

The project demonstrates concurrency control, timing accuracy, and graceful termination in a canonical concurrency problem.

Key Features
------------
- Threaded implementation with per-philosopher mutexes and a monitor thread
- Bonus process-based implementation using semaphores for inter-process synchronization
- Deterministic timing utilities for millisecond and microsecond precision
- Graceful shutdown on philosopher death or when all philosophers have eaten required times
- Robust argument validation and defensive mutex/semaphore initialization

Tech Stack
----------
- Language: C (C99 / POSIX)
- Concurrency: pthreads, POSIX mutexes, POSIX semaphores (bonus)
- Build: Makefile, clang
- Platform assumptions: UNIX-like OS (Linux, macOS) with POSIX APIs

Architecture & Design
---------------------
- Central data structures:
  - [`t_table`](include/philo.h) holds global state and synchronization primitives ([`include/philo.h`](include/philo.h))
  - [`t_philo`](include/philo.h) represents each philosopher and per-philosopher state
- Threaded mode:
  - Main creates philosopher threads ([`start_philos`](src/start_dinner.c)) and a monitor thread ([`ft_monitor`](src/monitor.c))
  - Philosophers run [`ft_routine`](src/routine.c) which loops through take-eat-sleep-think
  - Timing via [`get_time_milli`](src/times.c) and [`ft_usleep`](src/times.c)
- Bonus mode:
  - Forks are separate processes coordinated by semaphores (see bonus sources under `bonus/`)
- Synchronization is handled either by pthread mutexes (`src/`) or semaphores (`bonus/src_bonus/`)

Getting Started
---------------
Prerequisites
- clang or gcc
- make
- POSIX-compliant environment (Linux or macOS)
- For bonus mode: semaphores (provided by libc on POSIX systems)

Installation
- Clone the repository (assume default path)
- Build the default threaded program:
  ```bash
  make
  ```

- Build the bonus (process + semaphores) program:

  ```bash
  make bonus
  ```

Running the project

- Threaded (default):

  ```bash
    ./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_must_eat]
  ```

Example:
  ```bash
    ./philo 5 800 200 200 7
  ```

- Bonus (process + semaphores):

  ```bash
    ./philo_bonus number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_must_eat]
  ```

Usage
-----

- CLI arguments:
    1. number_of_philosophers (int)
    2. time_to_die (ms)
    3. time_to_eat (ms)
    4. time_to_sleep (ms)
    5. [optional] number_of_times_each_must_eat (int)

- The program prints timestamped actions to stdout, e.g. "123 3 is eating".
- Termination:
    - A philosopher dying triggers a graceful stop and final message.
    - If a must-eat count is provided, the simulation ends when all philosophers reach it.
- Important implementation points: see main[](src/main.c), [](http://_vscodecontentref_/0)init_table, and start_dinner for entry and lifecycle management.

Relevant files & symbols

- Build: Makefile
- Program entry: main
- Table initialization: init_table
- Start routines: start_dinner[](src/start_dinner.c), [](http://_vscodecontentref_/5)start_philos
- Philosopher routine: ft_routine
- Monitor: ft_monitor
- Timing utilities: get_time_milli[](src/times.c), [](http://_vscodecontentref_/8)ft_usleep
- Public types & API: philo.h
- Bonus implementations: files under src_bonus (e.g. init_table_bonus[](bonus/src_bonus/init_table_bonus.c), [](http://_vscodecontentref_/11)
routine_monitor_bonus)

What I Learned / Technical Challenges
-------------------------------------

- Correctly coordinating shared state under high concurrency and timing constraints
- Designing safe initialization and teardown of mutexes/semaphores to avoid leaks and deadlocks
- Achieving accurate sleeps without busy-waiting using a microsecond-based helper (ft_usleep)
- Differences and trade-offs between thread-based and process-based synchronization (mutexes vs semaphores)

Future Improvements
-------------------

- Add automated unit and integration tests for concurrency paths (use CI)
- Add sanitizers (ASan/TSan) to detect races and memory issues during development
- Improve CLI and logging (structured logs, verbosity flags)
- Add runtime configuration and benchmarking harness to measure timing fidelity
- Harden error handling and resource cleanup across all failure paths

Author & Contact
----------------

- Author: schamizo
- Contact: salvadorchamizo@gmail.com

Notes & Assumptions
-------------------

- This README assumes a UNIX-like development environment and standard POSIX APIs.
- For implementation details, see the listed source files above (links to file paths within the repository).