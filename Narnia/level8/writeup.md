```sh
$ ssh -p 2226 narnia8@narnia.labs.overthewire.org
```

password: mohthuphog

```
++++++++++ high(0xffffffff)
.........
++++++++++
   esp
++++++++++
  argv[1]  <- ebp + 0x10
++++++++++
  argv[0]  <- ebp + 0xc
++++++++++
   argc    <- ebp + 0x8
++++++++++
return addr <- ebp + 0x4
++++++++++
   ebp
++++++++++
.........
++++++++++ low(0x00000000)
```


## In local
```sh
~/ctf/OverTheWire/Narnia/level8:yyy@[master](*｡˃̵ω ˂̵｡) < ./narnia8 $(python -c 'print "A" *20')
AAAAAAAAAAAAAAAAAAAA�B��
```

overflowはしている

format string attack?
