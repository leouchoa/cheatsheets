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

# Matrix Strategy

Add the following to your `yml`:

```
...

jobs:
  example_matrix:
    strategy:
      matrix:
        os: [ubuntu-22.04, macos-latest]
        version: [10, 12, 14]
    runs-on: ${{ matrix.os }}
    steps:
      - uses: actions/setup-node@v3
        with:
          node-version: ${{ matrix.version }}
```

which will add a matrix of options into your contexts, meaning that `${{ matrix.version }}` and `${{ matrix.os }}` can be used. [Here's a good example of usage](https://github.com/alialaa/github-actions-course/blob/master/.github/workflows/matrix.yml) which also has an example for how to use the `include` and `exclude` functions.

# Using Docker Containers

Here's a dumb example of how to spin up a postgres container on a ubuntu host with github-actions.

```
name: containers
on: push


jobs:
  docker-example:
    runs-on: ubuntu-latest
    container:
      image: postgres
      env: 
        POSTGRES_PASSWORD: "${{ secrets.YOUR_PSQL_PASS }}"
      # options:
      # volume:
      # ports:
```

For a more complete example, check out [this example](https://docs.github.com/en/actions/using-containerized-services/creating-postgresql-service-containers#running-jobs-in-containers)


## Making a Step Have it's Own Container

You can have a step use a separate container:


```
jobs:
  docker-example:
    container: 
      image: alpine-latest
    steps:
      name: Docker Step
      uses: docker://bullseye-latest # notice: this means this step will use it's own container
      run: |
        lsb -a
```

## Specifying `Entrypoints` and `Args`

In the docker there are the `ENTRYPOINTS` and `CMD` commands. In github-actions the related yaml entries are, respectively, `entrypoint` and `args`.

So for example if we have in a `Dockerfile`:

```
ENTRYPOINT ['/bin/echo', 'hello']
CMD 'hi'
```

the respective in a github-actions yaml will be something like:

```
jobs:
  docker-example:
    container: 
      image: bullseye-latest
    steps:
      name: Docker Step
      uses: docker://alpine-latest # notice: this means this step will use it's own container
      with:
        entrypoint: '/bin/echo' <---- here
        args: 'hello hi' <---- here
```

Also it is important to remember that in this case the `'hello hi'` args will be available as `['hello', 'hi']` to docker's `CMD` command.


### Multiple Arguments

```
jobs:
  docker-example:
    container: 
      image: bullseye-latest
    steps:
      name: Docker Step
      uses: docker://alpine-latest # notice: this means this step will use it's own container
      with:
        entrypoint: ./script.sh <---- here
        args: 'hello hi' <---- here
```


where `script.sh` is, for example:

```
#!/bin/bash
echo $1 $2
```

will print `'hello hi'`.

**Don't forge to add permission to your script with: `chmod +x script.sh` **



# Adding a Workflow Status Badge

You can add a github badge to display the status of the current commit workflow run (passing/failing). The [syntax](https://docs.github.com/en/actions/monitoring-and-troubleshooting-workflows/adding-a-workflow-status-badge) is this:

```
![](https://github.com/<OWNER>/<REPOSITORY>/actions/workflows/<WORKFLOW_FILE>/badge.svg)
```

You can also filter branches and events you some query params in the URL, for example:

```
![](https://github.com/<OWNER>/<REPOSITORY>/actions/workflows/<WORKFLOW_FILE>/badge.svg?branch=<BRANCH_NAME>&event=<EVENT_NAME>)
```

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

will make the second step run even if the first fails.

One problem with using `failure()` is that only the specified step with run, but not every step after the one that failed. To make every step after the failed run, you can use the `continue-on-error` flag:


```
jobs:
  first-job:
    runs-on: ubuntu-latest
    steps:
      - name: first
        run: eccccccccccccccho "first"
        continue-on-error: true
      - name: second
        run: echo "second"
      - name: third
        run: echo "third"
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


## Caching Folders

You can cache folders by using the [cache action](https://github.com/actions/cache)

## Uploading Artifacts

You can upload artifacts by using the [upload-artifact](https://github.com/actions/upload-artifact) action. This way the artifact will be available for download for a [period of 90 days](https://docs.github.com/en/free-pro-team@latest/actions/reference/usage-limits-billing-and-administration#artifact-and-log-retention-policy).

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


## Setting up Timeout Minutes

If you want your jobs to stop running if it takes too long you can use the `timeout-minutes` entry:

```
jobs:
  first-job:
    runs-on: ubuntu-latest
    timeout-minutes: 360 # stops if it takes 1 hour
    steps:
      - name: first
        run: echo "first"
        continue-on-error: true
```

### Examples

- `feature/feat[AB]`: matches `featA` and `featB`
- `feature/feat[AB]+`: matches `featAB`
- `feature/feat[A-E]`: matches `featA`, `featB`, ..., `featE`
- `!README.md`: matches any branch that doesn't have a `README.md` file


# References

- [list of gha default env variables](https://docs.github.com/en/actions/learn-github-actions/environment-variables#default-environment-variables)
- [stackoverflow: GitHub Clone with OAuth Access Token](https://stackoverflow.com/a/66156992)

