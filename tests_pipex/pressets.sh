#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pressets.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: werodrig <werodrig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/04 15:44:26 by werodrig          #+#    #+#              #
#    Updated: 2025/03/08 15:03:36 by werodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

source "./lib/wrg.lib.sh"

# ===========================
# =         Globals         =
__exec_sh="./pressets.sh"
__exec_testsh="./test.sh"
# mode 0 (do)
# mode 1 (see)
__mode=0
# ===========================


# ===========================
# =        Functions        =
# Doc
_show_usage() {
    clear
    _p_nw
    _p_info "What is ${__exec_sh}?"
    _p_doc_desc "A pipex test pressets!"
    _p_doc_desc "Numeric test means 'should run normally'"
    _p_doc_desc "eNumeric test means 'should show an error'" 
    _p_doc_desc "It run with $__exec_testsh"
    _p_nw

    _p_info "Usage:"
    _p_doc_arg "do"					"Do this test with my pipex"
    _p_doc_arg_ex ${__exec_sh} "do"\
        "1"\
        "e1"\
        "b1"\
        "eb1"
    _p_doc_arg "see"					"Do this with real pipex"
    _p_doc_arg_ex ${__exec_sh} "do"\
        "1"\
        "e1"
    _p_doc_arg "help"					"Show usage info"
    _p_nw

    exit 0;
}

# Pipex
_pipex() {
    if [ "$#" -lt 2 ]; then
        _p $(_icon_wrong) "At least two commands are required"
        return 1
    fi

    local input_file="$1"
    shift
    local commands=("$@")
    local last_cmd="${commands[-1]}"
    unset 'commands[-1]'

    local cmd_chain="cat \"$input_file\""
    for cmd in "${commands[@]}"; do
        cmd_chain+=" | $cmd"
    done
    cmd_chain+=" > \"$last_cmd\""

    eval "$cmd_chain"
}

# Execute test
_do_test()
{
    case "$__mode" in
        "0")
            $__exec_testsh --test "$@";;
        *)
            _pipex "$@";;
    esac
}
# ===========================

# Args
case "$1" in
    "--help")
        _show_usage;;
    "--do")
        shift
        __mode=0
        ;;
    "--see")
        shift
        __mode=1
        ;;
    *)
        _show_usage;;
esac

if [[ "$1" == e* ]]; then
    case "$1" in
        "e1")
            # No args
            _do_test ;;
        "e2")
            # Non existing file in
            _do_test data/100_404notfound cat cat log/out.txt;;
        "e3")
            # Non permission file out
            _do_test data/00_lorem.txt cat cat /osquery.flags;;
        "e4")
            # Non existing file in and non permission file out
            _do_test data/100_404notfound cat cat /osquery.flags;;
        "e5")
            # Non existing first cmd
            _do_test data/00_lorem.txt katinka cat log/out.txt;;
        "e6")
            # Non existing second cmd
            _do_test data/00_lorem.txt cat katinka log/out.txt;;
        "e7")
            # Non existing both cmd
            _do_test data/00_lorem.txt stranger katinka log/out.txt;;
        "e8")
            # NOTHING EXIST!!!!!
            _do_test data/100_404notfound katinka stranger /osquery.flags;;
        "e9")
            # Wrong first cmd
            _do_test data/00_lorem.txt "cat -werodrig" cat log/out.txt;;
        "e10")
            # Wrong second cmd
            _do_test data/00_lorem.txt "cat -werodrig" cat log/out.txt;;
        "e11")
            # Wrong both cmd
            _do_test data/00_lorem.txt "cat -werodrig" "ls -werodrig" log/out.txt;;
        
        # ===========================
        # BONUS
        # ===========================
        "eb1")
            # Non exists 2 first cmds
            _do_test data/00_lorem.txt katinka katinka cat log/out.txt;;
        "eb2")
            # Non exists 2 lasts cmds
            _do_test data/00_lorem.txt cat katinka katinka log/out.txt;;
        "eb3")
            # Non exist any cmd
            _do_test data/00_lorem.txt katinka katinka katinka log/out.txt;;
        "eb4")
            # Non exist first file
            _do_test data/100_404notfound cat cat cat log/out.txt;;
        "eb5")
            # Non permission file out
            _do_test data/00_lorem.txt cat cat cat /osquery.flags;;
        "eb6")
            # Non existing file in and non permission file out
            _do_test data/100_404notfound cat cat cat /osquery.flags;;
        "eb7")
            # NOTHING!!!
            _do_test data/100_404notfound katinka katinka katinka /osquery.flags;;
        # ===========================
        *)
            _p $(_icon_wrong) "No error example $1"
            exit 1
            ;;
    esac
else
    case "$1" in
        "1")
            # Basic pipe through info
            _do_test data/00_lorem.txt cat cat log/out.txt;;
        "2")
            # How many files are?
            _do_test data/00_lorem.txt "ls " "wc -l" log/out.txt;;
        "3")
            # Birds Herrerillo in Arbol
            cmd1="grep -e \"Ave: 'Herrerillo'\""
            _do_test data/01_birds.log "$cmd1" "cat" log/out.txt;;
        "4")
            # Get First line
            _do_test data/00_lorem.txt "head -n 1" "cat" log/out.txt;;
        "5")
            # Get First line, but dont shout
            cmd1="head -n 1"
            cmd2="tr '[:lower:]' '[:upper:]'"
            _do_test data/01_birds.log "$cmd1" "$cmd2" log/out.txt;;
        # ===========================
        # BONUS
        # ===========================
        "b1")
            # Basic pipe
            _do_test data/00_lorem.txt cat cat cat log/out.txt;;
        "b2")
            # One last alive
            _do_test data/00_lorem.txt katinka "cat -werodrig" ls log/out.txt;;
        "b3")
            # Midle work
            _do_test data/00_lorem.txt "cat -werodrig" katinka ls cat cat log/out.txt;;
        "b4")
            # << Here_doc >>
            _do_test here_doc Katinka cat log/out.txt;;
        "b5")
            # << Here_doc with n cmds >>
            _do_test here_doc EOF "grep hola" "grep xd" cat log/out.txt;;
        "b6")
            # PipexChained (Should print nothing)
            cmd1="./cache/pipex data/02_empty.txt cat cat log/out.txt"
            _do_test here_doc EOF "$cmd1" log/out.txt
            ;;
        "b7")
            # Hypnotic (Should print nothing)
            cmd1="cat data/02_empty.txt"
            _do_test here_doc EOF "$cmd1" log/out.txt
            ;;
        # ===========================
        *)
            _p $(_icon_wrong) "No example $1"
            exit 1
            ;;
    esac
fi
