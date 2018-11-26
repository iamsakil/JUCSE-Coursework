import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.JLabel;
import java.awt.event.ActionListener;
import java.util.Calendar;
import java.util.Date;
import java.util.Random;
import java.awt.event.ActionEvent;
import java.awt.Font;
import javax.swing.SwingConstants;
import java.awt.Component;
import java.awt.Window.Type;
import java.awt.Color;

public class Abc {

	static Quotes_For_Morning qm = new Quotes_For_Morning();
	static Quotes_For_Night qn = new Quotes_For_Night();
	
	
	public static int Time_stamp()
	{
		Date dNow = new Date();
		Calendar calendar = Calendar.getInstance();
		calendar.setTime(dNow);
		int total_seconds = calendar.get(Calendar.HOUR_OF_DAY)*3600+calendar.get(Calendar.MINUTE)*60+calendar.get(Calendar.SECOND);
		//System.out.println("\n\t " + calendar.get(Calendar.HOUR_OF_DAY) + ":" + calendar.get(Calendar.MINUTE) + ":" + calendar.get(Calendar.SECOND));
		return total_seconds;
	}
	
	public static void Time_stamp1()
	{
		Date dNow = new Date();
		Calendar calendar = Calendar.getInstance();
		calendar.setTime(dNow);
		//int total_seconds = calendar.get(Calendar.HOUR_OF_DAY)*3600+calendar.get(Calendar.MINUTE)*60+calendar.get(Calendar.SECOND);
		System.out.println("\n\t " + calendar.get(Calendar.HOUR_OF_DAY) + ":" + calendar.get(Calendar.MINUTE) + ":" + calendar.get(Calendar.SECOND));
		//return total_seconds;
	}
	
	public static int randInt(int min, int max) {
		Random rand = new Random();
	    int randomNum = rand.nextInt((max - min) + 1) + min;
	    return randomNum;
	}
	
	public static int time_now()
	{
		Date dNow = new Date();
		Calendar calendar = Calendar.getInstance();
		calendar.setTime(dNow);
		return calendar.get(Calendar.HOUR_OF_DAY);
	}
	
	private JFrame frmQuoteOfThe;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		
		qm.Initialize_Quotes_And_Time();
		qn.Initialize_Quotes_And_Time();
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Abc window = new Abc();
					window.frmQuoteOfThe.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public Abc() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frmQuoteOfThe = new JFrame();
		frmQuoteOfThe.setType(Type.POPUP);
		frmQuoteOfThe.setTitle("Quote Of The Day");
		frmQuoteOfThe.setBackground(Color.yellow);
		frmQuoteOfThe.setFont(new Font("Arial Black", Font.PLAIN, 12));
		frmQuoteOfThe.setBounds(100, 100, 843, 515);
		frmQuoteOfThe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frmQuoteOfThe.getContentPane().setLayout(null);
		
		JLabel label1 = new JLabel("");
		label1.setAutoscrolls(true);
		label1.setAlignmentX(Component.CENTER_ALIGNMENT);
		label1.setHorizontalAlignment(SwingConstants.CENTER);
		label1.setFont(new Font("Dialog", Font.BOLD | Font.ITALIC, 12));
		label1.setBounds(12, 91, 803, 38);
		frmQuoteOfThe.getContentPane().add(label1);
		
		JLabel label = new JLabel("");
		label.setHorizontalAlignment(SwingConstants.CENTER);
		label.setFont(new Font("Dialog", Font.BOLD | Font.ITALIC, 12));
		label.setAutoscrolls(true);
		label.setAlignmentX(0.5f);
		label.setBounds(156, 164, 545, 38);
		frmQuoteOfThe.getContentPane().add(label);
		
		JButton btnNewButton = new JButton("Enter");
		
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				
				label.setText("");
				if(time_now()>=6 && time_now()<18)
				{
						
					int n = randInt(0,33);
					
					if(qm.Time.get(n)==0)
					{
						label1.setText(qm.Quotes.get(n));
						System.out.println(qm.Quotes.get(n));
						qm.Time.set(n,Time_stamp());
						Time_stamp1();
					}
					
					else if (Time_stamp()-qm.Time.get(n)>10)
					{
						label1.setText(qm.Quotes.get(n));
						System.out.println(qm.Quotes.get(n));
						label.setText("Again Print after " + Integer.toString(Time_stamp()-qm.Time.get(n))+ " sec");
						qm.Time.set(n,Time_stamp());
						Time_stamp1();
					}
					else
						actionPerformed(e);
				
				}
				
				else
				{
					int n = randInt(0,35);
						
						if(qn.Time.get(n)==0)
						{
							label1.setText(qn.Quotes.get(n));
							System.out.println(qn.Quotes.get(n));
							qn.Time.set(n,Time_stamp());
							Time_stamp1();
						}
						
						else if (Time_stamp()-qn.Time.get(n)>10)
						{
							label1.setText(qn.Quotes.get(n));
							System.out.println(qn.Quotes.get(n));
							label.setText("Again Print after " + Integer.toString(Time_stamp()-qn.Time.get(n))+ " sec");
							qn.Time.set(n,Time_stamp());
							Time_stamp1();
						}
						else
							actionPerformed(e);
					
				}
			}
		});
		btnNewButton.setBounds(360, 246, 98, 26);
		frmQuoteOfThe.getContentPane().add(btnNewButton);
		
		
	}
}
