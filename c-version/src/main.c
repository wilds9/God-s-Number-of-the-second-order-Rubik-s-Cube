#include <stdio.h>
#include <stdlib.h>
#define DFST 11
void mo_xia1();void mo_xia2();void mo_xia3();void mo_hou1();void mo_hou2();void mo_hou3();void mo_you1();void mo_you2();void mo_you3();
int (*step[])(void)={mo_xia1,mo_xia2,mo_xia3,mo_hou1,mo_hou2,mo_hou3,mo_you1,mo_you2,mo_you3};
int begin[DFST];//开始工作的数组

char fk[16];
char pf[16]={0,1,2,3,4,5,6,7,3,3,3,3,3,3,3,3};
char temp[12][16];
int cube[5040][2187][DFST];
int x,y,i,j,k,T;
int pathIn=0;

int stop(int bIn[DFST],int aIn)
{
    int tIn;
    if(bIn[DFST-aIn]!=9)return 0;
    else
    {
        for(tIn=DFST-aIn+1;tIn<DFST;tIn++)
        {
            if(bIn[tIn]!=9&&bIn[tIn]!=6)return 0;
        }
    }
    return 1;
    printf("控制停止的子函数报错\n");
    getchar();

}

void jinwei(int bIn[DFST],int aIn)
{

    if(bIn[aIn]==9)
    {

        jinwei(bIn,aIn-1);
        if(bIn[aIn-1]<4)bIn[aIn]=4;
        else bIn[aIn]=1;
    }
    else
    {
        bIn[aIn]++;
        if(0<bIn[aIn-1]&&bIn[aIn-1]<4)
            if(bIn[aIn]==1)
                bIn[aIn]=4;
        if(3<bIn[aIn-1]&&bIn[aIn-1]<7)
            if(bIn[aIn]==4)
                bIn[aIn]=7;
        if(bIn[aIn-1]>6&&bIn[aIn-1]<10)
            if(bIn[aIn]==7)
            {
                bIn[aIn]=1;
                jinwei(bIn,aIn-1);
            }
    }
}


char fx_x(char aIn)
{
	char bIn;
	if(aIn==1)bIn=1;
	else if(aIn==2)bIn=3;
	else if(aIn==3)bIn=2;
	return(bIn);
}

char fx_y(char aIn)
{
    char bIn;
	if(aIn==1)bIn=3;
	else if(aIn==2)bIn=2;
	else if(aIn==3)bIn=1;
	return(bIn);
}

char fx_z(char aIn)
{
	char bIn;
	if(aIn==1)bIn=2;
	else if(aIn==2)bIn=1;
	else if(aIn==3)bIn=3;
	return(bIn);
}

void mo_hou1()
{
    char a=fk[2];
	char a_fx=fk[10];
	fk[2]=fk[6];
	fk[10]=fx_x(fk[14]);
	fk[6]=fk[5];
	fk[14]=fx_x(fk[13]);
	fk[5]=fk[1];
	fk[13]=fx_x(fk[9]);
	fk[1]=a;
	fk[9]=fx_x(a_fx);
}

void mo_hou2()
{
    char a=fk[2];
	char a_fx=fk[10];
	fk[2]=fk[5];
	fk[10]=fk[13];
	fk[5]=a;
	fk[13]=a_fx;
	a=fk[1];
	a_fx=fk[9];
	fk[1]=fk[6];
	fk[9]=fk[14];
	fk[6]=a;
	fk[14]=a_fx;
}

void mo_hou3()
{
    char a=fk[2];
	char a_fx=fk[10];
	fk[2]=fk[1];
	fk[10]=fx_x(fk[9]);
	fk[1]=fk[5];
	fk[9]=fx_x(fk[13]);
	fk[5]=fk[6];
	fk[13]=fx_x(fk[14]);
	fk[6]=a;
	fk[14]=fx_x(a_fx);
}

void mo_xia1()
{
    char a=fk[7];
	char a_fx=fk[15];
	fk[7]=fk[4];
	fk[15]=fx_z(fk[12]);
	fk[4]=fk[5];
	fk[12]=fx_z(fk[13]);
    fk[5]=fk[6];
	fk[13]=fx_z(fk[14]);
	fk[6]=a;
	fk[14]=fx_z(a_fx);
}

void mo_xia2()
{
    char a=fk[7];
	char a_fx=fk[15];
	fk[7]=fk[5];
	fk[15]=fk[13];
	fk[5]=a;
	fk[13]=a_fx;
	a=fk[4];
	a_fx=fk[12];
	fk[4]=fk[6];
	fk[12]=fk[14];
	fk[6]=a;
	fk[14]=a_fx;
}

void mo_xia3()
{
    char a=fk[7];
	char a_fx=fk[15];
	fk[7]=fk[6];
	fk[15]=fx_z(fk[14]);
	fk[6]=fk[5];
	fk[14]=fx_z(fk[13]);
    fk[5]=fk[4];
	fk[13]=fx_z(fk[12]);
	fk[4]=a;
	fk[12]=fx_z(a_fx);
}

