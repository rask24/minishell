# Grammer

```bison
%token WORD
%token && AND_IF
%token || OR_IF
%token ( LEFT_PARENTHESES
%token ) RIGHT_PARENTHESES
%token | PIPE
%token < LESS
%token << DLESS
%token > GREAT
%token >> DGREAT

list             :           pipeline
                 | list '&&' pipeline
                 | list '||' pipeline
                 ;
pipeline         :              command
                 | pipeline '|' command
                 ;
command          : simple_command
                 | '(' list ')'
                 | '(' list ')' redirect_list
                 ;
simple_command   : cmd_element
                 | simple_command cmd_element
                 ;

cmd_element      : cmd_word
                 | io_redirect
                 ;
cmd_word         : WORD
                 ;
redirect_list    :               io_redirect
                 | redirect_list io_redirect
                 ;
io_redirect      :           io_file
                 |           io_here
                 ;
io_file          : '<'       filename
                 | '>'       filename
                 | '>>'      filename
                 ;
filename         : WORD                      /* Apply rule 2 */
                 ;
io_here          : '<<' here_end             /* Apply rule 3 */
                 ;
here_end         : WORD /* Apply rule 3 */
                 ;
```
