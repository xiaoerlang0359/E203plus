################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/picojpeg.c 

OBJS += \
./src/main.o \
./src/picojpeg.o 

C_DEPS += \
./src/main.d \
./src/picojpeg.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\drivers" -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\include\headers" -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\include" -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\env" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


