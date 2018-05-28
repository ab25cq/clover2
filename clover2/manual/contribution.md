# コントリビューション

## 開発バージョン

develop が開発版で、masterがリリースバージョンです。

## FORK と PULL REQUEST のライフサイクル

1. https://github.com/ab25cq/clover2 リポジトリをフォークします

2. ローカルPCにクローンします。

```bash
$ git clone git@github.com:youraccount/clover2.git
$ cd clover2
```

3. developをcheckoutして開発します。

コマンド | 意味
--- | ---
|git checkout develop	| developブランチに移動
git pull origin develop	| developブランチを更新
git checkout -b feature-[task_name]	| developブランチから新しいブランチを生成してそのブランチにチェックアウト
[add → commit → add → commit →...]	| ブランチ内で新機能開発
git checkout develop	| developブランチに移動
git pull origin develop	| developブランチを更新
git merge --no-ff feature-[task_name]	| 作った新機能をマージする。このときに必ずコミットメッセージを残す(--no-ff)
git push origin develop	| developブランチにプッシュ

3. clover2 の upstream repository を追加して & fetch & 確認します。

```bash
$ git remote add upstream git@github.com:ab25cq/clover2.git
$ git fetch upstream
$ git branch -a

* develop
master
remotes/origin/HEAD -> origin/master
remotes/origin/master
remotes/origin/develop
remotes/upstream/develop
remotes/upstream/master
```

4. fetch と upstream の marge 

```
$ git fetch upstream
$ git merge upstream/master
```

5. 開発＆テスト

```
make
sudo make install
make test
```

6. github 上で develop に pull request します。


```
$ git checkout develop
$ git push
```
