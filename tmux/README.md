# Tmux Cheatsheet

This cheatsheet is based on [this configuration file](https://github.com/leouchoa/.dotfiles). But most commands are default.

# Sessions

- Sessions overview: `C-prefix s`


# Windows

- create new window: `C-prefix c`
- windows overview: `C-prefix w`
- move between windows: 
    - number-based switching: `C-prefix window_number`
    - next window: `C-prefix n`
    - previous window: `C-prefix p`
- rename windows: `C-prefix ,`
- enter vim mode to move in you terminal screen: `C-prefix [`
- if you're inside a section and wants to rename it: `tmux rename-session new_session_name`

# Panes

- cycling between between panes: `C-prefix o`
