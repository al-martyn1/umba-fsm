@rem Добавить примеры диаграмм состояний отсюда - https://plantuml.com/ru/guide
@call %~dp0find_test_exe.bat plantuml_test_001
@call %~dp0plantuml_test_files.bat

%TEST_EXE% ^ %PLANTUML_TEST_FILES%
