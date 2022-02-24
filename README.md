# :heavy_check_mark: minishell
This project is aim to understand how shell called bash works and this project is a part methodology learning students from 42 school (21 school in Moscow).  

### Implementation rests on AST(Abstract syntax tree)

### Available options

Minishell runs executables from an absolute, relative or environment PATH (``/bin/ls`` or ``ls``), including arguments or options. ``'`` and ``"`` work the same as bash, except for multiline commands.

You can use redirections ``>`` ``>>`` ``<`` and pipes ``|`` as well as heredoc ``<<``.

Environment variables are handled, like ``$HOME``, including the return code ``$?``.

Finally, you can use ``Ctrl-C`` to interrupt and ``Ctrl-\`` to quit a program, as well as ``Ctrl-D`` to throw an EOF, same as in bash.

A few of the functions are "built-in", meaning we don't call the executable, we re-coded them directly. It's the case for ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset`` and ``exit``.

### Usage

Using ``make`` will create the ``minishell`` executable.

Simply run it with :

```
./minishell
```
## Other
**Authors:**  
:vampire:*[Deeds Baron](https://github.com/DeedsBaron)*

:vampire_woman:*[Wspectra](https://github.com/wspectra)*
