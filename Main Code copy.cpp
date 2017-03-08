#include <iostream>
#include <fstream>
using namespace std;
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

char si = 'S';
char di = 'D';
int NumClicks;

int abs(int A)
{
	if (A>=0)
		return A;
	else
		return (-1*A);
};
class Color
{
	private:
		int red;
		int green;
		int blue;

	public:
		Color()
		{
			setColor(0, 0, 0);
		}

		void setColor(int r, int g, int b)
		{
			setRed(r);
			setGreen(g);
			setBlue(b);
		}

		void setRed(int r)
		{
			red = r;
		}

		void setGreen(int g)
		{
			green = g;
		}

		void setBlue(int b)
		{
			blue = b;
		}

		int getRed() const
		{
			return red;
		}

		int getGreen() const
		{
			return green;
		}

		int getBlue() const
		{
			return blue;
		}
};

class Image
{
	private:
		char type[5];
		int width, height;
		int max_val;
		Color **color;

		Mat convertToCvImage()
		{
			Mat img(height, width, CV_8UC3);

			for(int i = 0; i < height; i++)
			{
				for(int j = 0; j < width; j++)
				{
					img.at<Vec3b>(i, j) = Vec3b(color[i][j].getBlue(), color[i][j].getGreen(), color[i][j].getRed());
				}
			}

			return img;
		}

	public:
		Image()
		{
			strcpy(type, "\0");
			width = 0;
			height = 0;
			max_val = 0;
			color = NULL;
		}

		bool readImage(char filename[])
		{
			ifstream file;
			file.open(filename, ios::in);

			if(file.good())
			{
				file >> type;
				file >> width >> height;
				file >> max_val;

				color = new Color*[height];
				for(int i = 0; i < height; i++)
				{
					color[i] = new Color[width];

					for(int j = 0; j < width; j++)
					{
						int r, g, b;
						file >> r >> g >> b;
						color[i][j].setColor(r, g, b);
					}
				}

				file.close();

				return true;
			}
			else
			{
				cerr << "Error reading image: " << filename << endl;
				return false;
			}
		}

/*		bool writeImage(char filename[])
		{
			ofstream file;
			file.open(filename, ios::out);

			if(file.good())
			{
				file << type << endl;
				file << width << " " << height << endl;
				file << max_val << endl;

				for(int i = 0; i < height; i++)
				{
					for(int j = 0; j < width; j++)
					{
						file << color[i][j].getRed() << " " << color[i][j].getGreen() << " " << color[i][j].getBlue() << endl;
					}
				}

				file.close();
				return true;
			}
			else
			{
				cerr << "Error writing file: " << filename << endl;
				return false;
			}
		}

		static bool writeVideo(Image images[], int num_images, char filename[])
		{
			if(num_images == 0)
			{
				cerr << "No frames to write" << endl;
				return false;
			}

			VideoWriter outputVideo;
			Size frame_size = Size(images[0].width, images[0].height);

			outputVideo.open(filename, 861292868, 25, frame_size, true);	// 3rd argument is the frame rate

			if (!outputVideo.isOpened())
			{
				cerr << "Unable to write video: " << filename << endl;
				return false;
			}

			for(unsigned int f = 0; f < num_images; f++)
			{
				outputVideo << images[f].convertToCvImage();
			}

			return true;
		}*/
};

struct point
{
	int x;
	int y;
}a[100],dc[100];

