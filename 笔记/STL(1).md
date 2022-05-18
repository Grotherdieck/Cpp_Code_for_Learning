# 一、什么是STL

&emsp;&emsp;STL(standard template libaray-标准模板库)：是C++标准库的重要组成部分，不仅是一个可复用的组件库，而且 是一个包罗数据结构与算法的软件框架。

# 二、STL的版本

- 原始版本 Alexander Stepanov、Meng Lee (开发UNIX的大佬)在惠普实验室完成的原始版本，本着开源精神，他们声明允许任何人任意 运用、拷贝、修改、传播、商业使用这些代码，无需付费。唯一的条件就是也需要向原始版本一样做开源使 用。 HP 版本--所有STL实现版本的始祖。 

- P. J. 版本 由P. J. Plauger开发，继承自HP版本，被**Windows Visual C++**采用，不能公开或修改，缺陷：可读性比较低， 符号命名比较怪异。 

- RW版本 由Rouge Wage公司开发，继承自HP版本，被C+ + Builder采用(这个编译器已经寄了= =)，不能公开或修改，可读性一般。 

- SGI版本 由Silicon Graphics Computer Systems，Inc公司开发，继承自HP版 本。被**GCC(Linux)**采用，可移植性好， 可公开、修改甚至贩卖，从命名风格和编程 风格上看，阅读性非常高。**我们学习STL要阅读部分源代码， 主要参考的就是这个版本**。

# 三、STL的主要组成部分

![](https://router-picture-bed.oss-cn-chengdu.aliyuncs.com/img/img/20220219153924.png)

&emsp;&emsp;网上有句话说：“不懂STL，不要说你会C++”。STL是C++中的优秀作品，有了它，许多底层的数据结构 以及算法都不需要自己重新造轮子，站在前人的肩膀上，健步如飞的快速开发。

# 四、STL的缺陷

1. STL的更新太慢了，25年能用上C++20吗？
2. STL不支持线程安全，并发环境下需要自己加锁。
3. STL极度追求效率，导致设计比较复杂，比如类型萃取，迭代器萃取
4. STL会有代码膨胀的问题，如``vector<vector<vector<int>>>``会生成多份vector，这是模板语法本身导致的。

