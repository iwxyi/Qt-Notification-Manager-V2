Qt通知控件
===

仿Windows通知，多个通知显示，定时消失，支持出现/消失动画

和之前版本相比，使用了另一套控件：InteractiveButton，提高交互操作

另外支持卡片本身、附加三个按钮的点击事件

![picture](picture.gif)



## 部署

开发环境：Qt13.1（理论上相近版本亦可）

## 用法

初始化

```C++
TipBox* tip_box = new TipBox(this);
```

添加通知

```C++
NotificationEntry noti;
noti.key = "key";
noti.title = "title";
noti.content = "content1";
noti.btn1 = "btn1";
tip_box->createTipCard(noti);
```

