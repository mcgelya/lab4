import subprocess
import time
import matplotlib.pyplot as plt

PARAMS = [
    100,
    200,
    500,
    10000,
    20000,
    30000,
    40000,
    80000,
    100000,
    120000,
    150000,
    200000,
    600000,
    800000,
    1000000,
    3000000,
    7000000,
    10000000,
]

REPEATS = 1


def run_and_time(binary, param):
    times = []
    for _ in range(REPEATS):
        print(param)
        start = time.time()
        subprocess.run([binary, str(param)], stdout=subprocess.DEVNULL)
        end = time.time()
        times.append(end - start)
    return sum(times) / REPEATS


def benchmark(binary, params):
    results = []
    for p in params:
        t = run_and_time(binary, p)
        results.append(t)
    return results


def main():
    plt.xlabel("Размер дерева")
    plt.xscale("log")
    plt.ylabel("Время выполнения (сек)")

    times_insert = benchmark("../build-release/tests/stress_insert", PARAMS)
    plt.plot(PARAMS, times_insert)

    times_erase = benchmark("../build-release/tests/stress_erase", PARAMS)
    plt.plot(PARAMS, times_erase)

    times_map = benchmark("../build-release/tests/stress_map", PARAMS[:10])
    plt.plot(PARAMS[:10], times_map)

    plt.legend(["Вставки", "Удаления", "Map"])
    plt.grid(True)
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
