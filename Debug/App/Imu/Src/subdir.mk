################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Imu/Src/imu.c 

OBJS += \
./App/Imu/Src/imu.o 

C_DEPS += \
./App/Imu/Src/imu.d 


# Each subdirectory must supply rules for building sources it contributes
App/Imu/Src/%.o App/Imu/Src/%.su App/Imu/Src/%.cyclo: ../App/Imu/Src/%.c App/Imu/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"E:/Myproject/sensor_module/App/Imu/Inc" -I"E:/Myproject/sensor_module/App/Imu/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-Imu-2f-Src

clean-App-2f-Imu-2f-Src:
	-$(RM) ./App/Imu/Src/imu.cyclo ./App/Imu/Src/imu.d ./App/Imu/Src/imu.o ./App/Imu/Src/imu.su

.PHONY: clean-App-2f-Imu-2f-Src

