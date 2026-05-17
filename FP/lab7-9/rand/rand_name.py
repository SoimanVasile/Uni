import random
import string


def generate_random_name():
    length = generate_length()
    charset = string.ascii_letters
    name = ""

    for _ in range(length):
        random_char = random.choice(charset)
        name += random_char

    return name


def generate_length():
    length = random.randint(1, 15)
    return length


if __name__ == "__main__":
    random.seed(5)
    name = generate_random_name()

    print(name)
