#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 声明函数原型
void next();
void sensor(int i);
void timing();
void setLight();

// 定义一个结构体来表示灯光区域的状态
typedef struct {
	int state;       // 灯光开关状态（0关闭，1打开）
	int brightness;  // 亮度（0-100）
	int color;       // 色温（单位：K）
} LightZone;

// 初始化三个灯光区域的状态
LightZone zones[3] = {
	{0, 50, 4000},  // 书桌灯：初始状态关闭，亮度50%，色温4000K
	{0, 50, 4000},  // 顶灯：初始状态关闭，亮度50%，色温4000K
	{0, 50, 4000}   // 床头灯：初始状态关闭，亮度50%，色温4000K
};

// 当前选中的灯光区域索引
int zone = 0;

int main() {
	// 指向当前选中灯光区域的指针
	LightZone* p = &zones[zone];

	// 打印欢迎信息和当前选中的区域
	printf("\n欢迎访问宿舍灯光控制系统!\n");
	printf("-----------------------------------------------------\n");
	printf("当前选中区域：");
	if (zone == 0) {
		printf("书桌灯\n");
	}
	else if (zone == 1) {
		printf("顶灯\n");
	}
	else {
		printf("床头灯\n");
	}
	printf("切换区域(请输入0)             查看状态(请输入123)\n");
	printf("开关(请输入1)                 调整(请输入2)\n");
	printf("定时(请输入3)                 退出(请输入4)\n");
	printf("-----------------------------------------------------\n");

	// 获取用户输入
	int a;
	scanf("%d", &a);

	// 根据用户输入执行相应操作
	if (a == 0) {
		// 切换区域
		printf("\n请选择区域：0=书桌灯，1=顶灯，2=床头灯\n");
		int z;
		scanf("%d", &z);
		if (z >= 0 && z <= 2) {
			zone = z;
			printf("\n已切换到区域：");
			if (zone == 0) printf("书桌灯\n\n");
			else if (zone == 1) printf("顶灯\n\n");
			else printf("床头灯\n\n");
		}
		else {
			printf("\n输入错误！请选0-2\n\n");
		}
		main();  // 递归调用main函数重新显示菜单
	}
	else if (a == 1) {
		// 控制灯光开关
		sensor(a);
		main();  // 递归调用main函数重新显示菜单
	}
	else if (a == 2) {
		// 调整灯光属性
		int c;
		printf("\n您要调整色温(请输入2)还是亮度(请输入3)？\n\n预设模式(请输入4)\n\n");
		scanf("%d", &c);
		if (c == 2 || c == 3) {
			sensor(c);
		}
		else if (c == 4) {
			// 预设模式选择
			int m;
			printf("----------------------------------------------------------------------------------\n");
			printf("《阅读模式》：色温4000K（偏冷白）+ 亮度80%（护眼亮度）(请输入1)\n\n");
			printf("《睡前模式》：色温2700K（暖黄）+ 亮度10%（低亮度不刺眼）(请输入2)\n\n");
			printf("《娱乐模式》：色温3500K（中性光）+ 亮度60%（氛围适配）(请输入3)\n\n");
			printf("《节能模式》：亮度自动降至30%(请输入4)\n");
			printf("----------------------------------------------------------------------------------\n");
			scanf("%d", &m);
			switch (m) {
			case 1:
				p->color = 4000;
				p->brightness = 80;
				printf("\n调整成功！\n\n现在的亮度为：%d\n现在的色温为：%d\n\n", p->brightness, p->color);
				break;
			case 2:
				p->color = 2700;
				p->brightness = 10;
				printf("\n调整成功！\n\n现在的亮度为：%d\n现在的色温为：%d\n\n", p->brightness, p->color);
				break;
			case 3:
				p->color = 3500;
				p->brightness = 60;
				printf("\n调整成功！\n\n现在的亮度为：%d\n现在的色温为：%d\n\n", p->brightness, p->color);
				break;
			case 4:
				p->brightness = 30;
				printf("\n调整成功！\n\n现在的亮度为：%d\n\n", p->brightness);
				break;
			default:
				printf("\n输入错误！请选1-4\n\n");
				break;
			}
			next();  // 继续下一次操作
		}
		else {
			printf("\n请输入正确选项！\n\n");
			main();  // 递归调用main函数重新显示菜单
		}
	}
	else if (a == 3) {
		// 设置定时功能
		timing();
	}
	else if (a == 4) {
		// 退出程序
		printf("\n祝您生活愉快！\n");
		exit(EXIT_SUCCESS);  // 使用EXIT_SUCCESS表示正常退出
	}
	else if (a == 123) {
		// 查看当前灯光状态
		if (p->state == 0) {
			printf("当前灯是关着的\n\n");
		}
		else {
			printf("当前灯是开着的，色温为：%d，亮度为：%d\n\n", p->color, p->brightness);
		}
		next();  // 继续下一次操作
	}
	else {
		printf("\n请输入正确选项！\n\n");
		main();  // 递归调用main函数重新显示菜单
	}
}


