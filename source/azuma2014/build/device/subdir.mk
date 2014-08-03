################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/Bluetooth.c \
../device/GyroSensor.c \
../device/LCD.c \
../device/LightSensor.c \
../device/Logger.c \
../device/Motor.c \
../device/SonarSensor.c \
../device/Timer.c \
../device/TouchSensor.c 

OBJS += \
./device/Bluetooth.o \
./device/GyroSensor.o \
./device/LCD.o \
./device/LightSensor.o \
./device/Logger.o \
./device/Motor.o \
./device/SonarSensor.o \
./device/Timer.o \
./device/TouchSensor.o 

C_DEPS += \
./device/Bluetooth.d \
./device/GyroSensor.d \
./device/LCD.d \
./device/LightSensor.d \
./device/Logger.d \
./device/Motor.d \
./device/SonarSensor.d \
./device/Timer.d \
./device/TouchSensor.d 


# Each subdirectory must supply rules for building sources it contributes
device/%.o: ../device/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -I"C:\cygwin\nxtOSEK\ecrobot" -I"C:\cygwin\nxtOSEK\lejos_nxj\src\nxtvm\platform\nxt" -I"C:\cygwin\nxtOSEK\ecrobot\bios" -I"C:\cygwin\nxtOSEK\ecrobot\c" -I"C:\cygwin\nxtOSEK\ecrobot\nxtway_gs_balancer" -I"C:\cygwin\nxtOSEK\toppers_osek\sg" -I"C:\cygwin\nxtOSEK\toppers_osek\syslib\at91sam7s-gnu\lego_nxt" -I"C:\cygwin\nxtOSEK\toppers_osek\include" -I"C:\cygwin\nxtOSEK\toppers_osek\config\at91sam7s-gnu" -I"C:\cygwin\nxtOSEK\toppers_osek\kernel" -I"C:\cygwin\nxtOSEK\lejos_nxj\src\nxtvm\javavm" -I"C:\cygwin\nxtOSEK\toppers_osek\config\at91sam7s-gnu\lego_nxt" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


