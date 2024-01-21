# Compiler and linker settings
CC := riscv64-unknown-elf-gcc
AS := riscv64-unknown-elf-as
LD := riscv64-unknown-elf-ld

# Compiler and linker flags
CFLAGS := -march=rv64imafdvxhwacha -mabi=lp64d  -static -mcmodel=medlow -std=gnu99
ASFLAGS := -march=rv64imafdvxhwacha
LDFLAGS := -T link.ld

# Source files
ASM_SRCS := util_asm.s
C_SRCS := main.c converter.c converter_layer.c util.c 

# Object files
ASM_OBJS := $(ASM_SRCS:.S=.o)
C_OBJS := $(C_SRCS:.c=.o)
# Object files
OBJ := $(C_SRCS:.c=.riscv) $(ASM_SRCS:.S=.o)


# Executable name
TARGET := hwacha_conversion.riscv

# Rule to compile .c files to .o files
%.riscv: %.c
	$(CC) $(CFLAGS) -c $< -o $@


# Rule to compile .c files to .s files (assembly)
%.s: %.c
	$(CC) $(CFLAGS) $< -o $@

# Rule to assemble .s files to .o files (object)
%.o: %.s
	$(AS) $(ASFLAGS) -c $< -o $@

# Assemble assembly sources to object files
%.o: %.S
	$(AS) $(ASFLAGS) $< -o $@

# Main rule to build the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Clean rule to remove object files, assembly files, and the executable
clean:
	rm -f $(OBJ) $(OBJ:.s=.o) $(TARGET)