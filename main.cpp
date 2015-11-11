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
struct snake//�ߵı���
{
    int x;
    int y;
    int direction;

} snake[150];

int n=3;//�����ߵĳ�ʼ����
int life=1;//�����ߵ�����
int hscore;//��߷ּ�¼
char hscorename[20];//��¼����Ϸ��

struct food//ʳ��
{
    int x;
    int y;
} food;

#include <math.h>//���ģ��
#define myrand(m) ((float)(randomf() * m ))
#define MAXOBJ 20
typedef struct//���ṹ��
{
    float x, y;
    float vx, vy;
    int color;
} Point;




void snakeup()//�ߵ��ƶ�
{
    for(int i=n-1; i>0; i--)
    {
        snake[i].x=snake[i-1].x;
        snake[i].y=snake[i-1].y;
    }
}

void drawsnake()//����
{
    setfillcolor(LIGHTGREEN);
    for(int i=0; i<n; i++)
    {
        bar(snake[i].x,snake[i].y,snake[i].x+10,snake[i].y+10);
        setfillcolor(GREEN);
        rectangle(snake[i].x,snake[i].y,snake[i].x+10,snake[i].y+10);

    }
}

void lastdied()//������β
{
    int i=n-1;
    setfillcolor(BLACK);
    bar(snake[i].x,snake[i].y,snake[i].x+10,snake[i].y+10);
}

void key()//���̿���
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




#define MAP_W 63//��Ϸ���򳤿��ʮ��֮һ
#define MAP_H 47
void snakefood()//�ߵ�ʳ��   ʳ�ﲻ��~
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
            food.x=a*10;//�������ʳ������
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
void sshit()//��������ײ
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

void board()//�߽�
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

