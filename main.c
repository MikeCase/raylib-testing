// #include <raylib.h>
/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0

*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "player.c"
#include "game_camera.c"
#include "world.c"
#include "ui.c"

#define MAX_BUILDINGS 100

bool hidden = false;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // Build Player
    Player myPlayer = InitPlayer();

    // Initialize world
    World environment = InitWorld(environment.buildings, environment.buildingColors, MAX_BUILDINGS, screenWidth, screenHeight);

    // Initialize Camera
    Camera2D camera = InitCam(myPlayer.rect, screenWidth, screenHeight);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        myPlayer.rect.y += environment.gravity;

        if (CheckCollisionRecs(myPlayer.rect, environment.ground)) {
            myPlayer.rect.y = environment.ground.y-myPlayer.rect.height;
            myPlayer.jumpTimer = 0;
            myPlayer.jump = false;
        }

        myPlayer = MovePlayer(myPlayer);

        camera.target = (Vector2){ myPlayer.rect.x + 20, myPlayer.rect.y + 20 };

        camera = MoveCamera(camera);

        if (IsKeyPressed(KEY_D)) myPlayer = DamagePlayer(myPlayer, 5);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            // Blank canvas
            ClearBackground(RAYWHITE);

            // Start camera view
            BeginMode2D(camera);

                // Draw the ground plane
                DrawGround(environment.ground);

                // Draw buildings in the background
                DrawBuildings(environment.buildings, environment.buildingColors);

                // Draw the player
                DrawPlayer(myPlayer.rect);

            EndMode2D();

            // Display player health
            DrawText(TextFormat("Player Health: %i", myPlayer.health), 600, 10, 20, GREEN);

            // Draw infobox with key help
            if(IsKeyPressed(KEY_F1) && hidden == false){
                hidden = true;
            } else if (IsKeyPressed(KEY_F1) && hidden == true) {
                hidden = false;
            }
            DrawInfoBox(hidden);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
