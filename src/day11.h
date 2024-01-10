// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav
// Licensed under the MIT license.

// Space Police

#include "../lib/emulator.h"
#define DIMENSION 1024
#define INPUTS 1
#define MEMORY 4096
#define OUTPUTS 2

struct Cell
{
    bool value;
    bool exists;
};

typedef struct Cell* Cell;
typedef struct Cell* Matrix;

int day11_robot(Matrix matrix, bool white)
{
    Word inputs[INPUTS];
    Word memory[MEMORY];
    Word outputs[OUTPUTS];
    int total = 1;
    int direction = 0;
    int x = DIMENSION / 2;
    int y = DIMENSION / 2;
    struct Emulator robot;

    parser_parse(stdin, memory);
    emulator(&robot, memory);
    queue(&robot.inputs, inputs, INPUTS);
    queue(&robot.outputs, outputs, OUTPUTS);
    queue_enqueue(&robot.inputs, white);

    while (emulator_execute(&robot))
    {
        Word white;
        Word right;
        Cell cell = matrix + x * DIMENSION + y;

        queue_try_dequeue(&robot.outputs, &white);
        queue_try_dequeue(&robot.outputs, &right);

        cell->value = white;

        if (!cell->exists)
        {
            cell->exists = true;
            total++;
        }
        
        if (right) 
        {
            direction = (direction + 3) % 4;
        }
        else
        {
            direction = (direction + 1) % 4;
        }

        switch (direction)
        {
            case 0: y--; break;
            case 1: x--; break;
            case 2: y++; break;
            case 3: x++; break;
        }
        
        queue_enqueue(&robot.inputs, matrix[x * DIMENSION + y].value);
    }

    return total;
}
