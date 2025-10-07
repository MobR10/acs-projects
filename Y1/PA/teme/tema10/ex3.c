#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define ROWS 5
#define COLS 6

typedef struct {
    int row, col;
} Point;

typedef struct {
    Point pos;
    int g; // cost de la start
    int h; // estimare la end
    int f; // g + h
    Point parent;
    bool has_parent;
} Node;

// Obstacolele din imagine (1 = obstacol, 0 = liber)
int grid[ROWS][COLS] = {
    {0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 0},
    {0, 1, 0, 0, 1, 0},
    {0, 0, 0, 0, 1, 0}
};

// Verifică dacă o poziție este validă și liberă
bool is_valid(int row, int col) {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS && grid[row][col] == 0;
}

// Distanța Manhattan
int heuristic(Point a, Point b) {
    return abs(a.row - b.row) + abs(a.col - b.col);
}

// Verifică dacă două puncte sunt egale
bool equal(Point a, Point b) {
    return a.row == b.row && a.col == b.col;
}

// Lista de noduri deschise (open list)
int find_lowest_f(Node open[], int count) {
    int min = 0;
    for (int i = 1; i < count; i++) {
        if (open[i].f < open[min].f)
            min = i;
    }
    return min;
}

// Reconstruiește și afișează drumul
void reconstruct_path(Node closed[], int closed_count, Point end) {
    printf("Drumul gasit:\n");
    Point path[ROWS * COLS];
    int path_len = 0;

    Point current = end;
    bool found = true;

    while (found) {
        found = false;
        for (int i = 0; i < closed_count; i++) {
            if (equal(closed[i].pos, current)) {
                path[path_len++] = current;
                if (closed[i].has_parent) {
                    current = closed[i].parent;
                    found = true;
                }
                break;
            }
        }
    }

    for (int i = path_len - 1; i >= 0; i--)
        printf("(%d,%d) ", path[i].row, path[i].col);
    printf("\n");
}


void a_star(Point start, Point end) {
    Node open[ROWS * COLS];
    int open_count = 0;
    Node closed[ROWS * COLS];
    int closed_count = 0;

    Node start_node = {start, 0, heuristic(start, end), 0, {-1, -1}, false};
    start_node.f = start_node.g + start_node.h;
    open[open_count++] = start_node;

    int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}}; // sus, jos, stanga, dreapta

    while (open_count > 0) {
        int idx = find_lowest_f(open, open_count);
        Node current = open[idx];

        // eliminăm nodul din open
        for (int i = idx; i < open_count - 1; i++)
            open[i] = open[i + 1];
        open_count--;

        closed[closed_count++] = current;

        if (equal(current.pos, end)) {
            reconstruct_path(closed, closed_count, end);
            return;
        }

        for (int d = 0; d < 4; d++) {
            int new_r = current.pos.row + directions[d][0];
            int new_c = current.pos.col + directions[d][1];

            if (!is_valid(new_r, new_c))
                continue;

            Point neighbor = {new_r, new_c};
            bool in_closed = false;
            for (int i = 0; i < closed_count; i++)
                if (equal(closed[i].pos, neighbor)) {
                    in_closed = true;
                    break;
                }
            if (in_closed)
                continue;

            int g = current.g + 1;
            int h = heuristic(neighbor, end);
            int f = g + h;

            bool in_open = false;
            for (int i = 0; i < open_count; i++) {
                if (equal(open[i].pos, neighbor)) {
                    if (f < open[i].f) {
                        open[i].g = g;
                        open[i].h = h;
                        open[i].f = f;
                        open[i].parent = current.pos;
                        open[i].has_parent = true;
                    }
                    in_open = true;
                    break;
                }
            }

            if (!in_open) {
                Node new_node = {neighbor, g, h, f, current.pos, true};
                open[open_count++] = new_node;
            }
        }
    }

    printf("Nu exista drum de la start la end.\n");
}

int main() {
    Point start = {0, 0};
    Point end = {4, 5};

    a_star(start, end);

    return 0;
}
