cmake_minimum_required(VERSION 3.3)
project(PSU_2016_nmobjdump)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src_nm/main.c src_objdump/main.c include/objdump.h src_objdump/check_map_data.c src_objdump/Objdump_elf32.c
        src_objdump/verify_header.c  src_objdump/FlagsObjdump.c src_objdump/Print_Flags_Type.c src_objdump/read_files.c
       include/nm.h src_nm/check_set_tab.c)
add_executable(PSU_2016_nmobjdump ${SOURCE_FILES})