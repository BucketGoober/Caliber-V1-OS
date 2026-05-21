#include "../include/vga.h"

static uint16_t* vga_buffer = (uint16_t*)VGA_BUFFER;
static uint32_t cursor_x = 0;
static uint32_t cursor_y = 0;
static vga_color current_fg = VGA_WHITE;
static vga_color current_bg = VGA_BLACK;

// Combine fore and background color into a single byte
static uint8_t vga_make_color(vga_color fg, vga_color bg) {
    return fg | bg << 4;
}

// Combine character and color into a VGA entry
static uint16_t vga_make_entry(char c, uint8_t color) {
    return (uint16_t)c | (uint16_t)color << 8;
}

// Initialize VGA
void vga_init() {
    cursor_x = 0;
    cursor_y = 0;
    vga_clear();
}

// Clear the screen
void vga_clear() {
    uint8_t color = vga_make_color(VGA_WHITE, VGA_BLACK);
    for (uint32_t y = 0; y < VGA_HEIGHT; y++) {
        for (uint32_t x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[y * VGA_WIDTH + x] = vga_make_entry(' ', color);
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

// Scroll screen up one line
static void vga_scroll() {
    uint8_t color = vga_make_color(VGA_WHITE, VGA_BLACK);
    for (uint32_t y = 0; y < VGA_HEIGHT - 1; y++) {
        for (uint32_t x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[y * VGA_WIDTH + x] = vga_buffer[(y + 1) * VGA_WIDTH + x];
        }
    }
    // Clear last line
    for (uint32_t x = 0; x < VGA_WIDTH; x++) {
        vga_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_make_entry(' ', color);
    }
    cursor_y = VGA_HEIGHT - 1;
}

// New line
void vga_newline() {
    cursor_x = 0;
    cursor_y++;
    if (cursor_y >= VGA_HEIGHT) {
        vga_scroll();
    }
}

// Print a string with specific colors
void vga_print_color(const char* str, vga_color fg, vga_color bg) {
    uint8_t color = vga_make_color(fg, bg);
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            vga_newline();
        } else {
            vga_buffer[cursor_y * VGA_WIDTH + cursor_x] = vga_make_entry(str[i], color);
            cursor_x++;
            if (cursor_x >= VGA_WIDTH) {
                vga_newline();
            }
        }
        i++;
    }
}

// Print a string with default colors
void vga_print(const char* str) {
    vga_print_color(str, VGA_WHITE, VGA_BLACK);
}