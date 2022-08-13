#include <raylib.h>

/**
 * @brief Draw the help/info box on the screen.
 *
 * @param hidden bool
 */
void DrawInfoBox(bool hidden){
    if (hidden == false) {
        DrawRectangle( 10, 10, 250, 133, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines( 10, 10, 250, 133, BLUE);

        DrawText("Free 2d camera controls:", 20, 20, 10, BLACK);
        DrawText("- Right/Left to move Offset", 40, 40, 10, DARKGRAY);
        DrawText("- Up/Down to zoom in and out", 40, 60, 10, DARKGRAY);
        DrawText("- A / S to Rotate", 40, 80, 10, DARKGRAY);
        DrawText("- R to reset Zoom and Rotation", 40, 100, 10, DARKGRAY);
        DrawText("- Space to jump", 40, 120, 10, DARKGRAY);
    }
}
