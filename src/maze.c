#include "../include/maze.h"

#include <stdio.h>

static const int dir_x[4] = {0, 1, 0, -1};
static const int dir_y[4] = {-1, 0, 1, 0};

maze_t* maze_read(char* path) {
    FILE* f = fopen(path, "r");
    if(!f) {
        fprintf(stderr, "error: couldn't open file `%s` in `maze_read` function\n", path);
        exit(1);
    }

    maze_t* self = (maze_t*)malloc(sizeof(maze_t));
    
    self->map = (node_t**)malloc(MAX_DIM * sizeof(node_t*));
    if(!self->map) {
        fprintf(stderr, "error: couldn't allocate memory in `maze_read` function\n");
        exit(1);
    }

    for(size_t i = 0; i < MAX_DIM; i++) {
        self->map[i] = (node_t*)malloc(MAX_DIM * sizeof(node_t));
        if(!self->map[i]) {
            fprintf(stderr, "error: couldn't allocate memory in `maze_read` function\n");
            exit(1);
        }
    }

    char buf[MAX_DIM+2];

    size_t i = 0, j = 0;
    for(i = 0; i < MAX_DIM && fgets(buf, sizeof(buf), f); i++) {
        for(j = 0; j < MAX_DIM && buf[j] != '\n' && buf[j] != '\0'; j++) {
            self->map[i][j] = (node_t) {
                .symbol = buf[j],
                .g_score = MAX_SIZE,
                .h_score = MAX_SIZE,
                .f_score = MAX_SIZE,
                .x = j,
                .y = i,
                .px = 0,
                .py = 0,
            };
        }
    }

    self->height = i;
    self->width = j;

    self->open_set_len = 0;
    self->open_set_cap = self->height * self->width;
    self->open_set = (node_t**)malloc(self->open_set_cap * sizeof(node_t*));

    fclose(f);
    
    return self;
}

void maze_print(maze_t* self) {
    if(!self) {
        fprintf(stderr, "error: null value `self` in `maze_print` function\n");
        exit(1);
    }
        
    for(size_t i = 0; i < self->height; i++) {
        for(size_t j = 0; j < self->width; j++) {
            printf("%c", self->map[i][j].symbol);
        }
        printf("\n");
    }
}

void maze_free(maze_t* self) {
    for(size_t i = 0; i < MAX_DIM; i++) {
        free(self->map[i]);
    }
    free(self->map);
    free(self);
}

static inline int maze_heuristic(int src_x, int src_y, int dest_x, int dest_y) {
    return abs(dest_x - src_x) + abs(dest_y - src_y);
}

static void maze_add_to_open_set(maze_t* self, node_t* node) {
    if(self->open_set_len >= self->open_set_cap) {
        fprintf(stderr, "error: can't push to open_set in `maze_add_to_open_set` function\n");
        exit(1);
    }

    for(size_t i = 0; i < self->open_set_len; i++) {
        if(node_equals(self->open_set[i], node)) {
            return;
        }
    }
    
    self->open_set[self->open_set_len++] = node;
}

static node_t* maze_lowest_f_score(maze_t* self) {
    if(self->open_set_len == 0) return NULL;

    node_t* n = self->open_set[0];
    size_t idx = 0;
    
    for(size_t i = 0; i < self->open_set_len; i++) {
        if(self->open_set[i]->f_score < n->f_score) {
            n = self->open_set[i];
            idx = i;
        }
    }

    for(size_t i = idx; i < self->open_set_len-1; i++) {
        self->open_set[i] = self->open_set[i+1];
    }
    
    self->open_set_len--;

    return n;
}

static void maze_trace_path(maze_t* self, node_t* start, node_t* end) {
    node_t* n = end;
    
    while(!node_equals(n, start)) {
        n->symbol = 'o';
        n = &self->map[n->py][n->px];
    }

    n->symbol = 'o';
}

void maze_a_star(maze_t* self) {
    if(!self) {
        fprintf(stderr, "error: null value `self` in `maze_a_star` function\n");
        exit(1);
    }
    
    size_t src_x = 0; 
    size_t src_y = 0;
    size_t dest_x = self->width-1;
    size_t dest_y = self->height-1;

    node_t* start = &self->map[src_y][src_x];
    node_t* end = &self->map[dest_y][dest_x];
    start->g_score = 0;
    start->h_score = maze_heuristic(src_x, src_y, dest_x, dest_y);
    start->f_score = start->h_score;
    maze_add_to_open_set(self, start);
    
    while(self->open_set_len) {
        node_t* curr = maze_lowest_f_score(self);

        if(!curr) {
            goto error;
        }

        if(node_equals(curr, end)) {
            maze_trace_path(self, start, end);
            maze_print(self);
            return;
        }

        for(size_t i = 0; i < 4; i++) {
            int nx = curr->x + dir_x[i];
            int ny = curr->y + dir_y[i];

            if(nx >= (int)self->width || nx < 0 || ny >= (int)self->height || ny < 0) continue;
            node_t* neighbor = &self->map[ny][nx];
            
            if(node_is_wall(neighbor)) continue;
            
            if(curr->g_score+1 < neighbor->g_score) {
                neighbor->px = curr->x;
                neighbor->py = curr->y;
                neighbor->g_score = curr->g_score+1;
                neighbor->h_score = maze_heuristic(nx, ny, dest_x, dest_y);
                neighbor->f_score = neighbor->g_score + neighbor->h_score;

                maze_add_to_open_set(self, neighbor);
            }
        }
    }

error:
    printf("no solution found\n");
}
