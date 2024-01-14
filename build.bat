@ECHO OFF

gcc %1.c .\headers\matrix.c -o %1.exe -Wall -Werror -Wextra -ggdb
.\%1.exe %2