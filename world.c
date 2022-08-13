#include <raylib.h>
#define MAX_BUILDINGS 100

typedef struct {
    int gravity;
    Rectangle ground;
    Rectangle buildings[MAX_BUILDINGS];
    Color buildingColors[MAX_BUILDINGS];
} World;