#include "stdafx.h"
#include <stdlib.h>
#include "stdafx.h"

#include "stdio.h"
#include "string.h"

/*
代码大全2 第18章 直接访问表
*/

typedef struct _Person {
    int Id;
    int Age;
    char Gender;
    char SmokingStatus;
    char MatitalStatus;
    double Rate;
} Person;

#define Recoder 200
Person person[Recoder];

int getId (int num) {
    return person[num].Id;
}
void addTable (int age, char gender, char smokingstatus, char matitalstatus, double rate) {
    static id = 0;

    person[id].Id = id;
    person[id].Age = age;
    person[id].Gender = gender;
    person[id].SmokingStatus = smokingstatus;
    person[id].MatitalStatus = matitalstatus;
    person[id].Rate = rate;

    id++;
}

enum Gender {
    Gender_First = 0,
    Gender_Male = 0,
    Gender_Female = 1,
    Gender_Last = 1
};

enum MaritalStatus {
    MaritalStatus_First = 0,
    MaritalStatus_Single = 0,
    MaritalStatus_Married = 1,
    MaritalStatus_Last = 1
};

enum SmokingStatus {
    SmokingStatus_First = 0,
    SmokingStatus_Smoking = 0,
    SmokingStatus_NonSmoking = 1,
    SmokingStatus_Last = 1
};

void Table_Init () {
    //addTable(18, Gender_Male, MaritalStatus_Single, SmokingStatus_Smoking,1000);
    //addTable(50, Gender_Female, MaritalStatus_Married, SmokingStatus_NonSmoking, 500);

    addTable (18, 0, 0, 0, 1000);
    addTable (50, 1, 1, 1, 500);
    addTable (50, 1, 1, 0, 600);
    addTable (50, 0, 1, 0, 700);
}

double rateTable (int age, char gender, char smokingstatus, char matitalstatus) {
    double rate = 0;
    int id = 0;

    int i = 0;
    for (i = 0; i < Recoder; i++) {
        if (age == person[i].Age)   //年龄匹配
        {
            //printf("age = %d, gender = %d, smokingstatus = %d, matitalstatus = %d \n",age, gender, smokingstatus, matitalstatus);
            if ((gender == person[i].Gender) && (smokingstatus == person[i].SmokingStatus) && (matitalstatus == person[i].MatitalStatus)) {
                return (person[i].Rate);
            }
        }
    }
    return (-1);
}

int Find_MapTable () {
    Table_Init ();

    //printf("需要的费率 %f 块 \n",rateTable(18, 0, 0, 0));
    printf ("需要的费率 %.1f 块 \n", rateTable (50, 1, 1, 1));
    printf ("需要的费率 %.1f 块 \n", rateTable (50, 0, 1, 0));
    return 0;
}

/*
代码大全2  13.3全局数据
代码演示：
1：全局变量作为函数参数
*/

int global_variable = 3;

void global_in (int g) {
    g = 100;
    printf ("global_variable = %d \n", global_variable);
    global_variable = 6;
}

int global_test (void) {
    global_in (global_variable);
    printf ("global_variable = %d \n", global_variable);
    return 0;
}

/*
代码大全2  13.2指针
演示：
1：子函数指针传参
*/
void pointer_change_value_1 (int *ptr) {
    ptr = 2;
}
void pointer_change_value_2 (int *ptr) {
    *ptr = 3;
}
void pointer_change_value (void) {
    int a = 1;
    int *b = &a;

    pointer_change_value_1 (b); //b指向的值没变
    printf ("%d \n", *b);
    pointer_change_value_2 (b); //b指向的值被修改
    printf ("%d \n", *b);
}

/*
演示：
1：枚举类型定义
*/
enum _COLOR {
    RED = 9,
    GREEN,
    YELLOW
} COLOR;

void enum_test (void) {
    //枚举变量的值为0， 枚举内容为常量
    printf ("enum = %d,  GREEN = %d,  RED = %d \n", COLOR, GREEN, RED);
}

/*
演示：
1：结构体类型定义
*/
struct _EMPOLYEE {
    int id;
    char name[10];
    char gender;
    int salary;
} EMPOLYEE, old_empolyee, new_empolyee;

struct _EMPOLYEE empolyee;

void struct_test (void) {
    char name[] = "kevin";

    old_empolyee.id = 1;
    memcpy (old_empolyee.name, name, sizeof (name) / sizeof (char));
    old_empolyee.gender = 0;
    old_empolyee.salary = 20;

    new_empolyee = old_empolyee;

    printf ("old_empolyee.name = %s \n", old_empolyee.name);
    printf ("new_empolyee.name = %s \n", new_empolyee.name);
    printf ("new_empolyee.salary = %d \n", new_empolyee.salary);
}

/*
代码大全2 12.4节 字符与字符串
演示：
1：字符串的定义
*/
#define CONSTANT (10+1)

void string_test (void) {
    char PtrString = 'a';       //"asdf";
    char name[CONSTANT] = "abcdefghi";

    printf ("%c \n", PtrString);
    printf ("%s \n", name);

    char my_name[10];
    //strcpy(my_name,name);
    strncpy_s (my_name, sizeof (my_name) / sizeof (char), name, strlen (name));
    printf ("%s \n", my_name);
}

/*
7.5 如何使用子程序参数
 按照输入-修改-输出的顺序排列参数
创建无意义的IN  OUT关键字，弊端：
1、需要在整个项目中保持一致
2、可能与之前的IN重复
引入工作变量
*/
#define IN
#define OUT

void PrintfPageNum (IN int PageNum, OUT int status) {
    if (PageNum == 1)
        printf ("xxx");

    status = 1;
}

