# setsockopt_shim

#### 
- Force enables SO_REUSEADDR for a socket() that uses bind()
- So we can start and stop ./proxy without waiting for TIME_WAIT state

####
- Usage
```
LD_PRELOAD=./socket_shim.so ./proxy
```
