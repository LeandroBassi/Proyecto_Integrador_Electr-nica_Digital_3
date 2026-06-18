################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../services/src/Alarma.c \
../services/src/ComunicacionUART.c \
../services/src/ConversionToCm_HCSR04.c \
../services/src/ConversionToCm_Sharp.c \
../services/src/TimeService.c 

C_DEPS += \
./services/src/Alarma.d \
./services/src/ComunicacionUART.d \
./services/src/ConversionToCm_HCSR04.d \
./services/src/ConversionToCm_Sharp.d \
./services/src/TimeService.d 

OBJS += \
./services/src/Alarma.o \
./services/src/ComunicacionUART.o \
./services/src/ConversionToCm_HCSR04.o \
./services/src/ConversionToCm_Sharp.o \
./services/src/TimeService.o 


# Each subdirectory must supply rules for building sources it contributes
services/src/%.o: ../services/src/%.c services/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"C:\A - Sistemas embebidos\TP-FINAL-ED3\CMSISv2p00_LPC17xx\inc" -I"C:\A - Sistemas embebidos\TP-FINAL-ED3\CMSISv2p00_LPC17xx\Drivers\inc" -I"C:\A - Sistemas embebidos\TP-FINAL-ED3\Integracion_ALL_IN\app\inc" -I"C:\A - Sistemas embebidos\TP-FINAL-ED3\Integracion_ALL_IN\devices\inc" -I"C:\A - Sistemas embebidos\TP-FINAL-ED3\Integracion_ALL_IN\services\inc" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-services-2f-src

clean-services-2f-src:
	-$(RM) ./services/src/Alarma.d ./services/src/Alarma.o ./services/src/ComunicacionUART.d ./services/src/ComunicacionUART.o ./services/src/ConversionToCm_HCSR04.d ./services/src/ConversionToCm_HCSR04.o ./services/src/ConversionToCm_Sharp.d ./services/src/ConversionToCm_Sharp.o ./services/src/TimeService.d ./services/src/TimeService.o

.PHONY: clean-services-2f-src

