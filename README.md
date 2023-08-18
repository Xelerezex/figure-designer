## Проект Дизайнер Фигур

### Build:

1. Для начала стоит зайти в файл ```CMakeSettings.json``` и в строке ```"cmakeCommandArgs":"-DCMAKE_PREFIX_PATH='C:/Qt/Qt5.13.1/5.13.1/msvc2017'"``` нужно изменить значение переменной ```CMake``` ```-DCMAKE_PREFIX_PATH='YOUR_PATH'``` на собственный путь к исходникам _Qt_.

2. Сбилдить проект в _Visual Studio_

3. Дальше открыть терминал, в терминале перейти в папку в папку c бинарными файлами _Qt_ (в моем случае это: ```cd C:\Qt\Qt5.13.1\5.13.1\msvc2017\bin```), там найти утилиту ```windeployqt.exe```. \
Вызвать утилиту ```windeployqt.exe``` с аршументом в виде пути к файлу __figure-designer.exe__ \
(На моей машине полная команда будет выглядеть так: ```windeployqt.exe C:\Users\person\Documents\repositories\figure-designer\out\build\x64-Debug\figure-designer.exe```).

4. Еще раз сделать ```Run``` в Visual Studio 2019

### Описание проекта:

> TLDR: Основная иерархия классов Фигур лежит в папке **figures**

