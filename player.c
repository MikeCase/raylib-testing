#include <raylib.h>

typedef struct {
    Rectangle rect;
    int health;
    bool alive;
    int speed;
    bool jump;
    int jumpSpeed;
    int jumpTimer;

} Player;


Player MovePlayer(Player player){
    if (player.alive == false) return player;
    // Move player left/right
    if (IsKeyDown(KEY_RIGHT) &! IsKeyDown(KEY_LEFT_SHIFT)) player.rect.x += player.speed;
    else if (IsKeyDown(KEY_LEFT) &! IsKeyDown(KEY_LEFT_SHIFT)) player.rect.x -= player.speed;
    if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT_SHIFT)) player.rect.x += player.speed * 3;
    else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_LEFT_SHIFT)) player.rect.x -= player.speed * 3;

    if (IsKeyPressed(KEY_SPACE)) {
        player.jump = true;
    }

    if (player.jump) {
        player.jumpTimer += 1;
        if (player.jumpTimer < 60){
            player.rect.y -= player.jumpSpeed - (player.jumpTimer / player.jumpSpeed);
        }
    }

    return player;
}


Player DamagePlayer(Player player, int damage){
    if (player.health <= 0) {
        player.health = 0;
        player.alive = false;
        return player;
    }

    player.health -= damage;

    return player;
}

void DrawPlayer(Rectangle player){
    DrawRectangleRec(player, RED);
}