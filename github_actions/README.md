# Enabling debug mode

Follow these steps:

1. go to settings
2. go to secrets
3. add those two new secrets: 
  - `ACTIONS_RUNNER_DEBUG` to `true`
  - `ACTIONS_STEP_DEBUG` to `true`

Note that they're very verbose, so use with care. Also take note that you can download the log artifacts by clicking on the top right three dot button.

# Specifying Other Shell Commands

Github actions allows you to run a shell other than `bash`, like `zsh` or even `python`. For python, you can do something like:

```
...
  - steps: 
    ...
    - name: python cmd
      run: |
        import platform
        print(platform.processor())
      shel: python
```

# Using `GITHUB_TOKEN` to give third-party actions Access

To give access permission you just have to use the `${{ secrets.GITHUB_TOKEN }}` token. [Here](https://docs.github.com/en/actions/security-guides/automatic-token-authentication#example-2-calling-the-rest-api) is a nice example of creating an issue by making an API request.

# Specifying Secrets Bigger than `64`kbs

Github secrets [cannot be bigger than `64`kbs](https://docs.github.com/en/actions/security-guides/encrypted-secrets). But if there's no way around that, what you can do is to:

1. add the config to a file
2. encrypt it with gpg
3. save the decryption password as a github secret
4. add a step in your workflow to decrypt the file by running something like `gpg --quit --batch --yes --decrypt --passphrase="$GPG_PASSPHRASE" encrypted_file.gpg` (don't forget to access the secret with `${{ secrets.GPG_PASSPHRASE }})

# Contexts

Remember the `${{ asd.VARIABLE }}` syntax? Well the `asd` thing inside of it is called a [`context`](https://docs.github.com/en/actions/learn-github-actions/contexts). There are also some special [functions that can be used in conjunction with function](https://docs.github.com/en/actions/learn-github-actions/expressions#functions)

# Common Scenarios

## Make a Step Depend on Another

Add the `needs` field in the `jobs` field.

```
jobs:
  first-job:
    runs-on: ubuntu-latest
    steps:
      - name: first
        run: echo "first"
  second-job:
    runs-on: ubuntu-latest
    needs: ["first-job"] <---- here
    steps:
      - name: second
        run: echo "second"
```

## Run a Step Even if the Previous Fails

You can achieve this by adding an `if: failure()` check. For example

```
jobs:
  first-job:
    runs-on: ubuntu-latest
    steps:
      - name: first
        run: eccccccccccccccho "first"
      - name: second
        if: failure() <-------- here
        run: echo "second"
```

## Using Pre-Built Action

By using the `uses` keyword you can specify a Pre-Built Action, like bellow. Note in the `identifier` part that you can **optionally** use:

- branch (`@master`)
- commit hash (`@e76147da8e5c81eaf017dede5645551d4b94427b`)
- version tag (`@v1.0.0`)

```
jobs:
  first-job:
    runs-on: ubuntu-latest
    steps:
      - name: first
        uses: actions/hello-world-javascript-action@identifier <---- here
```

## Checkout

### Using the `checkout` Action

By default gha won't clone the repo into the server cwd. To do this you can use an action to do this with the checkout action, which will checkout the latest commit:

```
jobs:
  ...
  - name: checkout
    uses: actions/checkout@v3
  ...
```

Checkout the actions [repo](https://github.com/actions/checkout#usage)!

### Manually doing it

```
jobs:
  ...
  - name: checkout
    run: |
      # test this!!
      git clone https://${{ github.token }}git@github:$GITHUB_REPOSITORY
      git checkout $GITHUB_SHA
  ...
```

Reference: [stackoverflow: GitHub Clone with OAuth Access Token](https://stackoverflow.com/a/66156992)
# References

- [list of gha default env variables](https://docs.github.com/en/actions/learn-github-actions/environment-variables#default-environment-variables)
- [stackoverflow: GitHub Clone with OAuth Access Token](https://stackoverflow.com/a/66156992)

## Setting up Cronjobs

You can easily setup (multiple!) cronjobs with the following:

```
name: blahblahblah

on:
  schedule:
    - cron: "* * * * *"
    # - cron: "* * * * *" <---- you can add multiple cronjobs
```

!!IMPORTANT!!: you can only have schedules that run at least every 5 minutes! That means you can't have a workflow that runs every 1, 2, 3 or 4 minutes.

!!**Tip**!! [here's](https://crontab.guru) a nice site to help you create your cronjobs!
## Filtering Branches

You can make your actions run only in certain branches. There are many ways to specify branches, which are described [here](https://help.github.com/en/actions/automating-your-workflow-with-github-actions/workflow-syntax-for-github-actions#filter-pattern-cheat-sheet), like using the single `*` or double `**` wildcards.

### Examples

- `feature/feat[AB]`: matches `featA` and `featB`
- `feature/feat[AB]+`: matches `featAB`
- `feature/feat[A-E]`: matches `featA`, `featB`, ..., `featE`
- `!README.md`: matches any branch that doesn't have a `README.md` file