/****************** symname.h *****************/
#include <stdlib.h>
#include <string.h>
#include "sym.h"
char names[64][64];
int  count[64] = {0};
void symnameinit()
{
  strcpy(names[symEOF],"�ɮ׵���");
  strcpy(names[symerror],"error");
  strcpy(names[symHEADER],"���Y��");
  strcpy(names[symDEFINE],"�w�q");
  strcpy(names[symUNDEF],"�����w�q");
  strcpy(names[symTYPE],"�ŧi");
  strcpy(names[INT_CONST],"���");
  strcpy(names[FLOAT_CONST],"�B�I��");
  strcpy(names[CHAR_CONST],"�r��");
  strcpy(names[ID_CONST],"�ѧO��");
  strcpy(names[STRING_CONST],"�r��");
  strcpy(names[SINGLE_COMMENT],"������");
  strcpy(names[MULTI_COMMENT],"�h�����");
  strcpy(names[STORAGE],"�x�s���O");
  strcpy(names[TYPE],"�ŧi");
  strcpy(names[QUAL],"�`��");
  strcpy(names[ENUM],"�C�|");
  strcpy(names[CASE],"case ����");
  strcpy(names[DEFAULT],"default ����");
  strcpy(names[IF],"if ���z��");
  strcpy(names[SWITCH],"switch ���z��");
  strcpy(names[ELSE],"else ���z��");
  strcpy(names[FOR],"���йB��y�y");
  strcpy(names[DO],"do ���z��");
  strcpy(names[WHILE],"while ���z��");
  strcpy(names[GOTO],"goto ���D���z��");
  strcpy(names[CONTINUE],"continue ���D���z��");
  strcpy(names[BREAK],"break ���D���z��");
  strcpy(names[struct_const],"���c����");
  strcpy(names[RETURN],"return ���D���z��");
  strcpy(names[SIZEOF],"sizeof �B��l");
  strcpy(names[WHITESPACES],"�Ŧr��");
  strcpy(names[ID],"�ѧO��");
  strcpy(names[CHANGETYPE],"�j���૬");
  strcpy(names[FUNC],"�禡");
  strcpy(names[STRING],"�r��");
  strcpy(names[CHAR],"�r��");
  strcpy(names[_NULL],"NULL ���ܵ�");
}
