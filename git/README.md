# Interactive Rebase

- p: pick = use commit
- r: reword = use commit, but edit the commit message
- e: edit = use commit, but stop for amending
- s: squash = use commit, but meld into previous commit
- f: fixup = like "squash", but discard this commit's log message
- x: exec = run command (the rest of the line) using shell
- b: break = stop here (continue rebase later with 'git rebase --continue')
- d: drop = remove commit

# Reset

References:

- [git kraken](https://www.gitkraken.com/learn/git/git-reset)


## Soft 

This option moves HEAD back to the specified commit, undoes all the changes made between where HEAD was pointing and the specified commit, and saves all the changes in the index. In other words, git re-adds the changes as staged, ready to be committed again.

git reset soft is a very safe way to move back to a prior point in your git history and preserve all changes. Since the changes are preserved, this is one way to rewrite your history, applying all the changes across multiple commits into one commit while providing a path for making additional changes at the same time.

## Mixed

Similar to git reset soft, performing a git reset with the --mixed option will undo all the changes between HEAD and the specified commit, but will preserve your changes in the Working Directory, as unstaged changes.

## Hard

Discard all the changes made between HEAD and the specified commit.  

## Tips and Tricks

1. git reset hard discards all working directory and index changes: just run `git rest --hard` and all staged and unstaged files will disapear.
