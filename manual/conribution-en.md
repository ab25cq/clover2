# Contribution

## Development version

develop is the development version, master is the release version.

Life cycle of ## FORK and PULL REQUEST

1. Fork the https://github.com/ab25cq/clover2 repository

2. Clone to the local PC.

```
bash
$ git clone git@github.com:youraccount/clover2.git
$ cd clover 2
```

3. Develop by checkout.

Command | Meaning
--- | ---
| git checkout develop | Go to develop branch
git pull origin develop | update branch
git checkout -b feature- [task_name] | create Generate a new branch from the develop branch and check out to that branch
[add → commit → add → commit → ...] | New function development in branch
Go to git checkout develop | develop branch
git pull origin develop | update branch
git merge --no - ff feature - [task_name] | Merge the new function you created. Be sure to leave a commit message at this time (- no - ff)
git push origin develop | push to develop branch

3. Add clover2 's upstream repository and & fetch & confirm.

```
bash
$ git remote add upstream git@github.com: ab25cq / clover2.git
$ git fetch upstream
$ git branch -a
```

* develop

```
master
remotes / origin / HEAD -> origin / master
remotes / origin / master
remotes / origin / develop
remotes / upstream / develop
remotes / upstream / master
```

4. marge of fetch and upstream

```
$ git fetch upstream
$ git merge upstream / master
```

5. Development & Test

```
make
sudo make install
make test
```

6. Pull request develop on github.


```
$ git checkout develop
$ git push
```