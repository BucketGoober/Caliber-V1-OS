#include "../include/types.h"
#include "../include/vga.h"

void kernel_main() {
    // Initialize VGA driver
    vga_init();

    // Print Caliber OS boot message
    vga_print_color("Caliber OS\n", VGA_LIGHT_CYAN, VGA_BLACK);
    vga_print_color("Version 1.0\n", VGA_LIGHT_GREY, VGA_BLACK);
    vga_print_color("------------\n", VGA_DARK_GREY, VGA_BLACK);
    vga_print("Booting...\n");

    // Hang forever
    while (1) {}
}