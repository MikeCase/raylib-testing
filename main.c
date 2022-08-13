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
#include "world.c"
#include "ui.c"

#define MAX_BUILDINGS 100

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
    Player myPlayer;

    myPlayer.rect.x = 400;
    myPlayer.rect.y = 260;
    myPlayer.rect.width = 40;
    myPlayer.rect.height = 60;
    myPlayer.health = 100;
    myPlayer.alive = true;
    myPlayer.jumpSpeed = 8;
    myPlayer.jump = false;
    myPlayer.jumpTimer = 0;
    myPlayer.speed = 2;

    // Build world
    World environment;
    environment.gravity = 3;
    environment.ground.x = -6000;
    environment.ground.y = 320;
    environment.ground.width = 13000;
    environment.ground.height = 8000;

    int spacing = 0;
    for (int i = 0; i < MAX_BUILDINGS; i++){
        environment.buildings[i].width = (float)GetRandomValue(50, 200);
        environment.buildings[i].height = (float)GetRandomValue(100,800);
        environment.buildings[i].y = screenHeight - 130.0f - environment.buildings[i].height;
        environment.buildings[i].x = -6000.0f + spacing;

        spacing += (int)environment.buildings[i].width;

        environment.buildingColors[i] = (Color){ GetRandomValue(100,240), GetRandomValue(100,240), GetRandomValue(100, 240), 255 };
    }

    Camera2D camera = { 0 };
    camera.target = (Vector2){ myPlayer.rect.x + 20.0f, myPlayer.rect.y + 20.0f };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

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

        // Camera Rotation.
        if (IsKeyDown(KEY_A)) camera.rotation--;
        else if (IsKeyDown(KEY_S)) camera.rotation++;

        // Limit camera rotation to 80 degrees
        if (camera.rotation > 40) camera.rotation = 40;
        else if (camera.rotation < -40) camera.rotation = -40;

        // Zoom controls
        if (IsKeyDown(KEY_UP)) camera.zoom += 0.05f;
        else if (IsKeyDown(KEY_DOWN)) camera.zoom -= 0.05f;

        // Limit Zoom
        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

        if (IsKeyPressed(KEY_R)) {
            camera.zoom = 1.0f;
            camera.rotation = 0.0f;
        }

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
            DrawInfoBox();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
