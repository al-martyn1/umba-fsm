rem can_box\xlibs
set TARGET_ROOT=old_code
set OLD_LIBS_ROOT=C:\work\github\umba-tools\releases\stm\can_box\xlibs
umba-hcp %OLD_LIBS_ROOT% periph\keyboard.cpp       %TARGET_ROOT%
umba-hcp %OLD_LIBS_ROOT% periph\keyboard_uart.cpp  %TARGET_ROOT%

