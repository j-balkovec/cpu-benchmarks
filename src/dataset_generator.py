# Jakob Balkovec
# dataset_generator.py

import random
import os

DATA_DIR = "data"

SIZES = {
    "small": 10000,
    "medium": 50000,
    "large": 100000
}


def write_to_file(filename, nums):
    with open(filename, "w") as f:
        for num in nums:
            f.write(f"{num}\n")


def gen_random(size):
    return [random.randint(0, 1000000) for _ in range(size)]


def gen_sorted(size):
    nums = gen_random(size)
    nums.sort()
    return nums


def gen_reverse(size):
    nums = gen_random(size)
    nums.sort(reverse=True)
    return nums


def main():

    os.makedirs(DATA_DIR, exist_ok=True)

    generators = {
        "random": gen_random,
        "sorted": gen_sorted,
        "reverse": gen_reverse
    }

    for name, generator in generators.items():
        for label, size in SIZES.items():

            nums = generator(size)

            filename = f"{DATA_DIR}/{name}_{label}.txt"

            write_to_file(filename, nums)

            print(f"generated {filename} ({size} numbers)")


if __name__ == "__main__":
    main()
