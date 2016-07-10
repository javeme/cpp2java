本程序功能是将c++源码转换为java源码,转好代码将全部放在目标目录下的java文件夹中.
我的主要目的是方便一些算法的迁移,当然也希望能出一个java源码转成c++的,这是求之不得的事,虽然有点复杂,就等待大家的智慧了.
这个软件也只是做了一些基本的直译,很多类还是需要自己手动转换,毕竟方法名称都不大一样,
比如vector转换成ArrayList,同样添加元素前者是push_back,而后者是add,此外有一点特别注意的地方,c++的string截取字串方法substr(strat,offset)和java的String方法substring(start,end)有很大差别,我就调试了好久才发现.
有什么好的方法来改进程序,希望联系本人javaloveme@gmail.com.
