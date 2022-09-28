Set-Location C:/
git clone https://github.com/Microsoft/vcpkg.git
Set-Location vcpkg
./bootstrap-vcpkg.bat
setx PATH "$($Env:PATH);C:\vcpkg;"
vcpkg integrate install
vcpkg install raylib:x64-windows