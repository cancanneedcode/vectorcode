# vectorcode
please use Visual Studio 2022
如果用Dev++可能存在中文编码问题，导致中文乱码
文件分为vector和homework两个文件夹，前者存储了vector.h和vector_fun.h文件定义了vector的模板类，后者存储了complex.h和main.cpp文件，complex定义了复数类和相关函数
在main.cpp中主要进行了以下操作：

1.随机生成无序向量并进行置乱，查找，插入，删除，唯一化的操作

2.以复数的模进行乱序、顺序、逆序下的起泡排序和归并排序的效率

3.在顺序向量中查找区间为[m1,m2)的所有元素，并返回子向量中

在进行查找，排序等操作时由于定义的complex类的数据类型与vector.h中的vector的数据类型不同，故在查找、排序等函数中添加了bool函数来判断大小关系
