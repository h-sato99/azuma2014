################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../template/Class.c 

OBJS += \
./template/Class.o 

C_DEPS += \
./template/Class.d 


# Each subdirectory must supply rules for building sources it contributes
template/%.o: ../template/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -I"C:\cygwin\nxtOSEK\ecrobot" -I"C:\cygwin\nxtOSEK\lejos_nxj\src\nxtvm\platform\nxt" -I"C:\cygwin\nxtOSEK\ecrobot\bios" -I"C:\cygwin\nxtOSEK\ecrobot\c" -I"C:\cygwin\nxtOSEK\ecrobot\nxtway_gs_balancer" -I"C:\cygwin\nxtOSEK\toppers_osek\sg" -I"C:\cygwin\nxtOSEK\toppers_osek\syslib\at91sam7s-gnu\lego_nxt" -I"C:\cygwin\nxtOSEK\toppers_osek\include" -I"C:\cygwin\nxtOSEK\toppers_osek\config\at91sam7s-gnu" -I"C:\cygwin\nxtOSEK\toppers_osek\kernel" -I"C:\cygwin\nxtOSEK\lejos_nxj\src\nxtvm\javavm" -I"C:\cygwin\nxtOSEK\toppers_osek\config\at91sam7s-gnu\lego_nxt" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


