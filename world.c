#include <raylib.h>

#define MAX_BUILDINGS 100
#define GRAVITY 3

typedef struct {
    int gravity;
    Rectangle ground;
    Rectangle buildings[MAX_BUILDINGS];
    Color buildingColors[MAX_BUILDINGS];
} World;

Texture2D groundTexture;

/**
 * @brief Initialize the environment.
 *
 * @param buildings Rectangle[]
 * @param buildingColors Color[]
 * @param maxBuildings int
 * @param screenWidth int
 * @param screenHeight int
 * @return World
 */
World InitWorld(Rectangle buildings[], Color buildingColors[], int maxBuildings, int screenWidth, int screenHeight){
    World myWorld;

    // Set initial environment settings
    myWorld.gravity = GRAVITY;
    myWorld.ground.x = -6000;
    myWorld.ground.y = 320;
    myWorld.ground.width = 13000;
    myWorld.ground.height = 8000;

    // groundTexture = LoadTexture('resources/ground.png');

    // Generate buildings in background.
    int spacing = 0;
    for (int i = 0; i < maxBuildings; i++){
        myWorld.buildings[i].width = (float)GetRandomValue(50, 200);
        myWorld.buildings[i].height = (float)GetRandomValue(screenHeight/4,screenHeight);
        myWorld.buildings[i].y = screenHeight - 448.0f - myWorld.buildings[i].height;
        myWorld.buildings[i].x = -6000.0f + spacing;

        spacing += (int)myWorld.buildings[i].width;

        myWorld.buildingColors[i] = (Color){ GetRandomValue(100,240), GetRandomValue(100,240), GetRandomValue(100, 240), 255 };
    }
    return myWorld;
}

/**
 * @brief Draw the buildings to the screen.
 *
 * @param building Rectangle[]
 * @param buildingColor Color[]
 */
void DrawBuildings(Rectangle building[], Color buildingColor[]){
    for (int i=0; i < MAX_BUILDINGS; i++) {
        DrawRectangleRec(building[i], buildingColor[i]);
    }
}

/**
 * @brief Draw the ground to the screen.
 *
 * @param ground Rectangle
 */
void DrawGround(Rectangle ground){
    DrawRectangleRec(ground, DARKGRAY);
}