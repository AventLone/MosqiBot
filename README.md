> 作者简介：
>
> 北京化工大学，陈国昊
>
> 邮箱：aventlone@outlook.com

# 昆虫信息采集系统

## 文件夹注释

- `Embedded`：下位机软件；
- `Host`：上位机软件，包括 ROS2 程序和 Qt 图形界面程序；
- `Matlab`：Matlab 脚本文件，用于计算某些参数；
- `Shell`：Shell 脚本文件；
- `test`：测试上位机软件的某些功能。

总体测试效果如下：

![test](README.assets/test.gif)




## 算法流程图

<img src="README.assets/001.svg" alt="001"  />

## Qt 用户界面



<img src="README.assets/IMG_3454.PNG" alt="IMG_3454" style="zoom: 33%;" />

<img src="README.assets/IMG_3455.PNG" alt="IMG_3455" style="zoom:33%;" />

## 景深融合

通过控制用于对焦（Focus）的微型步进电机，可以将焦平面移动到靶虫不同的身体部位。

<img src="README.assets/IMG_0540.jpeg" alt="IMG_0540" style="zoom: 33%;" />

这里由焦平面从上到下，依次拍取 3 张照片：

<img src="README.assets/001.png" alt="001" style="zoom: 33%;" />

<img src="README.assets/002.png" alt="002" style="zoom: 33%;" />

<img src="README.assets/003.png" alt="003" style="zoom: 33%;" />

景深融合结果如下：

<img src="README.assets/result.png" alt="result" style="zoom:33%;" />



## tensorRT 部署 Yolov5模型

推理效果如下

<img src="README.assets/image-20230914102737072.png" alt="image-20230914102737072" style="zoom:50%;" />





