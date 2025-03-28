@echo off
setlocal enabledelayedexpansion

REM 设置存放 pak 文件的文件夹（相对于当前目录）
set "PakFolder=Windows"

REM 检查 pak 文件夹是否存在
if not exist "%PakFolder%" (
    echo 文件夹 "%PakFolder%" 不存在！
    pause
    exit /b 1
)

REM 统计 PakFolder 中的 .pak 文件数量
set count=0
for %%F in ("%PakFolder%\*.pak" "%PakFolder%\*.ucas" "%PakFolder%\*.utoc") do (
    set /a count+=1
)

REM 自动获取当前目录名称作为基础名称，并拼接 "Key" 得到 BUILD_ID
for %%i in ("%CD%") do set "BUILD_ID=%%~nxi"

REM 定义生成的 manifest 文件名（放在当前目录下）
set "ManifestFile=BuildManifest-Windows.txt"

REM 写入头两行到 manifest 文件
(
    echo $NUM_ENTRIES = %count%
    echo $BUILD_ID = %BUILD_ID%
) > "%ManifestFile%"

REM 定义一个 TAB 字符（请确保这里是真正的 TAB 字符）
set "TAB=	"

REM 遍历 PakFolder 中所有 .pak 文件，按规则生成条目
for %%F in ("%PakFolder%\*.pak" "%PakFolder%\*.ucas" "%PakFolder%\*.utoc") do (
    set "FILENAME=%%~nxF"
    set "FILESIZE=%%~zF"
    set "FILEVersion=Ver"

    for /f "tokens=1 delims=-" %%A in ("%%~nxF") do (
        set "PREFIX=%%A"
        set "CHUNKID=!PREFIX:~8!"
    )
    
    REM 写入一行：文件名<TAB>文件大小<TAB>ver01<TAB>pak编号<TAB>/Windows/文件名
    >> "%ManifestFile%" echo !FILENAME!%TAB%!FILESIZE!%TAB%!FILEVersion!%TAB%!CHUNKID!%TAB%/!PakFolder!/!FILENAME!
)

echo Manifest 文件已生成: %ManifestFile%
pause
