#include<graphics.h> //图形库
#include<stdio.h>
#include<time.h>  //时间种子
#include<stdlib.h> //产生随机数
#include<conio.h> //按键
#include"mmsystem.h" // 媒体接口
#pragma comment(lib,"Winmm.lib") 

int width = 902;  //宽度
int hight = 602;  //高度
int game = 1;     //游戏进度
int size = 1;     //蛇等级
int east = 0;
double time_ = 0; //生存指数
     //生存指数转码
char direct = 'a';//方向指令
char k = 'a';     //直行指令
double speed = 100;//行进速度
int apple_flag = 0;//果实刷新指令
int poison_flag = 0;//毒苹果生成
double score = 100;     //总分
double score1 = 0;
int biggest = 0;
int kii = 0;
char s1[] = "■";  //围墙
char s2[] = "□";  //蛇身体

struct snake {
	int x ;
	int y ;
}snake[60 * 40];
struct apple {
	int x;
	int y;
}apple;
struct poison {
	int x;
	int y;
}poison;
 
void BGM();
void snake1();
void MAP();
void initsnake();
void apple1();
void act();
void over_well();
void over_apple();
void body();
void re_MAP();
void eat_body();
void go_direct();
void rainbow(int i);
void east1();
void rank_();
void toxic();
void score_();

