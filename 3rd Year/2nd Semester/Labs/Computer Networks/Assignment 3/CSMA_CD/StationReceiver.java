/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


import java.io.*;
import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.Semaphore;
import java.util.logging.Level;
import java.util.logging.Logger;

public class StationReceiver extends Thread {

    String type;
    int backoff, k;
    static Semaphore[] receive;
    static int maxStations,  kMax = 50,  countR = 0;

    public StationReceiver(String type, String threadName) {
        super(threadName);
        this.type = type;
        backoff = k = 0;
    }

    @Override
    public void run() {
        {
            try {
                char ch = Thread.currentThread().getName().charAt(0);
                System.out.println(ch);
                if (type.equals("sender")) {
                    //writes to file
                    //messRead.acquire(); // to ensure no overwriting till threads reads data
                    double p = 0.85;
                    Random rand = new Random();
                    while (true) {
                        if (rand.nextDouble() < p) {
                            System.out.println("Thread - " + Thread.currentThread().getName() + ". Message Entered.");
                            //Scanner sc = new Scanner(System.in);
                            //String message = sc.next();
                            String message = Thread.currentThread().getName() + " hello.";
                            Writer output = null;

                            File file = new File("Message_st" + ch + ".txt");
                            output = new BufferedWriter(new FileWriter(file));
                            //output = new BufferedWriter(new FileWriter("Message_st.txt"));
                            output.write(message);
                            output.close();
                            receive[Character.getNumericValue(ch)].release();
                            System.out.println("Station " + Thread.currentThread().getName() + " has completed work");
                            break;
                        } else {
                            k++;
                            System.out.println("Channel busy. Acquisition fails for - " + Thread.currentThread().getName());

                            if (k > kMax) {
                                System.out.println("Station " + Thread.currentThread().getName() + " stops");
                                break;
                            }
                            receive[Character.getNumericValue(ch)].release();
                            backoff = (int) (Math.pow(2, k) * rand.nextDouble());
                        //Thread.sleep(backoff);
                        }
                    }
                } else {
                    // reads and checks if meant for itself
                    receive[Character.getNumericValue(ch)].acquire();
                    String namet = Thread.currentThread().getName();
                    System.out.println("Station reading - " + namet);
                    File file = new File("Message_st" + ch + ".txt");
                    //File file = new File("Message_st.txt");
                    Scanner sc = null;
                    try {
                        sc = new Scanner(file);
                    } catch (FileNotFoundException ex) {
                        System.out.println("File not fount in " + ch);
                        Logger.getLogger(StationReceiver.class.getName()).log(Level.SEVERE, null, ex);
                    }
                    String str = "";
                    while (sc.hasNextLine()) {
                        str = str + sc.nextLine();
                    }
                    sc.close();

                    System.out.println("Read - " + str);
                    return;

                }

            } catch (IOException ex) {
                Logger.getLogger(StationReceiver.class.getName()).log(Level.SEVERE, null, ex);
            } catch (InterruptedException ex) {
                Logger.getLogger(StationReceiver.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    public static void create() {
        int count = maxStations;
        StationReceiver arr[] = new StationReceiver[count * 2];
        try {
            for (int i = 0; i < count; i++) {
                String threadName = Integer.toString(i);
                arr[2 * i] = new StationReceiver("sender", threadName + "s");
                arr[(2 * i) + 1] = new StationReceiver("receiver", threadName + "r");
                arr[2 * i].start();
                arr[(2 * i) + 1].start();
            }
            for (int i = 0; i < count; i++) {
                arr[2 * i].join();
                arr[(2 * i) + 1].join();
                System.out.println("Station - " + i + " has ended.");
            }
        } catch (InterruptedException ex) {
            Logger.getLogger(StationReceiver.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void main(String[] args) throws InterruptedException {
        int count = 4;
        System.out.println("hello boss");
        receive = new Semaphore[count];
        for (int i = 0; i < count; i++) {
            receive[i] = new Semaphore(1);
            receive[i].acquire();
        }
        maxStations = count;
        create();
        return;
    }
}
