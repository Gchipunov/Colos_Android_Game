
#ifndef colo_game_gosha_objectlist_hpp
#define colo_game_gosha_objectlist_hpp


#include <vector>
#include "gosha_math.h"

// VRAM Allocates
       // -- spreads UI Text, by Quad for Letters , per quad
	   // -- Game Sprites
	   // -- Player with attachment bones 

typedef struct {
    float x, y, z;
	
	int iDrawIndex; // where to modify ""*vertices_dynamic"" location in point to modify
	int iType; // triangle, quad, 2d? , box, hex
	int iNumVertices;
	int iSubType;    // UI or GameObject, Static Map, editor tool, editor object?
} objectlist;

// https://github.com/lohedges/aabbcc

typedef struct {
  
  int objectlistsID;
  
  float m[16]; //AABB Object coordinates ,Column-major order
  
} BVHBox;


// need functions to move vertices to front and back, like a triangle gets drawn later than a quad

#endif