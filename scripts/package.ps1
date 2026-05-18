param(
    [string]$QtRoot = "C:\Qt\6.11.0\mingw_64",
    [string]$PackageName = "LapisTechnologiesPortable"
)

$ErrorActionPreference = "Stop"

$projectRoot = Split-Path -Parent $PSScriptRoot
$buildDir = Join-Path $projectRoot "build"
$packageDir = Join-Path $buildDir $PackageName
$zipPath = Join-Path $buildDir "$PackageName.zip"

$env:PATH = "C:\Qt\Tools\mingw1310_64\bin;C:\Qt\Tools\Ninja;C:\Qt\Tools\CMake_64\bin;$QtRoot\bin;$env:PATH"

cmake -S $projectRoot -B $buildDir -G Ninja -DCMAKE_PREFIX_PATH=$QtRoot
cmake --build $buildDir

if ((Test-Path -LiteralPath $packageDir) -and
    ((Resolve-Path -LiteralPath $packageDir).Path.StartsWith($projectRoot))) {
    Remove-Item -LiteralPath $packageDir -Recurse -Force
}

New-Item -ItemType Directory -Path $packageDir | Out-Null

Copy-Item -LiteralPath (Join-Path $buildDir "InventoryManager.exe") `
    -Destination (Join-Path $packageDir "LapisTechnologies.exe")

Copy-Item -Path `
    (Join-Path $buildDir "Qt6*.dll"), `
    (Join-Path $buildDir "libgcc_s_seh-1.dll"), `
    (Join-Path $buildDir "libstdc++-6.dll"), `
    (Join-Path $buildDir "libwinpthread-1.dll"), `
    (Join-Path $buildDir "opengl32sw.dll") `
    -Destination $packageDir

foreach ($directory in "assets", "platforms", "styles", "imageformats",
    "iconengines", "generic", "networkinformation", "tls") {
    $source = Join-Path $buildDir $directory
    if (Test-Path -LiteralPath $source) {
        Copy-Item -LiteralPath $source -Destination $packageDir -Recurse
    }
}

if (Test-Path -LiteralPath $zipPath) {
    Remove-Item -LiteralPath $zipPath -Force
}

Compress-Archive -Path (Join-Path $packageDir "*") -DestinationPath $zipPath

Write-Output "Portable app created:"
Write-Output $packageDir
Write-Output $zipPath
