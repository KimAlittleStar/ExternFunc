If you want to use this file, you should support the printf function in your project.

usage :
in  file Externfunc.c 
add item to functable[];
    EXPOTRFUNC( call _functionstr , real Function name ,  input format , function Introduction)
Eg:  EXPOTRFUNC(LIST,ExternFunc_list, ,can call functionlist);
waring ## input format only use ' ' (space) Separate  
call _functionstr cannot have ' '
Eg: %d %d
Err Eg: %d,%d (it is wrong)

--------------------------------------------------------------------------------------------------------

如果你想使用该文件,你的工程中应该支持 printf 这个函数
用法:
在 文件Externfunc.c中
增加一个元素到 functable[] 数组中
  EXPOTRFUNC( 函数别名 , 真正的函数名 , 输入的格式限定符 ,函数简介)
示例:
EXPOTRFUNC(LIST,ExternFunc_list, ,所有能调用的函数列表);
警告: 在输入限定符中 只能使用 ' ' (空格) 对其隔开
在函数别名中不能含有' ' 字符
示例: %d %d 
错误示例 : %d,%d