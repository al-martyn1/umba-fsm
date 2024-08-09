@rem %UMBA_TOOLS% - eg F:\umba-tools

@if "%UMBA_TOOLS%"=="" goto UMBA_TOOLS_VAR_NOT_SET
@goto UMBA_TOOLS_VAR_IS_SET

:UMBA_TOOLS_VAR_NOT_SET
@echo UMBA_TOOLS environmetnt variable is not set
@exit /B 1

:UMBA_TOOLS_VAR_IS_SET

@call %~dp0\.bat\setup_out_pp_root_paths.bat
@call %~dp0\update_md-pp-view-conf-options.bat

@if not exist %UMBA_TOOLS%\bin    mkdir %UMBA_TOOLS%\bin
@if not exist %UMBA_TOOLS%\conf   mkdir %UMBA_TOOLS%\conf

@IF "%PPROOTPATH%"=="" @(
    @echo PPROOTPATH not found
    exit /B 1
)


copy /Y "%PPROOTPATH%\Release\umba-fsm.exe"         %UMBA_TOOLS%\bin\
copy /Y "%PPROOTPATH%\Release\umba-fsm-view.exe"    %UMBA_TOOLS%\bin\

@xcopy /Y /S /E /I /F /R %~dp0\_distr_conf\conf\*               %UMBA_TOOLS%\conf

@rem umba-brief-scanner --help > help.txt