################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/hbird-e200/stubs/_exit.c \
../bsp/hbird-e200/stubs/close.c \
../bsp/hbird-e200/stubs/fstat.c \
../bsp/hbird-e200/stubs/isatty.c \
../bsp/hbird-e200/stubs/lseek.c \
../bsp/hbird-e200/stubs/malloc.c \
../bsp/hbird-e200/stubs/printf.c \
../bsp/hbird-e200/stubs/read.c \
../bsp/hbird-e200/stubs/sbrk.c \
../bsp/hbird-e200/stubs/write.c \
../bsp/hbird-e200/stubs/write_hex.c 

OBJS += \
./bsp/hbird-e200/stubs/_exit.o \
./bsp/hbird-e200/stubs/close.o \
./bsp/hbird-e200/stubs/fstat.o \
./bsp/hbird-e200/stubs/isatty.o \
./bsp/hbird-e200/stubs/lseek.o \
./bsp/hbird-e200/stubs/malloc.o \
./bsp/hbird-e200/stubs/printf.o \
./bsp/hbird-e200/stubs/read.o \
./bsp/hbird-e200/stubs/sbrk.o \
./bsp/hbird-e200/stubs/write.o \
./bsp/hbird-e200/stubs/write_hex.o 

C_DEPS += \
./bsp/hbird-e200/stubs/_exit.d \
./bsp/hbird-e200/stubs/close.d \
./bsp/hbird-e200/stubs/fstat.d \
./bsp/hbird-e200/stubs/isatty.d \
./bsp/hbird-e200/stubs/lseek.d \
./bsp/hbird-e200/stubs/malloc.d \
./bsp/hbird-e200/stubs/printf.d \
./bsp/hbird-e200/stubs/read.d \
./bsp/hbird-e200/stubs/sbrk.d \
./bsp/hbird-e200/stubs/write.d \
./bsp/hbird-e200/stubs/write_hex.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/hbird-e200/stubs/%.o: ../bsp/hbird-e200/stubs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\drivers" -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\include\headers" -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\include" -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\env" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


