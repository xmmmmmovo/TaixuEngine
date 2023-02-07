:: install the vcpkg
git clone https://github.com/Microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat -disableMetrics
cd vcpkg
.\vcpkg.exe install
exit