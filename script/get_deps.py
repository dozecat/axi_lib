#!/usr/bin/env python3
"""
Dependency manager for axi_lib.
Downloads vaxivip and corosim sources into .deps/ for simulation.

Usage:
    python script/get_deps.py --init      download / update dependencies
    python script/get_deps.py --update    update dependencies to latest
    python script/get_deps.py --status    show dependency version status
"""

import os
import sys
import time
import shutil
import argparse
import subprocess

ROOT       = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEPS_DIR   = os.path.join(ROOT, ".deps")
CACHE_DIR  = os.path.join(os.path.expanduser("~"), ".cache", "axi_lib_deps")

REPOS = {
    "vaxivip": {
        "url":    "git@github.com:dozecat/vaxivip.git",
        "dest":   "sim",
        "prefix": "src/",
        "files":  [
            "axi/",
            "axil/",
            "axis/",
            "log.hpp",
            "sig.hpp",
        ],
    },
    "corosim": {
        "url":    "git@github.com:dozecat/corosim.git",
        "dest":   "sim",
        "prefix": "src/",
        "files":  [
            "corosim.hpp",
            "task.hpp",
            "delay.hpp",
            "signal.hpp",
            "engine.hpp",
            "engine.cpp",
            "triggers.hpp",
        ],
    },
}


GIT_TIMEOUT = 15


def run(cmd, cwd=None):
    r = subprocess.run(cmd, cwd=cwd)
    if r.returncode != 0:
        sys.exit(r.returncode)


def git_pull(cwd):
    env = os.environ.copy()
    env["GIT_TERMINAL_PROMPT"] = "0"
    try:
        subprocess.run(["git", "pull", "--ff-only"], cwd=cwd, env=env,
                       timeout=GIT_TIMEOUT, capture_output=True)
    except subprocess.TimeoutExpired:
        print(f"  git pull timed out, using cached version")


def repo_cache_dir(name):
    return os.path.join(CACHE_DIR, name)


def repo_dest_dir(name):
    dest_sub = REPOS[name].get("dest", "")
    return os.path.join(DEPS_DIR, dest_sub, name)


def copy_files(name, repo):
    cache = repo_cache_dir(name)
    dest = repo_dest_dir(name)
    prefix = repo["prefix"]

    for rel in repo["files"]:
        src = os.path.join(cache, prefix + rel)
        dst = os.path.join(dest, rel)

        if rel.endswith("/"):
            if os.path.exists(dst):
                shutil.rmtree(dst)
            shutil.copytree(src, dst)
        else:
            os.makedirs(os.path.dirname(dst), exist_ok=True)
            shutil.copy2(src, dst)

    print(f"  {name} -> {dest}")


def init_deps():
    os.makedirs(DEPS_DIR, exist_ok=True)
    os.makedirs(CACHE_DIR, exist_ok=True)

    for name, repo in REPOS.items():
        cache = repo_cache_dir(name)
        if os.path.exists(cache):
            print(f"  {name} cache exists, updating...")
            git_pull(cache)
        else:
            print(f"  cloning {name}...")
            run(["git", "clone", repo["url"], cache])
        copy_files(name, repo)

    _write_stamp()
    print("done")


def update_deps():
    for name, repo in REPOS.items():
        cache = repo_cache_dir(name)
        if not os.path.exists(cache):
            print(f"  {name} not initialized, run --init first")
            continue
        print(f"  updating {name}...")
        git_pull(cache)
        copy_files(name, repo)

    _write_stamp()
    print("done")


def _write_stamp():
    stamp = os.path.join(DEPS_DIR, ".stamp.prepare")
    with open(stamp, "w") as f:
        f.write(time.ctime() + "\n")


def status_deps():
    for name, repo in REPOS.items():
        cache = repo_cache_dir(name)
        dest = repo_dest_dir(name)

        if not os.path.exists(cache):
            print(f"  {name}: not initialized")
            continue

        r = subprocess.run(
            ["git", "rev-parse", "--short", "HEAD"],
            cwd=cache, capture_output=True, text=True,
        )
        sha = r.stdout.strip()

        r = subprocess.run(
            ["git", "status", "--short"],
            cwd=cache, capture_output=True, text=True,
        )
        dirty = bool(r.stdout.strip())

        file_count = 0
        if os.path.exists(dest):
            for root, dirs, files in os.walk(dest):
                file_count += len(files)

        icon = "*" if dirty else "v"
        dirties = " (dirty)" if dirty else ""
        print(f"  {icon} {name} @ {sha}{dirties}  ({file_count} files)")


def main():
    parser = argparse.ArgumentParser(description="axi_lib dependency manager")
    parser.add_argument("--init", action="store_true", help="download / update dependencies")
    parser.add_argument("--update", action="store_true", help="update dependencies to latest")
    parser.add_argument("--status", action="store_true", help="show dependency version status")
    args = parser.parse_args()

    if not any([args.init, args.update, args.status]):
        parser.print_help()
        return

    if args.init:
        init_deps()
    elif args.update:
        update_deps()
    elif args.status:
        status_deps()


if __name__ == "__main__":
    main()
