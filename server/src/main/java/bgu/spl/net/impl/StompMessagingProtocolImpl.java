package bgu.spl.net.impl;

import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.Connections;

import java.util.LinkedList;
import java.util.List;



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
        String regex= "\n";
        String[] lines= message.split(regex);
        lines= fixedFrameArray(lines);//returns an array with no \n and no spaces at the end of the lines
        this.errorM="ERROR\n"+checkReciptToAddForError(lines)+"message : malformed frame received\n\n"+"The message:\n-----\n";
        if(!isCommand(lines[0].toUpperCase()))
            sendError("no command was found");
        else
            switch(lines[0].toUpperCase()){
                case "CONNECT":
                System.out.println("connect in proccess");
                if(!connections.isConnected(connectionId))
                    caseConnect(lines,message);
                    else
                        sendError("Already connected");
                    break;

                case "STOMP":
                if(!connections.isConnected(connectionId))
                    caseConnect(lines,message);
                    else
                        sendError("Already connected");
                    break;
                case "SEND":
                if(!connections.isConnected(connectionId))
                    sendError("Not connected");
                    else
                        caseSend(lines,message);             
                    break;

                case "SUBSCRIBE":
                if(!connections.isConnected(connectionId))
                    sendError("Not connected");
                    else
                        caseSubscribe(lines,message);
                    break;
                case "UNSUBSCRIBE":
                if(!connections.isConnected(connectionId))
                    sendError("Not connected");
                    else
                        caseUnsubscribe(lines,message);
                    break;
                case "DISCONNECT":
                if(!connections.isConnected(connectionId))
                    sendError("Not connected");
                    else
                        caseDisconnect(lines,message);
                    break;
            }
        

            errorReset();
        
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
            fixed[insertIndex]=s.trim();
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
    while(index<lines.length)
    {
        if(lines[index].split(":")[0].equals("host")){
            if(!lines[index].split(":")[1].equals("stomp.cs.bgu.ac.il"))//local host case is for testing
            sendError("host is not valid");
            else
                Ishost=true;
        }
        if(lines[index].split(":")[0].equals("accept-version")){
            if(lines[index].split(":").length<=1||!lines[index].split(":")[1].equals("1.2"))
                sendError("accept-version is not valid");
            else
                IsacceptVersion=true;
        }
        if(lines[index].split(":")[0].equals("login")){
            if(lines[index].split(":").length==1)
            sendError("username is not valid");
            else{
                 username= lines[index].split(":")[1];
                 Isusername=true;}
        }
        
        if(lines[index].split(":")[0].equals("passcode")){ 
            if(lines[index].split(":").length==1)
            sendError("password is not valid");
            else if(!connections.isRegisterd(username)||connections.IsCorrectPassword(username,password)){
                Ispassword=true;
                password= lines[index].split(":")[1];
            }
            else
                sendError("wrong password");
         }

        index++;
        
}
if(Ispassword&&IsacceptVersion&&Ishost&&Isusername)
       {
        connections.connect(username, password, connectionId);
        connections.send(connectionId, "CONNECTED\nversion:1.2\n");
        checkAndSendRecipt(lines);
       }
       else
        terminate=true;
}


public void caseSend(String[] lines,String message)
{
    String destination="";
    String body="";
    int index=1;
    boolean Isdestination=false;
    boolean Isbody=false;
    while(index<lines.length)
    {
        if(lines[index].split(":")[0].equals("destination")){
            if(lines[index].split(":").length==1)
            sendError("destination is not valid");
            else{
                 destination= lines[index].split(":")[1];
                 Isdestination=true;}
        }
        else{Isbody=true;
            body+= lines[index];}
        index++;
        
    

    
        
        }
        if(Isbody&&Isdestination){
            if(!connections.IsSubscribed(connectionId, destination))
            sendError("Not subscribed to channel");
            else{
            body="MESSAGE\nsubscription:"+Integer.toString(connections.getClientTopicId(connectionId,destination))+"\n"+"message - id:"+Integer.toString(connections.getMessageId())+"\ndestination:"+destination+"\n\n"+body+"\n";
            connections.send(destination, body,connectionId);
            checkAndSendRecipt(lines);}
    
        }
    }

    public void caseSubscribe(String[] lines,String message)
    {
        int i=1;
        boolean IsTopic=false;
        boolean IsId=false;
        String topic="";
        int id=-77;
        while(i<lines.length)
        {
            if(lines[i].split(":")[0].equals("destination")){
                if(lines[i].split(":").length==1)
                sendError("destination is not valid");
                else{
                     topic= lines[i].split(":")[1];
                     IsTopic=true;} 
            }
            if(lines[i].split(":")[0].equals("id")){
                if(lines[i].split(":").length==1)
                sendError("id is not valid");
                else{
                     id= Integer.parseInt(lines[i].split(":")[1]);
                     IsId=true;} 
            }
            i++;
        }

        if(IsTopic&&IsId){
            connections.subscribe(connectionId,topic, id);
            checkAndSendRecipt(lines);
        }
        
    }

    public void caseUnsubscribe(String[] lines,String message)
    {
        
        for(int i=1; i<lines.length; i++)
        {if(lines[i].split(":")[0].equals("id"))
        {
            if(lines[i].split(":").length==1)
                {
                    sendError("id is not valid");
                }
            else{
                int id= Integer.parseInt(lines[i].split(":")[1]);
                connections.unsubscribe(id,connectionId);
                checkAndSendRecipt(lines);
                break;
                 }

        }}
        
    }

    public void caseDisconnect(String[] lines,String message)
    {
        if(lines[1].split(":").length==2&&lines[1].split(":")[0].equals("receipt")) {
            int recipt = Integer.parseInt(lines[1].split(":")[1]);
            connections.send(connectionId, "RECEIPT\nreceipt-id:" + recipt + "\n\u0000");
            disconnect();
        }
        else
            sendError("no valid receipt");
    }
    public void checkAndSendRecipt(String[] lines)
    {
        for(int i=1; i<lines.length; i++)
        if(lines[i].split(":")[0].equals("receipt"))
        {
            if(lines[1].split(":").length==1){
                sendError("receipt is not valid");
            }
            else {
                int recipt = Integer.parseInt(lines[i].split(":")[1]);
                connections.send(connectionId, "RECEIPT\nreceipt-id:"+recipt+"\n\u0000");
            }
        
        }
    }


    public String checkReciptToAddForError(String[] lines)
    {
        for(int i=1; i<lines.length; i++){
        if(lines[i].split(":")[0].equals("receipt"))
        {
            if(lines[1].split(":").length==1){
                sendError("receipt is not valid");
                return "";}
            else {
                int recipt = Integer.parseInt(lines[i].split(":")[1]);
                return "receipt-id:"+recipt+"\n";
            }
        
        }
    }
    return "";
    }

    private void errorReset()
    {
        this.errorM="ERROR\nmessage : malformed frame received\n\n"+"The message:\n-----\n";

    }

    private void sendError(String message)
    {
        errorM+=message+"\n-----\n";
        connections.send(connectionId, errorM);
        disconnect();
        terminate=true;
    }
    public void Terminate()//for test purposes only
    {
        terminate=true;
    }
    

}