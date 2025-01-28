call %~dp0\..\.bat\find-exe-in-out.bat tokenizer_test_011
@echo FOUND_EXE: %FOUND_EXE%
@set TEST_EXE=%FOUND_EXE%
@set LIB_ROOT=%~dp0\..\_libs
@set LIB_UMBA=%LIB_ROOT%\umba
@set LIB_MARTY_DECIMAL=%LIB_ROOT%\marty_decimal
@set LIB_UMBA_TOKENIZER=%LIB_ROOT%\umba_tokenizer\inc\umba
@set SRC_ROOT=%~dp0\..\_src

@rem exit /B 1

@rem %TEST_EXE%

@%TEST_EXE% ^
%~dp0\suffix_gluing_sample.h ^
%SRC_ROOT%\umba-fsm\tokenizer_test_011.cpp ^
%LIB_UMBA%\preprocessor.h ^
%LIB_UMBA%\the.h ^
%LIB_UMBA%\stl_keil_initializer_list.h ^
%LIB_UMBA%\stl_keil_type_traits.h ^
%LIB_UMBA%\string_plus.h ^
%LIB_UMBA%\rgbquad.h ^
%LIB_UMBA_TOKENIZER%\tokenizer\lang\cpp.h ^
%LIB_MARTY_DECIMAL%\tests\src\regression_tests.cpp     > test_011.log


@rem @%TEST_EXE% %LIB_UMBA%\preprocessor.h                            > preprocessor.html
@rem @%TEST_EXE% %LIB_UMBA%\the.h                                     > the.html
@rem @%TEST_EXE% %LIB_UMBA%\stl_keil_initializer_list.h               > stl_keil_initializer_list.html
@rem @%TEST_EXE% %LIB_UMBA%\stl_keil_type_traits.h                    > stl_keil_type_traits.html
@rem @%TEST_EXE% %LIB_UMBA%\string_plus.h                             > string_plus.html
@rem @%TEST_EXE% %LIB_UMBA%\rgbquad.h                                 > rgbquad.html
@rem @%TEST_EXE% %LIB_MARTY_DECIMAL%\tests\src\regression_tests.cpp   > regression_tests.html
@rem 
@rem 


@rem %TEST_EXE% %LIB_UMBA%\                             >
@rem %TEST_EXE% %LIB_UMBA%\                             >

