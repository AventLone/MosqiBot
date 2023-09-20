> 作者简介：
>
> 北京化工大学，陈国昊
>
> 邮箱：aventlone@outlook.com

# 昆虫信息采集系统

## 文件夹注释

<img src="README.assets/File_Tree.svg" alt="File_Tree"  />

- `Embedded`：下位机软件；
- `Host`：上位机软件，包括 ROS2 程序和 Qt 图形界面程序；
- `Matlab`：Matlab 脚本文件，用于计算某些参数；
- `Shell`：Shell 脚本文件；
- `test`：测试上位机软件的某些功能。

总体测试效果如下：

![test](README.assets/test.gif)



## 算法流程图

GitHub Light 主题下：

<img src="README.assets/001.svg" alt="001"  />

GitHub Dark 主题下：

![algorithm](README.assets/algorithm.svg)



## Qt 用户界面



<img src="README.assets/IMG_3454.PNG" alt="IMG_3454" style="zoom: 33%;" />

<img src="README.assets/IMG_3455.PNG" alt="IMG_3455" style="zoom:33%;" />

## 景深融合

通过控制用于对焦（Focus）的微型步进电机，可以将焦平面移动到靶虫不同的身体部位。

<img src="README.assets/camera.jpeg" alt="camera" style="zoom: 33%;" />

这里由焦平面从上到下，依次拍取 3 张照片：

![001](README.assets/001.jpg)

![002](README.assets/002.jpg)

![003](README.assets/003.jpg)

景深融合结果如下：

![006](README.assets/006.jpg)



## tensorRT 部署 Yolov5模型

推理效果如下

<img src="README.assets/detect.png" alt="detect" style="zoom:50%;" />





