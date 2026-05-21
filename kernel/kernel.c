#include "../include/types.h"

// VGA text buffer address - this is where screen output lives
#define VGA_BUFFER 0xB8000
#define VGA_WHITE_ON_BLACK 0x0F

// Write a string directly to the VGA buffer (your screen)
void print(const char* str) {
    uint16_t* vga = (uint16_t*)VGA_BUFFER;
    int i = 0;
    while (str[i] != '\0') {
        vga[i] = (uint16_t)str[i] | (uint16_t)(VGA_WHITE_ON_BLACK << 8);
        i++;
    }
}

// This is the main entry point - called by the bootloader
void kernel_main() {
    print("Caliber OS - Booting...");

    // Hang forever (for now)
    while (1) {}
}