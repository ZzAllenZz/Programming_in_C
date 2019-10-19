package cn.tedu.shoot;
import java.awt.image.BufferedImage;
import java.util.Random;
import javax.imageio.ImageIO;
import java.awt.Graphics;
public abstract class FlyingObject {
	public static final int LIFE = 0;
	public static final int DEAD = 1;
	public static final int REMOVE = 2;
	protected int state = LIFE ;
	protected int width;
	protected int height ;
	protected int x;
	protected int y;
	public abstract BufferedImage getImage();
	public abstract void step();
	public FlyingObject(int width , int height){
		this.width = width;
		this.height = height;
    	Random rand = new Random();
    	x = rand.nextInt(World.WIDTH-this.width);
    	y = -this.height;
	}
	public FlyingObject(int width , int height , int x , int y){
		this.width = width;
		this.height = height;
		this.x = x;
		this.y = y;
	}
	public static BufferedImage loadImage(String fileName){

		try{
			BufferedImage img = ImageIO.read(FlyingObject.class.getResource(fileName)) ;
			//Í¬°üÏÂ¶ÁÍ¼Æ¬
			return img;
		}catch(Exception e ){
			e.printStackTrace();
			throw new RuntimeException();
		}
	}
    public boolean isLife (){
    	return state == LIFE;
    }
    public boolean isDead(){
    	return state == DEAD;
    }
    public boolean isRemove(){
    	return state == REMOVE;  	
    }
    public void paintObject(Graphics g){//»­Í¼Æ¬
    	g.drawImage(getImage(), x, y, null);
    	
    }


}
