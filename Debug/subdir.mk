################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ConsoleSupport.cpp \
../Graph.cpp \
../Queue.cpp \
../SpanningTree.cpp \
../main.cpp 

OBJS += \
./ConsoleSupport.o \
./Graph.o \
./Queue.o \
./SpanningTree.o \
./main.o 

CPP_DEPS += \
./ConsoleSupport.d \
./Graph.d \
./Queue.d \
./SpanningTree.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


