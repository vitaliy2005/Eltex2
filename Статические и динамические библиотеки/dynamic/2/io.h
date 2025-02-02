#pragma once
#include <termios.h>
#include <stdio.h>
#include <stdint.h>
#include <curses.h>
#include <stddef.h>
#include <unistd.h>


static const char* options[] =
{
    "Сложение",
    "Вычитание",
    "Умножение",
    "Деление",
    "Выход",
};

static void clear_screen();
void disable_buffered_input();
void enable_buffered_input();
void menu(int32_t selected);
