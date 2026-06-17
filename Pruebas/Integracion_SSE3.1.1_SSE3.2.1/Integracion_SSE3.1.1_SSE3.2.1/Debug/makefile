################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include services/src/subdir.mk
-include devices/src/subdir.mk
-include app/src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Integracion_SSE3.1.1_SSE3.2.1
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: Integracion_SSE3.1.1_SSE3.2.1.axf

# Tool invocations
Integracion_SSE3.1.1_SSE3.2.1.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\A - Sistemas embebidos\TP-FINAL-ED3\CMSISv2p00_LPC17xx\Debug" -Xlinker -Map="Integracion_SSE3.1.1_SSE3.2.1.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "Integracion_SSE3_1_1_SSE3_2_1_Debug.ld" -o "Integracion_SSE3.1.1_SSE3.2.1.axf" $(OBJS) $(USER_OBJS) $(LIBS) -lCMSISv2p00_LPC17xx
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Integracion_SSE3.1.1_SSE3.2.1.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Integracion_SSE3.1.1_SSE3.2.1.axf"; # arm-none-eabi-objcopy -v -O binary "Integracion_SSE3.1.1_SSE3.2.1.axf" "Integracion_SSE3.1.1_SSE3.2.1.bin" ; # checksum -p LPC1769 -d "Integracion_SSE3.1.1_SSE3.2.1.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
