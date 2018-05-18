# Camera Detections Over Socket

This porject was tested for a UR3 robot to follow a line detected by camera. The UR3 was configurated as client, and the program was made on the teach pendant.

### Camera (C++)

Detects white lines and store 2 distant points in the line into a file in ../genfiles. 

### Server (Python)

Reads the points written in by the camera program and sends over socket.

### Usage

```sh
$ git clone <repo_url>
$ cd <repo_dir>/camera/src 
$ cmake .
$ make
```

Create a program in the teach pendant that receives the points and use them for robot motion. Then, connect to the robot by ethernet, put the IPs in the server and client nodes and:

```sh
$ ./camera
$ python ../sockets/server.py (in other terminal)
```

Run robot program.


