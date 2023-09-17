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
cmake --build .
```
## Управление
```
WASD - Перемещие;
ЛКМ - поставить блок;
ПКМ - убрать блок;
Клавиши 1-7 - выбрать тип блока
Клавиши '<' и '>' - уменьшить и увеличить скорость симуляции
```
В игре представлено 7 видов блоков