################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Cercle.cpp \
../ElementGeo.cpp \
../Figure.cpp \
../LectureEcriture.cpp \
../Ligne.cpp \
../ObjetAgrege.cpp \
../Point.cpp \
../PolyLigne.cpp \
../Rectangle.cpp \
../main.cpp 

OBJS += \
./Cercle.o \
./ElementGeo.o \
./Figure.o \
./LectureEcriture.o \
./Ligne.o \
./ObjetAgrege.o \
./Point.o \
./PolyLigne.o \
./Rectangle.o \
./main.o 

CPP_DEPS += \
./Cercle.d \
./ElementGeo.d \
./Figure.d \
./LectureEcriture.d \
./Ligne.d \
./ObjetAgrege.d \
./Point.d \
./PolyLigne.d \
./Rectangle.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


