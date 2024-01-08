def get_data():
    with open("a.csv", "r") as f:
        data = f.read()
    return [int(x) for x in data.split(",")]


def part1(data, noun=12, verb=2):
    ptr = 0
    prog = data[:]
    prog[1] = noun
    prog[2] = verb
    print(prog)
    while True:
        if prog[ptr] == 1:
            prog[prog[ptr + 3]] = prog[prog[ptr + 1]] + prog[prog[ptr + 2]]
        elif prog[ptr] == 2:
            prog[prog[ptr + 3]] = prog[prog[ptr + 1]] * prog[prog[ptr + 2]]
        elif prog[ptr] == 99:
            break
        else:
            print("SHOULDN'T HAPPEN")
        ptr += 4

    return prog[0]


def part2(data):
    for noun in range(100):
        for verb in range(100):
            if part1(data, noun, verb) == 19690720:
                return 100 * noun + verb

data = get_data()   
p1 = part1(data)
print(p1)