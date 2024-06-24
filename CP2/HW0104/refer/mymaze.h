#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct _sRoom{
    uint32_t cost;
    uint8_t doors; // 8 bits: aabbccdd
    // aa: the up door number 0-3
    // bb: the right door number 0-3
    // cc: the down number 0-3
    // dd: the left door number 0-3
} sRoom;

typedef struct _sPoint {
    uint32_t row;
    uint32_t col;
} sPoint;

typedef struct _sPath {
    uint32_t length; // Path length.
    uint32_t cost; // Cost
    sPoint *pPath; // An array of all points in order.
} sPath;

typedef enum Direction{
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
}Direction;

typedef struct _sMaze_info {
    const sRoom *pMaze;
    sPath *cur_min_path;
    sPath *pMinPath;
    uint32_t row;
    uint32_t col;
    bool *found;
    bool has_path;
} sMaze_info;

// The start point is pMaze[0][0] and the exit point is pMaze[row -1][col -1]
// If there is no path , return 0; otherwise , return 1;
int32_t find_min_path(const sRoom *pMaze, const uint8_t row, const uint8_t col, sPath *pMinPath);
static void dfs_find_path(const sPoint src_pos);
static void add_room_to_path(const sPoint pos);
static void remove_room_from_path();
static bool is_arrive_maze_end(const sPoint pos);
static void update_min_path();
static bool can_move(const sPoint src_pos, const sPoint dest_pos, const Direction next_direction);
static bool has_path(const sRoom *src_room, const sRoom *dest_room, const Direction next_direction);
static int get_index(const sPoint pos);
static sRoom* get_room(const sPoint pos);
static uint8_t get_door(const sRoom *room, const Direction direction);
static sPoint get_dest_pos(const sPoint src_pos, const Direction next_direction);
static sMaze_info* create_maze_info(const sRoom *pMaze, const uint8_t row, const uint8_t col);
static void delete_maze_info(sMaze_info *maze_info);
static sPath* create_pMinPath(const uint16_t size);
static void free_pMinPath(sPath *pMinPath);
static void copy_pMinPath(const sPath *src, sPath *dest);