@echo off
echo === 项目根目录 ===
tree /F /A
echo.
echo === docs 目录 ===
cd docs
tree /F /A
cd ..
pause