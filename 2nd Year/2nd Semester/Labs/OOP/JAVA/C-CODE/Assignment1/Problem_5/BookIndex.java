import java.io.IOException;
import java.io.FileInputStream;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.util.Scanner;
import java.util.Hashtable;
import java.util.Set;
import java.util.Vector;
import java.util.*;

import java.io.*;


public class BookIndex {
    private Hashtable<String,Vector<Integer>> index;

    BookIndex() {
        index = new Hashtable<String, Vector<Integer>>();
    }

    BookIndex(String fileName) throws IOException {
        index = new Hashtable<String, Vector<Integer>>();

        BufferedReader br = new BufferedReader(new FileReader(fileName));
        String line;
        int lineNo = 0;
        while((line = br.readLine()) != null) {
                ++lineNo;
                line.toLowerCase();
                Pattern p = Pattern.compile("[\\w']+");
                Matcher m = p.matcher(line);

                while (m.find()) {
                    Vector<Integer> temp = index.get(line.substring(m.start(),m.end()));
                    if (temp != null) {
                        temp.add(lineNo);
                        index.put(line.substring(m.start(),m.end()), temp);
                    }
                    else {
                        temp = new Vector<Integer>();
                        temp.add(lineNo);
                        index.put(line.substring(m.start(),m.end()), temp);
                    }
                }
        }
    }

    void display()
    {
        Set<String> wordn = index.keySet();
        SortedSet<String> words = new TreeSet<String>();

        for (String word : wordn) {
            words.add(word);
        }

        for (String word : words)
        {
            System.out.print(word + ": ");
            for (int lineNo : index.get(word))
            {
                System.out.print(lineNo + " ");
            }
            System.out.println("\b\b");
        }
    }

    public static void main(String args[])
    {
        try
        {
            Scanner in = new Scanner(System.in);

            String filename;
            filename = in.nextLine();

            BookIndex index = new BookIndex(filename);
            index.display();

        }
        catch (Exception e)
        {
            System.out.println(e.toString() + ": try again");
        }
    }
}
