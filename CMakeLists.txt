cmake_minimum_required(VERSION 3.17)
project(Bloom_filter C)

set(CMAKE_C_STANDARD 11)

add_executable(
        Bloom_filter
        main.c
        Bloom/bloom.c
        Bloom/bloom.h
        Hash/hash.c
        Hash/hash.h Bloom/bloomStruct.h Test/test.c Test/test.h Errors/errors.c Errors/errors.h CommandLineAndFile/cmdFile.c CommandLineAndFile/cmdFile.h)