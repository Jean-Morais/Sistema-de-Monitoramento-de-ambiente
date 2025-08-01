################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/BMP280.c \
../Src/I2C.c \
../Src/INIT.c \
../Src/LDR.c \
../Src/NRF24L01.c \
../Src/SPI.c \
../Src/TIMER.c \
../Src/USART.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/BMP280.o \
./Src/I2C.o \
./Src/INIT.o \
./Src/LDR.o \
./Src/NRF24L01.o \
./Src/SPI.o \
./Src/TIMER.o \
./Src/USART.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/BMP280.d \
./Src/I2C.d \
./Src/INIT.d \
./Src/LDR.d \
./Src/NRF24L01.d \
./Src/SPI.d \
./Src/TIMER.d \
./Src/USART.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F103xB -c -I"/home/jeanm/Documentos/workspace-stm/Projeto Final - monitoramento de ambiente/Inc" -I"/home/jeanm/Documentos/workspace-stm/Projeto Final - monitoramento de ambiente/F1_Header/Include" -I"/home/jeanm/Documentos/workspace-stm/Projeto Final - monitoramento de ambiente/F1_Header/Device/ST/STM32F1xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/BMP280.cyclo ./Src/BMP280.d ./Src/BMP280.o ./Src/BMP280.su ./Src/I2C.cyclo ./Src/I2C.d ./Src/I2C.o ./Src/I2C.su ./Src/INIT.cyclo ./Src/INIT.d ./Src/INIT.o ./Src/INIT.su ./Src/LDR.cyclo ./Src/LDR.d ./Src/LDR.o ./Src/LDR.su ./Src/NRF24L01.cyclo ./Src/NRF24L01.d ./Src/NRF24L01.o ./Src/NRF24L01.su ./Src/SPI.cyclo ./Src/SPI.d ./Src/SPI.o ./Src/SPI.su ./Src/TIMER.cyclo ./Src/TIMER.d ./Src/TIMER.o ./Src/TIMER.su ./Src/USART.cyclo ./Src/USART.d ./Src/USART.o ./Src/USART.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