void help() {
	LightZone* p_help = &zones[zone];  // 复用区域指针
	printf("---------------------------------------------\n");
	printf("这是一个宿舍灯光控制系统，我可以实现的功能有:\n");
	printf("1.开关灯光\n");
	printf("2.调整灯光的色温\n");
	printf("3.调整灯光的亮度\n");
	printf("4.定时开关灯\n");
	printf("5.提供场景灯光预设供您选择\n");
	printf("6.根据时间进行灯光智能调节\n");
	printf("7.灯光状态查询\n");
	printf("8.宿舍灯光分区管理\n");
	printf("---------------------------------------------\n");
	printf("\n您在实现哪些功能上遇到了困难？我可以帮您跳转\n\n退出帮助请输入9\n");
	int j;
	scanf("%d", &j);
	switch (j) {
	case 1:  // 开关灯光 → 调用sensor(1)
		printf("\n已为您跳转到【开关灯光】功能\n");
		sensor(1);  // 直接调用开关函数
		break;
	case 2:  // 调整色温 → 调用sensor(2)
		printf("\n已为您跳转到【调整色温】功能\n");
		sensor(2);  // 直接调用色温调整函数
		break;
	case 3:  // 调整亮度 → 调用sensor(3)
		printf("\n已为您跳转到【调整亮度】功能\n");
		sensor(3);  // 直接调用亮度调整函数
		break;
	case 4:  // 定时开关 → 调用timing()
		printf("\n已为您跳转到【定时开关灯】功能\n");
		timing();   // 直接调用定时函数
		break;
	case 5:  // 场景预设 → 模拟跳转（对应main中a=2时的c=4）
		printf("\n已为您跳转到【场景灯光预设】功能\n");
		int m;
		printf("----------------------------------------------------------------------------------\n");
		printf("《阅读模式》：色温4000K+亮度80%(请输入1)\n");
		printf("《睡前模式》：色温2700K+亮度10%(请输入2)\n");
		printf("《娱乐模式》：色温3500K+亮度60%(请输入3)\n");
		printf("《节能模式》：亮度30%(请输入4)\n");
		printf("----------------------------------------------------------------------------------\n");
		scanf("%d", &m);
		switch (m) {
		case 1: p_help->color = 4000; p_help->brightness = 80; printf("\n调整成功！当前色温：%d，亮度：%d\n", p_help->color, p_help->brightness); break;
		case 2: p_help->color = 2700; p_help->brightness = 10; printf("\n调整成功！当前色温：%d，亮度：%d\n", p_help->color, p_help->brightness); break;
		case 3: p_help->color = 3500; p_help->brightness = 60; printf("\n调整成功！当前色温：%d，亮度：%d\n", p_help->color, p_help->brightness); break;
		case 4: p_help->brightness = 30; printf("\n调整成功！当前亮度：%d\n", p_help->brightness); break;
		default: printf("\n输入错误！请选1-4\n");
		}
		next();  // 执行完场景预设后回到next选择
		break;
	case 6:  // 时间智能调节（开发中）
		printf("\n已为您跳转到【根据时间智能调节】功能\n");
		setLight();
		next();  
		break;
	case 7: 
		printf("\n已为您跳转到【灯光状态查询】功能\n");
		if (p_help->state == 0) {
			printf("当前灯是关着的\n\n");
		}
		else {
			printf("当前灯是开着的，色温为：%d，亮度为：%d\n\n", p_help->color, p_help->brightness);
		}
		next();
		break;
	case 8:  // 分区管理 → 模拟跳转（对应main中a=0）
		printf("\n已为您跳转到【宿舍灯光分区管理】功能\n");
		printf("请选择区域：0=书桌灯，1=顶灯，2=床头灯\n");
		int z_help;
		scanf("%d", &z_help);
		if (z_help >= 0 && z_help <= 2) {
			zone = z_help;
			printf("\n已切换到区域：");
			if (zone == 0) printf("书桌灯\n");
			else if (zone == 1) printf("顶灯\n");
			else printf("床头灯\n");
		}
		else {
			printf("\n输入错误！请选0-2\n");
		}
		next();  // 切换后回到选择界面
		break;
	case 9:  // 退出帮助 → 回到next
		printf("\n已退出帮助界面\n");
		next(); 
		break;
	default:
		printf("\n输入错误！请选1-9\n");
		help();  // 输入错误重新显示帮助
		break;
	}
}

void next() {
	// 打印分隔线和选项提示信息
	printf("--------------------------------------------------\n");
	printf("返回主界面(请输入1)        退出程序(请输入2)\n查看帮助(请输入3)\n");
	printf("--------------------------------------------------\n");

	int b;
	scanf("%d", &b);  // 读取用户输入的选择

	// 根据用户输入执行相应操作
	if (b == 1) {
		main();  // 返回主界面，即重新调用main函数
	}
	else if (b == 2) {
		printf("\n祝您生活愉快！\n");  // 打印告别语
		exit(EXIT_FAILURE);  // 退出程序
	}
	else if (b == 3) {
		help();  // 显示帮助信息
	}
	else {
		printf("\n请输入正确选项！\n");  // 提示用户输入错误
		next();  // 重新显示选项
	}
}

