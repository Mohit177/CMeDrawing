#include "include/primitives.cpp"
#define ll long long int

using namespace std;

int main()
{
	Context context;
	context.initialize();
	char name[]="Line and Circle Drawing";
	context.createWindow(1200,700,name);
	Primitive p = Primitive(&context);
	cout<<"****Draw Lines and Circles****"<<endl<<endl;
	cout<<"--------------------------------------"<<endl;
	cout<<"Enter 1 for Line Drawing"<<endl;
	cout<<"Enter 2 for Circle Drawing"<<endl;
	cout<<"Enter any other to exit"<<endl;
	int type;
	color_t* buffer = context.getFrameBuffer();
	glfwSwapBuffers(context.getWindow());
	glfwPollEvents();
	color_t c;
	c.r = 255*256*256*256;
	c.g = 255*256*256*256;
	c.b = 0;
	while(!glfwWindowShouldClose(context.getWindow()))
	{
		cin>>type;
		if(type==1)
		{
			cout<<"-------Enter the two points <xi> <yi> <xf> <yf>-------"<<endl;
			double xi,yi,xf,yf;
			cin>>xi>>yi>>xf>>yf;
			p.drawLine(p.makePoint(xi,yi),p.makePoint(xf,yf),c);
			cout<<"-------Line Drawn-------"<<endl;
		}
		else if(type==2)
		{
			cout<<"-------Enter the center of the circle <xi> <yi> and <radius>-------"<<endl;
			double x,y,rad;
			cin>>x>>y>>rad;
			p.drawCircle(p.makePoint(x,y),rad,c);
			cout<<"-------Circle Drawn-------"<<endl;
		}
		else
		{
			cout<<"Bye"<<endl;
			cout<<"-------------------------------------------------------"<<endl;
			return 0;
		}
		glDrawPixels(context.getWindowWidth(),context.getWindowHeight(),GL_RGB,GL_UNSIGNED_INT,buffer);
		glfwSwapBuffers(context.getWindow());
		glfwPollEvents();
	}
	context.terminate();
	return 0;
}