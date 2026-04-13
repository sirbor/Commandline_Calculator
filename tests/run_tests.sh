#!/usr/bin/env bash
set -euo pipefail

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROJECT_ROOT"

pass_count=0
fail_count=0

run_case() {
    local name="$1"
    local input="$2"
    local expected="$3"

    local out
    out="$(printf "%b" "$input" | ./calculator 2>&1 || true)"

    if [[ "$out" == *"$expected"* ]]; then
        echo "[PASS] $name"
        pass_count=$((pass_count + 1))
    else
        echo "[FAIL] $name"
        echo "  expected snippet: $expected"
        fail_count=$((fail_count + 1))
    fi
}

run_case "basic addition" "basic add 2 3\nquit\n" "5"
run_case "solver roots spaced expression" "solver roots x^2 - 2 0 2\nquit\n" "1.41421"
run_case "calculus integral spaced expression" "calculus integral x^2 + 1 0 1\nquit\n" "1.333"
run_case "expression trailing token rejected" "solver roots x^2 junk 0 2\nquit\n" "Error evaluating expression at bounds."
run_case "division by zero rejected" "graphical plot 1/0\nquit\n" "Could not evaluate expression"
run_case "history last works" "basic add 4 6\nhistory last\nquit\n" "10"
run_case "history clear works" "basic add 1 1\nhistory clear\nhistory\nquit\n" "History is empty"
run_case "programming concepts command" "programming concepts\nquit\n" "C Concepts Covered"

echo
echo "Passed: $pass_count"
echo "Failed: $fail_count"

if [[ "$fail_count" -ne 0 ]]; then
    exit 1
fi
