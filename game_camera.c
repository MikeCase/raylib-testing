#include <raylib.h>


Camera2D InitCam(Rectangle playerRect, int screenWidth, int screenHeight) {
    Camera2D camera;

    camera.target = (Vector2){ playerRect.x + 20.0f, playerRect.y + 20.0f };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    return camera;
}

Camera2D MoveCamera(Camera2D camera){
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

        return camera;

}