void mo_you1()
{
    char a=fk[2];
	char a_fx=fk[10];
	fk[2]=fk[3];
	fk[10]=fx_y(fk[11]);
	fk[3]=fk[7];
	fk[11]=fx_y(fk[15]);
    fk[7]=fk[6];
	fk[15]=fx_y(fk[14]);
	fk[6]=a;
	fk[14]=fx_y(a_fx);
}

void mo_you2()
{
    char a=fk[2];
	char a_fx=fk[10];
	fk[2]=fk[7];
	fk[10]=fk[15];
	fk[7]=a;
	fk[15]=a_fx;
	a=fk[6];
	a_fx=fk[14];
	fk[6]=fk[3];
	fk[14]=fk[11];
	fk[3]=a;
	fk[11]=a_fx;
}

void mo_you3()
{
    char a=fk[2];
	char a_fx=fk[10];
	fk[2]=fk[6];
	fk[10]=fx_y(fk[14]);
	fk[6]=fk[7];
	fk[14]=fx_y(fk[15]);
    fk[7]=fk[3];
	fk[15]=fx_y(fk[11]);
	fk[3]=a;
	fk[11]=fx_y(a_fx);
}

int f(int aIn)//阶乘
{
    if(aIn<0)
    {
        printf("阶乘计算报错\n");
        getchar();
        getchar();
        return 0;
    }
    else if(aIn==0)
    {
        return 1;
    }
    else
    {
        return f(aIn-1)*aIn;
    }
}

int turn(char cIn[16])
{
    char aIn[16];
    copy(aIn,cIn);
    int bIn=0;
    bIn=bIn+(aIn[1]-1)*720;
    for(i=2;i<8;i++)
    {
        if(aIn[i]>aIn[1])aIn[i]--;
    }
    bIn=bIn+(aIn[2]-1)*120;
    for(i=3;i<8;i++)
    {
        if(aIn[i]>aIn[2])aIn[i]--;
    }
    bIn=bIn+(aIn[3]-1)*24;
    for(i=4;i<8;i++)
    {
        if(aIn[i]>aIn[3])aIn[i]--;
    }
    bIn=bIn+(aIn[4]-1)*6;
    for(i=5;i<8;i++)
    {
        if(aIn[i]>aIn[4])aIn[i]--;
    }
    bIn=bIn+(aIn[5]-1)*2;
    for(i=6;i<8;i++)
    {
        if(aIn[i]>aIn[5])aIn[i]--;
    }
    bIn=bIn+(aIn[6]-1);
    return bIn;
}


int san(char aIn[16])
{
    int bIn=0;
    for(i=9;i<16;i++)
    {
        bIn=bIn*3+aIn[i]-1;
    }
    return bIn;
}

void start()
{
    int aIn;
    int bIn;
    int cIn;
    for(aIn=0;aIn<5040;aIn++)
    {
        for(bIn=0;bIn<2187;bIn++)
        {
            for(cIn=0;cIn<DFST;cIn++)
            cube[aIn][bIn][cIn]=0;
        }
    }
    cube[0][2186][DFST-1]=2;
    cube[0][2186][DFST-2]=2;
}

void copy(char x[16],char y[16])
{

    for(i=0;i<16;i++)
    {
            x[i]=y[i];
    }
}
void copy_(int x[DFST],int y[DFST])
{

    for(i=0;i<DFST;i++)
    {
            x[i]=y[i];
    }
}
void count()
{
    int aIn;
    int bIn;
    int cIn=0;
    for(aIn=0;aIn<5040;aIn++)
    {
        for(bIn=0;bIn<2187;bIn++)
            if(cube[aIn][bIn][DFST-1]!=0)
            {
                cIn++;//不等号可以去掉
            }
    }
    printf("\n计数结果：共%d项记录\n",cIn);
}


void work(int nIn)
{
    int dIn=0;
    for(i=0;i<DFST;i++)begin[i]=0;
    begin[DFST-1]=1;//从0,0,……,1开始工作
    while(1)
    {
        copy(fk,pf);
        for(i=DFST-1;i>=0;i--)
        {
            dIn=begin[i]-1;
            if(dIn>=0&&dIn<=8)
            {
            step[dIn]();
            }
        }
        x=turn(fk);
        y=san(fk);
        if(cube[x][y][DFST-1]==0)
        {
            copy_(cube[x][y],begin);
        }
    if(stop(begin,nIn)!=0){break;}
    jinwei(begin,DFST-1);//就该是
    }
}


void main()
{
    int nStep=7;
    printf("请输入要计算的步数(1-11之间的数字)：");
    scanf("%d",&nStep);
    start();
    printf("\n数组初始化完成\n\n");
    printf("正在计算……\n");
    work(nStep);
    count();
}

    /*for(i=0;i<DFST;i++)
    {
        printf("%d",begin[i]);
    }
    getchar();
    */
