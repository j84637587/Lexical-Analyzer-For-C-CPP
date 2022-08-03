# Lexical-Analyzer-For-C-CPP
此專案使用LEX語言來分析C&amp;CPP語法以實現編譯器之原理。

分辨 C 語言中的保留字, 詳細定義於 sym.h
辨識函式回傳型態與名稱、結構名稱
統計各項保留字, 字串, 字元…等 (定義於 sym.h)並顯示
Lex 程式中包含多個檔案的輸出處

### 需求
- Flex > 2.5.*
- GCC > 10

### 結構

#### 執行前
- test_cases - 存放要測試的檔案
- final.l lex - 主程式碼
- sym.h token - 定義文件
- symname.h - token 對應之名稱
- lexinput.cpp - 要解析的程式碼
- run.bat - 方便測試之檔案 直接執行即可產生結果

#### 執行後
- cmd_result.txt - Command Line STDOUT
- out_comment.cpp - 經解析後的註解程式碼
- out_src.cpp - 經解析後不含註解之程式碼
- output.c final.l - 經 flex 產生之 .c 檔
- output.exe output.c - 經 gcc 編譯之結果

### 使用說明

執行以下指令
```
run.bat

or

flex -o"output.c" "final.l"
gcc output.c -o output.exe
output.exe lexinput.cpp
```

### DEMO

#### 測試檔案 1 (/test cases/1/cmd_result.txt)
![image](https://user-images.githubusercontent.com/29170077/182730727-a68a899a-59a0-4d2b-820a-7dcc23699a5b.png)

![image](https://user-images.githubusercontent.com/29170077/182730780-099b900d-0690-4d56-b241-f06dfc0d6d4c.png)

#### 測試檔案 2 (/test cases/2/cmd_result.txt)
![image](https://user-images.githubusercontent.com/29170077/182730846-f0a97439-4d10-4d72-a52c-2bb3a7ccbd71.png)
