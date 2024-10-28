@if "%PLANTUML_JAR%"=="" goto CHECK_PLANTUML
@goto PLANTUML_FOUND

:CHECK_PLANTUML
@if "%PLANTUML%"=="" goto PLANTUML_NOT_FOUND
@set PLANTUML_JAR="%PLANTUML%"
@goto PLANTUML_FOUND

:PLANTUML_NOT_FOUND
echo Can't find PlantUML JAR
exit /B 1

:PLANTUML_FOUND
@set RUN_CMD=%JAVA_HOME%\bin\java.exe -jar %PLANTUML_JAR% -charset utf8

%RUN_CMD% balancing1.puml
exit /B 0
%RUN_CMD% balancing2.puml


%RUN_CMD% emoji-1F3.puml
%RUN_CMD% emoji-1F4.puml
%RUN_CMD% emoji-1F5.puml
%RUN_CMD% emoji-1F6.puml
%RUN_CMD% emoji-1F9.puml
%RUN_CMD% emoji-26.puml
%RUN_CMD% emoji-27.puml


%RUN_CMD% plantuml_to_fsm_tree_generator.puml

%RUN_CMD% 01-sequenceDiagram.puml

@rem https://plantuml.com/ru/ditaa
@rem More ditaa - https://plantuml.com/ru/ditaa#b5103345741509a1
%RUN_CMD% 02-ditaa-01.puml
%RUN_CMD% 03-ditaa-02a.puml
%RUN_CMD% 04-ditaa-02b.puml
%RUN_CMD% 05-ditaa-02c.puml
%RUN_CMD% 06-ditaa-03.puml

@rem https://plantuml.com/ru/jcckit
%RUN_CMD% 07-JCCKit-01.puml
%RUN_CMD% 08-JCCKit-02.puml
%RUN_CMD% 09-JCCKit-03.puml
%RUN_CMD% 10-JCCKit-04.puml
%RUN_CMD% 11-JCCKit-05.puml

@rem https://plantuml.com/ru/ebnf
%RUN_CMD% 12-bnf-01.puml
%RUN_CMD% 13-bnf-02.puml
%RUN_CMD% 14-bnf-03.puml
%RUN_CMD% 15-bnf-04.puml
%RUN_CMD% 16-bnf-05.puml
%RUN_CMD% 17-bnf-06.puml
%RUN_CMD% 18-bnf-07.puml
%RUN_CMD% 19-bnf-08.puml
%RUN_CMD% 20-bnf-09.puml
%RUN_CMD% 21-bnf-10.puml
%RUN_CMD% 22-bnf-11.puml
%RUN_CMD% 23-bnf-12.puml
%RUN_CMD% 24-bnf-13.puml
%RUN_CMD% 25-bnf-14.puml
%RUN_CMD% 26-bnf-15.puml
%RUN_CMD% 27-bnf-16.puml
%RUN_CMD% 28-bnf-17.puml
%RUN_CMD% 29-bnf-18.puml
%RUN_CMD% 30-bnf-19.puml
%RUN_CMD% 31-bnf-20.puml
%RUN_CMD% 32-bnf-21.puml
%RUN_CMD% 33-bnf-22.puml
%RUN_CMD% 34-bnf-23.puml
%RUN_CMD% 35-bnf-24.puml
%RUN_CMD% 36-state-01.puml
%RUN_CMD% 37-state-02.puml
%RUN_CMD% 38-state-03.puml
%RUN_CMD% 39-state-04.puml
%RUN_CMD% 40-state-05.puml
%RUN_CMD% 41-state-06.puml
%RUN_CMD% 42-state-07.puml
%RUN_CMD% 43-state-08.puml
%RUN_CMD% 44-state-09.puml
%RUN_CMD% 45-state-10.puml
%RUN_CMD% 46-state-11.puml
%RUN_CMD% 47-state-12.puml
%RUN_CMD% 48-state-13.puml
%RUN_CMD% 49-state-14.puml
%RUN_CMD% 50-state-15.puml
%RUN_CMD% 51-state-16.puml
%RUN_CMD% 52-state-17.puml
%RUN_CMD% 53-state-18.puml
%RUN_CMD% 54-state-19.puml
%RUN_CMD% 55-state-20.puml
%RUN_CMD% 56-state-21.puml
%RUN_CMD% 57-state-22.puml
%RUN_CMD% 58-state-23.puml
%RUN_CMD% 59-state-24.puml
%RUN_CMD% 60-state-25.puml
%RUN_CMD% 61-state-26.puml
%RUN_CMD% 62-state-27.puml
%RUN_CMD% 63-state-28.puml
%RUN_CMD% 64-state-29.puml
%RUN_CMD% 65-state-30.puml
%RUN_CMD% 66-state-31.puml
%RUN_CMD% 67-state-32.puml
%RUN_CMD% 68-state-33.puml
%RUN_CMD% 69-state-34.puml
%RUN_CMD% 70-state-35.puml
%RUN_CMD% 71-state-36.puml
%RUN_CMD% 72-state-37.puml
%RUN_CMD% 73-state-38.puml
%RUN_CMD% 74-state-39.puml
%RUN_CMD% 75-state-40.puml
%RUN_CMD% boost_sample_001_no_uml_name.puml
%RUN_CMD% boost_sample_001_org.puml
%RUN_CMD% plantuml_to_fsm_tree_generator.puml
