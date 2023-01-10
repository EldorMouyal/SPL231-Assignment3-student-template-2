package bgu.spl.net.impl.stomp.Tests;

import bgu.spl.net.impl.StompMessagingProtocolImpl;
import org.junit.Assert;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class StompMessagingProtocolImplTest {
    StompMessagingProtocolImpl stomp= new StompMessagingProtocolImpl();

    @Test
    void shouldTerminate() {
        Assert.assertEquals(false,stomp.shouldTerminate());
        stomp.Terminate();
        Assert.assertEquals(true,stomp.shouldTerminate());

    }


    @Test
    void isCommand() {
        Assert.assertEquals(true,stomp.isCommand("CONNECT"));
        Assert.assertEquals(true,stomp.isCommand("SEND"));
        Assert.assertEquals(true,stomp.isCommand("SUBSCRIBE"));
        Assert.assertEquals(true,stomp.isCommand("UNSUBSCRIBE"));
        Assert.assertEquals(true,stomp.isCommand("DISCONNECT"));
        Assert.assertEquals(false,stomp.isCommand("Dop"));
    }

    @Test
    void fixedFrameArray() {
        String frame="CONNECT\nomer:omer\n\n\nserver:OOOOO      \nKKKKK";
        String[] expected={"CONNECT","omer:omer","server:OOOOO","KKKKK"};
        Assert.assertEquals(expected,stomp.fixedFrameArray(frame.split("\n")));

    }



    @Test
    void checkReciptToAddForError() {
        String expected= "kkk\nreceipt:43\n\u0000";
        String output=stomp.checkReciptToAddForError(stomp.fixedFrameArray(expected.split("\n")));
        Assert.assertEquals("receipt -id:43\n",output);


    }
}