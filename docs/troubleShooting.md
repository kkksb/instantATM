# segmentation fault

アクセス不可能なメモリにアクセスしてしまっているとのこと。
https://teratail.com/questions/100033

どうやら、nullポインタが返却されてしまっていたようだ。
https://ja.stackoverflow.com/questions/9663/strtok%E3%81%AE%E8%BF%94%E3%82%8A%E5%80%A4%E3%82%92strcpy%E3%81%99%E3%82%8B%E3%81%A8segfault%E3%81%99%E3%82%8B%E3%81%AE%E3%81%AF%E3%81%AA%E3%81%9C%E3%81%A7%E3%81%99%E3%81%8B
→分岐を入れてみると、確かにnullが返っていた。