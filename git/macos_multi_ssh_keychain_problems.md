# Configuring Multi-SSH Accounts in MacOS

Works as of `Tue Feb 7 21:33:30 -03 2023`.

Config your `~/.ssh/config` like this:

```
Host github.com
  HostName github.com
  User git
  IdentityFile ~/.ssh/id_ed25519

Host github.com-work
  HostName github.com
  User git
  IdentityFile ~/.ssh/id_ed25519_work

```

Important: when creating your ssh keys, don't forget to run: 

1. `eval "$(ssh-agent -s)"`
2. `ssh-add --apple-use-keychain ~/.ssh/personal_ssh` and `ssh-add --apple-use-keychain ~/.ssh/work_ssh`

Now to clone the repos, run: 

```
git clone git@github.com-work:Samplemed/work_repo.git
git clone git@github.com:Samplemed/personal_repo.git
```

## Troubleshooting

**Important**: you probably should run

```
git credential-osxkeychain erase
host=github.com
protocol=https
```
to erase your keychains credentials and get away from mac repeatedly asking for your credentials.

If apple keeps asking you for you ssh password, run both:
- `ssh-add --apple-use-keychain ~/.ssh/personal_ssh` 
- `ssh-add --apple-use-keychain ~/.ssh/work_ssh`

## Configuring `gh`

Your gh config file is located at `~/.config/gh/hosts.yml`. The thing here is that `gh` doesn't recognize multiple users for the same host website. The "trick" is to just comment out the one you're not gonna use for the moment, until gh decides to implement multi-users config. 

```
github.com:
    oauth_token: your_github_access_token
    user: your_first_user
    git_protocol: ssh
github.com:
    oauth_token: your_github_access_token
    user: your_second_user
    git_protocol: ssh
```

Also important to note is that for public repos you'll always fetch from the API.
