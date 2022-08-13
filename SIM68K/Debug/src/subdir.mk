################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BPoint.cpp \
../src/BPointExpr.cpp \
../src/CLogger.cpp \
../src/CODE1.cpp \
../src/CODE2.cpp \
../src/CODE3.cpp \
../src/CODE4.cpp \
../src/CODE5.cpp \
../src/CODE6.cpp \
../src/CODE7.cpp \
../src/CODE8.cpp \
../src/CODE9.cpp \
../src/FileHandling.cpp \
../src/MainFrame.cpp \
../src/Memory.cpp \
../src/MemoryCtrl.cpp \
../src/MemoryDialog.cpp \
../src/OPCODES.cpp \
../src/Properties.cpp \
../src/RUN.cpp \
../src/SIM68K.cpp \
../src/STARTSIM.cpp \
../src/SourceCtrl.cpp \
../src/UTILS.cpp \
../src/extern.cpp \
../src/hardware.cpp \
../src/tomlcpp.cpp 

C_SRCS += \
../src/toml.c 

CPP_DEPS += \
./src/BPoint.d \
./src/BPointExpr.d \
./src/CLogger.d \
./src/CODE1.d \
./src/CODE2.d \
./src/CODE3.d \
./src/CODE4.d \
./src/CODE5.d \
./src/CODE6.d \
./src/CODE7.d \
./src/CODE8.d \
./src/CODE9.d \
./src/FileHandling.d \
./src/MainFrame.d \
./src/Memory.d \
./src/MemoryCtrl.d \
./src/MemoryDialog.d \
./src/OPCODES.d \
./src/Properties.d \
./src/RUN.d \
./src/SIM68K.d \
./src/STARTSIM.d \
./src/SourceCtrl.d \
./src/UTILS.d \
./src/extern.d \
./src/hardware.d \
./src/tomlcpp.d 

C_DEPS += \
./src/toml.d 

OBJS += \
./src/BPoint.o \
./src/BPointExpr.o \
./src/CLogger.o \
./src/CODE1.o \
./src/CODE2.o \
./src/CODE3.o \
./src/CODE4.o \
./src/CODE5.o \
./src/CODE6.o \
./src/CODE7.o \
./src/CODE8.o \
./src/CODE9.o \
./src/FileHandling.o \
./src/MainFrame.o \
./src/Memory.o \
./src/MemoryCtrl.o \
./src/MemoryDialog.o \
./src/OPCODES.o \
./src/Properties.o \
./src/RUN.o \
./src/SIM68K.o \
./src/STARTSIM.o \
./src/SourceCtrl.o \
./src/UTILS.o \
./src/extern.o \
./src/hardware.o \
./src/toml.o \
./src/tomlcpp.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -o "$@" "$<" -std=c++2a -I/usr/local/include/wx-3.0 -I/usr/local/include -I/usr/include -I/usr/local/lib/wx/include/gtk2-unicode-3.0 -O0 -g3 -Wall -c -fmessage-length=0  `wx-config --cppflags` -v -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -I/usr/include -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/BPoint.d ./src/BPoint.o ./src/BPointExpr.d ./src/BPointExpr.o ./src/CLogger.d ./src/CLogger.o ./src/CODE1.d ./src/CODE1.o ./src/CODE2.d ./src/CODE2.o ./src/CODE3.d ./src/CODE3.o ./src/CODE4.d ./src/CODE4.o ./src/CODE5.d ./src/CODE5.o ./src/CODE6.d ./src/CODE6.o ./src/CODE7.d ./src/CODE7.o ./src/CODE8.d ./src/CODE8.o ./src/CODE9.d ./src/CODE9.o ./src/FileHandling.d ./src/FileHandling.o ./src/MainFrame.d ./src/MainFrame.o ./src/Memory.d ./src/Memory.o ./src/MemoryCtrl.d ./src/MemoryCtrl.o ./src/MemoryDialog.d ./src/MemoryDialog.o ./src/OPCODES.d ./src/OPCODES.o ./src/Properties.d ./src/Properties.o ./src/RUN.d ./src/RUN.o ./src/SIM68K.d ./src/SIM68K.o ./src/STARTSIM.d ./src/STARTSIM.o ./src/SourceCtrl.d ./src/SourceCtrl.o ./src/UTILS.d ./src/UTILS.o ./src/extern.d ./src/extern.o ./src/hardware.d ./src/hardware.o ./src/toml.d ./src/toml.o ./src/tomlcpp.d ./src/tomlcpp.o

.PHONY: clean-src

