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

�������ʹ�ø��ļ�,��Ĺ�����Ӧ��֧�� printf �������
�÷�:
�� �ļ�Externfunc.c��
����һ��Ԫ�ص� functable[] ������
  EXPOTRFUNC( �������� , �����ĺ����� , ����ĸ�ʽ�޶��� ,�������)
ʾ��:
EXPOTRFUNC(LIST,ExternFunc_list, ,�����ܵ��õĺ����б�);
����: �������޶����� ֻ��ʹ�� ' ' (�ո�) �������
�ں��������в��ܺ���' ' �ַ�
ʾ��: %d %d 
����ʾ�� : %d,%d