to compile from g4 to py files you need:
- have java
- download antlr-version-complete.jar from their site for your java (https://www.antlr.org/download/antlr-4.12.0-complete.jar)
- run command `java -jar antlr-4.9.2-complete.jar VIOLALexer.g4 VIOLAParser.g4 -Dlanguage=Python3 -listener -visitor`