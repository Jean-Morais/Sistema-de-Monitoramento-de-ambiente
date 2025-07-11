################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Projeto Final - monitoramento de ambiente
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Projeto\ Final\ -\ monitoramento\ de\ ambiente.elf \

MAP_FILES += \
Projeto\ Final\ -\ monitoramento\ de\ ambiente.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Projeto\ Final\ -\ monitoramento\ de\ ambiente.list \


# All Target
all: main-build

# Main-build Target
main-build: Projeto\ Final\ -\ monitoramento\ de\ ambiente.elf secondary-outputs

# Tool invocations
Projeto\ Final\ -\ monitoramento\ de\ ambiente.elf Projeto\ Final\ -\ monitoramento\ de\ ambiente.map: $(OBJS) $(USER_OBJS) /home/jeanm/Documentos/EC/5semestre/Micro/Projeto\ Final\ -\ monitoramento\ de\ ambiente/STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Projeto Final - monitoramento de ambiente.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"/home/jeanm/Documentos/EC/5semestre/Micro/Projeto Final - monitoramento de ambiente/STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Projeto Final - monitoramento de ambiente.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Projeto\ Final\ -\ monitoramento\ de\ ambiente.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Projeto Final - monitoramento de ambiente.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Projeto\ Final\ -\ monitoramento\ de\ ambiente.elf Projeto\ Final\ -\ monitoramento\ de\ ambiente.list Projeto\ Final\ -\ monitoramento\ de\ ambiente.map Projeto\\ Final\\ -\\ monitoramento\\ de\\ ambiente.elf default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
