import java.io.File;
import java.util.*;
public class DateSorting implements Comparable<Object>{
	public int compareTo(Object o) {
        long u = ((DateSorting) o).t;
        return t > u ? -1 : t == u ? 0 : 1;
    }

	
	public long t;
	public File f;
	public long sz;
	
	public DateSorting(File file) {
        f = file;
        t = file.lastModified();
		sz = file.length();
    }
	
public static long getFileSize(String filename) {
		  File file = new File(filename);
	      if (!file.exists() || !file.isFile()) {
	         System.out.println("File doesn\'t exist");
	         return -1;
	      }
	      return file.length();
	}

}
