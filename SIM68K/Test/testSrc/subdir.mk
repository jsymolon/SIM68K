################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../testSrc/CODE1Test.cpp \
../testSrc/CODE2Test.cpp \
../testSrc/CODE3Test.cpp \
../testSrc/CODE4Test.cpp \
../testSrc/CODE5Test.cpp \
../testSrc/CODE6Test.cpp \
../testSrc/CODE7Test.cpp \
../testSrc/CODE8Test.cpp \
../testSrc/CODE9Test.cpp \
../testSrc/MainTest.cpp \
../testSrc/MemoryCtrlTest.cpp \
../testSrc/MemoryTest.cpp \
../testSrc/PropertiesTest.cpp \
../testSrc/UTILS_effaddTest.cpp \
../testSrc/tomlcppTest.cpp 

CPP_DEPS += \
./testSrc/CODE1Test.d \
./testSrc/CODE2Test.d \
./testSrc/CODE3Test.d \
./testSrc/CODE4Test.d \
./testSrc/CODE5Test.d \
./testSrc/CODE6Test.d \
./testSrc/CODE7Test.d \
./testSrc/CODE8Test.d \
./testSrc/CODE9Test.d \
./testSrc/MainTest.d \
./testSrc/MemoryCtrlTest.d \
./testSrc/MemoryTest.d \
./testSrc/PropertiesTest.d \
./testSrc/UTILS_effaddTest.d \
./testSrc/tomlcppTest.d 

OBJS += \
./testSrc/CODE1Test.o \
./testSrc/CODE2Test.o \
./testSrc/CODE3Test.o \
./testSrc/CODE4Test.o \
./testSrc/CODE5Test.o \
./testSrc/CODE6Test.o \
./testSrc/CODE7Test.o \
./testSrc/CODE8Test.o \
./testSrc/CODE9Test.o \
./testSrc/MainTest.o \
./testSrc/MemoryCtrlTest.o \
./testSrc/MemoryTest.o \
./testSrc/PropertiesTest.o \
./testSrc/UTILS_effaddTest.o \
./testSrc/tomlcppTest.o 


# Each subdirectory must supply rules for building sources it contributes
testSrc/%.o: ../testSrc/%.cpp testSrc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -o "$@" "$<" -std=c++2a -DTESTINGON -I/usr/local/include/wx-3.0 -I/usr/local/lib/wx/include/gtk2-unicode-3.0 -I/usr/src/googletest/googletest/include -O0 -g3 -p -pg -Wall -c -fmessage-length=0  `wx-config --cppflags` -fPIC -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-testSrc

clean-testSrc:
	-$(RM) ./testSrc/CODE1Test.d ./testSrc/CODE1Test.o ./testSrc/CODE2Test.d ./testSrc/CODE2Test.o ./testSrc/CODE3Test.d ./testSrc/CODE3Test.o ./testSrc/CODE4Test.d ./testSrc/CODE4Test.o ./testSrc/CODE5Test.d ./testSrc/CODE5Test.o ./testSrc/CODE6Test.d ./testSrc/CODE6Test.o ./testSrc/CODE7Test.d ./testSrc/CODE7Test.o ./testSrc/CODE8Test.d ./testSrc/CODE8Test.o ./testSrc/CODE9Test.d ./testSrc/CODE9Test.o ./testSrc/MainTest.d ./testSrc/MainTest.o ./testSrc/MemoryCtrlTest.d ./testSrc/MemoryCtrlTest.o ./testSrc/MemoryTest.d ./testSrc/MemoryTest.o ./testSrc/PropertiesTest.d ./testSrc/PropertiesTest.o ./testSrc/UTILS_effaddTest.d ./testSrc/UTILS_effaddTest.o ./testSrc/tomlcppTest.d ./testSrc/tomlcppTest.o

.PHONY: clean-testSrc

