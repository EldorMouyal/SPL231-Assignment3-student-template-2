package bgu.spl.net.impl.stomp;

import bgu.spl.net.impl.StompMessageEncoderDecoder;
import bgu.spl.net.impl.StompMessagingProtocolImpl;
import bgu.spl.net.srv.Server;

public class StompServer {

    public static void main(String[] args) {
        //args= new String[]{"7777","tpc"};
        if(args.length>=2)
        {
        if(args[1].equals("reactor"))
            Server.reactor(
                    Runtime.getRuntime().availableProcessors(),
                    Integer.parseInt(args[0]), //port
                    () -> new StompMessagingProtocolImpl(), //protocol factory
                    () -> new StompMessageEncoderDecoder() //message encoder decoder factory
            ).serve();
        else
       if(args[1].equals("tpc"));
       Server.threadPerClient(
        Integer.parseInt(args[0]), //port
        () -> new StompMessagingProtocolImpl(), //protocol factory
        () -> new StompMessageEncoderDecoder() //message encoder decoder factory
        ).serve();
    }
    else{
        throw new RuntimeException("Please enter a port and a protocol type (tpc/reactor)");
    }
}
}
