package cn.tedu.shoot;
import java.awt.Graphics;
import java.util.Arrays;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;
import javax.swing.JFrame;
import javax.swing.JPanel;
import java.util.Arrays;
//整个世界
public class World extends JPanel { //符合is a 关系（World是一个面板）
	public static final int WIDTH = 400;
	public static final int HEIGHT = 700;
	
	private Sky sky = new Sky(); 
	private Hero hero = new Hero(); 
	private FlyingObject[] enemies = {} ;
	private Bullet[] bullets = {};
	public void paint(Graphics g){//因为world继承了Jpanel，Jpanel中有paint()方法，这个是派生类中的重写
		sky.paintObject(g);
		hero.paintObject(g);
		for(int i =0 ; i<enemies.length;i++){
			enemies[i].paintObject(g);
		}
		for( int i = 0; i<bullets.length;i++){
			bullets[i].paintObject(g);
		}
		
	}
	public FlyingObject nextOne(){//随机生成敌人对象
		Random rand = new Random();
		int type = rand.nextInt(20);
		if(type <5){
			return new Bee();
		}else if (type <12){
			return new Airplane();
		}else {
			return new BigAirplane();
		}
		
	}
    int enterIndex =0 ; //敌人入场计数
	public void enterAction(){
    	enterIndex ++;
    	if (enterIndex%30 == 0){
    		FlyingObject obj = nextOne();
    		enemies = Arrays.copyOf(enemies, enemies.length+1);
    		enemies[enemies.length-1] = obj ;
    		
    	}
    }
	int shootIndex = 0;
	public void shootAction(){
		shootIndex++;
		if(shootIndex%30 == 0){
			Bullet[] bs = hero.shoot(); //hero是对象，之前创建的。
		    bullets = Arrays.copyOf(bullets, bullets.length+bs.length); 
		    //先扩容；
		    System.arraycopy(bs,0,bullets,bullets.length-bs.length,bs.length);
		    //数组的追加；
		}
	}
	public void stepAction(){
		sky.step();
		for(int i = 0 ; i <enemies.length;i++){
			enemies[i].step();
		}
		for(int i =0; i<bullets.length;i++){
			bullets[i].step();
		}
		
	}
	//main前边有static的话，main就识别不了以上这堆引用；
	//解决方法：
	public void action(){ //启动程序的执行
		Timer timer = new Timer();
		int intervel = 10 ; //以毫秒为单位；
		timer.schedule(new TimerTask(){
			public void run(){//定时干的事---每隔intervel干的事
				enterAction();//专门实现敌人入场
				shootAction();
				stepAction();
				repaint();
			}
		},intervel,intervel); 
		//第一个interval：从程序启动到第一次触发的时间间隔
		//第二个interval：之后每次的间隔时间

	}
	public static void main(String[] args) {

		JFrame frame = new JFrame(); 
		World world = new World(); 
		frame.add(world); 
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(World.WIDTH,World.HEIGHT); 
		frame.setLocationRelativeTo(null);
		frame.setVisible(true); //干了两件事
		//1)设置窗口可见 2）尽快调用paint（）方法;
		
		world.action(); 
		
		
	

	}

}
