sshすると、checkというsetuidが立っているプログラムがある

実行してみると、パスワードを受け取って、チェックしているらしい
ダメだったら、Wrong password, Good Bye ...と終了させられてしまう

stringsで出てこないかとやってみるがだめ

よって、ltracを使ってライブラリコールをトレースすることを考える

ltrace ./check

とすると、標準ライブラリ関数の呼び出しをトレースできるので、試しにhogeと入力してみる

すると、

```
leviathan1@melinda:~$ ltrace ./check
__libc_start_main(0x804852d, 1, 0xffffd784, 0x80485f0 <unfinished ...>
printf("password: ")                                                                                  = 10
getchar(0x8048680, 47, 0x804a000, 0x8048642password: hoge
)                                                          = 104
getchar(0x8048680, 47, 0x804a000, 0x8048642)                                                          = 111
getchar(0x8048680, 47, 0x804a000, 0x8048642)                                                          = 103
strcmp("hog", "sex")                                                                                  = -1
puts("Wrong password, Good Bye ..."Wrong password, Good Bye ...
)                                                                  = 29
+++ exited (status 0) +++
```

hogeの文字がカットされて3文字にされsexと比較している

```sh
$ whoami
leviathan2
```

leviathan2 の shell が手に入った

```sh
$ cat /etc/leviathan_pass/leviathan2
ougahZi8Ta
```

ps:
ltrace ./check

でパスワードを入力しても、shellは切り替わったようなのだが、leviathan1のままだったので、./checkで普通に実行してからパスワードを入力

トレースしながらだと、ダメ？
