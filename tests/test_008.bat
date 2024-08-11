@call %~dp0\..\.bat\find-exe-in-out.bat test_008
@echo FOUND_EXE: %FOUND_EXE%
@set TEST_EXE=%FOUND_EXE%
@set LIB_ROOT=%~dp0\..\_libs
@set LIB_UMBA=%LIB_ROOT%\umba
@set LIB_MARTY_DECIMAL=%LIB_ROOT%\marty_decimal

@rem @%TEST_EXE% ^
@rem %LIB_UMBA%\preprocessor.h ^
@rem %LIB_UMBA%\the.h ^
@rem %LIB_UMBA%\stl_keil_initializer_list.h ^
@rem %LIB_UMBA%\stl_keil_type_traits.h ^
@rem %LIB_UMBA%\string_plus.h ^
@rem %LIB_UMBA%\rgbquad.h ^
@rem %LIB_MARTY_DECIMAL%\tests\src\regression_tests.cpp     > test_008.log
@rem 



@%TEST_EXE% %LIB_UMBA%\preprocessor.h                            > preprocessor.html
@%TEST_EXE% %LIB_UMBA%\the.h                                     > the.html
@%TEST_EXE% %LIB_UMBA%\stl_keil_initializer_list.h               > stl_keil_initializer_list.html
@%TEST_EXE% %LIB_UMBA%\stl_keil_type_traits.h                    > stl_keil_type_traits.html
@%TEST_EXE% %LIB_UMBA%\string_plus.h                             > string_plus.html
@%TEST_EXE% %LIB_UMBA%\rgbquad.h                                 > rgbquad.html
@%TEST_EXE% %LIB_MARTY_DECIMAL%\tests\src\regression_tests.cpp   > regression_tests.html




@rem %TEST_EXE% %LIB_UMBA%\                             >
@rem %TEST_EXE% %LIB_UMBA%\                             >

