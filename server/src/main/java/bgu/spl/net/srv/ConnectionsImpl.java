package bgu.spl.net.srv;

//import java.util.Dictionary;
import java.util.WeakHashMap;

public class ConnectionsImpl<T> implements Connections<T> {
    WeakHashMap<Integer, ConnectionHandler<T>> connections;
    
    public ConnectionsImpl(){
        connections = new WeakHashMap<Integer,ConnectionHandler<T>>();
    }

    @Override
    public boolean send(int connectionId, T msg) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public void send(String channel, T msg) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void disconnect(int connectionId) {
        // TODO Auto-generated method stub
        
    }
    
}