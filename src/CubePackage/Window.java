package CubePackage;

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;



public class Window extends JFrame implements ActionListener
{
	/* * */
	private static final long serialVersionUID = 1L;
	private JTextField myTextField = new JTextField(15);
	private JButton myButton = new JButton("开始运算");
	private JLabel myLabel = new JLabel("　　请输入1-11之间的整数　　",JLabel.CENTER);
	private JLabel Information = new JLabel("<html><body>Author's Information<br>Home Page: http://dxnotes.com<br>Email: huidexuan@gmail.com</body></html>",JLabel.LEFT);
	private JLabel Title = new JLabel("二阶魔方“上帝之数”的验证",JLabel.CENTER);
	private JLabel Time = new JLabel("　　　　　　　　　",JLabel.CENTER);
	private JLabel aboutTime = new JLabel("(9步大约8秒，之后每步x6）",JLabel.CENTER);

	
	public Window()
	{
		setTitle("Mini Cube God's Number Verification");
		setLayout(new FlowLayout());
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(240,230);
		setLocation(400,300);
		add(Title);
		add(myTextField);
		add(myButton);
		add(myLabel);
		add(Time);
		add(aboutTime);
		add(Information);
		myButton.addActionListener(this);
		setVisible(true);			
		setResizable(false);
		
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		this.setLocation(screenSize.width/2 - 115, screenSize.height/2-105);

	}
	public void actionPerformed(ActionEvent e)
	{
		Work myWork = new Work();
		int result=0;
		String myText;
		myText = myTextField.getText();
		double temp = Double.parseDouble(myText);
		int temp2 = (int)temp;
		if(temp2>=1&&temp<=11)
		{
			myWork.setnStep(temp2);
			long startTime=System.currentTimeMillis(); 		
			result = myWork.mainWork();
			long endTime=System.currentTimeMillis();
			Time.setText("运行时间：" + (endTime-startTime) + "ms");
			myLabel.setText("推演 "+(int)temp+" 步，共有: " + result + " 条结果");
		}
		else
		{
			myLabel.setText("　　　输入不合法！　　　");
			
			String arg1 = new String();
			arg1 = "";
			myTextField.setText(arg1);
		}
		

	}
	
}
