

class CommandReader {
public:
    static int readByte() {
        fd_set rfds;
        struct timeval tv;
        int ch = 0;
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 5;//设置等待超时时间
        //检测键盘是否有输入
        if (select(1, &rfds, NULL, NULL, &tv) > 0)
        {
            ch = getchar();
            printf("You Pressed key = %c(%d)\n\r", ch, ch);
        }
        return ch;
    }
};