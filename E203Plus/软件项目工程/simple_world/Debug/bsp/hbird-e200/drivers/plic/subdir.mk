################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/hbird-e200/drivers/plic/plic_driver.c 

OBJS += \
./bsp/hbird-e200/drivers/plic/plic_driver.o 

C_DEPS += \
./bsp/hbird-e200/drivers/plic/plic_driver.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/hbird-e200/drivers/plic/%.o: ../bsp/hbird-e200/drivers/plic/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -msmall-data-limit=8 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\drivers" -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\include\headers" -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\include" -I"C:\NucleiStudio_workspace3\simple_world\bsp\hbird-e200\env" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


