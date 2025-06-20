import subprocess
import time
import matplotlib.pyplot as plt
import os
import sys

BINARY_PATH = sys.argv[1]

PARAMS = [
    10000,
    80000,
    100000,
    200000,
    600000,
    800000,
    1000000,
    3000000,
    7000000,
    10000000,
]

REPEATS = 1


def run_and_time(param):
    times = []
    for _ in range(REPEATS):
        start = time.time()
        subprocess.run([BINARY_PATH, str(param)], stdout=subprocess.DEVNULL)
        end = time.time()
        times.append(end - start)
    return sum(times) / REPEATS


def benchmark(params):
    results = []
    for p in params:
        t = run_and_time(p)
        results.append(t)
    return results


def plot_results(params, times):
    plt.plot(params, times, marker="o")
    plt.xlabel("Количество вставок")
    plt.xscale("log")
    plt.ylabel("Время выполнения (сек)")
    plt.title("Бенчмарк")
    plt.grid(True)
    plt.tight_layout()
    plt.show()


def main():
    if not os.path.isfile(BINARY_PATH) or not os.access(BINARY_PATH, os.X_OK):
        sys.exit(1)

    times = benchmark(PARAMS)
    plot_results(PARAMS, times)


if __name__ == "__main__":
    main()