void fireworks()//�Ƽ�¼���ģ��
{
    //initgraph(640, 480);
    randomize(); //��ʼ���������

    class AniObj
    {
    public:
        //��ʼ������������
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

        //����λ�õ��������
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

        //��������ֵ�滭11
        void drawobj()
        {
            for (int i = 0; i < n; i++)
            {
                putpixel(p[i].x, p[i].y, color);
            }
        }

        //�ͷ��������ʱ����
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

    AniObj obj[MAXOBJ]; //�����������
    int n;

    setrendermode(RENDER_MANUAL);
    for ( ; kbhit() == 0; delay_fps(60) )
    {
        for (n = 0; n < MAXOBJ; ++n)
        {
            obj[n].updateobj(); //����λ��
        }


        imagefilter_blurring(NULL, 0x4F, 0x100);
        for (n = 0; n < MAXOBJ; ++n)
        {
            obj[n].drawobj(); //�滭

            setfont(72,0,"����");
            setbkmode(TRANSPARENT,NULL);
            //setfontbkcolor(BLACK,NULL);
            xyprintf(170,180,"���������");
        }
    }

}

void scoreboard()
{
    //�Ҳ������
    {
        setfont(16,0,"����");
        setfontbkcolor(BLACK,NULL);
        xyprintf(650,30,"��ǰ����");//��ǰ����
        xyprintf(650,50,"      %d",n-3);
        setcolor(YELLOW);//��ͼǰ��ɫ
        rectangle(645,20,715,70);//���α߿�

        xyprintf(650,90,"��ǰ�ٶ�");//sudu
        xyprintf(650,110,"     %d",125-SPEED);
        rectangle(645,80,715,130);//���α߿�

        xyprintf(650,150," ��߷�");//��߷���
        xyprintf(650,170,"     %d",hscore);
        rectangle(645,140,715,250);//���α߿�

        xyprintf(650,210," ��¼��");//��¼������
        //xyprintf(650,170," ������");
        setfont(14,0,"����");
        xyprintf(650,230,"  %s",hscorename);
    }

    //��ʾfps
    {
        char str[60];
        xyprintf(650,440,"FPS");
        sprintf( str, "%.2f", getfps());
        outtextxy( 650, 460, str );
    }
}

int main ()
{
    //�ɼ���¼��ʼ��
    setinitmode(0);//���ο���
    FILE *fp;//���ļ�������߼�¼
    if((fp=fopen("jilu.txt","r"))==NULL)
        hscore=0;
    else
    {
        fgets(hscorename,20,fp);
        fscanf(fp,"%d",&hscore);
    }
    fclose (fp);


    //��ʼ��ͼ��
    {
        setcaption("̰����");
        initgraph(720,480);//��һ����700���أ���480���صĴ���
    }

    //��ʼ����
    {

        {
            PIMAGE img=newimage();
            getimage(img,"snake.jpg",0,0);
            putimage(0,              // ����λ�õ� x ����
                     0,              // ����λ�õ� y ����
                     720,          // ���ƵĿ��
                     480,         // ���Ƶĸ߶�
                     img,        // Ҫ���Ƶ� IMAGE ����ָ��
                     0,              // ���������� IMAGE �����е����Ͻ� x ����
                     0,              // ���������� IMAGE �����е����Ͻ� y ����
                     320,          // ����������Դ IMAGE �����еĿ��
                     240,         // ����������Դ IMAGE �����еĸ߶�
                     SRCCOPY  // ��Ԫ��դ�����루�����ע��
                    );
            delimage(img);
        }
        Sleep(1000);


        setfont(20,10,"����",0,0,600,false,false,false,NULL);
        setfontbkcolor(WHITE,NULL);
        outtextxy(150,400,"���á�,��,��,�������Ʒ��򣬰��������ʼ��Ϸ");
        outtextxy(250,420,"��Ϸ�пո����ͣ��Ϸ");

        PlaySound("the Blue.wav", NULL, SND_FILENAME | SND_ASYNC);//��Ϸ����

        getch();
        cleardevice();//����
    }

    //��Ϸ�����ʼ��
    {
        setfillcolor(YELLOW);//���Ʊ߽�
        bar(0,0,640,480);
        setfillcolor(BLACK);//�����м��ɫ
        bar(10,10,630,470);
        setfillcolor(BLACK);//�����Ҳ������
        bar(640,0,720,480);
        //randomize();

        //��ʼ���ߵ���Ϣ
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
    snakefood();//��ʳ��

    while(1)
    {

        setfillcolor(YELLOW);//bug����,������
        bar(0,0,10,10);



        scoreboard();//�Ʒְ�
        randomize();
        drawsnake();//����
        Sleep(SPEED);//�ߵ��ƶ��ٶ�
        lastdied();//����β
        snakeup();//���ƶ�
        //setfillcolor(GREEN);
        key();//���̿���

        //����ʵ����ͣ
        if(snake[0].direction==0x20)
        {
            //snake[0].direction=NULL;
            continue;
        }

        board();//�߽���ײ
        sshit();//������ײ

        if((snake[0].x==food.x)&&(snake[0].y==food.y))//���߻����ˣ��ú��ػ�
        {
            setfillcolor(BLACK);
            bar(food.x,food.y,food.x+10,food.y+10);
            snakefood();
            n++;

            if((n-3)%10==0&&SPEED>25)//����ģ��
            {
                SPEED=SPEED-25;
            }
        }


        if(life==0)//������
        {
            setfont(76,0,"����");
            setfontbkcolor(BLACK,NULL);
            xyprintf(150,180,"Game Over");
            Sleep(1000);
            break;//��ת����Ϸ����
        }


    }

    if (n-3>hscore)//�Ƽ�¼�ļ��洢���ʵ�
    {
        {
            fireworks();//��װ�̻�����
        }
        inputbox_getline("��ϲ�����Ƽ�¼�ˣ�","����������߼�¼!\n�������Ĵ����ɣ�\n���س�ȷ������",hscorename,20);
        fp=fopen("jilu.txt","w");
        fprintf(fp,"%s\n%d",hscorename,n-3);
        fclose (fp);
    }
    Sleep(1500);

    getch();//��ͣ
    //cleardevice();
    closegraph();//�رմ���
    return 0;

}

