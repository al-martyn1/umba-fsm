@call %~dp0\..\.bat\find-exe-in-out.bat test_008
@echo FOUND_EXE: %FOUND_EXE%
@set TEST_EXE=%FOUND_EXE%
@set LIB_ROOT=%~dp0\..\_libs
@set LIB_UMBA=%LIB_ROOT%\umba
@set LIB_MARTY_DECIMAL=%LIB_ROOT%\marty_decimal

@%TEST_EXE% %LIB_UMBA%\preprocessor.h %LIB_UMBA%\the.h %LIB_UMBA%\stl_keil_initializer_list.h %LIB_UMBA%\stl_keil_type_traits.h %LIB_UMBA%\string_plus.h %LIB_UMBA%\rgbquad.h %LIB_MARTY_DECIMAL%\tests\src\regression_tests.cpp


@rem %TEST_EXE% %LIB_UMBA%\                             >
@rem %TEST_EXE% %LIB_UMBA%\                             >

