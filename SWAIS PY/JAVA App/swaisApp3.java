import javax.swing.*;
import java.awt.*;
import java.io.*;



//package systems;
//package learn;

//package learn;

public class swaisApp3 extends javax.swing.JFrame {
    
    /** Creates new form swaisApp */
    public swaisApp3() {
        initComponents();
    }
    
  
    private void initComponents() {
        inputTextField = new javax.swing.JTextField();
        inputLabel = new javax.swing.JLabel();
        generateButton = new javax.swing.JButton();
        outputLabel = new javax.swing.JLabel();
		outputLabel2 = new javax.swing.JLabel();
        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("SWAIS Code Generator");

        inputLabel.setText("Zip File");

        generateButton.setText("Generate");
        generateButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                generateButtonActionPerformed(evt);
            }
        });

        outputLabel.setText("Output File");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
       
	   layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(inputTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(inputLabel)
						.addComponent(outputLabel2))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(generateButton)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(outputLabel2)))
						
                .addContainerGap(27, Short.MAX_VALUE))
        );

        layout.linkSize(javax.swing.SwingConstants.HORIZONTAL, new java.awt.Component[] {generateButton, inputTextField});

        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(inputTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(inputLabel))
					
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(generateButton)
                    .addComponent(outputLabel)
					.addComponent(outputLabel))
					
                .addContainerGap(21, Short.MAX_VALUE))
        );
		
			
        pack();
    }

    private void generateButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_generateButtonActionPerformed
	
        try{
			
			ProcessBuilder pb = new ProcessBuilder("python","swaisGenerator.py");
			Process p = pb.start();
			BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
			String ret = new String(in.readLine());
			//outputLabel.setText(ret);
			outputLabel.setText(ret);
			System.out.println("value is : "+ret);
		
		}catch(Exception e){}
			
		/
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        
		
		java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new swaisApp3().setVisible(true);
            }
        });
    }
    
    // Variables declaration 
    
	
	private javax.swing.JLabel outputLabel;
	
	private javax.swing.JLabel inputLabel;
    private javax.swing.JButton generateButton;
    private javax.swing.JLabel outputLabel;
    private javax.swing.JTextField inputTextField;
   
    
}

		
		
		
		
		
		
		
		/* JFrame.setDefaultLookAndFeelDecorated(true);
		JFrame frame = new JFrame("SWAIS Code Generator");
		frame.setSize(300,150);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
 
		// Change the background color
		frame.getContentPane().setBackground(Color.red); 	
		 */
				
	
	/* private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {                                         
		OpenMain();
	}	                                        

	private void OpenMain(){
		try{
			String a = "C:\\Users";
			Runtime.getRuntime().exec("cmd /c start "+a);
		}catch(Exception exception){
			exception.printStackTrace();
		}
	} */
		
	
    

	
		
   
   
   
   
   
   
   
   
   
   
   /* public static void main(String[] args) {
      
	// Create a basic JFrame
    JFrame.setDefaultLookAndFeelDecorated(true);
    JFrame frame = new JFrame("SWAIS Code Creator");
    frame.setSize(600,300);
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setVisible(true);
	  
	// Change the background color
    frame.getContentPane().setBackground(Color.blue);
	  

   
   private javax.swing.JButton jButton1;
   
   }
} */