  - [Генератор FSM](#user-content-генератор-fsm)

# Генератор FSM

Синтаксис будет похож на синтаксис языка описания графов GrapViz (но это не точно).


Глобально - идея такая: основа - токенизатор. Каждому символу задаём класс/классы, и на этой базе разбиваем входной поток на токены.

Далее, из токенов уже лепим свой язык, как хотим.

Почему не взять какой-то генератор языков - потом напишу большую статью.

Пока можно посмотреть:

 - [Раскрашиватель плюсового кода - сорс](src/umba-fsm/test_008.cpp)
 - [Пример рендеринга 1](doc/html/rendered_cpp/preprocessor.html)
 - [Пример рендеринга 2](doc/html/rendered_cpp/rgbquad.html)
 - [Пример рендеринга 3](doc/html/rendered_cpp/stl_keil_initializer_list.html)
 - [Пример рендеринга 4](doc/html/rendered_cpp/stl_keil_type_traits.html)
 - [Пример рендеринга 5](doc/html/rendered_cpp/string_plus.html)
 - [Пример рендеринга 6](doc/html/rendered_cpp/the.html)
 - [Пример рендеринга 7](doc/html/rendered_cpp/regression_tests.html)



