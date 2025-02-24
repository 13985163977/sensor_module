################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/I2C_Bridge/Src/i2c_dma.c \
../BSP/I2C_Bridge/Src/i2c_recovery.c \
../BSP/I2C_Bridge/Src/i2c_slave.c 

OBJS += \
./BSP/I2C_Bridge/Src/i2c_dma.o \
./BSP/I2C_Bridge/Src/i2c_recovery.o \
./BSP/I2C_Bridge/Src/i2c_slave.o 

C_DEPS += \
./BSP/I2C_Bridge/Src/i2c_dma.d \
./BSP/I2C_Bridge/Src/i2c_recovery.d \
./BSP/I2C_Bridge/Src/i2c_slave.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/I2C_Bridge/Src/%.o BSP/I2C_Bridge/Src/%.su BSP/I2C_Bridge/Src/%.cyclo: ../BSP/I2C_Bridge/Src/%.c BSP/I2C_Bridge/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"E:/Myproject/sensor_module/BSP/FreeRTOS_Config/Inc" -I"E:/Myproject/sensor_module/BSP/FreeRTOS_Config/Src" -I"E:/Myproject/sensor_module/BSP/I2C_Bridge/Inc" -I"E:/Myproject/sensor_module/BSP/I2C_Bridge/Src" -I"E:/Myproject/sensor_module/BSP/ErrorHandler/Inc" -I"E:/Myproject/sensor_module/BSP/ErrorHandler/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/IMU_406/Inc" -I"E:/Myproject/sensor_module/App/Sensor_Modules/IMU_406/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/RC_Receiver/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/RC_Receiver/Inc" -I"E:/Myproject/sensor_module/App/Sensor_Modules/Ultrasonic/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/Ultrasonic/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BSP-2f-I2C_Bridge-2f-Src

clean-BSP-2f-I2C_Bridge-2f-Src:
	-$(RM) ./BSP/I2C_Bridge/Src/i2c_dma.cyclo ./BSP/I2C_Bridge/Src/i2c_dma.d ./BSP/I2C_Bridge/Src/i2c_dma.o ./BSP/I2C_Bridge/Src/i2c_dma.su ./BSP/I2C_Bridge/Src/i2c_recovery.cyclo ./BSP/I2C_Bridge/Src/i2c_recovery.d ./BSP/I2C_Bridge/Src/i2c_recovery.o ./BSP/I2C_Bridge/Src/i2c_recovery.su ./BSP/I2C_Bridge/Src/i2c_slave.cyclo ./BSP/I2C_Bridge/Src/i2c_slave.d ./BSP/I2C_Bridge/Src/i2c_slave.o ./BSP/I2C_Bridge/Src/i2c_slave.su

.PHONY: clean-BSP-2f-I2C_Bridge-2f-Src

