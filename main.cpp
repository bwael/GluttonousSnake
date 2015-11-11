//#define SHOW_CONSOLE
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <fps.h>
#define UP 294
#define DOWN 296
#define RIGHT 295
#define LEFT 293
//#define PAUSE 32
//#define SPEED 50


int SPEED=100;//100ms=25,75ms=50,50ms=75,25ms=100
struct snake//蛇的本体
{
    int x;
    int y;
    int direction;

} snake[150];

int n=3;//定义蛇的初始长度
int life=1;//定义蛇的生命
int hscore;//最高分记录
char hscorename[20];//记录者游戏名

struct food//食物
{
    int x;
    int y;
} food;

#include <math.h>//焰火模块
#define myrand(m) ((float)(randomf() * m ))
#define MAXOBJ 20
typedef struct//焰火结构体
{
    float x, y;
    float vx, vy;
    int color;
} Point;




void snakeup()//蛇的移动
{
    for(int i=n-1; i>0; i--)
    {
        snake[i].x=snake[i-1].x;
        snake[i].y=snake[i-1].y;
    }
}

void drawsnake()//画蛇
{
    setfillcolor(LIGHTGREEN);
    for(int i=0; i<n; i++)
    {
        bar(snake[i].x,snake[i].y,snake[i].x+10,snake[i].y+10);
        setfillcolor(GREEN);
        rectangle(snake[i].x,snake[i].y,snake[i].x+10,snake[i].y+10);

    }
}

void lastdied()//擦除蛇尾
{
    int i=n-1;
    setfillcolor(BLACK);
    bar(snake[i].x,snake[i].y,snake[i].x+10,snake[i].y+10);
}

void key()//键盘控制
{
    if(kbhit())
    {
        int ch=getch();
        if((snake[0].direction-ch)!=2&&(snake[0].direction-ch)!=-2)
            snake[0].direction=ch;
    }
    switch(snake[0].direction)
    {

    case UP:
    {
        snake[0].y-=10;
        break;
    }
    case DOWN:
    {
        snake[0].y+=10;
        break;
    }
    case RIGHT:
    {
        snake[0].x+=10;
        break;
    }
    case LEFT:
    {
        snake[0].x-=10;
        break;
    }
        //default:
        // break;
    }

}




#define MAP_W 63//游戏区域长宽的十分之一
#define MAP_H 47
void snakefood()//蛇的食物   食物不能~
{
    setfillcolor(WHITE);
    //randomize();
    //for(int j=0;;j++)
A :
    int a=random(MAP_W),c=random(MAP_H);
    int flag=0;
    for(int i=0; i<n; i++)
    {
        if(((a*10)!=snake[i].x)&&((c*10)!=snake[i].y)&&((c>=2)&&(a>=1))/*&&(((a<=62)&&(a>=1))&&((c<=46)&&(c>=1)))*/)
        {
            food.x=a*10;//随机产生食物坐标
            food.y=c*10;
            flag++;
            if(flag==n)
            {
                bar(food.x,food.y,food.x+10,food.y+10);
                flag=0;
            }
        }
        else
            goto A;


    }
}
void sshit()//蛇自身相撞
{


    for(int i=1; i<=n; i++)
    {
        if((snake[0].x==snake[i].x)&&(snake[0].y==snake[i].y))
        {

            life--;
            getch();
        }
    }

}

void board()//边界
{

    if(snake[0].x==630)//OK
    {
        life--;
    }
    else if(snake[0].y==470)//OK
    {
        life--;
    }
    else if(snake[0].x==0)//OK
    {
        life--;
    }
    else if(snake[0].y==0)//OK
    {
        life--;
    }

}

void fireworks()//破纪录焰火模块
{
    //initgraph(640, 480);
    randomize(); //初始化随机种子

    class AniObj
    {
    public:
        //初始化，设置坐标
        AniObj()
        {
            Init();
        }

        void Init()
        {
            n = 100;
            float x = myrand(600.0f) + 20.0f;
            float y = myrand(100.0f) + 100.0f;
            for (int i = 0; i < n; i++)
            {
                p[i].x = x;
                p[i].y = y;
                p[i].vx = 1.0f - myrand(2.0f);
                p[i].vy = 1.0f - myrand(2.0f);
                p[i].color = HSVtoRGB(myrand(360.0f), 1.0f, 1.0f);
            }
            color = HSVtoRGB(myrand(360.0f), 1.0f, 1.0f);
            start = rand() % 300;
            cnt = 0;
        }

        //更新位置等相关属性
        void updateobj()
        {
            if (cnt++ > start)
                for (int i = 0; i < n; i++)
                {
                    p[i].vy += 0.01f;
                    p[i].x += p[i].vx;
                    p[i].y += p[i].vy;
                }
            if (cnt > start + 400) Init();
        }

        //根据属性值绘画11
        void drawobj()
        {
            for (int i = 0; i < n; i++)
            {
                putpixel(p[i].x, p[i].y, color);
            }
        }

        //释放这个对象时调用
        ~AniObj()
        {
        }

    private:
        Point p[100];
        int n;
        int color;
        int start;
        int cnt;
    };

    AniObj obj[MAXOBJ]; //定义对象数组
    int n;

    setrendermode(RENDER_MANUAL);
    for ( ; kbhit() == 0; delay_fps(60) )
    {
        for (n = 0; n < MAXOBJ; ++n)
        {
            obj[n].updateobj(); //更新位置
        }


        imagefilter_blurring(NULL, 0x4F, 0x100);
        for (n = 0; n < MAXOBJ; ++n)
        {
            obj[n].drawobj(); //绘画

            setfont(72,0,"宋体");
            setbkmode(TRANSPARENT,NULL);
            //setfontbkcolor(BLACK,NULL);
            xyprintf(170,180,"任意键继续");
        }
    }

}

