@echo off
gcc -Wall -Werror -pedantic -o conway conway.c

if %errorlevel% neq 0 (
    echo Erreur lors de la compilation.
    pause
    exit /b
)

conway.exe