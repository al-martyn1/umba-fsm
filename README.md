  - [Генератор FSM](#user-content-генератор-fsm)

# Генератор FSM

Синтаксис будет похож на синтаксис языка описания графов GrapViz (но это не точно).


Глобально - идея такая: основа - токенизатор. Каждому символу задаём класс/классы, и на этой базе разбиваем входной поток на токены.

Далее, из токенов уже лепим свой язык, как хотим.

Почему не взять какой-то генератор языков - потом напишу большую статью.

Самого генератора пока нет, есть только тесты токенизера. Последний "интеграционный" тест раскрашивает
исходники на C++ в HTML.

Пока можно посмотреть:

 - [Раскрашиватель плюсового кода v1 (test_008)](src/umba-fsm/test_008.cpp) - препроцессор обрабатывается в конечном обработчике
 - [Раскрашиватель плюсового кода v2 (test_009)](src/umba-fsm/test_009.cpp)  - препроцессор обрабатывается в фильтре CcPreprocessorFilter


Примеры рендеринга плюсового кода:

 - [Склейка литералов и суффиксов (SimpleSuffixGluingFilter)](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/suffix_gluing_sample.html)
 - [Пример 1](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/preprocessor.html)
 - [Пример 2](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/rgbquad.html)
 - [Пример 3](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/stl_keil_initializer_list.html)
 - [Пример 4](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/stl_keil_type_traits.html)
 - [Пример 5](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/string_plus.html)
 - [Пример 6](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/the.html)
 - [Пример 7](https://raw.githack.com/al-martyn1/umba-fsm/main/doc/html/rendered_cpp/regression_tests.html)