void scoreboard()
{
    //右侧积分器
    {
        setfont(16,0,"黑体");
        setfontbkcolor(BLACK,NULL);
        xyprintf(650,30,"当前分数");//当前分数
        xyprintf(650,50,"      %d",n-3);
        setcolor(YELLOW);//绘图前景色
        rectangle(645,20,715,70);//矩形边框

        xyprintf(650,90,"当前速度");//sudu
        xyprintf(650,110,"     %d",125-SPEED);
        rectangle(645,80,715,130);//矩形边框

        xyprintf(650,150," 最高分");//最高分数
        xyprintf(650,170,"     %d",hscore);
        rectangle(645,140,715,250);//矩形边框

        xyprintf(650,210," 纪录者");//纪录保持者
        //xyprintf(650,170," 保持者");
        setfont(14,0,"黑体");
        xyprintf(650,230,"  %s",hscorename);
    }

    //显示fps
    {
        char str[60];
        xyprintf(650,440,"FPS");
        sprintf( str, "%.2f", getfps());
        outtextxy( 650, 460, str );
    }
}

int main ()
{
    //成绩记录初始化
    setinitmode(0);//屏蔽开场
    FILE *fp;//从文件载入最高记录
    if((fp=fopen("jilu.txt","r"))==NULL)
        hscore=0;
    else
    {
        fgets(hscorename,20,fp);
        fscanf(fp,"%d",&hscore);
    }
    fclose (fp);


    //初始化图形
    {
        setcaption("贪吃蛇");
        initgraph(720,480);//打开一个长700像素，宽480像素的窗口
    }

    //开始界面
    {

        {
            PIMAGE img=newimage();
            getimage(img,"snake.jpg",0,0);
            putimage(0,              // 绘制位置的 x 坐标
                     0,              // 绘制位置的 y 坐标
                     720,          // 绘制的宽度
                     480,         // 绘制的高度
                     img,        // 要绘制的 IMAGE 对象指针
                     0,              // 绘制内容在 IMAGE 对象中的左上角 x 坐标
                     0,              // 绘制内容在 IMAGE 对象中的左上角 y 坐标
                     320,          // 绘制内容在源 IMAGE 对象中的宽度
                     240,         // 绘制内容在源 IMAGE 对象中的高度
                     SRCCOPY  // 三元光栅操作码（详见备注）
                    );
            delimage(img);
        }
        Sleep(1000);


        setfont(20,10,"黑体",0,0,600,false,false,false,NULL);
        setfontbkcolor(WHITE,NULL);
        outtextxy(150,400,"请用↑,↓,←,→来控制方向，按任意键开始游戏");
        outtextxy(250,420,"游戏中空格键暂停游戏");

        PlaySound("the Blue.wav", NULL, SND_FILENAME | SND_ASYNC);//游戏音乐

        getch();
        cleardevice();//清屏
    }

    //游戏界面初始化
    {
        setfillcolor(YELLOW);//绘制边界
        bar(0,0,640,480);
        setfillcolor(BLACK);//绘制中间黑色
        bar(10,10,630,470);
        setfillcolor(BLACK);//绘制右侧积分器
        bar(640,0,720,480);
        //randomize();

        //初始化蛇的信息
        snake[0].x=30;
        snake[0].y=10;
        snake[0].direction=RIGHT;
        snake[1].x=20;
        snake[1].y=10;
        snake[1].direction=RIGHT;
        snake[2].x=10;
        snake[2].y=10;
        snake[2].direction=RIGHT;
    }
    snakefood();//画食物

    while(1)
    {

        setfillcolor(YELLOW);//bug补丁,不完善
        bar(0,0,10,10);



        scoreboard();//计分板
        randomize();
        drawsnake();//画蛇
        Sleep(SPEED);//蛇的移动速度
        lastdied();//擦蛇尾
        snakeup();//蛇移动
        //setfillcolor(GREEN);
        key();//键盘控制

        //用于实现暂停
        if(snake[0].direction==0x20)
        {
            //snake[0].direction=NULL;
            continue;
        }

        board();//边界相撞
        sshit();//蛇身相撞

        if((snake[0].x==food.x)&&(snake[0].y==food.y))//和蛇画重了，置黑重画
        {
            setfillcolor(BLACK);
            bar(food.x,food.y,food.x+10,food.y+10);
            snakefood();
            n++;

            if((n-3)%10==0&&SPEED>25)//加速模块
            {
                SPEED=SPEED-25;
            }
        }


        if(life==0)//蛇死亡
        {
            setfont(76,0,"宋体");
            setfontbkcolor(BLACK,NULL);
            xyprintf(150,180,"Game Over");
            Sleep(1000);
            break;//跳转到游戏结束
        }


    }

    if (n-3>hscore)//破纪录文件存储及彩蛋
    {
        {
            fireworks();//封装烟花函数
        }
        inputbox_getline("恭喜！打破纪录了！","您打破了最高记录!\n留下您的大名吧！\n按回车确认输入",hscorename,20);
        fp=fopen("jilu.txt","w");
        fprintf(fp,"%s\n%d",hscorename,n-3);
        fclose (fp);
    }
    Sleep(1500);

    getch();//暂停
    //cleardevice();
    closegraph();//关闭窗口
    return 0;

}

