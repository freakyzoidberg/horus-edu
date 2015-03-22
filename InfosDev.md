# Introduction #




# SVN #

## Liaison avec les issues ##

Pour résoudre une issue par le svn

|(Fixes issue NNN) 	| Enclose command in parentheses|
|:------------------|:------------------------------|
|Fixes issue NNN. 	|Full sentence in your log message description|
|Fixes issue NNN 	|On a line by itself |


These commands begin on some line in your commit-log message and continue until the end of the message. The syntax is:

Your commit log message descriptive text...

> COMMAND-LINE
> ISSUE-FIELD-UPDATE**> COMMENT-TEXT...**

Where COMMAND-LINE is one of the following:

  * Update issue NNN
  * New issue
  * New review

There can be any number of ISSUE-FIELD-UPDATE lines. These lines can be one of the following:

  * Summary: NEW-VALUE
  * Status: NEW-VALUE
  * Owner: NEW-VALUE
  * Cc: PLUS-MINUS-LIST
  * Labels: PLUS-MINUS-LIST

## wiki ##

Le wiki est versione sur le svn, il faut donc appliquer les meme regles que pour les commit de code.

## issues ##

Il est important de respecter les template d'issues afin de ne pas perdre de temps sur la recherche d information lie au problème.