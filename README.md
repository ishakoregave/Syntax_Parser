# Syntax_Parser
A recursive descent syntax parser  that can validate the syntax of a source code file provided by the
user.
The source code file provided by the user will be written in a new programming language called “DanC” and is
based upon the following grammar (in BNF):
![image](https://user-images.githubusercontent.com/65064098/221279805-d1319f74-ad46-4250-9dcc-ca78d5e64eb2.png)

Lexeme formation is guided using the BNF rules / grammar above. This application will identify each lexeme
and its associated token. Invalid lexemes will identify their token group as UNKNOWN. The following token
names should be used to identify each valid lexeme:
![image](https://user-images.githubusercontent.com/65064098/221279966-d38d1ac7-b1cd-4c40-8000-df0079695dc7.png)

The parser will read the given DanC source code file then, using the lexical syntax analyzer(https://github.com/ishakoregave/Syntax_Analyzer), identify
lexemes/tokens one at a time to ensure they can be aligned with known BNF rules for the language. For this
language, P::=S would be the root of the parse tree.
