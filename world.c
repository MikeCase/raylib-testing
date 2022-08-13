#include <raylib.h>
#define MAX_BUILDINGS 100

typedef struct {
    int gravity;
    Rectangle ground;
    Rectangle buildings[MAX_BUILDINGS];
    Color buildingColors[MAX_BUILDINGS];
} World;

void DrawBuildings(Rectangle building[], Color buildingColor[]){
    for (int i=0; i < MAX_BUILDINGS; i++) {
        DrawRectangleRec(building[i], buildingColor[i]);
    }
}
void DrawGround(Rectangle ground){
    DrawRectangleRec(ground, DARKGRAY);
}