#!/usr/bin/env python3
import argparse
import os
import sys
import subprocess
import time

ROOT   = os.path.dirname(os.path.abspath(__file__))
TB_DIR = os.path.join(ROOT, "sim", "tb")


def color(s, c):
    if not sys.stdout.isatty():
        return s
    codes = {
        "green":  "\033[32m",
        "red":    "\033[31m",
        "bold":   "\033[1m",
    }
    return codes.get(c, "") + s + "\033[0m"


LINE = "=" * 42


def tbs():
    return sorted(
        d for d in os.listdir(TB_DIR)
        if os.path.isdir(os.path.join(TB_DIR, d))
    )


def cmd_init(args):
    subprocess.run(
        [sys.executable, os.path.join(ROOT, "script", "get_deps.py"), "--init"]
    )


def cmd_sim(args):
    if args.tb:
        ok = run_one_tb(args.tb)
        sys.exit(0 if ok else 1)
    else:
        run_all_tbs()


def run_one_tb(tb, idx=None, total=None):
    label = f"[{idx+1}/{total}] " if idx is not None else ""

    tb_dir = os.path.join(TB_DIR, tb)
    t0 = time.time()
    subprocess.run(["make", "-C", tb_dir, "clean"], capture_output=True)
    r = subprocess.run(["make", "-C", tb_dir], capture_output=True, text=True)
    elapsed = time.time() - t0

    icon = color("PASS", "green") if r.returncode == 0 else color("FAIL", "red")
    ok = r.returncode == 0
    print(f"  [{icon}] {label}{tb}  ({elapsed:.1f}s)")
    return ok


def run_all_tbs():
    all_tbs = tbs()
    results, t0 = [], time.time()

    for i, tb in enumerate(all_tbs):
        ok = run_one_tb(tb, idx=i, total=len(all_tbs))
        results.append((tb, ok))

    elapsed = time.time() - t0
    passed = sum(1 for _, ok in results if ok)
    total = len(results)

    print()
    if passed == total:
        print(color(f"  ALL PASS ({passed}/{total})  {elapsed:.1f}s", "green"))
    else:
        print(f"  {color('FAIL', 'red')} ({passed}/{total})  {elapsed:.1f}s")


def cmd_list(args):
    for tb in tbs():
        print(tb)


def cmd_clean(args):
    for tb in tbs():
        subprocess.run(
            ["make", "-C", os.path.join(TB_DIR, tb), "clean"],
            capture_output=True,
        )
    print("all cleaned")


def cmd_fmt(args):
    subprocess.run(
        [sys.executable, os.path.join(ROOT, "script", "remove_trailing_spaces.py"),
         "-r"]
    )


def cmd_status(args):
    subprocess.run(
        [sys.executable, os.path.join(ROOT, "script", "get_deps.py"), "--status"]
    )


def main():
    parser = argparse.ArgumentParser(description="axi_lib project entry point")
    sub = parser.add_subparsers(title="commands", dest="command")

    sub.add_parser("init", help="download / update dependencies")
    sub.add_parser("list", help="list all testbenches")
    sub.add_parser("clean", help="clean all build artifacts")
    sub.add_parser("fmt", help="remove trailing whitespace from source files")
    sub.add_parser("status", help="show dependency version status")
    sub.add_parser("help", help="show this help message")

    sim_parser = sub.add_parser("sim", help="run simulation")
    sim_parser.add_argument(
        "tb", nargs="?",
        help="testbench name (run all if omitted)"
    )

    args = parser.parse_args()

    dispatch = {
        "init":   cmd_init,
        "sim":    cmd_sim,
        "list":   cmd_list,
        "clean":  cmd_clean,
        "fmt":    cmd_fmt,
        "status": cmd_status,
        "help":   lambda _: parser.print_help(),
    }

    if args.command in dispatch:
        dispatch[args.command](args)
    else:
        parser.print_help()


if __name__ == "__main__":
    main()
