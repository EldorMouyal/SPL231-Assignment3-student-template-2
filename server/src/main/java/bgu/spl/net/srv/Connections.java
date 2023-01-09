package bgu.spl.net.srv;



public interface Connections<T> {

    boolean send(int connectionId, T msg);

    void send(String channel, T msg,int connectionId);

    void disconnect(int connectionId);

    void connect(String username, String password, int connectionId);
    public void addConnection(ConnectionHandler<T> handler,int connectionId);
    public void subscribe(int connectionId, String chanel, int topicId);
    public void unsubscribe(int id, int connectionId);
    public Integer getMessageId();
    public Integer getClientTopicId(int connectionId, String chanel);
    public boolean IsSubscribed(int connectionId, String chanel);
    public boolean isRegisterd(String userName);
    public boolean isConnected(int connectionId);
}
