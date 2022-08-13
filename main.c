#include "raylib.h"
#include "raymath.h"
#include "player.c"
#include "game_camera.c"
#include "game_timer.c"
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
    const int screenWidth = 1366;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    ToggleFullscreen();

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

            // // Toggle full screen
            // if (IsKeyPressed(KEY_F11) &! IsWindowFullscreen()){
            //     CloseWindow();
            //     InitWindow(1366,768, "My Game");
            //     ToggleFullscreen();
            // } else if (IsKeyPressed(KEY_F11) && IsWindowFullscreen()){
            //     CloseWindow();
            //     InitWindow(screenWidth, screenHeight, "My Game");
            // }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
