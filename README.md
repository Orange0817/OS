# **如何編譯程式碼**

#### 在Ubuntu輸入：`gcc -o test test.c`

`gcc`是把test.c編譯成執行檔的指令

`test.c`是我們寫的程式碼

`-o test`是指定編譯後輸出的檔名為test

# 如何執行程式碼

#### 在Ubuntu輸入：`./test 5 2 3`

`./`代表執行檔案

`./`後面要加上執行的檔案名稱`test`，以及三個參數（buffer_size, producer_speed, consumer_speed）

三個參數之間要空格否則會被視為只有一個參數

