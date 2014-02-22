#include "tests/lib.h"
#include "game/display.h"
#include "game/config.h"

int x = 10;
int y = 5;

void move(int dx, int dy) {
    x += dx; y += dy;
    if(x < 1) x = 1;
    if(y < 1) y = 1;
    if(x >= WIDTH-1) x = WIDTH-2;
    if(y >= HEIGHT-1) y = HEIGHT-2;
}

int main(void) {
    display_t disp;
    char c;
    int i;
    heap_init();

    display_init(&disp, WIDTH, HEIGHT);

    // Put in the walls
    for(i = 0; i < disp.width; i++) {
        display_set(&disp, '-', i, 0);
        display_set(&disp, '-', i, disp.height - 1);
    }
    for(i = 1; i < disp.height-1; i++) {
        display_set(&disp, '|', 0, i);
        display_set(&disp, '|', disp.width - 1, i);
    }

    // Place player and show!
    display_set(&disp, 'x', x, y);
    display_flip(&disp);
    while((c = getc_raw()) != 'q') {
        display_set(&disp, ' ', x, y);
        if(c == 'a') {
            move(-1,0);
        } else if(c == 'd') {
            move(1,0);
        } else if(c == 'w') {
            move(0,-1);
        } else if(c == 's') {
            move(0,1);
        }
        display_set(&disp, 'x', x, y);
        display_flip(&disp);
    }

    syscall_halt();
    syscall_exit(0);
    return 0;
}
