leviathan0@leviathan.labs.overthewire.org にパスワード：leviathan0でsshすると .backupというディレクトリ

移動してlsすると、bookmarks.htmlというhtmlファイルがある

とりあえず、passwdやpasswordでgrepすると、

cat bookmarks.html |grep password

```
<DT><A HREF="http://leviathan.labs.overthewire.org/passwordus.html | This will be fixed later, the password for leviathan1 is rioGegei8m" ADD_DATE="1155384634" LAST_CHARSET="ISO-8859-1" ID="rdf:#$2wIU71">password to leviathan1</A>
```

ということで、the password for leviathan1 is rioGegei8m より

rioGegei8m
