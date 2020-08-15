package CubePackage;

class Cube 
{
	private int[] cube_state = new int[16];
	//pf→perfect 还原状态
	private int cube_pf[]={0,1,2,3,4,5,6,7,3,3,3,3,3,3,3,3};
		
	public Cube(){ 
		for(int i=0;i<16;i++)
			cube_state[i]=cube_pf[i];		
	}

	//初始化
	public void clear(){ 
		for(int i=0;i<16;i++)
			cube_state[i]=cube_pf[i];		
	}

	//输出，调试的时候才用
	public void printout(){
		for(int i=0;i<16;i++)
		{
			System.out.print(cube_state[i] + ",");
		}
		System.out.println();
	}

	//把方块的位置转换为0-5039之间的数，A表示全排列
	public int getNum_A()
	{
		int[] aIn = new int [8];
		for(int i=0;i<8;i++)
		{
			aIn[i]=cube_state[i];
		}
	    int bIn=0;
	    bIn=bIn+(aIn[1]-1)*720;
	    for(int i=2;i<8;i++)
	    {
	        if(aIn[i]>aIn[1])aIn[i]--;
	    }
	    bIn=bIn+(aIn[2]-1)*120;
	    for(int i=3;i<8;i++)
	    {
	        if(aIn[i]>aIn[2])aIn[i]--;
	    }
	    bIn=bIn+(aIn[3]-1)*24;
	    for(int i=4;i<8;i++)
	    {
	        if(aIn[i]>aIn[3])aIn[i]--;
	    }
	    bIn=bIn+(aIn[4]-1)*6;
	    for(int i=5;i<8;i++)
	    {
	        if(aIn[i]>aIn[4])aIn[i]--;
	    }
	    bIn=bIn+(aIn[5]-1)*2;
	    for(int i=6;i<8;i++)
	    {
	        if(aIn[i]>aIn[5])aIn[i]--;
	    }
	    bIn=bIn+(aIn[6]-1);
	    return bIn;
		
	}
	//把方块的方向转换为0-2186之间的数，T表示三进制
	public int getNum_T()
	{
		int bIn=0;
	    for(int i=9;i<16;i++)
	    {
	        bIn=bIn*3+cube_state[i]-1;
	    }
	    return bIn;
	}