int Sample (int inputVal) {
    int workingVal = inputVal;  //工作变量
    /*
     * 逻辑处理代码
     */
    return workingVal;
}

/*
16.1 控制循环
将用foreach循环判断数组中的奇偶数
void foreach_test(void)
{
	int fibonacciSequence[] = { 0,1,1,2,3,5,8,13,21,34 };
	int oddFibonacciNumbers = 0;
	int evenFibonacciNumbers = 0;
	for each (int fibonacciNumber in fibonacciSequence)
	{
		if( (fibonacciNumber % 2) == 0 )
	   {
			evenFibonacciNumbers++;
	   }
		else
		{
			oddFibonacciNumbers++;
		}
  }
}
*/

/*
17.2 不要用递归去计算阶乘 或者 斐波那契数列
*/
int Fibonacci (int number) {
    int i = 0;
    int n_num = 0;

    if (number < 1)
        return -1;
    /*第1、2项固定为0、1 */
    else if (number == 1)
        return 0;
    else if (number == 2)
        return 1;
    else {
        /*第3项开始，使用通项公式 f(n) = f(n-1) + f(n-2); */
        int n1 = 0;
        int n2 = 1;
        for (i = 2; i < number; i++) {
            n_num = n1 + n2;
            n1 = n2;
            n2 = n_num;
        }
    }

    printf ("n_num = %d \n", n_num);

    return n_num;
}

/*
19.1 布尔表达式
*/
#define  true  1
#define  flase (!true)

void Boolean_test (int bool) {
    if (bool == true) {

    }
}

/*
19.3 空语句  创建空语句的宏定义
*/
#define  DoNothing()

/*
26.1  逻辑
1、在知道答案后停止判断
2、使用查表法替换复杂逻辑
3、打最忙的循环放在最内层
*/
void logic_test (int x) {
    if ((5 < x) && (x < 10)) {
        /*当x<5时，后面表达式（x<10)不会进行判断 */
    }

    {
        // 复杂的逻辑链
        int a = 0, b = 0, c = 0;
        int category;

        if ((a && !c) || (a && b && c)) {
            category = 1;
        } else if ((b && !a) || (a && c && !b)) {
            category = 2;
        } else if (c && !a && !b) {
            category = 3;
        } else {
            category = 0;
        }

        //使用查表法替换复杂逻辑
        static int categoryTable[2][2][2] = {
            //!b!c   !bc   b!c   bc
            0, 3, 2, 2,         //!a
            1, 2, 1, 1,         //a
        };

        category = categoryTable[a][b][c];
    }

    {
        /*
         * 可以改进的嵌套循环：  循环次数（100 + 100*5）
         * 将循环的顺序调换一下，循环次数（5 + 5*100）
         */
        int column = 0, row = 0, sum = 0;
        for (column = 0; column < 100; column++) {
            for (row = 0; row < 5; row++) {
                sum = sum + 1;
            }
        }

    }
}

/*
26.4  表达式
1、编译期初始化
2、小心系统函数
*/
void expression_test (unsigned int x) {
    /*用系统函数和常量实现的以2为底的对数函数
     * (unsigned int)(log(x) / log( 2 ));
     */

    const double LOG2 = 0.69314718;
    (unsigned int) (log (x) / LOG2);

    /*
     * 编写Log2函数，返回精度为整形的计算值
     */

    /*
     * 另一种方法： 使用右移运算的以2为底的对数函数
     */
    //unsigned int Log2(unsigned int x) 
    {
        unsigned int i = 0;
        while ((x = (x >> 1)) != 0) {
            i++;
        }
    }
}

/*
32.5  注释技术
注释代码段时应注重“为何做（why）”而不是“怎么做（how）”
*/

void comment_test (void) {
/*  该注释与代码表达的意思一样：重复，没能表达出代码的意图
	//if accout flag  is zero
	if ( accountFlag == 0 ) ...
*/

/*  好的注释，能反映出代码的作用
    //if establinshing a new account
	if ( acctountFlag == 0 ) ...
*/

/*  着眼于“为何”的注释，并具有良好编码风格
   //if establinshing a new account
    if ( acctountType == AccountType.NewAccount ) ...
*/

/*  使用“小节标题”注释
//establinsh a new account
if ( acctountType == AccountType.NewAccount ) ...
*/

}

/*
对比const char 与 char const 的用法。
引申：与java关键字final对比。
可以修饰数据、方法（函数）、类，也可以修饰函数参数
final数据：编译时常量
final参数：无法修改所修饰的引用或者数据
final方法：继承类不能修改方法
final类：不能继承该类
*/
void const_test () {
    char a[10] = { 1, 2, 3, 4, 6, 4, 6, 8, 7, 5 };
    char b[2] = { 3, 5 };

    char *ptr = &a;             //ptr引用或者指向值都可变
    *(ptr + 1) = 2;
    *(a + 3) = 5;

    const char *ptr1 = &a;      //ptr的引用可以变，但是ptr所指向的值不可以变

    ptr1 = &b;
    //*(ptr1 + 1) = 2; //出错

    char const *ptr2 = &a;      //同上
    ptr2 = &b;

    char *const ptr3 = &a;      //ptr所指向的值可以变，但是ptr的引用不可以变
    //ptr3 = &b; //出错

    printf ("ptr1 = %#x, ptr2 = %#x ", ptr1, ptr2);
}

void main7 (void) {
    //Find_MapTable();
    //global_test();
    //pointer_change_value();
    //enum_test();
    //struct_test();
    //string_test();
    //Fibonacci(25);
    //DoNothing();

    const_test ();
}
