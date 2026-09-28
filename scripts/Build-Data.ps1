$ProjectRoot = Split-Path -Parent $PSScriptRoot 

$size  = 64MB
$bytes = New-Object byte[] $size
$file  = @(Join-Path $ProjectRoot "data\data.bin") 
[System.Security.Cryptography.RandomNumberGenerator]::Fill($bytes)
[System.IO.File]::WriteAllBytes($file, $bytes)
