#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
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
__path_cache="./cache/"
__path_data="./data/"
__exec_sh="./test.sh"
__file_err="$__path_cache/_err.log"
__file_val="$__path_cache/_val.log"
_path_project="./../"
_exec_out="pipex"
__exec_out="$__path_cache$_exec_out"
# ===========================


# ===========================
# =        Functions        =
# Custom icons
_icon_fds()         { echo -ne "$(_red      "ƒ")"; }

# Doc
_show_usage() {
    clear
    _p_nw
    _p_info "What is ${__exec_sh}?"
    _p_doc_desc "A pipex test tool!"
    _p_doc_desc "It run with valgrind"
    _p_doc_desc "This depends on your Makefile"
    _p_nw

    _p_info "Usage:"
    _p_doc_arg "test"					"Test with args"
    _p_doc_arg_ex ${__exec_sh} "test"\
        "<filein> <cmd1> <cmd2> ... <cmdn> <fileout>"\
        "data/00_lorem.txt cat cat log/out.txt"
    _p_doc_arg "help"					"Show usage info"
    _p_nw

    _p_info "Glossary:"
    _p_doc_glossary $(_icon_make)      "makefile failed"
    _p_doc_glossary $(_icon_valgrind)  "memory leaks"
    _p_doc_glossary $(_icon_fds)       "file descriptors not closed"
    _p_doc_glossary $(_icon_wrong)     "output is wrong"
    _p_doc_glossary $(_icon_dot)       "in VsCode terminal, ctrl + click, to open the file"
    _p_doc_glossary $(_icon_ok)        "test correct"
    _p_nw

    exit 0;
}

# Search a file, and copy in the cache
_add_to_cache() {
    local file_name="$1"
    local file_path=$(find "$_path_project" -name "$file_name" 2>/dev/null)
    if [ -z "$file_path" ]; then
        _p_nw
        _p $(_icon_wrong) "File '$file_name' not found in '$_path_project'."
        _p_nw
        exit 1
    fi
    cp "$file_path" "$__path_cache"
    if [ $? -ne 0 ]; then
        _p_nw
        _p $(_icon_wrong) "Copying '$file_name' failed."
        _p_nw
        exit 1
    fi
}
# ===========================


# Args
if [ "$1" == "--help" ]; then
    _show_usage
elif [ "$1" == "--test" ]; then
    shift
else
    _show_usage
fi

# Make
_p_info "Compiling pipex..."
make -C $_path_project > /dev/null 2>&1
if [ $? -ne 0 ]; then
    _p_nw
    _p $(_icon_make)    "Make failed."
    _p_nw
    exit 1;
fi

# Cache
rm -rf ./cache/*
mkdir -p ./cache
mkdir -p ./log

_add_to_cache $_exec_out


# Title
clear
_p_title "Pipex"
_p "\t" "test tool by werodrig"
_p_nw


# Valgrind
__flagsopt="--verbose -s"
__flagsmem="--show-leak-kinds=all --track-origins=yes --leak-check=full"
__flagsfds="--track-fds=all"
__flagschd="--trace-children=yes"
__flagslog="--log-file=$__file_val"
echo -e "Doing this: \nvalgrind $__flagsopt $__flagsmem $__flagsfds $__flagschd $__exec_out $@"
valgrind $__flagsopt $__flagsmem $__flagsfds $__flagschd $__flagslog $__exec_out "$@" 2> $__file_err

# Check memory leaks
grep "All heap blocks were freed -- no leaks are possible" $__file_val > /dev/null 2>&1
if [ $? -ne 0 ]; then
    _p $(_icon_valgrind) "Memory leaks founded"
    _p_info "You can open $(_icon_dot) $__file_val"
    _p " "   "\n\n$(_rnd_msg "${_MSG_ALL_TEST_KO[@]}")"
    exit 1
fi

unclosed_fds=$(awk '
  /Open file descriptor/ {
    fd = $0
    while (getline && $0 ~ /^\s*$/) ;
    if ($0 !~ /inherited from parent/ && $0 !~ /inherit/) {
      print fd
      exit 1  # Fd leak!
    }
  }
  END { exit 0 }  # No fds
' "$__file_val")

# Check for non-inherited FDs
if [ -n "$unclosed_fds" ]; then
    _p $(_icon_fds) "Unclosed FDs found:\n\n$unclosed_fds\n\n"
    _p_info "You can open $(_icon_dot) $__file_val"
    _p " "   "\n\n$(_rnd_msg "${_MSG_ALL_TEST_KO[@]}")"
    exit 1
fi

# Check for any Valgrind errors (must be 0)
grep "ERROR SUMMARY: 0 errors" $__file_val > /dev/null 2>&1
if [ $? -ne 0 ]; then
    _p $(_icon_valgrind) "Valgrind errors detected"
    _p_info "You can open $(_icon_dot) $__file_val"
    _p " "   "\n\n$(_rnd_msg "${_MSG_ALL_TEST_KO[@]}")"
    exit 1
fi

_p_nw
_p $(_icon_ok)      "$(_rnd_msg "${_MSG_ALL_TEST_OK[@]}")"
