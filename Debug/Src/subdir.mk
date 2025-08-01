################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/AHT20.c \
../Src/I2C.c \
../Src/LDR.c \
../Src/NRF24L01.c \
../Src/SPI.c \
../Src/conversorAD.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/AHT20.o \
./Src/I2C.o \
./Src/LDR.o \
./Src/NRF24L01.o \
./Src/SPI.o \
./Src/conversorAD.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/AHT20.d \
./Src/I2C.d \
./Src/LDR.d \
./Src/NRF24L01.d \
./Src/SPI.d \
./Src/conversorAD.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F103xB -c -I"/home/jeanm/Documentos/workspace-stm/Projeto Final - monitoramento de ambiente/Inc" -I"/home/jeanm/Documentos/workspace-stm/Projeto Final - monitoramento de ambiente/F1_Header/Include" -I"/home/jeanm/Documentos/workspace-stm/Projeto Final - monitoramento de ambiente/F1_Header/Device/ST/STM32F1xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/AHT20.cyclo ./Src/AHT20.d ./Src/AHT20.o ./Src/AHT20.su ./Src/I2C.cyclo ./Src/I2C.d ./Src/I2C.o ./Src/I2C.su ./Src/LDR.cyclo ./Src/LDR.d ./Src/LDR.o ./Src/LDR.su ./Src/NRF24L01.cyclo ./Src/NRF24L01.d ./Src/NRF24L01.o ./Src/NRF24L01.su ./Src/SPI.cyclo ./Src/SPI.d ./Src/SPI.o ./Src/SPI.su ./Src/conversorAD.cyclo ./Src/conversorAD.d ./Src/conversorAD.o ./Src/conversorAD.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

