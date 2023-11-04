################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/mg995/mg995.c 

OBJS += \
./Core/Src/mg995/mg995.o 

C_DEPS += \
./Core/Src/mg995/mg995.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/mg995/%.o Core/Src/mg995/%.su Core/Src/mg995/%.cyclo: ../Core/Src/mg995/%.c Core/Src/mg995/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-mg995

clean-Core-2f-Src-2f-mg995:
	-$(RM) ./Core/Src/mg995/mg995.cyclo ./Core/Src/mg995/mg995.d ./Core/Src/mg995/mg995.o ./Core/Src/mg995/mg995.su

.PHONY: clean-Core-2f-Src-2f-mg995

