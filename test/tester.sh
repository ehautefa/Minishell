# MINISHELL-TESTER

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

# Compile and set executable rights
make -C ../ 
cp ../minishell .
chmod 755 minishell

function exec_test()
{
	echo "exit |" $@ | ./minishell | cut -d'$' -f2 2>&- 1>sorti
	ES_1=$?
	TEST1=$(tail -n +2 sorti | head -n -1 )
	TEST2=$(echo "exit |" $@ | bash 2>&-)
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED|$TEST1|\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN|$TEST2|\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi

	echo
	sleep 0.1
}

function exec_env()
{
	echo $@ "; exit" | ./minishell 2>&- 1>out_1
	ES_1=$?
	echo $@ "; exit" | bash 2>&- 1>out_2
	ES_2=$?
	sed -i '/SHLVL/d' ./out_1 ./out_2
	sed -i '/declare -x _=/d' ./out_1 ./out_2
	TEST1=$(tail -n +2 out_1)
	TEST2=$(cat out_2)
	if [ "$TEST1" == "$TEST2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED|$TEST1|\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN|$TEST2|\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	# if [ "$ES_1" != "$ES_2" ]; then
	# 	echo
	# 	echo
	# 	printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
	# 	printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	# fi
	echo
	sleep 0.1
}

printf "$BOLDMAGENTA __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
printf "| |\/| | | | | . \ | | |  \___ \|  __  |  __| | |    | |     \n"
printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$RESET"
echo

# SYNTAX ERROR
exec_test 'cat Makefile'
exec_test '' 

# # ECHO TESTS ESPACE
exec_test 'echo test tout'
exec_test 'echo "coucou"les"amis"'
exec_test 'echo test      tout'
exec_test 'echo "salut"cou""'
exec_test 'echo testtout' 
exec_test 'echo "coucou"les"amis"' 
exec_test 'echo testout' 
exec_test 'echo "salut"cou""' 
exec_test 'echo $PATH' 

# # ENV EXPANSIONS + ESCAPE
exec_test 'echo test     test'
exec_test 'echo test'
exec_test 'echo $TEST'
exec_test 'echo "$TEST"'
# exec_test "echo '$TEST'"
exec_test 'echo "$TEST$TEST$TEST"'
exec_test 'echo "$TEST$TEST=lol$TEST"'
exec_test 'echo "   $TEST lol $TEST"'
exec_test 'echo $TEST$TEST$TEST'
exec_test 'echo $TEST$TEST=lol$TEST""lol'
exec_test 'echo    $TEST lol $TEST'
exec_test 'echo test "" test "" test'
exec_test 'echo "$TEST"'
exec_test 'echo "$=TEST"'
exec_test 'echo "$"'
exec_test 'echo "$?TEST"'
exec_test 'echo $TEST $TEST'
exec_test 'echo "$1TEST"'
exec_test 'echo "$T1TEST"'
exec_test 'echo $ZSH$PWD'
exec_test 'echo $PATH?'


# EXIT
# exec_test "exit 42"
# exec_test "exit 42 53 68"
# exec_test "exit 259"
# exec_test "exit 9223372036854775807"
# exec_test "exit -9223372036854775808"
# exec_test "exit 9223372036854775808"
# exec_test "exit -9223372036854775810"
# exec_test "exit -4"
# exec_test "exit wrong"
# exec_test "exit wrong_command"

# REDIRECTIONS
exec_test 'cat < ls' 
exec_test 'cat < ls > ls' 
exec_test 'cat ls > out' 
exec_test 'cat ls > /dev/null' 
# exec_test 'cat ls >> /dev/random'
exec_test '< /dev/null cat' 

# ENV EXPANSIONS
# ENV_SHOW="env"
# EXPORT_SHOW="export"
# exec_env 'export'
# exec_env 'export coucou="salut les gars" hey="heyhey" ; export'
# exec_env 'export coucou="salut" blabla=hey ; export'
# exec_env 'export coucou='salut' blabla=hey ; export'
# exec_test 'export 1TEST=louloute ;' $ENV_SHOW
# exec_test 'export TEST ;' $EXPORT_SHOW
# exec_test 'export ""="" ; ' $ENV_SHOW
# exec_test 'export TES=T="" ;' $ENV_SHOW
# exec_test 'export TE+S=T="" ;' $ENV_SHOW
# exec_test 'export TEST=LOL ; echo $TEST ;' $ENV_SHOW
# exec_test 'export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST'
# exec_test 'export TEST=LOL; export TEST+=LOL ; echo $TEST ;' $ENV_SHOW
# exec_test $ENV_SHOW
# exec_test $EXPORT_SHOW
# exec_test 'export TEST="ls       -l     - a" ; echo $TEST ; $LS ; ' $ENV_SHOW

#NEW TEST
exec_test 'echo bonjour > test\ 1'
exec_test 'cd $HOME/Documents'
exec_test 'echo >'
exec_test 'export ""'
exec_test 'unset ""'
exec_test 'echo test > file test1'
exec_test 'echo bonjour >>> test'
exec_test 'echo bonjour > > out'
exec_test 'echo 2 >> out1 > out2'
exec_test 'echo 2 > out1 >> out2'
exec_test 'tester.sh'
exec_test 'export "test=ici"=coucou'
exec_test '$LESS$VAR'
exec_test '/bin/echo bonjour'
exec_test 'not_cmd'
exec_test '"exit retour a la ligne"'
exec_test 'exit -10'
exec_test 'exit +10'
exec_test 'echo "$HOME"'
exec_test 'echo '$HOME''
exec_test '> log echo coucou'
exec_test 'echo $HOME'
exec_test 'echo'
exec_test 'echo simple'
exec_test 'echo '''
exec_test '> a ls > b < Makefile'
exec_test 'echo > a Hello World!'
exec_test '> a echo Hello World!'
exec_test 'pwd a'
exec_test 'pwd a b c d'
exec_test 'export LOL=lala ROR=rara'
exec_test 'unset LOL ROR'
exec_test 'export "HI= hi"'
exec_test 'export "HI =hi"'
exec_test '/bin/ls'
exec_test 'echo $?'
exec_test 'cd /'
exec_test 'cd'
exec_test 'cd .'
exec_test 'l^Ds'
exec_test 'cat < >'

rm a b file log out out1 out2 test\\ test\ 1 sorti 
