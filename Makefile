# GLOBAL VARIABLES W/ IMPLICIT VARIABLES
CC      = clang
TARGET 	= build/BOOTX64.EFI
OBJS	= src/boot.o

INCDIR	= ./include
TGFLAGS	= -target x86_64-unknown-windows -ffreestanding -nostdlib -std=c89    \
	  -pedantic -Werror
CFLAGS  = $(TGFLAGS) -I$(INCDIR)

# SPECIFIC VARIABLES
BOOTLOADER_LINKER_FLAGS = -Wl,-entry:efi_bootloader -Wl,-subsystem:efi_application

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(TGFLAGS) $(BOOTLOADER_LINKER_FLAGS) -o $@ $^

.PHONY clean:
	rm -f $(TARGET) $(OBJS)