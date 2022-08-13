#include <stdio.h>
#include <raylib.h>

typedef struct {
    float lifeTime;
} Timer;

void StartTimer(Timer* timer, float lifeTime) {
    if (timer != NULL){
        timer->lifeTime = lifeTime;
    }
}

void UpdateTimer(Timer* timer) {
    // Subtract this frames time from the timer if it's not already expired.
    if (timer != NULL && timer->lifeTime > 0) {
        timer->lifeTime -= GetFrameTime();
    }
}

bool TimerDone(Timer* timer) {
    if (timer != NULL) {
        return timer->lifeTime <= 0;
    }
}