# Caliber OS Build System

ASM = nasm
CC = i686-elf-gcc
LD = i686-elf-ld

ASM_FLAGS = -f bin
CC_FLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -c
LD_FLAGS = -m elf_i386 -T linker.ld

BUILD = build
BOOT = boot
KERNEL = kernel

all: $(BUILD)/caliber.bin

# Assemble bootloader
$(BUILD)/boot.bin: $(BOOT)/boot.asm
	$(ASM) $(ASM_FLAGS) $(BOOT)/boot.asm -o $(BUILD)/boot.bin

# Compile kernel
$(BUILD)/kernel.o: $(KERNEL)/kernel.c
	$(CC) $(CC_FLAGS) $(KERNEL)/kernel.c -o $(BUILD)/kernel.o

# Link everything together
$(BUILD)/caliber.bin: $(BUILD)/boot.bin $(BUILD)/kernel.o
	cat $(BUILD)/boot.bin $(BUILD)/kernel.o > $(BUILD)/caliber.bin

# Run in QEMU
run: $(BUILD)/caliber.bin
	qemu-system-i386 -drive format=raw,file=$(BUILD)/caliber.bin

# Clean build folder
clean:
	rm -f $(BUILD)/*.bin $(BUILD)/*.o