Set-Location C:/
git clone https://github.com/Microsoft/vcpkg.git
Set-Location vcpkg
./bootstrap-vcpkg.bat
# setx PATH "$($Env:PATH);C:\vcpkg;"
$current_PATH = [Environment]::GetEnvironmentVariable("PATH", "USER"); [Environment]::SetEnvironmentVariable("PATH", $current_PATH + "C:\vcpkg;", "USER")
    $env:Path = [System.Environment]::GetEnvironmentVariable("Path","MACHINE") + [Environment]::GetEnvironmentVariable("Path","USER")
vcpkg integrate install
vcpkg install raylib:x64-windows