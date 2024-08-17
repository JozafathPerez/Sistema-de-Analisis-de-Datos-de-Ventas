@echo off
REM Compilar el código
gcc ./src/main.c .\lib\cJSON\cJSON.c -o main.exe -lm

REM Verificar si la compilación fue exitosa
if %ERRORLEVEL% NEQ 0 (
    echo Error: La compilación falló.
    exit /b %ERRORLEVEL%
)

REM Ejecutar el archivo compilado
echo Ejecutando main.exe...
main.exe

REM Pausar para ver la salida
pause
