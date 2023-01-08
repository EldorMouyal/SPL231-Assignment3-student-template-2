package bgu.spl.net.impl;

import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.Server;

import java.util.LinkedList;
import java.util.List;
import java.util.regex.Pattern;

import org.omg.CORBA.FloatSeqHelper;

public class StompMessagingProtocolImpl implements StompMessagingProtocol<String> {
    Connections<String> connections;
    private int connectionId;
    private boolean terminate= false;
    private String[] commands= {"CONNECT","SEND","SUBSCRIBE","UNSUBSCRIBE","DISCONNECT"};

    @Override
    public void start(int connectionId, Connections<String> connections) {
        this.connections=connections;
        this.connectionId=connectionId;
    }

    @Override
    public void process(String message) 
    {
        int index=0;
        String regex= "/n";
        String[] lines= message.split(regex);
        lines= fixedFrameArray(lines);//returns an array with no \n and no spaces at the end of the lines
        
        if(!isCommand(lines[0]))
            connections.send(connectionId, "ERROR, no command was found");
        else
            switch(lines[0]){
                case "CONNECT":
                    caseConnect(lines);
                    break;

                case "SEND":
                caseSend(lines);             
                    break;

                case "SUBSCRIBE":
                   
                    break;
                case "UNSUBSCRIBE":
                    break;
                case "DISCONNECT":
                    disconnect();
                    break;
            }
        

        
        
    }

    @Override
    public boolean shouldTerminate() {
        // TODO Auto-generated method stub
        return terminate;
    }

    public void disconnect(){
        connections.disconnect(connectionId);
    }

    public boolean isCommand(String command){
        for (int i = 0; i < commands.length; i++) {
            if(commands[i].equals(command))
                return true;
        }
        return false;
    }


    public String[] fixedFrameArray(String[] lines){
        String [] fixed;
        int insertIndex=0;
        List<String> strings= new LinkedList<String>();
        for(String s:lines){
            s.trim();
            if(!s.equals("")){
                strings.add(s);
            }
        }
        fixed= new String[strings.size()];
        for(String s:strings){
            fixed[insertIndex]=s;
            if(insertIndex>0)
                fixed[insertIndex].toLowerCase();
            insertIndex++;
        }
        return fixed;
    
}


public void  caseConnect(String[] lines){

    String password="";
    String username="";
    int index=1;
    boolean Ishost=false;
    boolean IsacceptVersion=false;
    boolean Isusername=false;
    boolean Ispassword=false;
    while(index<lines.length-1)
    {
        if(lines[index].split(":")[0].equals("host")){
            if(!lines[index].split(":")[1].equals("stomp.cs.bgu.ac.il"))
                connections.send(connectionId, "ERROR, host is not valid");
            else
                Ishost=true;
        }
        if(!lines[index].split(":")[0].equals("accept-version")){
            if(!lines[index].split(":")[1].equals("1.2"))
                connections.send(connectionId, "ERROR, accept-version is not valid");
            else
                IsacceptVersion=true;
        }
        if(lines[index].split(":")[0].equals("username")){
            if(lines[index].split(":")[1].equals(""))
                connections.send(connectionId, "ERROR, username is not valid");
            else{
                 username= lines[index].split(":")[1];
                 Isusername=true;}
        }
        
        if(lines[index].split(":")[0].equals("password")){ 
            if(lines[index].split(":")[1].equals(""))
                connections.send(connectionId, "ERROR, password is not valid");
            else{
                Ispassword=true;
                password= lines[index].split(":")[1];
            }
         }

        index++;
        
    
     if(Ispassword&&IsacceptVersion&&Ishost&&Isusername&&lines[lines.length-1].equals("\u0000"))
        connections.connect(username, password, connectionId);
        
}
}


public void caseSend(String[] lines)
{
    String destination="";
    String body="";
    int index=1;
    boolean Isdestination=false;
    boolean Isbody=false;
    while(index<lines.length-1)
    {
        if(lines[index].split(":")[0].equals("destination")){
            if(lines[index].split(":")[1].equals(""))
                connections.send(connectionId, "ERROR, destination is not valid");
            else{
                 destination= lines[index].split(":")[1];
                 Isdestination=true;}
        }
        else{Isbody=true;
            body+= lines[index];}
        index++;
        
    
     if(Isbody&&Isdestination&&lines[lines.length-1].equals("\u0000"))
        connections.send(destination, body, connectionId);
        
}
}

}