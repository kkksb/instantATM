# segmentation fault

アクセス不可能なメモリにアクセスしてしまっているとのこと。
https://teratail.com/questions/100033

どうやら、nullポインタが返却されてしまっていたようだ。
https://ja.stackoverflow.com/questions/9663/strtok%E3%81%AE%E8%BF%94%E3%82%8A%E5%80%A4%E3%82%92strcpy%E3%81%99%E3%82%8B%E3%81%A8segfault%E3%81%99%E3%82%8B%E3%81%AE%E3%81%AF%E3%81%AA%E3%81%9C%E3%81%A7%E3%81%99%E3%81%8B
→分岐を入れてみると、確かにnullが返っていた。

## 文字コードの指定

コンソールで文字化けしたら、以下を実行。
```
$ chcp 65001
```

[Windows10のgccでUTF8で作ったコードが文字化けする場合の対処 \| 電脳産物](https://dianxnao.com/windows10%E3%81%AEgcc%E3%81%A7utf8%E3%81%A7%E4%BD%9C%E3%81%A3%E3%81%9F%E3%82%B3%E3%83%BC%E3%83%89%E3%81%8C%E6%96%87%E5%AD%97%E5%8C%96%E3%81%91%E3%81%99%E3%82%8B%E5%A0%B4%E5%90%88%E3%81%AE%E5%AF%BE/)

## デバッグの方法

https://mattyan1053.hatenablog.com/entry/2018/12/08/155228#VSCode%E3%81%A7CC%E3%81%AE%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%A0%E3%82%92%E3%83%87%E3%83%90%E3%83%83%E3%82%B0%E3%81%97%E3%81%9F%E3%81%84https://mattyan1053.hatenablog.com/entry/2018/12/08/155228#VSCode%E3%81%A7CC%E3%81%AE%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%A0%E3%82%92%E3%83%87%E3%83%90%E3%83%83%E3%82%B0%E3%81%97%E3%81%9F%E3%81%84

これをC言語ように変形する。