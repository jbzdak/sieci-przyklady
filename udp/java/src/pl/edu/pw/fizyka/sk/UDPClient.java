package pl.edu.pw.fizyka.sk;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketTimeoutException;

public class UDPClient {

    public static void main(String[] args) throws IOException {

        for(String s: args){
            System.out.println(s);
        }
        //Odczytujemy wiadomosc albo z konsoli albo z pierwszego argumentu
        String message = null;
        if (args.length != 2){
            System.out.println(args.length);
            System.out.println("USAGE: Client <serverAddress> <nessage>");
            return;
        }

        message = args[1];
        InetAddress serverAddress = InetAddress.getByName(args[0]);
        System.out.println(serverAddress);

                DatagramSocket socket = new DatagramSocket(); //Otwarcie gniazda
        byte[] stringContents = message.getBytes("utf8"); //Pobranie strumienia bajtów z wiadomosci

        DatagramPacket sentPacket = new DatagramPacket(stringContents, stringContents.length);
        sentPacket.setAddress(serverAddress);
        sentPacket.setPort(Config.PORT);
        socket.send(sentPacket);

        DatagramPacket reclievePacket = new DatagramPacket( new byte[Config.BUFFER_SIZE], Config.BUFFER_SIZE);
        socket.setSoTimeout(1010);

        try{
            socket.receive(reclievePacket);
            System.out.println("Serwer otrzymał wiadomość");
        }catch (SocketTimeoutException ste){
            System.out.println("Serwer nie odpowiedział, więc albo dostał wiadomość albo nie...");
        }

    }
}
