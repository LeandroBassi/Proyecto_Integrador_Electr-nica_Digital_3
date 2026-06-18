################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../devices/src/Buzzer.c \
../devices/src/Leds.c \
../devices/src/Pulsador.c \
../devices/src/SensorHCSR04.c \
../devices/src/SensorSharp.c \
../devices/src/UART.c 

C_DEPS += \
./devices/src/Buzzer.d \
./devices/src/Leds.d \
./devices/src/Pulsador.d \
./devices/src/SensorHCSR04.d \
./devices/src/SensorSharp.d \
./devices/src/UART.d 

OBJS += \
./devices/src/Buzzer.o \
./devices/src/Leds.o \
./devices/src/Pulsador.o \
./devices/src/SensorHCSR04.o \
./devices/src/SensorSharp.o \
./devices/src/UART.o 


# Each subdirectory must supply rules for building sources it contributes
devices/src/%.o: ../devices/src/%.c devices/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"C:\A - Sistemas embebidos\TP-FINAL-ED3\CMSISv2p00_LPC17xx\inc" -I"C:\A - Sistemas embebidos\TP-FINAL-ED3\CMSISv2p00_LPC17xx\Drivers\inc" -I"C:\A - Sistemas embebidos\TP-FINAL-ED3\Integracion_ALL_IN\app\inc" -I"C:\A - Sistemas embebidos\TP-FINAL-ED3\Integracion_ALL_IN\devices\inc" -I"C:\A - Sistemas embebidos\TP-FINAL-ED3\Integracion_ALL_IN\services\inc" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-devices-2f-src

clean-devices-2f-src:
	-$(RM) ./devices/src/Buzzer.d ./devices/src/Buzzer.o ./devices/src/Leds.d ./devices/src/Leds.o ./devices/src/Pulsador.d ./devices/src/Pulsador.o ./devices/src/SensorHCSR04.d ./devices/src/SensorHCSR04.o ./devices/src/SensorSharp.d ./devices/src/SensorSharp.o ./devices/src/UART.d ./devices/src/UART.o

.PHONY: clean-devices-2f-src

