package CubePackage;

class CubeSheet {
	//相当于之前C中的宏定义
	public static int STEP = 11;
	private char [][][] cube_sheet = new char [5040][2187][STEP];

	//表格的初始化
	public CubeSheet()
	{
		int aIn;
	    int bIn;
	    int cIn;
	    for(aIn=0;aIn<5040;aIn++)
	    {
	        for(bIn=0;bIn<2187;bIn++)
	        {
	            for(cIn=0;cIn<STEP;cIn++)
	            cube_sheet[aIn][bIn][cIn]=0;
	        }
	    }
	    cube_sheet[0][2186][STEP-1]=2;
	    cube_sheet[0][2186][STEP-2]=2;
	}

	//计数
	public int count()
	{
	    int cIn=0;
	    for(int aIn=0;aIn<5040;aIn++)
	    {
	        for(int bIn=0;bIn<2187;bIn++)
	        {
				if(cube_sheet[aIn][bIn][STEP-1]!=0)
	            {
	                cIn++;//不等号可以去掉
	            }
	        }
	    }
	    return cIn;
	}

	//增加记录
	public void add(int xIn,int yIn,char[] aIn)
	{
        if(cube_sheet[xIn][yIn][STEP-1]==0)
        {
            for(int i=0;i<STEP;i++)
            {
            	cube_sheet[xIn][yIn][i]=aIn[i];
            }
        }
	}

	//返回step的值
	public static int getSTEP(){
		return STEP;
	}	
	
}