struct tri
{
	short int q;
	short int w;
	short int e;
};
int b=0,v=0;
Mat source_image;
Mat destination_image;
void on_mouse(int event, int x, int y, int flags, void *param)
{
	char im_type = *(char *) param;
	if(event == EVENT_LBUTTONDOWN)
	{
		char im_type = *(char *) param;

		if(im_type == si) 						// Clicked on source image
		{
			for(int i = y - 2; i <= y + 2; i++)
			{
				for(int j = x - 2; j <= x + 2; j++)
				{
					source_image.at<Vec3b>(i, j) = Vec3b(255, 0, 0);
				}
			}

			imshow("Source Image", source_image);
			waitKey(0);
		}
		else if(im_type == di)					// Clicked on destination image
		{
			for(int i = y - 2; i <= y + 2; i++)
			{
				for(int j = x - 2; j <= x + 2; j++)
				{
					destination_image.at<Vec3b>(i, j) = Vec3b(255, 0, 0);
				}
			}

			imshow("Destination Image", destination_image);
			waitKey(0);
		}
	}
		// TODO: Write your code for mouse click here
	if (event==EVENT_LBUTTONDOWN)
	{
		if (im_type==si)
		{
			a[b].x=x;
			a[b].y=y;
			b++;
			if (b==NumClicks)
				destroyWindow("Source Image");
		}
		if (im_type==di)
		{
			dc[v].x=x;
			dc[v].y=y;
			v++;
			if (v==NumClicks)
				destroyWindow("Destination Image");
		}
	}
}
int main()
{
	char src[50];
	char dest[50];
	int NumOutputImages=1;
	cin >> src >> dest;
	cin >> NumOutputImages >> NumClicks;
	point b,ic[NumClicks+4];

	source_image = imread(src);
	destination_image = imread(dest);

	namedWindow("Source Image");
	namedWindow("Destination Image");
	{
		setMouseCallback("Source Image", on_mouse, &si);
		setMouseCallback("Destination Image", on_mouse, &di);

		imshow("Source Image", source_image);
		imshow("Destination Image", destination_image);

		waitKey(0);
	}
	int height=0,width=0,max,lq,lw,le;
	char m1[2];
	ifstream filename(src);
	filename>>m1[0]>>m1[1]>>width>>height>>max;
	Color si[height][width],ii[height][width][NumOutputImages],di[height][width];
	for (int i=0;i<height;i++)
	{
		for (int j=0;j<width;j++)
		{
			filename>>lq>>lw>>le;
			si[i][j].setColor(lq,lw,le);
		}
	}
	filename.close();
	ifstream myfile(dest);
	myfile>>m1[0]>>m1[1]>>width>>height>>max;
	for (int i=0;i<height;i++)
	{
		for (int j=0;j<width;j++)
		{
			myfile>>lq>>lw>>le;
			di[i][j].setColor(lq,lw,le);
		}
	}
	myfile.close();
	a[NumClicks].x=0;
	a[NumClicks].y=0;
	a[NumClicks+1].x=0;
	a[NumClicks+1].y=height-1;
	a[NumClicks+2].x=width-1;
	a[NumClicks+2].y=0;
	a[NumClicks+3].x=width-1;
	a[NumClicks+3].y=height-1;
	a[NumClicks].x=0;
	dc[NumClicks].y=0;
	dc[NumClicks+1].x=0;
	dc[NumClicks+1].y=height-1;
	dc[NumClicks+2].x=width-1;
	dc[NumClicks+2].y=0;
	dc[NumClicks+3].x=width-1;
	dc[NumClicks+3].y=height-1;
	NumClicks+=4;
	int c[NumClicks+1],k;
	bool found=true;
	int i;
	for (i=0;i<NumClicks;i++)
		c[i]=i+1;
	for (int j=0;j<NumClicks;j++)
	{
		int temp,t,n=0;
		temp=a[j].x;
		for (i=j;i<NumClicks;i++)
			if (a[i].x<temp)
				{
					temp=a[i].x;
					t=i;
					n=1;
				}
		if (n==1)
		{
			b=a[j];
			a[j]=a[t];
			a[t]=b;
			n=0;
			k=c[t];
			c[t]=c[j];
			c[j]=k;
		}
	}
	for (int j=0;j<NumClicks;j++)
	{
		int temp,t;
		temp=a[j].y;
		for (i=j;a[i].x==a[j].x;i++)
			if (a[i].y<temp)
			{
				temp=a[i].y;
				a[i].y=a[j].y;
				a[j].y=temp;
				t=c[i];
				c[i]=c[j];
				c[j]=t;
			}
	}
	point edge[50*NumClicks];
	int n=0;
	float l1,l2,p1,p2;
	for (i=1;i<NumClicks;i++)
		for (int j=0;j<i;j++)
		{
			for (int k=0;k<n;k++)
			{
				if (a[edge[k].y].x!=a[edge[k].x].x)
				{
					l1=((float)(a[edge[k].x].y-a[i].y)-(float)((a[edge[k].y].y-a[edge[k].x].y)*(a[edge[k].x].x-a[i].x)/(float)(a[edge[k].y].x-a[edge[k].x].x)));
					l2=((float)(a[edge[k].x].y-a[j].y)-(float)((a[edge[k].y].y-a[edge[k].x].y)*(a[edge[k].x].x-a[j].x)/(float)(a[edge[k].y].x-a[edge[k].x].x)));
				}
				else
				{
					l1=0;
					l2=0;
				}
				if (a[i].x!=a[j].x)
				{
					p1=(float)((a[i].y-a[edge[k].x].y)+((float)((a[j].y-a[i].y)*(a[edge[k].x].x-a[i].x))/(float)(a[j].x-a[i].x)));
					p2=(float)((a[i].y-a[edge[k].y].y)+((float)((a[j].y-a[i].y)*(a[edge[k].y].x-a[i].x))/(float)(a[j].x-a[i].x)));
				}
				if ((a[i].x==a[j].x)&&(j==i-1))
					continue;
				else if (a[edge[k].y].x==a[edge[k].x].x)
				{
					if (a[j].x>a[edge[k].x].x)
						continue;
					else if (p1*p2>=0)
						continue;
					else
					{
						found=false;
						break;
					}

				}
				else if (l1*l2>=0)
					continue;
				else if (p1*p2>0)
					continue;
				else
				{
					found=false;
					break;
				}

			}
			if (found==true)
			{
				edge[n].x=i;
				edge[n].y=j;
				n++;
			}
			else
				found=true;

		}
	int count=0;
	tri l[50*NumClicks],m;
	for (i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			if (edge[j].y==edge[i].y)
				for (int k=j+1;k<n;k++)
					if ((edge[k].y==edge[i].x)&&(edge[k].x==edge[j].x))
					{
						l[count].q=edge[i].y;
						l[count].w=edge[i].x;
						l[count].e=edge[j].x;
						count++;
					}
	found=true;
	for (i=0;i<count;i++)
	{
		point found1,found2,found3;
		float w1,w2,w3,d;
		for (int j=l[i].q-1;j<l[i].e;j++)
		{
			found1.x=a[l[i].w].x-a[l[i].q].x;
			found1.y=a[l[i].w].y-a[l[i].q].y;
			found2.x=a[l[i].e].x-a[l[i].q].x;
			found2.y=a[l[i].e].y-a[l[i].q].y;
			found3.x=a[j].x-a[l[i].q].x;
			found3.y=a[j].y-a[l[i].q].y;
			d=found1.x*found2.y-found2.x*found1.y;
			w1=((found3.x*(found1.y-found2.y)+found3.y*(found2.x-found1.x)+found1.x*found2.y-found2.x*found1.y)/d);
			w2=(found3.x*found2.y-found3.y*found2.x)/d;
			w3=(found3.y*found1.x-found3.x*found1.y)/d;
			if ((w1>0)&&(w2>0)&&(w3>0)&&(w1<1)&&(w2<1)&&(w3<1))
			{
				found=false;
				break;
			}
		}
		if (found==false)
		{
			l[i].e=-1;
			found=true;
		}
	}
	for (i=0;i<count;i++)
	{
		l[i].q++;
		l[i].w++;
		l[i].e++;
	}
	for (i=NumClicks;i>0;i--)
		c[i]=c[i-1];
	c[0]=0;
	for (i=0;i<count;i++)
	{
		int temp;
		if (l[i].e<l[i].q)
		{
			temp=l[i].e;
			l[i].e=l[i].q;
			l[i].q=temp;
		}
		if (l[i].w<l[i].q)
		{
			temp=l[i].w;
			l[i].w=l[i].q;
			l[i].q=temp;
		}
		if (l[i].e<l[i].w)
		{
			temp=l[i].e;
			l[i].e=l[i].w;
			l[i].w=temp;
		}
	}
	for (i=0;i<count;i++)
	{
		int temp,t,d=0;
		temp=l[i].q;
		for (int j=i;j<count;j++)
		{
			if (l[j].q<temp)
			{
				temp=l[j].q;
				t=j;
				d=1;
			}
		}
		if (d==1)
		{
			d=0;
			m=l[t];
			l[t]=l[i];
			l[i]=m;
		}
	}
	for (i=0;i<count;i++)
	{
		int temp;
		temp=l[i].w;
		for (int j=i;l[i].q==l[j].q;j++)
		{
			if (l[j].w<temp)
			{
				temp=l[j].w;
				m=l[i];
				l[i]=l[j];
				l[j]=m;
			}
		}
	}
	for (i=0;i<count;i++)
	{
		int temp;
		temp=l[i].e;
		for (int j=i;l[i].q==l[j].q;j++)
		{
			if (l[i].w==l[j].w)
				if (l[j].e<temp)
				{
					temp=l[i].e;
					m=l[i];
					l[i]=l[j];
					l[j]=m;
				}
		}
	}
	for (i=0;i<count;i++)
	{
		l[i].q--;
		l[i].w--;
		l[i].e--;
	}
	int j,p;
	point u[NumClicks];
	for (i=0;i<NumClicks;i++)
		u[i]=dc[c[i+1]-1];
	for (i=0;i<NumClicks;i++)
	{
		dc[i]=u[i];
	}
	for (p=0;p<NumOutputImages;p++)
	{
		float alpha,beta,gamma;
		alpha=(p+1)/(float)(NumOutputImages+1);
		for (i=0;i<NumClicks;i++)
		{
			ic[i].x=(1.0-alpha)*(float)a[i].x+(float)(alpha*(float)dc[i].x);
			ic[i].y=(1.0-alpha)*(float)a[i].y+alpha*(float)dc[i].y;
		}
		int o,x1,x2,x3,y1,y2,y3,A,A1,A2,A3,x,y,xs,ys,xd,yd;
		for (i=0;i<height;i++)
		{
			for (j=0;j<width;j++)
			{
				for (o=0;o<count;o++)
				{
					if (l[o].q==-1)
						continue;
					x=j;
					y=i;
					x1=ic[l[o].q].x;
					x2=ic[l[o].w].x;
					x3=ic[l[o].e].x;
					y1=ic[l[o].q].y;
					y2=ic[l[o].w].y;
					y3=ic[l[o].e].y;
					A=x2*(y3-y1)+x1*(y2-y3)+x3*(y1-y2);
					A1=x2*(y3-y)+x*(y2-y3)+x3*(y-y2);
					A2=x*(y3-y1)+x1*(y-y3)+x3*(y1-y);
					A3=x2*(y-y1)+x1*(y2-y)+x*(y1-y2);
					if (abs(A)==abs(A1)+abs(A2)+abs(A3))
					{
						found=true;
						break;
					}
				}
				if (found==false)
				{
					ii[i][j][p].setColor(0,0,0);
				}

				else
				{
					beta=-1*((x-x1)*(y2-y1)-(y-y1)*(x2-x1))/(float)A;
					gamma=((x-x1)*(y3-y1)-(y-y1)*(x3-x1))/(float)A;
					xs=a[l[o].q].x+beta*(float)(a[l[o].e].x-a[l[o].q].x)+gamma*(float)(a[l[o].w].x-a[l[o].q].x);
					ys=a[l[o].q].y+beta*(float)(a[l[o].e].y-a[l[o].q].y)+gamma*(float)(a[l[o].w].y-a[l[o].q].y);
					xd=dc[l[o].q].x+beta*(float)(dc[l[o].e].x-dc[l[o].q].x)+gamma*(float)(dc[l[o].w].x-dc[l[o].q].x);
					yd=dc[l[o].q].y+beta*(float)(dc[l[o].e].y-dc[l[o].q].y)+gamma*(float)(dc[l[o].w].y-dc[l[o].q].y);
					lq=(1.0-alpha)*(float)si[ys][xs].getRed()+alpha*(float)di[yd][xd].getRed();
					lw=(1.0-alpha)*(float)si[ys][xs].getGreen()+alpha*(float)di[yd][xd].getGreen();
					le=(1.0-alpha)*(float)si[ys][xs].getBlue()+alpha*(float)di[yd][xd].getBlue();
					ii[i][j][p].setColor(lq,lw,le);
					found=false;
				}
			}
		}
	}
		ofstream file("image.ppm");
		file<<"P3"<<endl<<width*(NumOutputImages+2)<<endl<<height<<endl<<"255"<<endl;
		for (j=0;j<height;j++)
		{
			for (i=0;i<NumOutputImages+2;i++)
			{
				for (int o=0;o<width;o++)
				{
					if (i==0)
						file<<si[j][o].getRed()<<endl<<si[j][o].getGreen()<<endl<<si[j][o].getBlue()<<endl;
					else if (i==NumOutputImages+1)
						file<<di[j][o].getRed()<<endl<<di[j][o].getGreen()<<endl<<di[j][o].getBlue()<<endl;
					else
						file<<ii[j][o][i-1].getRed()<<endl<<ii[j][o][i-1].getGreen()<<endl<<ii[j][o][i-1].getBlue()<<endl;
				}
			}
		}
		cout<<"complete"<<endl;
	return 0;
}
