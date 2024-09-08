```
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

simple_command   : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 |            cmd_word cmd_suffix
                 |            cmd_word
                 ;
cmd_word         : WORD
                 ;
cmd_prefix       :            io_redirect
                 | cmd_prefix io_redirect
                 ;
cmd_suffix       :            io_redirect
                 | cmd_suffix io_redirect
                 |            WORD
                 | cmd_suffix WORD
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
