# cheatsheet_vim
My cheatsheet for navigating inside vim

## Listing keybinds

- `:help index` will show you every default key-bindings.
- `:map` will show you every custom mapping.
- `:map <leader>` will show you every custom <leader> mapping.
- `:verbose nmap` will show you every custom normal mode mapping and where they are defined.

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
```
L1: raise HTTPException(
L2:   status_code=status.HTTP_404_NOT_FOUND,
L3:   detail=f"post with id {id} not found"
L4: )
```
where LX is the line numbering. If you go on Line 1 (L1) and press `V%`, you'll see the vim is smart enough to notice that this code is scope inside parantheses and will select all the text within it. In this case you can then proceed to delete this text. This also works for brackets.

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
  
# Using `g`

- Going back to where you writing text: `gi`
- Going back to your last visual mode selection: `gv`
- Deleting lines containing certain word: `:g/word/d`
- Commenting lines containing certain word: `:g/word/norm I comment_pattern`
- Formatting paragraph: on normal mode just do `gq`
- If you have a filename written in your text you can open it with: `gf`
- If you did a line substitution with `s/pattern_1/pattern_2/g`, you can apply this globally with `g&`
- In visual mode you set the selected text into upper case with `gU` and lower case with `gu`
  
  
# Misc
  
- asterisk `*` is a quicker find that auto-identifies the word and searches for it!
- `~` switch cases.
- Reopen last edited file with `c-o` (control-o)
- Redo an action you did on normal mode: hit dot `.`
- Cut text to a specified letter: `cfLETTER`
  - Example: consider the word `texttt`. We can use `cft` to delete all letter ou to the first match of the letter `t` which means that the resulting text of the deletion will be `tt`.
  - Another example: `cf1` --> `text1text2` = `text2`


# Folding

First you need to set the Folding method. I usually set to `indent`. Then you can use those [Fold commands](https://neovim.io/doc/user/fold.html):

- To navigate between folds, you can use `zj` and `zk`
- to open a fold you can use `za` or `zo` with respective uppe cases
- to close a fold you can use `zc`
- there's a cool thing you can with zm and zr which opens/closes by level recursively


# The dot operator

It repeats the last action performed. Here's a [link](https://sodocumentation.net/vim/topic/3665/the-dot-operator) to good example 

# Vimdiff

You can diff and merge files inside vim. Also you can [diff buffers](http://vimcasts.org/episodes/comparing-buffers-with-vimdiff/).

IMPROVE this
