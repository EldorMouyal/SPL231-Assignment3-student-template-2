package bgu.spl.net.impl;

import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.Server;

import java.util.LinkedList;
import java.util.List;
import java.util.regex.Pattern;

import javax.lang.model.util.ElementScanner6;

import org.omg.CORBA.FloatSeqHelper;

public class StompMessagingProtocolImpl implements StompMessagingProtocol<String> {
    Connections<String> connections;
    private int connectionId;
    private boolean terminate= false;
    private String[] commands= {"CONNECT","SEND","SUBSCRIBE","UNSUBSCRIBE","DISCONNECT"};
    private String errorM="ERROR\nmessage : malformed frame received\n\n"+"The message:\n-----\n";

    @Override
    public void start(int connectionId, Connections<String> connections) {
        this.connections=connections;
        this.connectionId=connectionId;
    }

    @Override
    public void process(String message) 
    {
        String regex= "/n";
        String[] lines= message.split(regex);
        lines= fixedFrameArray(lines);//returns an array with no \n and no spaces at the end of the lines
        this.errorM="ERROR\n"+checkReciptToAddForError(lines)+"message : malformed frame received\n\n"+"The message:\n-----\n";
        if(!isCommand(lines[0]))
            connections.send(connectionId, errorM+"no command was found");
        else
            switch(lines[0]){
                case "CONNECT":
                    caseConnect(lines,message);
                    break;

                case "SEND":
                caseSend(lines,message);             
                    break;

                case "SUBSCRIBE":
                   caseSubscribe(lines,message);
                    break;
                case "UNSUBSCRIBE":
                caseUnsubscribe(lines,message);
                    break;
                case "DISCONNECT":
                    caseDisconnect(lines,message);
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


public void  caseConnect(String[] lines,String message){

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
                connections.send(connectionId, errorM+"host is not valid");
            else
                Ishost=true;
        }
        if(!lines[index].split(":")[0].equals("accept-version")){
            if(lines[index].split(":").length>1&&!lines[index].split(":")[1].equals("1.2"))
                connections.send(connectionId, errorM+"accept-version is not valid");
            else
                IsacceptVersion=true;
        }
        if(lines[index].split(":")[0].equals("username")){
            if(lines[index].split(":").length==1)
                connections.send(connectionId, errorM+"username is not valid");
            else{
                 username= lines[index].split(":")[1];
                 Isusername=true;}
        }
        
        if(lines[index].split(":")[0].equals("password")){ 
            if(lines[index].split(":").length==1)
                connections.send(connectionId, errorM+"password is not valid");
            else{
                Ispassword=true;
                password= lines[index].split(":")[1];
            }
         }

        index++;
        
    
     if(Ispassword&&IsacceptVersion&&Ishost&&Isusername&&lines[lines.length-1].equals("\u0000"))
       {
        connections.connect(username, password, connectionId);
        connections.send(connectionId, "CONNECTED\nversion:1.2\n\n\u0000");
        checkAndSendRecipt(lines);
       }
        
}
}


public void caseSend(String[] lines,String message)
{
    String destination="";
    String body="";
    int index=1;
    boolean Isdestination=false;
    boolean Isbody=false;
    boolean recipt=false;
    while(index<lines.length-1)
    {
        if(lines[index].split(":")[0].equals("destination")){
            if(lines[index].split(":").length==1)
                connections.send(connectionId, errorM+"destination is not valid");
            else{
                 destination= lines[index].split(":")[1];
                 Isdestination=true;}
        }
        else{Isbody=true;
            body+= lines[index];}
        index++;
        
    
     if(Isbody&&Isdestination&&lines[lines.length-1].equals("\u0000")){
        body="MESSAGE\nsubscription:"+Integer.toString(connections.getClientTopicId(connectionId,destination))+"\n"+"message - id:"+Integer.toString(connections.getMessageId())+"\ndestination:"+destination+"\n\n"+body+"\n\u0000";
        connections.send(destination, body,connectionId);
        checkAndSendRecipt(lines);

    }
        
        }
    }

    public void caseSubscribe(String[] lines,String message)
    {
        int i=1;
        boolean IsTopic=false;
        boolean IsId=false;
        String topic="";
        int id=-77;
        while(i<lines.length-1)
        {
            if(lines[i].split(":")[0].equals("destination")){
                if(lines[i].split(":").length==1)
                    connections.send(connectionId, errorM+"destination is not valid");
                else{
                     topic= lines[i].split(":")[1];
                     IsTopic=true;} 
            }
            if(lines[i].split(":")[0].equals("id")){
                if(lines[i].split(":").length==1)
                    connections.send(connectionId, errorM+"id is not valid");
                else{
                     id= Integer.parseInt(lines[i].split(":")[1]);
                     IsId=true;} 
            }
            i++;
        }

        if(IsTopic&&IsId&&lines[lines.length-1].equals("\u0000")){
            connections.subscribe(connectionId,topic, id);
            checkAndSendRecipt(lines);
        }
        
    }

    public void caseUnsubscribe(String[] lines,String message)
    {
        
        for(int i=1; i<lines.length-1; i++)
        {if(lines[i].split(":")[0].equals("id"))
        {
            if(lines[i].split(":").length==1)
                connections.send(connectionId, errorM+"id is not valid");
            else if(lines[lines.length-1].equals("\u0000")){
                int id= Integer.parseInt(lines[i].split(":")[1]);
                connections.unsubscribe(connectionId,id);
                checkAndSendRecipt(lines);
                break;
                 }
                 else{
                    connections.send(connectionId, errorM+"no end of frame character was found");}
        }}
        
    }

    public void caseDisconnect(String[] lines,String message)
    {
        int recipt = Integer.parseInt(lines[1].split(":")[1]);
        if(lines[lines.length-1].equals("\u0000")){
            connections.send(connectionId, "RECEIPT\nreceipt -id:"+recipt+"\n\u0000");
            disconnect();
        }
        else{
            connections.send(connectionId, errorM+"no end of frame character was found");
        }

    }
    public void checkAndSendRecipt(String[] lines)
    {
        for(int i=1; i<lines.length-1; i++)
        if(lines[i].split(":")[0].equals("receipt -id"))
        {
            if(lines[1].split(":").length==1)
                connections.send(connectionId, errorM+"receipt is not valid");
            else {
                int recipt = Integer.parseInt(lines[i].split(":")[1]);
                connections.send(connectionId, "RECEIPT\nreceipt -id:"+recipt+"\n\u0000");
            }
        
        }
    }


    public String checkReciptToAddForError(String[] lines)
    {
        for(int i=1; i<lines.length-1; i++){
        if(lines[i].split(":")[0].equals("receipt -id"))
        {
            if(lines[1].split(":").length==1){
                connections.send(connectionId, errorM+"receipt is not valid");
                return "";}
            else {
                int recipt = Integer.parseInt(lines[i].split(":")[1]);
                return "receipt -id:"+recipt+"\n";
            }
        
        }
    }
    return "";
    }
    

}