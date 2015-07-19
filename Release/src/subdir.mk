################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Particles.cpp \
../src/Screen.cpp \
../src/Swarm.cpp \
../src/main.cpp 

OBJS += \
./src/Particles.o \
./src/Screen.o \
./src/Swarm.o \
./src/main.o 

CPP_DEPS += \
./src/Particles.d \
./src/Screen.d \
./src/Swarm.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/SDL2 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


