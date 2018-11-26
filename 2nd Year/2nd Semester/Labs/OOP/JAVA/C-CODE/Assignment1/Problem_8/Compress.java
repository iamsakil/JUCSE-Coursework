import java.io.*;
import java.util.*;
import java.util.zip.GZIPOutputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;
import java.lang.*;

class Compress{
	List<String> fileList;
	private static final String OUTPUT_GZIP_FILE="C:/Users/iamsakil/Desktop/MP/OUTPUT1.gz";
	private static final String SOURCE_FILE="C:/Users/iamsakil/Desktop/MP/input.txt";
	private static final String OUTPUT_ZIP_FILE="C:/Users/iamsakil/Desktop/MP/OUTPUT.zip";
	private static final String SOURCE_FOLDER="C:/Users/iamsakil/Desktop/MP";

	Compress(){
	fileList = new ArrayList<String>();
    }
	private static void gzipFile(){
		 byte[] buffer = new byte[1024];

     	try{

    		GZIPOutputStream gzos = new GZIPOutputStream(new FileOutputStream(OUTPUT_GZIP_FILE));
	        FileInputStream in = new FileInputStream(SOURCE_FILE);
	        int len;
    	    while ((len = in.read(buffer)) > 0) {
        		gzos.write(buffer, 0, len);
       		 }

      		  in.close();

		    	gzos.finish();
		    	gzos.close();
		    	System.out.println("Done");
		    }catch(IOException ex){
     			  ex.printStackTrace();
    		}
		}

	private void zipDirectory(String zipFile){
		byte[] buffer = new byte[1024];

     try{

    	FileOutputStream fos = new FileOutputStream(zipFile);
    	ZipOutputStream zos = new ZipOutputStream(fos);

    	System.out.println("Output to Zip : " + zipFile);

    	for(String file : this.fileList){

    		System.out.println("File Added : " + file);
    		ZipEntry ze= new ZipEntry(file);
        	zos.putNextEntry(ze);

        	FileInputStream in =
                       new FileInputStream(SOURCE_FOLDER + File.separator + file);

        	int len;
        	while ((len = in.read(buffer)) > 0) {
        		zos.write(buffer, 0, len);
        	}

        	in.close();
    	}

    	zos.closeEntry();
    	
    	zos.close();

    	System.out.println("Done");
    }catch(IOException ex){
       ex.printStackTrace();
    }
   }

  
    public void generateFileList(File node){

    	
	if(node.isFile()){
		fileList.add(generateZipEntry(node.getAbsoluteFile().toString()));
	}

	if(node.isDirectory()){
		String[] subNote = node.list();
		for(String filename : subNote){
			generateFileList(new File(node, filename));
		}
	}

    }

    
    private String generateZipEntry(String file){
    	return file.substring(SOURCE_FOLDER.length()+1, file.length());
    }

    public static void main(String[] args) {
    	Compress fzip = new Compress();
    	fzip.gzipFile();
    	fzip.generateFileList(new File(SOURCE_FOLDER));
    	fzip.zipDirectory(OUTPUT_ZIP_FILE);
    }
}
