/****************** symname.h *****************/
#include <stdlib.h>
#include <string.h>
#include "sym.h"
char names[64][64];
int  count[64] = {0};
void symnameinit()
{
  strcpy(names[symEOF],"檔案結尾");
  strcpy(names[symerror],"error");
  strcpy(names[symHEADER],"標頭檔");
  strcpy(names[symDEFINE],"定義");
  strcpy(names[symUNDEF],"消除定義");
  strcpy(names[symTYPE],"宣告");
  strcpy(names[INT_CONST],"整數");
  strcpy(names[FLOAT_CONST],"浮點數");
  strcpy(names[CHAR_CONST],"字元");
  strcpy(names[ID_CONST],"識別項");
  strcpy(names[STRING_CONST],"字串");
  strcpy(names[SINGLE_COMMENT],"單行註解");
  strcpy(names[MULTI_COMMENT],"多行註解");
  strcpy(names[STORAGE],"儲存類別");
  strcpy(names[TYPE],"宣告");
  strcpy(names[QUAL],"常數");
  strcpy(names[ENUM],"列舉");
  strcpy(names[CASE],"case 標籤");
  strcpy(names[DEFAULT],"default 標籤");
  strcpy(names[IF],"if 陳述式");
  strcpy(names[SWITCH],"switch 陳述式");
  strcpy(names[ELSE],"else 陳述式");
  strcpy(names[FOR],"反覆運算語句");
  strcpy(names[DO],"do 陳述式");
  strcpy(names[WHILE],"while 陳述式");
  strcpy(names[GOTO],"goto 跳躍陳述式");
  strcpy(names[CONTINUE],"continue 跳躍陳述式");
  strcpy(names[BREAK],"break 跳躍陳述式");
  strcpy(names[struct_const],"結構類型");
  strcpy(names[RETURN],"return 跳躍陳述式");
  strcpy(names[SIZEOF],"sizeof 運算子");
  strcpy(names[WHITESPACES],"空字符");
  strcpy(names[ID],"識別項");
  strcpy(names[CHANGETYPE],"強制轉型");
  strcpy(names[FUNC],"函式");
  strcpy(names[STRING],"字串");
  strcpy(names[CHAR],"字元");
  strcpy(names[_NULL],"NULL 指示詞");
}
