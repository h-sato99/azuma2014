################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../technique/BalanceControl.c \
../technique/Commander.c \
../technique/Communication.c \
../technique/Dash.c \
../technique/Distance.c \
../technique/GrayDecision.c \
../technique/PidControl.c \
../technique/Tail.c \
../technique/Wheel.c \
../technique/WheelAverage.c 

OBJS += \
./technique/BalanceControl.o \
./technique/Commander.o \
./technique/Communication.o \
./technique/Dash.o \
./technique/Distance.o \
./technique/GrayDecision.o \
./technique/PidControl.o \
./technique/Tail.o \
./technique/Wheel.o \
./technique/WheelAverage.o 

C_DEPS += \
./technique/BalanceControl.d \
./technique/Commander.d \
./technique/Communication.d \
./technique/Dash.d \
./technique/Distance.d \
./technique/GrayDecision.d \
./technique/PidControl.d \
./technique/Tail.d \
./technique/Wheel.d \
./technique/WheelAverage.d 


# Each subdirectory must supply rules for building sources it contributes
technique/%.o: ../technique/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -I"C:\cygwin\nxtOSEK\ecrobot" -I"C:\cygwin\nxtOSEK\lejos_nxj\src\nxtvm\platform\nxt" -I"C:\cygwin\nxtOSEK\ecrobot\bios" -I"C:\cygwin\nxtOSEK\ecrobot\c" -I"C:\cygwin\nxtOSEK\ecrobot\nxtway_gs_balancer" -I"C:\cygwin\nxtOSEK\toppers_osek\sg" -I"C:\cygwin\nxtOSEK\toppers_osek\syslib\at91sam7s-gnu\lego_nxt" -I"C:\cygwin\nxtOSEK\toppers_osek\include" -I"C:\cygwin\nxtOSEK\toppers_osek\config\at91sam7s-gnu" -I"C:\cygwin\nxtOSEK\toppers_osek\kernel" -I"C:\cygwin\nxtOSEK\lejos_nxj\src\nxtvm\javavm" -I"C:\cygwin\nxtOSEK\toppers_osek\config\at91sam7s-gnu\lego_nxt" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


