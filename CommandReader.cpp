#include <thread>

class CommandReader {

public:
    static void run(Draw *draw) {
        
        std::thread mCommandReader(&CommandReader::whatKey, draw);
        mCommandReader.detach();
        
    }

    static void whatKey(Draw *draw) {
        printf("[Thread/KeyboardReader] Started~\n\r");
        int ch=0;
        while (ch = getchar()) {
          if (ch=='\n') continue;
          printf("You Pressed key = %c(%d)\n\r", ch, ch);
          if (ch=='w') draw->moveUp();
          if (ch=='s') draw->moveDown();
          if (ch=='a') draw->moveLeft();
          if (ch=='d') draw->moveRight();
          if (ch==3) {
              draw->shutdown();
              printf("[Thread/KeyboardReader] Bye~\n\r");
              system("stty -raw echo -F /dev/tty");
              exit(0);
          }
          delay(100);
        }
    }
    //弃用
    static int readByte() {
        fd_set rfds;
        struct timeval tv;
        int ch=0;
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 5;//设置等待超时时间
        //检测键盘是否有输入
        if (select(1, &rfds, NULL, NULL, &tv) > 0)
        {
            //system("stty -echo");
            //c=getchar();
            ch = getchar();
            //system("stty echo");
            printf("You Pressed key = %c(%d)\n\r", ch, ch);
        }
        //return ch;
    }

    static void hello() {
        for (int i=0;i<10;i++) {
            printf("[%d]Hello, I am CommandReader~\n\r",i);
            delay(3000);
        }
        printf("[Thread/CommandReader] Bye~\n\r");
    }
};
