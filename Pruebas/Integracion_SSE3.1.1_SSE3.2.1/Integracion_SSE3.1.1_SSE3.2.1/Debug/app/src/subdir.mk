################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/src/Procesamiento.c \
../app/src/main.c 

C_DEPS += \
./app/src/Procesamiento.d \
./app/src/main.d 

OBJS += \
./app/src/Procesamiento.o \
./app/src/main.o 


# Each subdirectory must supply rules for building sources it contributes
app/src/%.o: ../app/src/%.c app/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"C:\A - Sistemas embebidos\TP-FINAL-ED3\CMSISv2p00_LPC17xx\inc" -I"C:\A - Sistemas embebidos\TP-FINAL-ED3\CMSISv2p00_LPC17xx\Drivers\inc" -I"C:\A - Sistemas embebidos\TP-FINAL-ED3\Integracion_SSE3.1.1_SSE3.2.1\app\inc" -I"C:\A - Sistemas embebidos\TP-FINAL-ED3\Integracion_SSE3.1.1_SSE3.2.1\devices\inc" -I"C:\A - Sistemas embebidos\TP-FINAL-ED3\Integracion_SSE3.1.1_SSE3.2.1\services\inc" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-app-2f-src

clean-app-2f-src:
	-$(RM) ./app/src/Procesamiento.d ./app/src/Procesamiento.o ./app/src/main.d ./app/src/main.o

.PHONY: clean-app-2f-src

