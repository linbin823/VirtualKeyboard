# VirtualKeyboard Qt5虚拟键盘
支持Qt版本：Qt5.0.x ~ Qt5.4.x
使用说明：
1、先编译 VirtualKeyboard 源代码，生成 VirtualKeyboard.so(.dll)；
2、假设要使用输入法的程序是Qt5Demo.exe;
3、在Qt5Demo.exe所在目录新建一个文件夹 platforminputcontexts (文件夹名称不可更改成其他)，
   将 VirtualKeyboard.so(.dll) 放入其中；
4、将代码文件夹中 dict 整个文件夹复制到Qt5Demo.exe所在目录；
5、最后运行 Qt5Demo.exe 即可。
