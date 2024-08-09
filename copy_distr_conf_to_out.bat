@call %~dp0\update_md-pp-view-conf-options.bat
@call %~dp0\.bat\setup_out_pp_root_paths.bat

@FOR %%i IN (%PPROOTPATHS%) DO @(
        @IF EXIST "%%~i\" @(
            xcopy /Y /S /E /I /F /R %~dp0\_distr_conf\conf\*  "%%~i\\conf"
)
)
