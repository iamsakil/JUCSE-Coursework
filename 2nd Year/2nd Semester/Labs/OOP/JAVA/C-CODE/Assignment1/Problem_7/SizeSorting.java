import java.io.File;

public class SizeSorting implements Comparable<Object>{

	public static long getFileSize(String filename) {
		  File file = new File(filename);
	      if (!file.exists() || !file.isFile()) {
	         System.out.println("File doesn\'t exist");
	         return -1;
	      }
	      return file.length();
	}

	public long t;
	public File f;
	public long sz;
	
	public SizeSorting(File file) {
        f = file;
        t = file.lastModified();
		sz = file.length();
    }
	public int compareTo(Object o) {
        long u = ((SizeSorting) o).sz;
        return sz > u ? -1 : sz == u ? 0 : 1;
    }
}