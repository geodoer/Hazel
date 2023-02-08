OpenGL只是一个标准，而其具体实现是由显卡厂商完成的。因此，在使用OpenGL函数之前，我们需要从显卡驱动中获得具体的函数指针。而这个工作，可以交给Glad第三方库来完成。

GLEW也可以完成同样的工作，虽然GLEW更容易配置，但GLAD更加现代。


glad下载地址：https://glad.dav1d.de