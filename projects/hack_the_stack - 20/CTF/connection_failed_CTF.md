1. go over both files in gidra and review the codes.
2. we understand that we communicate with the client file, and that it expects the input "YES" and enter it to local_3c variable.
3. when we give it this input it tries to connect to the server and ask the flag but connect functiob failed.
4. when we exmine why it failed, we check and everything looks fine, so we check what ip the server is lisening on 
   (we can find it in two ways:
   1. in gidra exemine the variable local_33 tells us that it's the ip 127.1.33.7
   2. run the server program and on another terminal run netstat -npa | grep server)
      and we can tell that the client is trying to connect to another ip (127.0.0.1) that the server is not bind to and that's why it failed.
5. so we know that our "YES" is going to the variable "local_3c", and we check in gidra what is the offset from it
   to the local_32 variable, wich holds the (currentlly wrong) ip that the client enter to connect.
6. so local_3c is 8 byte, and after it comes local_34 of 2 byte size. but we enter the letters YES + NULL     terminator wich is 4 characters so we need to enter 6 more characters to get to the local_32 variable that hold the ip address for connect function.
7. so in the terminal we put the following string: YES^@123456127.1.33.7 and the connect is working! ("^@" is one character, it's ctrl+v and then ctrl+@ wich is a way to enter null character in the terminal.)

