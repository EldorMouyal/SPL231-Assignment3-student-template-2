package bgu.spl.net.srv;

import java.io.IOException;


public interface Connections<T> {

    boolean send(int connectionId, T msg);

    void send(String channel, T msg,int connectionId);

    void disconnect(int connectionId);

    void connect(String username, String password, int connectionId);
    public void addHandler(ConnectionHandler<T> handler,int connectionId);
}
