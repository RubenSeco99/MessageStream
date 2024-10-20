cmake_minimum_required(VERSION 3.29)
project(MessageStream C)

set(CMAKE_C_STANDARD 99)

add_library(MessageStream STATIC
        Feed/feed.c
        Feed/feed.h
        Mensagem/mensagem.h
        Mensagem/mensagem.c
        Manager/manager.h
        Manager/manager.c)
