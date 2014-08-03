################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../competision/BasicStage.c \
../competision/Competision.c \
../competision/GarageIn.c \
../competision/LineTracer.c \
../competision/LookUpGate.c \
../competision/Runner.c \
../competision/Seesaw.c \
../competision/Strategy.c 

OBJS += \
./competision/BasicStage.o \
./competision/Competision.o \
./competision/GarageIn.o \
./competision/LineTracer.o \
./competision/LookUpGate.o \
./competision/Runner.o \
./competision/Seesaw.o \
./competision/Strategy.o 

C_DEPS += \
./competision/BasicStage.d \
./competision/Competision.d \
./competision/GarageIn.d \
./competision/LineTracer.d \
./competision/LookUpGate.d \
./competision/Runner.d \
./competision/Seesaw.d \
./competision/Strategy.d 


# Each subdirectory must supply rules for building sources it contributes
competision/%.o: ../competision/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -I"C:\cygwin\nxtOSEK\ecrobot" -I"C:\cygwin\nxtOSEK\lejos_nxj\src\nxtvm\platform\nxt" -I"C:\cygwin\nxtOSEK\ecrobot\bios" -I"C:\cygwin\nxtOSEK\ecrobot\c" -I"C:\cygwin\nxtOSEK\ecrobot\nxtway_gs_balancer" -I"C:\cygwin\nxtOSEK\toppers_osek\sg" -I"C:\cygwin\nxtOSEK\toppers_osek\syslib\at91sam7s-gnu\lego_nxt" -I"C:\cygwin\nxtOSEK\toppers_osek\include" -I"C:\cygwin\nxtOSEK\toppers_osek\config\at91sam7s-gnu" -I"C:\cygwin\nxtOSEK\toppers_osek\kernel" -I"C:\cygwin\nxtOSEK\lejos_nxj\src\nxtvm\javavm" -I"C:\cygwin\nxtOSEK\toppers_osek\config\at91sam7s-gnu\lego_nxt" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


