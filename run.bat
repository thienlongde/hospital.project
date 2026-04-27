@echo off
cd /d "%~dp0"
gcc src/main.c src/UI.c src/patient.c src/search.c src/appointment.c -I include -o main.exe
main.exe
pause