################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Interfacing/BUTTON/BUTTON.c 

OBJS += \
./Interfacing/BUTTON/BUTTON.o 

C_DEPS += \
./Interfacing/BUTTON/BUTTON.d 


# Each subdirectory must supply rules for building sources it contributes
Interfacing/BUTTON/%.o: ../Interfacing/BUTTON/%.c Interfacing/BUTTON/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


