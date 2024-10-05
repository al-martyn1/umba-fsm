@set UMBA_MDPP_EXTRA_OPTIONS="--batch-page-index-file=%~dp0doc\pages_index.md"
@call "%~dp0\.bat\fix_tabs.bat"
@set CLOCMD=md_
@call "%~dp0\.bat\run_clock.bat"
@call "%~dp0\.bat\gen-doc.bat"
