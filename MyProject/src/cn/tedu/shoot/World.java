package cn.tedu.shoot;
import java.awt.Graphics;
import java.util.Arrays;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;
import javax.swing.JFrame;
import javax.swing.JPanel;
import java.util.Arrays;
//��������
public class World extends JPanel { //����is a ��ϵ��World��һ����壩
	public static final int WIDTH = 400;
	public static final int HEIGHT = 700;
	
	private Sky sky = new Sky(); 
	private Hero hero = new Hero(); 
	private FlyingObject[] enemies = {} ;
	private Bullet[] bullets = {};
	public void paint(Graphics g){//��Ϊworld�̳���Jpanel��Jpanel����paint()������������������е���д
		sky.paintObject(g);
		hero.paintObject(g);
		for(int i =0 ; i<enemies.length;i++){
			enemies[i].paintObject(g);
		}
		for( int i = 0; i<bullets.length;i++){
			bullets[i].paintObject(g);
		}
		
	}
	public FlyingObject nextOne(){//������ɵ��˶���
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
    int enterIndex =0 ; //�����볡����
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
			Bullet[] bs = hero.shoot(); //hero�Ƕ���֮ǰ�����ġ�
		    bullets = Arrays.copyOf(bullets, bullets.length+bs.length); 
		    //�����ݣ�
		    System.arraycopy(bs,0,bullets,bullets.length-bs.length,bs.length);
		    //�����׷�ӣ�
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
	//mainǰ����static�Ļ���main��ʶ��������������ã�
	//���������
	public void action(){ //���������ִ��
		Timer timer = new Timer();
		int intervel = 10 ; //�Ժ���Ϊ��λ��
		timer.schedule(new TimerTask(){
			public void run(){//��ʱ�ɵ���---ÿ��intervel�ɵ���
				enterAction();//ר��ʵ�ֵ����볡
				shootAction();
				stepAction();
				repaint();
			}
		},intervel,intervel); 
		//��һ��interval���ӳ�����������һ�δ�����ʱ����
		//�ڶ���interval��֮��ÿ�εļ��ʱ��

	}
	public static void main(String[] args) {

		JFrame frame = new JFrame(); 
		World world = new World(); 
		frame.add(world); 
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(World.WIDTH,World.HEIGHT); 
		frame.setLocationRelativeTo(null);
		frame.setVisible(true); //����������
		//1)���ô��ڿɼ� 2���������paint��������;
		
		world.action(); 
		
		
	

	}

}
