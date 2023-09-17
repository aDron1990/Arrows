# Arrows
## Описание
Игра представляет из себя клеточный автомат, способный симулировать логические схемы
## Сборка
Перед сборкой необходимо установить Cmake, библиотеки boost и opengl, а так же среда программирования (Windows - Visual Studio; Linux - gcc и Makefile)
Процесс сборки(Linux bash/Windows PowerShell):
```
git clone --recursive https://github.com/aDron1990/Arrows.git
cd Arrows
mkdir build
cd build
cmake ..
```
Далее процесс сборки зависит от платфомы. В Windows необходимо произвести сбоку из Visual studio, в Linux выполнить коммаду ***make***
## Управление
```
WASD - Перемещие;
ЛКМ - поставить блок;
ПКМ - убрать блок;
Клавиши 1-7 - выбрать тип блока
```
В игре представлено 7 видов блоков