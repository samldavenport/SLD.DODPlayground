$ProjectRoot = Split-Path -Parent $PSScriptRoot 

$SrcFile = Join-Path $ProjectRoot "src\main.cpp"
$Compile = @(
    "cl.exe"
    $SrcFile
    "/Fo:" + @(Join-Path $ProjectRoot "build\debug\obj\DOD.obj")  
    "/I"   + @(Join-Path $ProjectRoot "include")
    "/nologo"             # startup banner disabled
    "/c"                  # compile without linking
    "/MD"                 # link against multithreaded runtime library (MSVCRT.dll)
    "/Z7"                 # generate debug info
    "/EHs-"               # disable exception handling
    "/std:c++17"          # c++17 standard mode
    "/O2"                 # level 2 optimizations
    "/D_HAS_EXCEPTIONS=0" # disable exceptions for STL and CRT
    "/Fa" + @(Join-Path $ProjectRoot "build\debug\obj\DOD.asm") # generate assembly 
) -join " "

$Link = @(
    "link.exe"
    "/nologo"
    "/SUBSYSTEM:CONSOLE"
    "/DEBUG"
    "/LIBPATH:build\debug\obj"
    "DOD.obj"
    "user32.lib"
    "/OUT:build\debug\exe\DOD.exe"
) -join " "

Invoke-Expression $Compile
Invoke-Expression $Link

