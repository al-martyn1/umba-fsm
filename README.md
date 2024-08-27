  - [Генератор FSM](#user-content-генератор-fsm)
  - [Сборка и отладка проекта](#user-content-сборка-и-отладка-проекта)
    - [Извлечение библиотек](#user-content-извлечение-библиотек)
    - [Генерация сборочных скриптов и сборка](#user-content-генерация-сборочных-скриптов-и-сборка)
    - [Открытие проекта в IDE](#user-content-открытие-проекта-в-ide)
      - [Запуск VSCode](#user-content-запуск-vscode)
      - [Запуск MSVC](#user-content-запуск-msvc)

# Генератор FSM

Синтаксис будет похож на синтаксис языка описания графов GrapViz (но это не точно).


Глобально - идея такая: основа - токенизатор. Каждому символу задаём класс/классы, и на этой базе разбиваем входной поток на токены.

Далее, из токенов уже лепим свой язык, как хотим.

Почему не взять какой-то генератор языков - потом напишу большую статью.

Самого генератора пока нет, есть только тесты токенизера. Последний "интеграционный" тест раскрашивает
исходники на C++ в HTML.

Пока можно посмотреть:

 - [Раскрашиватель плюсового кода v1 (test_010)](src/umba-fsm/test_010.cpp) - препроцессор обрабатывается в фильтре CcPreprocessorFilter
 - [Раскрашиватель плюсового кода v2 (test_011)](src/umba-fsm/test_011.cpp) - создание токенизер билдера и токенизера для плюсиков вынесено в отдельную функцию (в библиотеку)


Примеры рендеринга плюсового кода:

 - [Склейка литералов и суффиксов (SimpleSuffixGluingFilter)](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/suffix_gluing_sample.html)
 - [Пример 1](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/preprocessor.html)
 - [Пример 2](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/rgbquad.html)
 - [Пример 3](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/stl_keil_initializer_list.html)
 - [Пример 4](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/stl_keil_type_traits.html)
 - [Пример 5](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/string_plus.html)
 - [Пример 6](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/the.html)
 - [Пример 7](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/regression_tests.html)


# Сборка и отладка проекта


## Извлечение библиотек

Для сборки проекта требуются внешние библиотеки. Внешние библиотеки не подгружаются автоматически.
Для их подгрузки требуется выполнить скрипт `_libs/_clone_libs.bat`.


## Генерация сборочных скриптов и сборка

Для генерации сборочных скриптов и их сборки при помощи `MSBuild` предназначены файлы:

 - `.bat/cmake_generate_all_msvc2017.bat`
 - `.bat/cmake_generate_all_msvc2019.bat`
 - `.bat/cmake_generate_all_msvc2022.bat`
 - `.bat/cmake_build_all_msvc2017.bat`
 - `.bat/cmake_build_all_msvc2019.bat`
 - `.bat/cmake_build_all_msvc2022.bat`


## Открытие проекта в IDE

### Запуск VSCode

Для запуска VSCode предназначен файл `_start_code.bat`. 
VSCode с плагином "CMake Tools" сам обнаружит `CMakeLists.txt`. Следует выбрать подходящий тулчейн
и можно начинать работу.


### Запуск MSVC

Для запуска MSVC предназначен файл `_start_msvc.bat`.
По умолчанию будет сгенерированна и открыта в 2019ой студии конфигурация `x86`.
Для того, чтобы открывалась другая студия с другой конфигурацией, следует
переименовать файл `setup_msvc.bat.example` в `setup_msvc.bat` и настроить нужную конфигурацию там.





