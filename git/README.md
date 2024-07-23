# Notes on Using Git

## IDK

### Syntax

- parent searching:
  - either with `~` or `^`
  - tilde (`~`): get the parent of the thing (`HEAD`, `branch_name`, ...).
  - caret (`^`): like `~`, but useful mostly in merges because of
  multiple paths.
  - Examples:
    - `git show HEAD~` reads as: "show HEAD first parent"
    - `git show HEAD~2` reads as: "show HEAD grandparent"
    - `git show HEAD~3` reads as: "show HEAD grand grandparent"
- triple dot: `git show master...your_branch`
  - find commits reachable from either `your_branch` or `master`, but not both.
- double dot: `git show master..your_branch`
  - find commits reachable from `your_branch` but not from `master`
  - you can revert the order `your_branch..master`

### Grep

- context: `git grep your_pattern .py` (search only for python files)
- `and`: `git grep your_pattern --and another_pattern .py`
(search only for python files with two patterns)

## Worktrees

Usually used to fix things. Instead of using a `git clone` in the repo to get a
clean sheet, you use worktree do to it instead. It will get you a clean branch
out of a repo that you choose. Than you fix thing and get back where you where.

### Step-by-Step

```bash
git worktree list
git worktree add choose_your_path choose_branch_usually_main
cd choose_your_path
# fix stuff!
cd back_to_your_original_git_cwd
git worktree remove choose_your_path
# do stuff!
```

### Worktrees Tips and Tricks

- Usually people either make a worktree
  - outside the repo or
  - inside the repo, in a hidden folder.
- Always clean up!

## Interactive Rebase

- p: pick = use commit
- r: reword = use commit, but edit the commit message
- e: edit = use commit, but stop for amending
- s: squash = use commit, but meld into previous commit
- f: fixup = like "squash", but discard this commit's log message
- x: exec = run command (the rest of the line) using shell
- b: break = stop here (continue rebase later with 'git rebase --continue')
- d: drop = remove commit

## Reset

References:

- [git kraken](https://www.gitkraken.com/learn/git/git-reset)

### Soft

This option moves HEAD back to the specified commit, undoes all the changes made
between where HEAD was pointing and the specified commit, and saves all the changes
in the index. In other words, git re-adds the changes as staged, ready to be committed
again.

Git reset soft is a very safe way to move back to a prior point in your git
history and preserve all changes. Since the changes are preserved,
this is one way to rewrite your history, applying all the changes across multiple
commits into one commit while providing a path for making additional changes at
the same time.

### Mixed

Similar to git reset soft, performing a git reset with the --mixed option will
undo all the changes between HEAD and the specified commit, but will preserve
your changes in the Working Directory, as unstaged changes.

### Hard

Discard all the changes made between HEAD and the specified commit.  

### Reset Tips and Tricks

1. git reset hard discards all working directory and index changes:
just run `git rest --hard` and all staged and unstaged files will disapear.

## Updating `ssh` remote path

Suppose you're working in a repo called `git@github.com:username/example_repo.git`,
where `username` could be your user (`leouchoa`) or an organization (`CoolOrg`).
But now you have new ssh keys and your `~/.ssh/config` looks like this:

```bash
```bash
Host github.com
  HostName github.com
  User git
  IdentityFile ~/.ssh/id_ed25519

Host github.com-work
  HostName github.com
  User git
  IdentityFile ~/.ssh/work
```

You can update your remote path to point to those new `ssh` keys so that
you keep perfoming `git` operations without having to reclone the repo:

```bash
git remote set-url origin git@github.com-work:username/example_repo.git
git remote -v #to check if it worked
git fetch #to check if it worked
```

Now git will look for your `~/.ssh.work` keys, instead of `~/.ssh/id_ed25519`
keys.
