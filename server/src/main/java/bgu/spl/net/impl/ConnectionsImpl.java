package bgu.spl.net.impl;

import java.util.Collection;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
//import java.util.Dictionary;
import java.util.WeakHashMap;

import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;

public class ConnectionsImpl<T> implements Connections<T> {
    WeakHashMap<Integer, ConnectionHandler<T>> connections = new WeakHashMap<Integer,ConnectionHandler<T>>();;//clientId, connectionHandler
    //List <ConnectionHandler<T>> connectionHandlers= new LinkedList<ConnectionHandler<T>>();;
    HashMap<Integer,HashMap<Integer,String>> topicsOfClient=new HashMap<>();// [client id, and [topic id, sbscribed string]]    [integer,[integer,string]]
    HashMap<String, List<Integer[]>> subscriptionsOfChannel= new HashMap<>();// topic name and another hash map with connection id and its topic id// 
    HashMap<String,String> UserNameToPassword= new HashMap<>();//[Name,Password]
    HashMap<String,Integer> UserNameToConnctionId =new HashMap<>();//[Name,ConnectionId]
    Integer messageId=0;
    @Override
    public boolean send(int connectionId, T msg) {
        try{
            connections.get(connectionId).send(msg);
            return true;
        }
  
            catch(Exception e){
            return false;
        }
    }

    @Override
    public void send(String channel, T msg, int connectionId){
         
        List<Integer[]> ClientIDtoTopicID= subscriptionsOfChannel.get(channel);
        for(Integer[] arr: ClientIDtoTopicID)
        {
            send(arr[0], msg);
        }

        messageId++;
    }

    @Override
    public void disconnect(int connectionId) {
        connections.remove(connectionId);
        UserNameToConnctionId.remove(getUserName(connectionId));
    }
    private String getUserName(int connectionId){
        for(String name: UserNameToConnctionId.keySet()){
            if(UserNameToConnctionId.get(name)==connectionId)
                return name;
        }
        return null;
    }

    public void connect(String name,String password,int conntionId){//not sure if i need a new connection handler or should i give him one
       //if not contains name
        UserNameToPassword.put(name, password);
        UserNameToConnctionId.put(name, conntionId);
        //how to add a connection handler ???SSS
        
    }

    public boolean isRegisterd(String userName)
    {
        if(UserNameToPassword.containsKey(userName))
            return true;
        return false;
    }

    public boolean isConnected(int connectionId)
    {
        if(UserNameToConnctionId.containsValue(connectionId))
            return true;
         return false;
    }

    public boolean IsSubscribed(int connectionId, String chanel)
    {
        HashMap<Integer,String> map =topicsOfClient.get(connectionId);
        Collection<String>c= map.values();
        if(!c.contains(chanel))
            return false;

            return true;
    }

    public void subscribe(int connectionId, String chanel, int topicId){
    
       if(!subscriptionsOfChannel.containsKey(chanel))
       {
           List<Integer[]> list = new LinkedList<>();
           Integer[] arr = new Integer[2];
           arr[0]=connectionId;
           arr[1]=topicId;
           list.add(arr);
           subscriptionsOfChannel.put(chanel, list);
       }
       else
       {
           Integer[] arr = new Integer[2];
           arr[0]=connectionId;
           arr[1]=topicId;
           subscriptionsOfChannel.get(chanel).add(arr);
       }
    }

    public void unsubscribe(int id, int connectionId)
    {
        HashMap<Integer,String> map =topicsOfClient.get(connectionId);
        String chanel=map.get(id);
        map.remove(id);
        for(Integer[] a: subscriptionsOfChannel.get(chanel))
        {
            if(a[0]==connectionId)
                subscriptionsOfChannel.get(chanel).remove(a);
        }
    }
    public void addConnection(ConnectionHandler<T> handler,int connectionId){
        connections.put(connectionId, handler);
    }

    public Integer getMessageId(){
        return messageId;
    }
    public Integer getClientTopicId(int connectionId, String chanel){
        HashMap<Integer,String> map =topicsOfClient.get(connectionId);
        for(Integer i: map.keySet()){
            if(map.get(i).equals(chanel))
                return i;
        }
        return -1;
    }
    
    
}