	//接下来是三种方向转换，X轴、Y轴、Z轴
	private int fx_x(int aIn)
	{
		int bIn=0;
		if(aIn==1)bIn=1;
		else if(aIn==2)bIn=3;
		else if(aIn==3)bIn=2;
		return(bIn);
	}
	private int fx_y(int aIn)
	{
		int bIn=0;
		if(aIn==1)bIn=3;
		else if(aIn==2)bIn=2;
		else if(aIn==3)bIn=1;
		return(bIn);
	}
	private int fx_z(int aIn)
	{
		int bIn=0;
		if(aIn==1)bIn=2;
		else if(aIn==2)bIn=1;
		else if(aIn==3)bIn=3;
		return(bIn);
	}
	//下面是九种变化。1：顺时针，2：180°，3：逆时针
	private void mo_hou1(){
	    int a=cube_state[2];
		int a_fx=cube_state[10];
		cube_state[2]=cube_state[6];
		cube_state[10]=fx_x(cube_state[14]);
		cube_state[6]=cube_state[5];
		cube_state[14]=fx_x(cube_state[13]);
		cube_state[5]=cube_state[1];
		cube_state[13]=fx_x(cube_state[9]);
		cube_state[1]=a;
		cube_state[9]=fx_x(a_fx);
	}
	private void mo_hou2(){
		int a=cube_state[2];
		int a_fx=cube_state[10];
		cube_state[2]=cube_state[5];
		cube_state[10]=cube_state[13];
		cube_state[5]=a;
		cube_state[13]=a_fx;
		a=cube_state[1];
		a_fx=cube_state[9];
		cube_state[1]=cube_state[6];
		cube_state[9]=cube_state[14];
		cube_state[6]=a;
		cube_state[14]=a_fx;
	}	
	private void mo_hou3(){
		int a=cube_state[2];
		int a_fx=cube_state[10];
		cube_state[2]=cube_state[1];
		cube_state[10]=fx_x(cube_state[9]);
		cube_state[1]=cube_state[5];
		cube_state[9]=fx_x(cube_state[13]);
		cube_state[5]=cube_state[6];
		cube_state[13]=fx_x(cube_state[14]);
		cube_state[6]=a;
		cube_state[14]=fx_x(a_fx);
	}
	private void mo_xia1(){
		int a=cube_state[7];
		int a_fx=cube_state[15];
		cube_state[7]=cube_state[4];
		cube_state[15]=fx_z(cube_state[12]);
		cube_state[4]=cube_state[5];
		cube_state[12]=fx_z(cube_state[13]);
	    cube_state[5]=cube_state[6];
		cube_state[13]=fx_z(cube_state[14]);
		cube_state[6]=a;
		cube_state[14]=fx_z(a_fx);
	}
	private void mo_xia2(){
		int a=cube_state[7];
		int a_fx=cube_state[15];
		cube_state[7]=cube_state[5];
		cube_state[15]=cube_state[13];
		cube_state[5]=a;
		cube_state[13]=a_fx;
		a=cube_state[4];
		a_fx=cube_state[12];
		cube_state[4]=cube_state[6];
		cube_state[12]=cube_state[14];
		cube_state[6]=a;
		cube_state[14]=a_fx;
	}	
	private void mo_xia3(){
		int a=cube_state[7];
		int a_fx=cube_state[15];
		cube_state[7]=cube_state[6];
		cube_state[15]=fx_z(cube_state[14]);
		cube_state[6]=cube_state[5];
		cube_state[14]=fx_z(cube_state[13]);
	    cube_state[5]=cube_state[4];
		cube_state[13]=fx_z(cube_state[12]);
		cube_state[4]=a;
		cube_state[12]=fx_z(a_fx);
	}
	private void mo_you1(){
		int a=cube_state[2];
		int a_fx=cube_state[10];
		cube_state[2]=cube_state[3];
		cube_state[10]=fx_y(cube_state[11]);
		cube_state[3]=cube_state[7];
		cube_state[11]=fx_y(cube_state[15]);
	    cube_state[7]=cube_state[6];
		cube_state[15]=fx_y(cube_state[14]);
		cube_state[6]=a;
		cube_state[14]=fx_y(a_fx);
	}
	private void mo_you2(){
		int a=cube_state[2];
		int a_fx=cube_state[10];
		cube_state[2]=cube_state[7];
		cube_state[10]=cube_state[15];
		cube_state[7]=a;
		cube_state[15]=a_fx;
		a=cube_state[6];
		a_fx=cube_state[14];
		cube_state[6]=cube_state[3];
		cube_state[14]=cube_state[11];
		cube_state[3]=a;
		cube_state[11]=a_fx;
	}	
	private void mo_you3(){
		int a=cube_state[2];
		int a_fx=cube_state[10];
		cube_state[2]=cube_state[6];
		cube_state[10]=fx_y(cube_state[14]);
		cube_state[6]=cube_state[7];
		cube_state[14]=fx_y(cube_state[15]);
	    cube_state[7]=cube_state[3];
		cube_state[15]=fx_y(cube_state[11]);
		cube_state[3]=a;
		cube_state[11]=fx_y(a_fx);
	}
	public void run(int aIn)
	{
		switch(aIn)
		{
		case 0:mo_xia1();break;
		case 1:mo_xia2();break;
		case 2:mo_xia3();break;
		case 3:mo_hou1();break;
		case 4:mo_hou2();break;
		case 5:mo_hou3();break;
		case 6:mo_you1();break;
		case 7:mo_you2();break;
		case 8:mo_you3();break;
		default:System.out.println("Switch语句报错" );
		}
	}
	


}
