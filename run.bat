@echo off
cd /d "%~dp0"
gcc src/main.c src/UI.c src/patient.c src/search.c src/appointment.c src/booking.c src/auth.c -I include -o hospital.exe -mwindows
hospital.exe