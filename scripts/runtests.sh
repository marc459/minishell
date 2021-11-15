#!/bin/bash
#https://github.com/thallard/minishell_tester
#### PARSING TESTS ###
#echo pepe | > a
#ls | | wc
# ls <> a
# w c
#a
cd `find . -name "42_minishell_tester"`
bash grademe.sh -c
