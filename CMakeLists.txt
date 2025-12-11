cmake_minimum_required(VERSION 3.29.6)
project(Practica6)

set(CMAKE_CXX_STANDARD 20)

add_executable(Practica6 main.cpp
        MediExpress.cpp
        MediExpress.h
        PaMedicamento.cpp
        PaMedicamento.h
        Laboratorio.cpp
        Laboratorio.h
        Farmacia.cpp
        Farmacia.h
        Stock.cpp
        Stock.h
        ThashMedicam.cpp
        ThashMedicam.h
        MallaRegular.h
        Usuario.cpp
        Usuario.h
        UTM.cpp
        UTM.h)
