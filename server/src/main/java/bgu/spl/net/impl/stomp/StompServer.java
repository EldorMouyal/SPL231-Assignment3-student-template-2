package bgu.spl.net.impl.stomp;

import bgu.spl.net.impl.StompMessageEncoderDecoder;
import bgu.spl.net.impl.StompMessagingProtocolImpl;
import bgu.spl.net.srv.Server;

public class StompServer {

    public static void main(String[] args) {
        args = new String[] {"127.0.0.1", "tpc"};
        if(args[1].equals("reactor"))
            Server.reactor(
                    Runtime.getRuntime().availableProcessors(),
                    7777, //port
                    () -> new StompMessagingProtocolImpl(), //protocol factory
                    () -> new StompMessageEncoderDecoder() //message encoder decoder factory
            ).serve();
        else
       if(args[1].equals("tpc"));
       Server.threadPerClient(
        7777, //port
        () -> new StompMessagingProtocolImpl(), //protocol factory
        () -> new StompMessageEncoderDecoder() //message encoder decoder factory
        ).serve();
    }
}
