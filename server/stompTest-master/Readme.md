# STOMP TEST
This is a test for bgu spl stomp server

To run this code you need to have the following:
1. Linux or The VM or The given docker.
2. python 3.6 or above installed.
3. and installing stomp.py

### How To install stomp.py

    pip3 install stomp.py

make sure you have python installed


## How to run
1. Run you server on port 7777
2. Then run the fallowing command in the terminal for the folder of the test:
   
 
    python3 stompTest.py

3. You should see the following output:
   
```
I must not fear.
Fear is the mind-killer.
Fear is the little-death that brings total obliteration.
I will face my fear.
I will permit it to pass over me and through me.
And when it has gone past I will turn the inner eye to see its path.
Where the fear has gone there will be nothing.
Only I will remain.
--- Frank Herbert, Dune
disconnected 1
disconnected 2
disconnected 3
```


### Extra

You can change the ip and the port for the tests by running like this:

    python3 stompTest.py --ip <ip> --port <port>

And check double login by running:

    python3 stompTest.py --doubleLogin

or

    python3 --ip <ip> --port <port> --doubleLogin

This should add an error frame for a user already logged in.
