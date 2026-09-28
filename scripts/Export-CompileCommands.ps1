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
    "/Od"                 # disable optimizations
    "/D_HAS_EXCEPTIONS=0" # disable exceptions for STL and CRT
    "/DSLD_DLL_EXPORT"
) -join " "

$CompileCommands  = @()
$CompileCommands += [PSCustomObject]@{
    directory = $ProjectRoot  
    command   = $Compile
    file      = $SrcFile 
}

ConvertTo-Json -InputObject $CompileCommands -Depth 10 |
    Set-Content "compile_commands.json"