void sensor(int i) {
	LightZone* z = &zones[zone];  // 获取当前区域的灯光信息

	// 根据传入参数i执行不同操作
	if (i == 1) {
		z->state = !z->state;  // 切换灯光状态（开/关）

		// 根据新的灯光状态打印相应的消息
		if (z->state == 1) {
			printf("\n灯光开启成功!\n当前亮度：%d\n当前色温：%d\n\n", z->brightness, z->color);
			next();  // 返回主界面或其他选项
		}
		else if (z->state == 0) {
			printf("\n灯光关闭成功！\n\n");
			next();  // 返回主界面或其他选项
		}
	}

	// 调整色温
	if (i == 2 && z->state == 1) {
		printf("------------------------------------------------------------------------\n");
		printf("1850-3300：暖黄光     3300-5300：中性白光       5300-6500：冷白光\n");
		printf("------------------------------------------------------------------------\n");
		printf("\n当前色温为%d\n您要将色温调整至：\n", z->color);

		int b;
		scanf("%d", &b);  // 读取用户输入的新色温值

		// 检查输入的色温值是否在有效范围内
		if (b >= 1850 && b <= 6500) {
			z->color = b;  // 更新色温值
			printf("\n调整成功！\n\n现在的色温为：%d\n\n", z->color);
			next();  // 返回主界面或其他选项
		}
		else {
			printf("\n色温范围错误！请输入1850-6500之间的数值\n\n");
			next();  // 返回主界面或其他选项
		}
	}

	// 调整亮度
	if (i == 3 && z->state == 1) {
		printf("\n当前亮度为：%d \n您要将亮度调整至：\n", z->brightness);

		int a;
		scanf("%d", &a);  // 读取用户输入的新亮度值

		// 检查输入的亮度值是否在有效范围内
		if (a > 0 && a <= 100) {
			z->brightness = a;  // 更新亮度值
			printf("\n调整成功！\n\n现在的亮度为：%d\n\n", z->brightness);
			next();  // 返回主界面或其他选项
		}
	}

	// 如果灯光未开启且尝试调整色温或亮度，提示用户
	if (i != 1 && z->state == 0) {
		printf("\n灯光未开启！\n\n");
		next();  // 返回主界面或其他选项
	}
}

int show_time() {
	time_t now = time(NULL);
	struct tm* tm_now = localtime(&now);
	int hour = tm_now->tm_hour; // 提取当前小时（0-23）

	// 1. 保留原有功能：显示当前时间
	printf("------------------------\n");
	printf("当前时间：%02d:%02d:%02d\n", hour, tm_now->tm_min, tm_now->tm_sec);
	printf("------------------------\n");

	// 2. 新增：判断时段并返回
	if (hour >= 8 && hour < 18) {
		printf("【时段提示】当前为白天（适合学习）\n");
		return 1; // 白天时段标识
	}
	else if (hour >= 18 && hour < 23) {
		printf("【时段提示】当前为傍晚（适合娱乐）\n");
		return 2; // 傍晚时段标识
	}
	else {
		printf("【时段提示】当前为夜间（适合休息）\n");
		return 3; // 夜间时段标识
	}
}

void timing() {
	LightZone* z = &zones[zone];  // 获取当前区域的灯光信息
	show_time();  // 显示当前时间

	// 根据当前灯光状态打印不同的提示信息
	if (z->state == 0) {
		printf("当前区域灯光是关着的\n您想在多少分钟后开灯？\n\n");
	}
	else {
		printf("当前区域灯光是开着的\n您想在多少分钟后关灯？\n\n");
	}

	int t;
	scanf("%d", &t);  // 读取用户输入的时间（分钟数）

	// 检查输入的时间是否为负数
	if (t < 0) {
		printf("\n时间不能为负！\n\n");
		next();  // 返回主界面或其他选项
	}

	// 根据当前灯光状态和用户输入的时间打印确认信息
	if (z->state == 1) {
		printf("好的，将在%d分钟后为您开灯\n\n", t);
		next();  // 返回主界面或其他选项
	}
	else {
		printf("好的，将在%d分钟后为您关灯\n\n", t);
		next();  // 返回主界面或其他选项
	}
}


void setLight() {
	int time_period = show_time(); // 调用show_time，获取时段
	LightZone* s = &zones[zone];
	// 根据时段设置灯光
	switch (time_period) {
	case 1: // 白天
		s->brightness = 80;
		s->color = 4000;
		printf("已自动调节为【学习模式】：亮度80%%，色温4000K\n");
		break;
	case 2: // 傍晚
		s->brightness = 60;
		s->color = 3500;
		printf("已自动调节为【娱乐模式】：亮度60%%，色温3500K\n");
		break;
	case 3: // 夜间
		s->brightness = 20;
		s->color = 2700;
		printf("已自动调节为【睡前模式】：亮度20%%，色温2700K\n");
		break;
	}
	next();
}