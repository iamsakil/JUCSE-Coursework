# Instructions on how to use graphics.h library on Dev C++ to run these projects

This section contains Dev C++ graphics projects.

1.Install Dev-C++. I installed from the Version 4.9.9.2 Setup File.

2.Download graphics.h to the include/ subdirectory of the Dev-C++ directories.

3.Download libbgi.a to the lib/ In order to use the WinBGIm subdirectory of the Dev-C++ directories.

4.Whenever you #include <graphics.h> in a program, you must instruct the linker to link in certain libraries. The command to do so from Dev-C++ is Alt-P. Choose the Parameters tab from the pop-up window and type the following into the Linker area:
-lbgi
-lgdi32
-lcomdlg32
-luuid
-loleaut32
-lole32
You can now compile and run programs that use the WinBGIm graphics library, such as this one that opens a small window, draws a circle and waits for the user to press a key:

![graphics_code](https://user-images.githubusercontent.com/18322412/32419305-dee80602-c29d-11e7-8ea7-a0094188d0fe.PNG)


##For a tutorial video, check this out:
https://www.youtube.com/watch?v=gibqiFtBARY&t=8s
