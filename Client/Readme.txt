通信约定：
typedef struct info {
    int tag;
    int cmd;
    char buf[1024];
}INFO;

tag:传参类型
1上传
2下载
3chat
4获取图像
5点歌
6控制led
7采集温度

cmd:通信协议
每四位用来表示一个参数的状态