int main()
{
	int choose = 1;
	printf("helle欢迎来到脚骚倾情制作游戏平台\n");
	printf("由于技术原因，现只支持贪吃蛇\n");
	rank_();
	do {
		
		printf("【1】贪吃蛇游戏 [最高记录：%d级]\n",biggest);
		printf("【0】退出");
		scanf_s("%d", &choose);
		switch (choose) {
		case 1:snake1(); break;
		default:break;
		}
		printf("\n【1】继续");
		printf("\n【0】打不了打不了");
		int n = getch();
		scanf_s("%d", &choose);
		if (choose != 1) {
			break;
		}
	
	} while (1);
	
	int n = _getch(); 
	
	return 0;
}
//游戏音乐
void BGM() //游戏音乐
{
	mciSendString("open Schnappi.mp3 alias song", NULL, 0, NULL);
	mciSendString("open 硬币.mp3", 0, 0, 0);
	mciSendString("open 时钟.mp3", 0, 0, 0);
	mciSendString("play song repeat", NULL, 0, NULL);
}
//贪吃蛇游戏
void snake1()
{
	printf("\n教程");
	printf("\n【w】上，【s】下，【a】左，【d】右");
	printf("\n【j】加速，【k】减速,【q】自爆");
	printf("\n温馨提示：首次开始贪吃蛇游戏后须按shifi解封键盘\n吃到白色果实会扣25金币但也会增加长度");
	printf("\n速度快得金币越多，速度太慢会扣金币！\n果实有概率隐身一段时间\n按Enter开始游戏\n\n");
	int n = getch();
	do {
		initgraph(width, hight, EW_NOCLOSE | EW_NOMINIMIZE);
		setbkcolor(RGB(3, 22, 52));
		cleardevice();
		BGM();
		//打印地图
		MAP();
		//初始化蛇位置
		initsnake();
		if (east == 1) {
			east = 0;
			game = 1;
			speed = 200;
			
		}
		else {
			game = 1;
			size = 1;
			score = 0;
			score1 = 0;
			speed = 100;
			time_ = 0;
		}
		do {
			//初始化果实
			apple1();
			Sleep(speed);
			//运行
			act();
			//地图修复
			re_MAP();
			//撞墙检测
			over_well();
			//咬自己检测
			eat_body();
			//吃苹果检测
			toxic();
			over_apple();
			//结算窗口
			score_();

		} while (game == 1);
		mciSendString("open 男惨叫.mp3", 0, 0, 0);
		mciSendString("play 男惨叫.mp3 wait", 0, 0, 0);
		mciSendString("close 男惨叫.mp3", 0, 0, 0);
		closegraph();
		if (game == 0) {
			printf("\n恭喜您！撞墙而亡");
		}
		else if (game == 2) {
			printf("\n恭喜您！自尽而亡");
		}
		else if (game == 3) {
			printf("成功自爆");
		}
		printf("\n\n生存指数%.3f\n等级%d\n金币%.3f\n\n最大等级%d\n\n", time_, size, score + score1,biggest);
	    
		east1();
		rank_();
	} while (east != 0);
	
}
//打印地图
void MAP()
{
	int i, j;
	settextcolor(RGB(254, 67, 101));
	for (i = 1; i <= width - 16; i += 15) {
		for (j = 1; j <= hight - 16; j += 15){
			if(i == 1 || i == width - 16 || j == 31|| j == hight - 16 || j == 1) {            //实际活动上：48 下：hight - 16左：17右：width - 17
				outtextxy(i, j, s1);
			}
		}
	}
	
	re_MAP();
	
}
//初始化蛇位置
void initsnake()
{
	snake[0].x = width / 2;
	snake[0].y = hight / 2;
	settextcolor(RGB(232, 221, 203));
	outtextxy(snake[0].x, snake[0].y, s1);
}
//初始化果实
void apple1()
{
	
	if (apple_flag == 0) {
		srand(time(NULL));
		settextcolor(RGB(3,22,52));
		outtextxy(apple.x, apple.y, s1);
		apple.x =( rand() % 7 * 100 + rand() % 16 * 10 + rand() % 10  + rand() % 10)  + 16;
		apple.y = rand() % 4 * 100 + rand() % 13 * 10 + rand() % 9  + 47;
		rainbow(size);
		outtextxy(apple.x, apple.y, s1);
		apple_flag = 1;
	}else {
		kii++;
		if (kii == 200) {
			apple_flag = 0;
			kii = 0;
		}
	}
	if (apple.y <= 45 || apple.y >= hight - 16 || apple.x >= width - 15 || apple.x <= 16) {
		apple_flag = 0;
	}
}
//运行
void act()
{
	
	
	settextcolor(RGB(3,22,52));
	outtextxy(snake[0].x, snake[0].y, s1);
	body();
	if (_kbhit()) {
		direct = _getch();
		if (direct == 'a' && k != 'd' || direct == 'd' && k != 'a' || direct == 'w' && k != 's' || direct == 's' && k != 'w' ) {
			k = direct;
		}
		else if (direct == 'j'&& speed > 0) {
			speed -= 20;
			direct = k; 
			if (speed < 100) {
				mciSendString("close 时钟.mp3", 0, 0, 0);
				mciSendString("open 时钟.mp3", 0, 0, 0);
				mciSendString("play 时钟.mp3", 0, 0, 0);
			}
		}
		else if (direct == 'k'&& speed <= 500) {
			speed += 20;
			direct = k;
			
		}
		else if (direct == 'q') {
			game = 3;
			direct = k;
		}
		else {
			direct = k;
		}
	}
	go_direct();
	
	settextcolor(RGB(255, 0, 0));
	outtextxy(snake[0].x, snake[0].y, s1);
}
//撞墙检测
void over_well()
{
	if (snake[0].x <= 15 ){
		game = 0;
	}
	else if (snake[0].x >= width - 17) {
		game = 0;
	}
	else if (snake[0].y <= 45) {
		game = 0;
	}
	else if (snake[0].y >= hight - 30) {
		game = 0;
	}
}
//吃苹果检测
void over_apple()
{
	static int sum = 0;
	sum = speed + sum;
	if (sum > 2000) {
		mciSendString("close 硬币.mp3", 0, 0, 0);
		sum = 0;
	}
	if (snake[0].x > apple.x - 10 && snake[0].x < apple.x + 10 && snake[0].y < apple.y + 10 && snake[0].y > apple.y - 10 ) {
		settextcolor(RGB(3,22,52));
		outtextxy(apple.x, apple.y, s1);
		apple_flag = 0;
		mciSendString("open 硬币.mp3", 0, 0, 0);
		mciSendString("play 硬币.mp3 ", 0, 0, 0);
		
		size++;
	}
}
//蛇身体
void body()
{
	int i;
	if (size > 1) {
		settextcolor(RGB(3,22,52));
		outtextxy(snake[size - 1].x, snake[size - 1].y, s1);
		for (i = size - 1; i >= 1; i--) {
			snake[i].x = snake[i - 1].x;
			snake[i].y = snake[i - 1].y;	
			rainbow(i);
			if (((i + 1) / 7 + 2 )% 2 == 0) {
				outtextxy(snake[i].x, snake[i].y, s1);
			}
			else {
				outtextxy(snake[i].x, snake[i].y, s2);
			}
		}
	}
}
//修复地图
void re_MAP()
{
	settextcolor(RGB(254, 67, 101));
	rectangle(16, 47, width - 15, hight - 15);
	rectangle(0, 30, width - 1, hight - 1);
	rectangle(16, 16, width - 15, 31);
	outtextxy(1, 1, s1);
}
//咬自己检测
void eat_body()
{
	int i;
	for (i = 2; i < size; i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			game = 2;
		}
	}
}
//直行函数
void go_direct()
{
	direct = k;
	switch (direct) {
	case 'a': snake[0].x = snake[0].x - 15; break;
	case 'd': snake[0].x = snake[0].x + 15; break;
	case 'w': snake[0].y = snake[0].y - 15; break;
	case 's': snake[0].y = snake[0].y + 15; break;
	}
}
//彩虹果实
void rainbow(int i)
{
	switch (i % 7) {
	case 0:settextcolor(RGB(255, 0, 0)); break;
	case 1:settextcolor(RGB(255, 165, 0)); break; 
	case 2:settextcolor(RGB(255, 255, 0)); break; 
	case 3:settextcolor(RGB(0, 255, 0)); break;
	case 4:settextcolor(RGB(0, 255, 255)); break;
	case 5:settextcolor(RGB(0, 0, 255)); break;
	case 6:settextcolor(RGB(139, 0, 255)); break;
	}
}
//分数面板
void score_()
{
	char tim[6];
	time_ = time_ + 0.258 - speed / 500;
	score = time_ + (size - 1) * (5 - speed / 100.0);

	outtextxy(20, 15, "生存指数：");
	outtextxy(180, 15, "等级：");
	outtextxy(340, 15, "金币：");
	outtextxy(480, 15, "速度：      节");

	settextcolor(RGB(255, 255, 255));
	sprintf(tim, "%.3f", time_);
	outtextxy(100, 15, tim);

	sprintf(tim, "%d", size);
	outtextxy(260, 15, tim);

	sprintf(tim, "%.3f", score + score1);
	outtextxy(410, 15, tim);
	
	int k;
	k = (50 - (speed / 10)) * 2;
    sprintf(tim, "%d", k);
	outtextxy(520, 15, tim);
}
void toxic() {
	
	srand(time(NULL) + 1);
	if (rand() % 20 == 1) {
		poison_flag = 0;
	}
	if (size >= 5 && poison_flag == 0) {
		
		settextcolor(RGB(3, 22, 52));
		outtextxy(poison.x, poison.y, s1);
		poison.x = (rand() % 7 * 100 + rand() % 16 * 10 + rand() % 10 + rand() % 10) + 16;
		poison.y = rand() % 4 * 100 + rand() % 13 * 10 + rand() % 9 + 47;
		settextcolor(WHITE);
		outtextxy(poison.x, poison.y, s1);
		poison_flag = 1;
		
	}
	if (snake[0].x > poison.x - 10 && snake[0].x < poison.x + 10 && snake[0].y < poison.y + 10 && snake[0].y > poison.y - 10) {
		settextcolor(RGB(3, 22, 52));
		settextcolor(RGB(3, 22, 52));
		outtextxy(poison.x, poison.y, s1);
		poison_flag = 0;
		size++;
		mciSendString("open 硬币.mp3", 0, 0, 0);
		mciSendString("play 硬币.mp3 ", 0, 0, 0);
		score1 -=50;
	}
	

}
void east1()
{
	int chose = 0;
	if (score > 0) {
		printf("\n消耗200金币可复活");
		printf("\n【1】还有什么好说的直接复活");
		printf("\n【2】算了算了，没分");
		scanf_s("%d", &chose);
		int n = getch();
	}
	if (chose == 1){
		if (score + score1 < 200){
			printf("菜狗，不够金币复活个屁");
		}
		else {
			east = 1;
			score1 = score1 - 200;
		}
	}
}
void rank_()
{
	FILE* fp;
	if ((fp = fopen("rank-jiaosao.txt", "r")) == NULL) {
		printf("\n警告 不要乱删东西");
		if ((fp = fopen("rank-jiaosao.txt", "w")) == NULL) {
			printf("\n 创建文件夹历史失败,请主动寻求脚骚帮助");
		}
	}
	if (fp) {
		fscanf_s(fp, "%d", &biggest);
		if (fclose(fp)) {
			printf("\n警告 关闭历史失败bug,请主动寻求脚骚帮助");
			exit(0);
		}
	}
	if((fp = fopen("rank-jiaosao.txt", "w")) == NULL) {
		printf("\n警告 查询或写入历史失败bug,请主动寻求脚骚帮助");
		exit(0);
	}
	if (size > biggest) {
		fprintf(fp, "%d", size);
	}else {
		fprintf(fp, "%d", biggest);
	}
	if (fclose(fp)) {
		printf("\n警告 关闭历史失败bug,请主动寻求脚骚帮助");
		exit(0);
	}
}