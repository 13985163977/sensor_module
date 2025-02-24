################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Sensor_Modules/RC_Receiver/Src/rc_decoder.c \
../App/Sensor_Modules/RC_Receiver/Src/rc_driver.c 

OBJS += \
./App/Sensor_Modules/RC_Receiver/Src/rc_decoder.o \
./App/Sensor_Modules/RC_Receiver/Src/rc_driver.o 

C_DEPS += \
./App/Sensor_Modules/RC_Receiver/Src/rc_decoder.d \
./App/Sensor_Modules/RC_Receiver/Src/rc_driver.d 


# Each subdirectory must supply rules for building sources it contributes
App/Sensor_Modules/RC_Receiver/Src/%.o App/Sensor_Modules/RC_Receiver/Src/%.su App/Sensor_Modules/RC_Receiver/Src/%.cyclo: ../App/Sensor_Modules/RC_Receiver/Src/%.c App/Sensor_Modules/RC_Receiver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"E:/Myproject/sensor_module/BSP/FreeRTOS_Config/Inc" -I"E:/Myproject/sensor_module/BSP/FreeRTOS_Config/Src" -I"E:/Myproject/sensor_module/BSP/I2C_Bridge/Inc" -I"E:/Myproject/sensor_module/BSP/I2C_Bridge/Src" -I"E:/Myproject/sensor_module/BSP/ErrorHandler/Inc" -I"E:/Myproject/sensor_module/BSP/ErrorHandler/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/IMU_406/Inc" -I"E:/Myproject/sensor_module/App/Sensor_Modules/IMU_406/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/RC_Receiver/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/RC_Receiver/Inc" -I"E:/Myproject/sensor_module/App/Sensor_Modules/Ultrasonic/Src" -I"E:/Myproject/sensor_module/App/Sensor_Modules/Ultrasonic/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-Sensor_Modules-2f-RC_Receiver-2f-Src

clean-App-2f-Sensor_Modules-2f-RC_Receiver-2f-Src:
	-$(RM) ./App/Sensor_Modules/RC_Receiver/Src/rc_decoder.cyclo ./App/Sensor_Modules/RC_Receiver/Src/rc_decoder.d ./App/Sensor_Modules/RC_Receiver/Src/rc_decoder.o ./App/Sensor_Modules/RC_Receiver/Src/rc_decoder.su ./App/Sensor_Modules/RC_Receiver/Src/rc_driver.cyclo ./App/Sensor_Modules/RC_Receiver/Src/rc_driver.d ./App/Sensor_Modules/RC_Receiver/Src/rc_driver.o ./App/Sensor_Modules/RC_Receiver/Src/rc_driver.su

.PHONY: clean-App-2f-Sensor_Modules-2f-RC_Receiver-2f-Src

