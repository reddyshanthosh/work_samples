################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/buzzer.c \
../src/delay.c \
../src/keypad.c \
../src/lcd.c \
../src/led.c \
../src/main.c \
../src/rotary.c \
../src/syscalls.c \
../src/uart_driver.c 

OBJS += \
./src/buzzer.o \
./src/delay.o \
./src/keypad.o \
./src/lcd.o \
./src/led.o \
./src/main.o \
./src/rotary.o \
./src/syscalls.o \
./src/uart_driver.o 

C_DEPS += \
./src/buzzer.d \
./src/delay.d \
./src/keypad.d \
./src/lcd.d \
./src/led.d \
./src/main.d \
./src/rotary.d \
./src/syscalls.d \
./src/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -IC:/Users/reddys/workspace/reddys_final/inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


