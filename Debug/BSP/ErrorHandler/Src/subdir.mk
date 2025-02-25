################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/ErrorHandler/Src/error_handler.c 

OBJS += \
./BSP/ErrorHandler/Src/error_handler.o 

C_DEPS += \
./BSP/ErrorHandler/Src/error_handler.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/ErrorHandler/Src/%.o BSP/ErrorHandler/Src/%.su BSP/ErrorHandler/Src/%.cyclo: ../BSP/ErrorHandler/Src/%.c BSP/ErrorHandler/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"E:/Myproject/sensor_module/BSP/FreeRTOS_Config/Inc" -I"E:/Myproject/sensor_module/BSP/FreeRTOS_Config/Src" -I"E:/Myproject/sensor_module/BSP/I2C_Bridge/Inc" -I"E:/Myproject/sensor_module/BSP/I2C_Bridge/Src" -I"E:/Myproject/sensor_module/BSP/ErrorHandler/Inc" -I"E:/Myproject/sensor_module/BSP/ErrorHandler/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/IMU_406/Inc" -I"E:/Myproject/sensor_module/App/Sensor_Modules/IMU_406/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/RC_Receiver/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/RC_Receiver/Inc" -I"E:/Myproject/sensor_module/App/Sensor_Modules/Ultrasonic/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/Ultrasonic/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BSP-2f-ErrorHandler-2f-Src

clean-BSP-2f-ErrorHandler-2f-Src:
	-$(RM) ./BSP/ErrorHandler/Src/error_handler.cyclo ./BSP/ErrorHandler/Src/error_handler.d ./BSP/ErrorHandler/Src/error_handler.o ./BSP/ErrorHandler/Src/error_handler.su

.PHONY: clean-BSP-2f-ErrorHandler-2f-Src

