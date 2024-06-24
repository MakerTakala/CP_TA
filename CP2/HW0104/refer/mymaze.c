#include "mymaze.h"

static sMaze_info *maze_info;

int32_t find_min_path(const sRoom *pMaze, const uint8_t row, const uint8_t col, sPath *pMinPath) {
    bool has_path = false;

    if (pMaze == NULL || pMinPath == NULL || row == 0 || col == 0) {
        return -1;
    }

    maze_info = create_maze_info(pMaze, row, col);
    
    dfs_find_path((sPoint){0, 0});
    has_path = maze_info->has_path;
    if (has_path) {
        copy_pMinPath(maze_info->pMinPath, pMinPath);
    }
   
    delete_maze_info(maze_info);

    return has_path ? 1 : 0;
}

static void dfs_find_path(const sPoint src_pos) {
    
    if (is_arrive_maze_end(src_pos)) {
        add_room_to_path((sPoint){maze_info->row - 1, maze_info->col - 1});
        update_min_path();
        remove_room_from_path();
        maze_info->has_path = true;
        return;
    }

    add_room_to_path(src_pos);
    
    for (int direction = 0; direction < 4; direction++) {   
        const sPoint dest_pos = get_dest_pos(src_pos, direction);
        if (can_move(src_pos, dest_pos, direction)) {
            dfs_find_path(dest_pos);
        }
    }
    remove_room_from_path();
}

static void add_room_to_path(const sPoint pos) {
    maze_info->found[get_index(pos)] = true;
    maze_info->cur_min_path->pPath[maze_info->cur_min_path->length] = pos;
    maze_info->cur_min_path->cost += get_room(pos)->cost;
    maze_info->cur_min_path->length++;
}

static void remove_room_from_path() {
    maze_info->cur_min_path->length--;
    const sPoint pos = maze_info->cur_min_path->pPath[maze_info->cur_min_path->length];

    maze_info->cur_min_path->cost -= get_room(pos)->cost;
    maze_info->found[get_index(pos)] = false;
    maze_info->cur_min_path->pPath[maze_info->cur_min_path->length] = (sPoint){0, 0};
}

static bool is_arrive_maze_end(const sPoint pos) {
    return pos.row == maze_info->row - 1 && pos.col == maze_info->col - 1;
}

static void update_min_path() {
    if (maze_info->cur_min_path->cost >= maze_info->pMinPath->cost) {
        return;
    }
    
    memcpy(maze_info->pMinPath->pPath,  maze_info->cur_min_path->pPath, maze_info->row * maze_info->col * sizeof(sPoint));
    maze_info->pMinPath->cost = maze_info->cur_min_path->cost;
    maze_info->pMinPath->length = maze_info->cur_min_path->length;
}

static bool can_move(const sPoint src_pos, const sPoint dest_pos, const Direction direction) {
    if (dest_pos.row < 0 || maze_info->row <= dest_pos.row || dest_pos.col < 0 || maze_info->col <= dest_pos.col)  {
        return false;
    }
    if (maze_info->found[get_index(dest_pos)]) {
        return false;
    }
    
    const sRoom *src_room = get_room(src_pos);
    const sRoom *dest_room = get_room(dest_pos);
    if (!has_path(src_room, dest_room, direction)) {
        return false;
    }

    return true;
}

static bool has_path(const sRoom *src_room, const sRoom *dest_room, const Direction direction) {
    if (direction == UP && get_door(src_room, UP) == get_door(dest_room, DOWN)) {
        return true;
    }
    if (direction == RIGHT && get_door(src_room, RIGHT) == get_door(dest_room, LEFT)) {
        return true;
    }
    if (direction == DOWN && get_door(src_room, DOWN) == get_door(dest_room, UP)) {
        return true;
    }
    if (direction == LEFT && get_door(src_room, LEFT) == get_door(dest_room, RIGHT)) {
        return true;
    }

    return false;
}


static int get_index(const sPoint pos) {
    return pos.row * maze_info->col + pos.col;
}

static sRoom* get_room(const sPoint pos) {
    return (sRoom *)(maze_info->pMaze + get_index(pos));
}

static uint8_t get_door(const sRoom *room, const Direction direction) {
    if (direction == UP) {
        return (room->doors & 0b11000000) >> 6;
    }
    if (direction == RIGHT) {
        return (room->doors & 0b00110000) >> 4;
    }
    if (direction == DOWN) {
        return (room->doors & 0b00001100) >> 2;
    }
    if (direction == LEFT) {
        return (room->doors & 0b00000011) >> 0;
    }
    return -1;
}

static sPoint get_dest_pos(const sPoint src_pos, const Direction direction) {
    // UP, RIGHT, DOWN, LEFT
    const int row_dir[4] = {-1, 0, 1, 0};
    const int col_dir[4] = {0, 1, 0, -1};

    return (sPoint){src_pos.row + row_dir[direction], src_pos.col + col_dir[direction]};
}



static sMaze_info* create_maze_info(const sRoom *pMaze, const uint8_t row, const uint8_t col) {
    sMaze_info *maze_info;

    maze_info = calloc(1, sizeof(sMaze_info));
    if (maze_info == NULL) {
        return NULL;
    }

    maze_info->pMaze = pMaze;
    maze_info->row = row;
    maze_info->col = col;
    maze_info->has_path = false;

    maze_info->found = calloc(row * col, sizeof(bool));
    if (maze_info->found == NULL) {
        free(maze_info);
        return NULL;
    }

    maze_info->cur_min_path = create_pMinPath((uint16_t)row * (uint16_t)col);
    maze_info->pMinPath = create_pMinPath((uint16_t)row * (uint16_t)col);
    maze_info->pMinPath->cost = UINT32_MAX;
    if (maze_info->cur_min_path == NULL) {
        free(maze_info->found);
        free(maze_info);
        return NULL;
    }
    
    return maze_info;
}

static void delete_maze_info(sMaze_info *maze_info) {
    if (maze_info == NULL) {
        return;
    }
    if (maze_info->found != NULL) {
        free(maze_info->found);
    }
    free_pMinPath(maze_info->cur_min_path);
    free_pMinPath(maze_info->pMinPath);
    free(maze_info);
}

static sPath* create_pMinPath(const uint16_t size) {
    sPath *pMinPath;

    pMinPath = (sPath *)calloc(1, sizeof(sPath));
    if (pMinPath == NULL) {
        return NULL;
    }

    pMinPath->length = 0;
    pMinPath->cost = 0;
    pMinPath->pPath = calloc(size, sizeof(sPoint));
    if (pMinPath->pPath == NULL) {
        free(pMinPath);
        return NULL;
    }
    return pMinPath;
}

static void free_pMinPath(sPath *pMinPath) {
    if (pMinPath == NULL) {
        return;
    }
    if (pMinPath->pPath != NULL) {
        free(pMinPath->pPath);
    }
    free(pMinPath);
}

static void copy_pMinPath(const sPath *src, sPath *dest) {
    dest->length = src->length;
    dest->cost = src->cost;
    dest->pPath = calloc(src->length, sizeof(sPoint));
    memcpy(dest->pPath, src->pPath, src->length * sizeof(sPoint));
}