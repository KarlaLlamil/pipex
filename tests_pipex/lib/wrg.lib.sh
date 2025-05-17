#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    wrg.lib.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: werodrig <werodrig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/04 15:44:26 by werodrig          #+#    #+#              #
#    Updated: 2025/04/13 17:35:59 by werodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ===========================
# =          Color          =
__clr()     { echo -ne "\033[$1m$2\033[0m"; }
_red()      { __clr "31" $1; }
_green()    { __clr "32" $1; }
_yellow()   { __clr "33" $1; }
_blue()     { __clr "34" $1; }
_gray()     { __clr "37" $1; }
_magenta()  { __clr "35" $1; }
_bold()     { __clr "1" $1; }
# ===========================



# ===========================
# =        Functions        =

_rnd_msg() {
    local msgs=("$@")
    local random_index=$(($((RANDOM % ${#msgs[@]}))))
    
    echo "${msgs[$random_index]}"
}

# Icons
_icon_make()        { echo -ne "$(_red      "𖹭")"; }
_icon_cc()          { echo -ne "$(_red      "c")"; }
_icon_valgrind()    { echo -ne "$(_red      "v")"; }
_icon_wrong()       { echo -ne "$(_red      "✘")"; }
_icon_info()        { echo -ne "$(_blue     "i")"; }
_icon_arrow()       { echo -ne "$(_blue     "→")"; }
_icon_corner()      { echo -ne              "»";   }
_icon_dot()         { echo -ne "$(_yellow   ">")"; }
_icon_ok()          { echo -ne "$(_green    "✔")"; }

# Helpers
_s()                { echo -ne " $1 "; }
_p()                { echo -e  "$(_s "$1")$2"; }
_p_ne()             { echo -ne  "$(_s "$1")$2"; }
_p_min()            { echo -ne "$(printf "%-$1s" "$2")"; }
_p_nw()             { echo -e  "\n"; }
_p_title()          { echo -e  "\n\n$(_s " ")$(_bold "$(_blue "$1")")"; }
_p_ok()             { _p       "$(_icon_ok)"      "$1"; }
_p_error()          { _p       "$(_icon_wrong)"   "$1"; }
_p_info()           { _p       "$(_icon_info)"    "$1"; }
_p_doc_desc()       { _p " "             "$1." ; }
_p_doc_arg()        { _p $(_icon_corner) "$(_p_min 20 "--$1")\t$2." ; }
_p_doc_glossary()   { _p $(_icon_corner) "$(_p_min 20 "$1")\tMeans, $2." ; }
_p_doc_arg_ex()     {
    local exec=("$1")
    local flag=("$2")
    shift; shift;

    for arg_ex in "$@"; do
        _p " " "$(_p_min 2 "")$(_p_min 15 "|ex:")\t$exec --$flag $arg_ex";
    done 
    _p " " "$(_p_min 2 "")- - - - - -"
}
_p_files()          {
    for filename in "$@"; do
        _p $(_icon_corner) "You can check this file:\t$(_icon_dot) $filename"
    done
}
_p_line() {
    local line=$(printf "%-$1s" | tr ' ' "$2")
    echo "$line"
}

# ===========================

# ===========================
# =        EasterPhr        =
_MSG_ALL_TEST_OK=(
    "You passed the test like a pipe!"
    "Perfect day to pass pipex!"
    "NICE → Pipe | Pipe → NICE"
    "Testin → PassedOut"
    "No leaks, just pipes!"
    "Pipe down the haters!"  
    "Pipe-riphic performance! 👏"
    "Pipe-ñata smashed! 🪅" 
    "Pipe-ntastic job! 🎉"
    "You're a wizard, Harry!"
    "You did it! You made it!"
    "You are the best!"
    "Another tester has been defeated!"
    "Pipex easy?"
    "Please, do your own tests!"
    "Werodrig is proudn't of you!"
    "Nice job!"
    "Are you sure all is OK?"
    "KO'nt"
    "You are free to add your own tests!"
    "OMG, you did it!"
    "ft_OK()!"
    "!Perfect"
    "So, what's next?"
    "Ready for the next test?"
    "Also try my other proyect tools!"
    "ft_NICE()!"
    "#ifndef BUGS_H # define NICE"
    "GG, you did it!"
)

_MSG_ALL_TEST_KO=(
    "Pipexn't"
    "Tuberiax?"
    "Data don't travel into the pipes!"
    "Data don't travel into the pipes!"
    "Debug time!"
    "Common, you can fix it!"
    "Step by step, you can do it!"
    "Remember, you can see the logs in ./log/"
    "You can do it!"
    "If you need help, you can ask me!"
    "You can do it, I believe in you!"
    "It just a little bug, you can fix it!"
    "Fix time!"
    "OMG, a bug! (╯°□°）╯︵ ┻━┻"
    "Take a break, you deserve it!"
    "Take a breath, you can do it!"
    "Close your eyes and think about the solution!"
    "Have you streched your legs in the last hour?"
    "KO!"
    "OK'nt"
    "Maybe you need to take a break?"
    "Ask your partner on the right!"
    "The battle is lost... but not the war!"
    "Try again!"
    "KO, KO, KO... PENTAKILL!!!"
    "Search on stackoverflow.com"
    "ft_memchr(\"-.,,*FIXTIME\", 42, 12)"
    "oh? A difficult bug?"
    "Let's break this bug!"
    "Errors found..."
    "You are so close to the solution!"
    "Compiling... but at what cost?"  
    "Segmentation fault (core dumped) 💀"  
    "Another day, another bug to squash!"  
    "Have you tried turning it off and on again?"  
    "Null pointer exception? Not today!"  
    "This code was working yesterday... I swear!"  
    "Time to caffeinate and debug!"  
    "‘It’s not a bug, it’s a feature’ — *nervous laugh*"  
    "Stack overflow (the website, not the error)."
    "Ctrl+C, Ctrl+V, xd."
    "Race condition? More like *panic* condition."
    "I’m not lazy, I’m in *energy-saving mode*."
    "‘Works on my machine’ XD" 
    "Error 404: Motivation not found."
    "Commit message: ‘please work’"
    "Debugging: 1% skill, 99% staring at the screen."
    "Me: 'I’ll fix it quickly.' *3 hours later*: (ಥ﹏ಥ)"
    "My code: ✨✨. My debugger: 🔥💀🔥."
    "‘It’s just a one-line change’ — *famous last words*."
    "I’d sell my soul for a working unit test right now."
    "My IDE’s autocomplete knows me better than my therapist."
    "Error: Out of coffee *and* patience."
    "Me: ‘I’ll document this later.’ *Later*: ‘What demon wrote this?!’"
    "My motivation is `#define`d as 0."
)
