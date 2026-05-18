@echo off
setlocal

set "PROJECT_ROOT=%~dp0"
set "APP=%PROJECT_ROOT%build\LapisTechnologiesPortable\LapisTechnologies.exe"

if not exist "%APP%" (
    powershell -ExecutionPolicy Bypass -File "%PROJECT_ROOT%scripts\package.ps1"
)

start "" "%APP%"
