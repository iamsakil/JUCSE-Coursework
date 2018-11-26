import java.io.*;
import java.util.*;

public class DirFile {
	
	private File directory = new File("C:/Users/iamsakil/Desktop/java_final/Problem_7");
    private long ms; 
    private double d1;
    private Date dt;
    private File files[]=directory.listFiles();		
	
	

	public void sortBySize() throws Exception {
		SizeSorting[] size = new SizeSorting[files.length];
    	for (int i = 0; i < files.length; i++)
			size[i] = new SizeSorting(files[i]);
    	
    	Arrays.sort(size);
    	for (int i = 0; i < files.length; i++) {
    		if(size[i].f.isDirectory()) {
				System.out.println("Directory:: "+size[i].f.getName());
				ms = size[i].t;
				dt = new Date(ms);
				System.out.println("Last Modified: "+ dt);
				d1=(double)(size[i].sz)/(1024*1024);
				if(d1<1.00) {
					d1*=1024;
					System.out.println("Size: " + d1 + " KB");
				}
				 else
					 System.out.println("Size: " + d1 + " MB");
				System.out.println();
			}
   	 
			else if(size[i].f.isFile()) {	//check whether files[i] is file or directory
				System.out.println("File:: "+size[i].f.getName());
				ms = size[i].t;
				dt = new Date(ms);
				System.out.println("Last Modified: "+ dt);
				d1=(double)(size[i].sz)/(1024*1024);
				if(d1<1.00) {
					d1*=1024;
					System.out.println("Size: " + d1 + " KB");
				}
				 else
					 System.out.println("Size: " + d1 + " MB");
				 System.out.println();
			}
    	}
	}
	
	public void sortByDate() throws Exception {
		DateSorting[] date = new DateSorting[files.length];
        for (int i = 0; i < files.length; i++) {
        	if(files[i].isDirectory())
        	{
        		date[i] = new DateSorting(files[i]);
        	}
        	else if(files[i].isFile())
        		date[i] = new DateSorting(files[i]);
        }
        
        Arrays.sort(date);
        for (int i = 0; i < files.length; i++) {
        	if(date[i].f.isDirectory()) {
				System.out.println("Directory:: "+date[i].f.getName());
				ms = date[i].t;
				dt = new Date(ms);
				System.out.println("Last Modified: "+ dt);
				d1=(double)(date[i].sz)/(1024*1024);
				System.out.println("Size: " + d1 + " MB");
				System.out.println();
				//checkNoOfFiles(date[i].f.getAbsolutePath(),"By_Size");
			}
       	
			else if(date[i].f.isFile()) {//check whether files[i] is file or directory
				System.out.println("File:: "+date[i].f.getName());
				ms = date[i].t;
				dt = new Date(ms);
				System.out.println("Last Modified: "+ dt);
				d1=(double)(date[i].sz)/(1024*1024);
				if(d1<1.00)
				{
				 d1*=1024;
				 System.out.println("Size: " + d1 + " KB");
				}
				else
				 System.out.println("Size: " + d1 + " MB");
				System.out.println();
			}
		}
	}
	
public void sortByName() throws Exception {
		for(int i=0;i<files.length;i++) {
    		if(files[i].isDirectory()) {
    	        System.out.println("Directory :: "+files[i].getName());
    	        ms = files[i].lastModified();
    	        dt = new Date(ms);
    	        System.out.println("Last Modified Date : "+ dt);
			    d1 = (double) (files[i].length()/(1024));
    	        System.out.println("Size : " + d1 + " KB");
    	        System.out.println();
    	    }
    	 
    		else if(files[i].isFile()) {	//check whether files[i] is file or directory
				
				System.out.println("File :: "+files[i].getName());
    	        ms = files[i].lastModified();
    		    dt = new Date(ms);
    		    System.out.println("Last Modified Date : "+ dt);
				d1 = (double) (files[i].length()/(1024));
    		    
				if(d1<1.00) {
					d1*=1024;
					System.out.println("Size : " + d1 + " KB");
    		    }
    		    
				else
					System.out.println("Size : " + d1 + " MB");
    	        
				System.out.println();
    	    } 
        }
	}
}
