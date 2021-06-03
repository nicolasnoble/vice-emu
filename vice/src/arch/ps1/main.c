#include "vice.h"

#include <stdio.h>

#include "log.h"
#include "machine.h"
#include "main.h"
#include "video.h"

int main() {
    return main_program(1, "vice.exe");
}

void main_exit(void) {
    log_message(LOG_DEFAULT, _("\nExiting..."));
    machine_shutdown();
    putchar('\n');
}
