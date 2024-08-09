@rem set BATCH_ROOT=--batch-output-path=C:\work\temp\mdpp-test
@set EXCLUDE_DIRS=--batch-exclude-dir=_libs,libs,_lib,lib,tests,test,rc,_generators,_distr_conf,src,.msvc2019,boost,icons
@set EXCLUDE=%EXCLUDE_DIRS% --batch-exclude-files=*upper_inc.md*
@set COMMON=--overwrite --copy-images --add-examples-path=.\doc --add-examples-path=.\tests\snippets --add-examples-path=.\src
@rem set GRAPHVIZ_OPTIONS=--graphviz-output-path=.\.doc.generated_images
@rem set TEMP_OPTS=--graphviz-keep-temp-dot-files
@set OPTIONS= %TEMP_OPTS% %COMMON% %VARS% %EXCLUDE% %GRAPHVIZ_OPTIONS% --batch-scan-recurse=.


@rem https://stackoverflow.com/questions/3160058/how-to-get-the-path-of-a-batch-script-without-the-trailing-backslash-in-a-single
@rem Для генерации в каталог выше уровнем
@rem set WIKI_DIR=%~dp0
@rem set WIKI_DIR=%WIKI_DIR:~0,-1%
@rem set WIKI_DIR=%WIKI_DIR%.wiki
@rem @if exist %WIKI_DIR% umba-md-pp %OPTIONS% --batch-output-path=%WIKI_DIR%

umba-md-pp %OPTIONS%

@rem C:\work\temp\mdpp-test\ 

