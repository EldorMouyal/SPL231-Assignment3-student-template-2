package bgu.spl.net.impl.stomp.Tests;

import bgu.spl.net.impl.StompMessageEncoderDecoder;
import org.junit.Assert;
import org.junit.jupiter.api.Test;


class StompMessageEncoderDecoderTest {
    private StompMessageEncoderDecoder encoderdecoder;

    @Test
    void encodeDecode() {
        encoderdecoder=new StompMessageEncoderDecoder();
        byte[] b=encoderdecoder.encode("hey");
        String s="";
        for(int i=0;i<b.length;i++)
        {
            s= encoderdecoder.decodeNextByte(b[i]);
        }
        System.out.println(s);
        Assert.assertEquals("hey",s);

        b=encoderdecoder.encode("omer\nomer\nomer");
        for(int i=0;i<b.length;i++)
        {
            s= encoderdecoder.decodeNextByte(b[i]);
        }
        System.out.println(s);
        Assert.assertEquals("omer\nomer\nomer",s);
    }

}