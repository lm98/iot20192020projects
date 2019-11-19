import java.io.BufferedReader;
import java.io.InputStreamReader;

/**
 * Smartradar console program to comand servo with a radar * 
 * @author davide
 *
 */
enum State
{ 
    SINGLE,MANUAL,AUTO; 
} 

public class TestPingPong {

    static int direction;
    static String inputLine;
    public static State s = State.valueOf("MANUAL");

    public static void main(String[] args) throws Exception {
        CommChannel channel = new SerialCommChannel("/dev/ttyACM0",9600);

        /* attesa necessaria per fare in modo che Arduino completi il reboot */
        System.out.println("Waiting Arduino for rebooting...");		
        Thread.sleep(4000);
        channel.sendMsg("ping");
        String msg = channel.receiveMsg();         
        Thread.sleep(500);

        //Controllo la risposta al ping
        if(msg.startsWith("pong")) {
            System.out.println("System connected"); 
        }
        else {
            System.out.println(msg);
            System.exit(1);
        }

        while (true) {

            BufferedReader reader =  
                    new BufferedReader(new InputStreamReader(System.in)); 

            // Reading data and control if is correct
            System.out.println("Enter modality s/m/a and press Enter"); 
            inputLine = reader.readLine();
            while(!inputLine.startsWith("a") && !inputLine.startsWith("s") && !inputLine.startsWith("m") ) {
                System.out.println("No! Enter modality s/m/a and press Enter");
                inputLine = reader.readLine();
            }
            if(inputLine.startsWith("a")) {
                s = State.AUTO;
            }
            else if(inputLine.startsWith("m")) {
                s = State.MANUAL;
            }else if(inputLine.startsWith("s")){
                s=State.SINGLE;
            }
            //Send modality to arduino and receive answer
            channel.sendMsg(inputLine);
            msg = channel.receiveMsg();
            System.out.println("Received: "+msg);

            //Control message received
            if(s == State.SINGLE) {


            }else if(s == State.MANUAL) {

                //Ask user for direction and control is okay
                System.out.println("Enter direction: 0-16");
                inputLine = reader.readLine();
                direction = Integer.parseInt(inputLine);
                while(direction<0 || direction > 16) {
                    System.out.println("No! Enter direction: 0-16");
                    inputLine = reader.readLine();
                    direction = Integer.parseInt(inputLine);
                }

                //Send direction to Arduino and controls it's correct
                channel.sendMsg(inputLine);
                msg = channel.receiveMsg();

                if(!msg.startsWith("OK")) {
                    System.out.println("Error on direction sending");
                }else {
                    msg = channel.receiveMsg();

                }

                //Parse the answer from Arduino
                //MANUAL DIRECTION DISTANCE
                String[] tokens = msg.split("  ");
                System.out.println("Modality: " + tokens[0]);
                System.out.println("Direction: " + tokens[1]);
                int dist = Integer.parseInt(tokens[2]);
                if(dist < 1 || dist > 100) {
                    System.out.println("Object not present");
                }else {
                    System.out.println("Object at "+ dist +" cm");
                }
            }else if(s == State.AUTO) {

            }
        }     
    }
}


