; Caliber OS Bootloader
; This is the first code that runs when Caliber boots

[BITS 16]           ; We start in 16-bit mode (how all x86 PCs boot)
[ORG 0x7C00]        ; BIOS always loads the bootloader at this memory address

START:
    ; Set up segments
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Print welcome message
    mov si, MSG_BOOT
    call PRINT

    ; Halt — kernel loading comes later
    cli
    hlt

; --- Print function ---
PRINT:
    mov ah, 0x0E        ; BIOS teletype mode
.loop:
    lodsb               ; Load next character
    cmp al, 0           ; Is it the end of the string?
    je .done
    int 0x10            ; Print the character
    jmp .loop
.done:
    ret

; --- Messages ---
MSG_BOOT db "Caliber OS Booting...", 0x0D, 0x0A, 0

; --- Boot sector magic ---
times 510-($-$$) db 0   ; Pad to 510 bytes
dw 0xAA55               ; Boot signature (BIOS requires this)