#!/usr/bin/env bash
# Black-box test.
# Usage: ./test_pipex.sh /path/to/pipex
#
# Mandatory: ./pipex infile cmd1 cmd2 outfile
#   must behave like:  < infile cmd1 | cmd2 > outfile
#
# Most checks run pipex and the equivalent bash pipeline on the same input
# and compare the resulting output files byte for byte.

PIPEX_ARG="${1:-./pipex}"
if [[ ! -x "$PIPEX_ARG" ]]; then
    echo "error: '$PIPEX_ARG' is not executable" >&2
    exit 1
fi
PIPEX=$(realpath "$PIPEX_ARG")

WORK=$(mktemp -d)
trap 'rm -rf "$WORK"' EXIT
cd "$WORK" || exit 1

TIMEOUT_SEC=3
PASS=0
FAIL=0

printf 'hello world\nfoo bar\nhello again\nlast line\n' > infile
: > empty
seq 1 50000 > big

JUNK='XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX'

pass() { PASS=$((PASS + 1)); printf 'PASS  %s\n' "$1"; }
fail() { FAIL=$((FAIL + 1)); printf 'FAIL  %s\n      %s\n' "$1" "$2"; }

# diff_test <name> <pipex args, OUT = outfile> <bash pipeline, OUT = outfile>
# The outfile is pre-filled with junk so truncation is also tested.
diff_test() {
    local name="$1" args="$2" ref="$3"
    printf '%s\n' "$JUNK" > out_p
    cp out_p out_b

    local p_args="${args//OUT/out_p}"
    local b_cmd="${ref//OUT/out_b}"

    eval "timeout $TIMEOUT_SEC $PIPEX $p_args" >/dev/null 2>&1
    local st=$?
    eval "$b_cmd" >/dev/null 2>&1

    if [[ $st -eq 124 ]]; then
        fail "$name" "pipex hung (timeout)"
    elif [[ $st -ge 128 ]]; then
        fail "$name" "pipex crashed (status $st)"
    elif cmp -s out_p out_b; then
        pass "$name"
    else
        fail "$name" "output differs from bash. expected: $(head -c 200 out_b | tr '\n' '|')  got: $(head -c 200 out_p | tr '\n' '|')"
    fi
}

echo "== Mandatory: basic pipeline =="
diff_test "grep | wc -l" \
    "infile 'grep hello' 'wc -l' OUT" \
    "< infile grep hello | wc -l > OUT"

diff_test "cat | tr (uppercase)" \
    "infile cat 'tr a-z A-Z' OUT" \
    "< infile cat | tr a-z A-Z > OUT"

diff_test "commands with options and arguments" \
    "infile 'grep -v foo' 'sed s/o/0/g' OUT" \
    "< infile grep -v foo | sed s/o/0/g > OUT"

diff_test "absolute command paths" \
    "infile /bin/cat /usr/bin/sort OUT" \
    "< infile /bin/cat | /usr/bin/sort > OUT"

diff_test "relative command path" \
    "infile 'cat' 'wc -c' OUT" \
    "< infile cat | wc -c > OUT"

echo "== Mandatory: edge cases =="
diff_test "empty input file" \
    "empty cat 'wc -c' OUT" \
    "< empty cat | wc -c > OUT"

diff_test "large input file" \
    "big 'grep 9' 'wc -l' OUT" \
    "< big grep 9 | wc -l > OUT"

diff_test "no match produces empty output" \
    "infile 'grep nomatch_xyz' cat OUT" \
    "< infile grep nomatch_xyz | cat > OUT"

diff_test "missing infile (outfile still created, cmd2 still runs)" \
    "nofile cat 'wc -c' OUT" \
    "< nofile cat | wc -c > OUT"

diff_test "invalid second command (outfile is empty)" \
    "infile cat nosuchcmd_xyz OUT" \
    "< infile cat | nosuchcmd_xyz > OUT"

diff_test "invalid first command still runs second" \
    "infile nosuchcmd_xyz 'wc -l' OUT" \
    "< infile nosuchcmd_xyz | wc -l > OUT"

echo "== Mandatory: argument handling =="
out=$(timeout "$TIMEOUT_SEC" "$PIPEX" infile cat OUT 2>&1); st=$?
if [[ $st -eq 124 ]]; then
    fail "too few arguments does not hang" "timed out"
elif [[ $st -ge 128 ]]; then
    fail "too few arguments does not crash" "status $st"
else
    pass "too few arguments does not hang or crash"
fi

echo "== Optional: memory leaks (requires valgrind) =="
if command -v valgrind >/dev/null 2>&1; then
    printf 'hello\n' > vg_in
    valgrind --leak-check=full --error-exitcode=42 -q \
        "$PIPEX" vg_in 'cat' 'wc -c' vg_out >/dev/null 2>vg_log
    vst=$?
    if [[ $vst -eq 42 ]]; then
        fail "no leaks or invalid accesses" "see valgrind errors (run valgrind manually for details)"
    else
        pass "no leaks or invalid accesses under valgrind"
    fi
else
    echo "SKIP  valgrind not installed"
fi

echo
echo "Passed: $PASS   Failed: $FAIL"
[[ "$FAIL" -eq 0 ]]
