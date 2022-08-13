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

/**
 * @brief Player movement
 * 
 * @param player Player
 * @return Player Player
 */
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

/**
 * @brief Give damage to the player.
 * 
 * @param player Player
 * @param damage int: Amount of damage to give.
 * @return Player Player
 */
Player DamagePlayer(Player player, int damage){
    if (player.health <= 0) {
        player.health = 0;
        player.alive = false;
        return player;
    }

    player.health -= damage;

    return player;
}

/**
 * @brief Draw the player to the screen.
 * 
 * @param player Player
 */
void DrawPlayer(Rectangle player){
    DrawRectangleRec(player, RED);
}