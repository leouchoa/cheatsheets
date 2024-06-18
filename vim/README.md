# Vim Cheatsheet

My cheatsheet for navigating inside vim

## Listing keybinds

- `:help index` will show you every default key-bindings.
- `:map` will show you every custom mapping.
- `:map <leader>` will show you every custom `<leader`> mapping.
- `:verbose nmap` will show you every custom normal mode mapping and where they
are defined.

[Reference](https://stackoverflow.com/questions/27458206/is-there-a-way-to-see-all-vim-keybindings)  
  
## Deleting Lines

- Delete range of lines: `:[from],[to]d`
- Delete x lines before: `:-xd`
- Delete x lines after: `:+xd`
- Delete everything from current line to:
  - top of file: `dgg`
  - end of file: `dG`

- Delete all lines containing a certain word: `:g/word/d`
- Delete all blank lines: `g/^$/d`

## Delete text within scope

Consider this code:

```python
raise HTTPException(
  status_code=status.HTTP_404_NOT_FOUND,
  detail=f"post with id {id} not found"
)
```

where LX is the line numbering. If you go on Line 1 (L1) and press `V%`, you'll
see the vim is smart enough to notice that this code is scope inside parantheses
and will select all the text within it. In this case you can then proceed to
delete this text. This also works for brackets.

You can achieve to this by using `vi(` or `vi)`.

## Using Buffers

- List all buffers: `ls`
- Switch from current buffer to buffer number B: `:bB`
- Execute shell command from vim: `:!your_shell_cmd`

## Moving Between Panes

- Open new pane: `new` or `vnew`
- Switch between panes using an arrow key: `CTRL-W-[arrow_key]`

## Moving in the Line
  
- You can use `f` and `t` to move to the occurrences of the word.
  - Consider this example: `status_code=status.HTTP_404_NOT_FOUND`
    - If you press `fT` you'll move from the first `T` appearence to next and so on
  - You can go to next occurence with `;` and go backward with `,`
  
## Using `g`

- **[GODLIKE INCREMENT TRICK](https://www.youtube.com/watch?v=uL9oOZStezw)**: Suppose you have something like this:

```
data_struct[0] = "foo";
data_struct[0] = "barr";
data_struct[0] = "buzzz";
data_struct[0] = "heheeheh";
```

If you v-block select those lines and press `g` + `CTRL` + `A`, then you'll get a auto-increment in the first incrementable item. (ofc you can just v-line the text and use it)

- You move through the changelist with `g;` (forward) and `g,` (backward)
- Going back to where you writing text: `gi`
- Going back to your last visual mode selection: `gv`
- Deleting lines containing certain word: `:g/word/d`
- Commenting lines containing certain word: `:g/word/norm I comment_pattern`
- Formatting paragraph: on normal mode just do `gq`
- If you have a filename written in your text you can open it with: `gf`
- If you did a line substitution with `s/pattern_1/pattern_2/g`, you can apply this globally with `g&`
- In visual mode you set the selected text into upper case with `gU` and lower case with `gu`
  
## Misc
  
- **lua**: sourcing the current file `:so` (ofc you set a target file)
- open netrw: `:Ex`
- asterisk `*` is a quicker find that auto-identifies the word and searches for it!
- `~` switch cases.
- Reopen last edited file with `c-o` (control-o)
- Redo an action you did on normal mode: hit dot `.`
- Cut text to a specified letter: `cfLETTER`
  - Example: consider the word `texttt`. We can use `cft` to delete all letter ou to the first match of the letter `t` which means that the resulting text of the deletion will be `tt`.
  - Another example: `cf1` --> `text1text2` = `text2`
- capital p (`P`) lets you paste above the line
- in insert mode, pressing `o` lets you jump between beginning/end of selected text

## Folding

First you need to set the Folding method. I usually set to `indent`. Then you can use those [Fold commands](https://neovim.io/doc/user/fold.html):

- To navigate between folds, you can use `zj` and `zk`
- to open a fold you can use `za` or `zo` with respective uppe cases
- to close a fold you can use `zc`
- there's a cool thing you can with zm and zr which opens/closes by level recursively

## The dot operator

It repeats the last action performed. Here's a [link](https://sodocumentation.net/vim/topic/3665/the-dot-operator) to good example

## Vimdiff

You can diff and merge files inside vim. Also you can [diff buffers](http://vimcasts.org/episodes/comparing-buffers-with-vimdiff/).

## Opening diffmode

Suppose you have two files, named `f1` and `f2`. Then to enter diffmode you can use:

1. `nvim -d f1 f2` or `nvim -d *` if there's only f1 and f2 there
2. `windo diffthis` if you have both `f1` and `f2` open already.

## diffmode commands

Inside `diffmode` you can use:

- `:diffput` ( or `dp` as a shortcut) to put the put the difference in the other buffer
- `:diffget` ( or `do` as a shortcut) to get the put the difference from the other buffer
- `:diffupdate`, `:diffu`: recalculate the diff
- `:diffg RE`: get from REMOTE
- `:diffg BA`: get from BASE
- `:diffg LO`: get from LOCAL

## Visual Block Editing

You can use `control-v` to enter visual block mode. Then you can delete, cut, yank, insert upper/lower case, etc... But the coolest thing is to insert text, which you achieve with `shift-i`:

1. Enter visual block mode and select text.
2. Press `shift-i` and write the text you want to be added.
3. Press escape `esc` and the changes should take effect.

## Regex

To use regex in vim, just remember to prepend `\` before any special characters, like `\w` for words or `\(\)` for grouping.

- **Tip**: don't forget you can access the grouping variable! This can be achieved with `\NumberOfMatch`. So for example to change the word between numbers you in this ---> `12345heheheh12345` <--- you can use: `s/\([a-z]\+\)/\1_hahahah/` and it will become `12345"heheheh_hahahah"12345`

## Vi vs Vim Differences

References:

- [Article from shell-tips](https://www.shell-tips.com/linux/vi-vs-vim/#gsc.tab=0)
- ["Official" differences](https://vimhelp.org/vi_diff.txt.html#vi-differences)
