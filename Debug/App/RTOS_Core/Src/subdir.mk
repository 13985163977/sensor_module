################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/RTOS_Core/Src/rtos_monitor.c \
../App/RTOS_Core/Src/task_creator.c 

OBJS += \
./App/RTOS_Core/Src/rtos_monitor.o \
./App/RTOS_Core/Src/task_creator.o 

C_DEPS += \
./App/RTOS_Core/Src/rtos_monitor.d \
./App/RTOS_Core/Src/task_creator.d 


# Each subdirectory must supply rules for building sources it contributes
App/RTOS_Core/Src/%.o App/RTOS_Core/Src/%.su App/RTOS_Core/Src/%.cyclo: ../App/RTOS_Core/Src/%.c App/RTOS_Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"E:/Myproject/sensor_module/BSP/FreeRTOS_Config/Inc" -I"E:/Myproject/sensor_module/BSP/FreeRTOS_Config/Src" -I"E:/Myproject/sensor_module/BSP/I2C_Bridge/Inc" -I"E:/Myproject/sensor_module/BSP/I2C_Bridge/Src" -I"E:/Myproject/sensor_module/BSP/ErrorHandler/Inc" -I"E:/Myproject/sensor_module/BSP/ErrorHandler/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/IMU_406/Inc" -I"E:/Myproject/sensor_module/App/Sensor_Modules/IMU_406/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/RC_Receiver/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/RC_Receiver/Inc" -I"E:/Myproject/sensor_module/App/Sensor_Modules/Ultrasonic/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/Ultrasonic/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-RTOS_Core-2f-Src

clean-App-2f-RTOS_Core-2f-Src:
	-$(RM) ./App/RTOS_Core/Src/rtos_monitor.cyclo ./App/RTOS_Core/Src/rtos_monitor.d ./App/RTOS_Core/Src/rtos_monitor.o ./App/RTOS_Core/Src/rtos_monitor.su ./App/RTOS_Core/Src/task_creator.cyclo ./App/RTOS_Core/Src/task_creator.d ./App/RTOS_Core/Src/task_creator.o ./App/RTOS_Core/Src/task_creator.su

.PHONY: clean-App-2f-RTOS_Core-2f-Src

