package cn.tedu.shoot;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
public class Sky extends FlyingObject{
	private static BufferedImage image ;
	static{ //给image赋值；
		image = loadImage("background.png");	
	}
	private int y1; //第二张图片的y坐标，两张图交替
	private int speed ; //天空冲着y方向移动速度；值越大，步长越大，移动越快
	public Sky(){
		super(World.WIDTH,World.HEIGHT,0,0);
		y1 = -World.HEIGHT ; 
		speed = 1 ;
	}
	public void step(){
    	y += speed;
    	y1 += speed;
    	if(y >= World.HEIGHT){
    		y = -World.HEIGHT;
    	}
    	if(y1 >= World.HEIGHT){
    		y1 = -World.HEIGHT;
    	}
    }
    public BufferedImage getImage(){
    	return image;
    }
    public void paintObject(Graphics g){
    	g.drawImage(getImage(), x, y, null);
    	g.drawImage(getImage(), x, y1, null);
    	
    }
	

}
