#include "../include/maze.h"

#include <stdio.h>

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
    size_t id = 0;

    size_t i = 0, j = 0;
    for(i = 0; i < MAX_DIM && fgets(buf, sizeof(buf), f); i++) {
        for(j = 0; j < MAX_DIM && buf[j] != '\n' && buf[j] != '\0'; j++) {
            self->map[i][j] = (node_t) {
                .id = id++,
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

    fprintf(stderr, "i: %zu, j: %zu\n", i, j);

#ifdef HEAP_SET
    self->open_set = heap_init(self->height * self->width);
#else
    self->open_set = array_init(self->height * self->width);
#endif

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
    if(self) {
        for(size_t i = 0; i < MAX_DIM; i++) {
            free(self->map[i]);
        }
        free(self->map);

#ifdef HEAP_SET
        heap_free(self->open_set);
#else
        array_free(self->open_set);
#endif
        
        free(self);
    }
}

static inline int maze_heuristic(int src_x, int src_y, int dest_x, int dest_y) {
    return abs(dest_x - src_x) + abs(dest_y - src_y);
}

static void maze_add_to_open_set(maze_t* self, node_t* node) {
#ifdef HEAP_SET
    heap_push(self->open_set, node);
#else
    array_push(self->open_set, node);
#endif
}

static node_t* maze_lowest_f_score(maze_t* self) {
#ifdef HEAP_SET
    return heap_pop(self->open_set);
#else
    return array_pop(self->open_set);
#endif
}

static uint8_t maze_is_set_empty(maze_t* self) {
#ifdef HEAP_SET
    return heap_is_empty(self->open_set);
#else
    return array_is_empty(self->open_set);
#endif
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
    
    const int delta_x[4] = {0, 1, 0, -1};
    const int delta_y[4] = {-1, 0, 1, 0};

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

    if(node_is_wall(start)) {
        goto error;
    }
    
    while(!maze_is_set_empty(self)) {
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
            int nx = curr->x + delta_x[i];
            int ny = curr->y + delta_y[i];

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
