################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/hbird-e200/env/init.c 

S_UPPER_SRCS += \
../bsp/hbird-e200/env/entry.S \
../bsp/hbird-e200/env/start.S 

OBJS += \
./bsp/hbird-e200/env/entry.o \
./bsp/hbird-e200/env/init.o \
./bsp/hbird-e200/env/start.o 

S_UPPER_DEPS += \
./bsp/hbird-e200/env/entry.d \
./bsp/hbird-e200/env/start.d 

C_DEPS += \
./bsp/hbird-e200/env/init.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/hbird-e200/env/%.o: ../bsp/hbird-e200/env/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -x assembler-with-cpp -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\drivers" -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\include" -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\env" -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\include\headers" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

bsp/hbird-e200/env/%.o: ../bsp/hbird-e200/env/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\drivers" -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\include\headers" -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\include" -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\env" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


