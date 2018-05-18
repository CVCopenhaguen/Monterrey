#!/urs/bin/python

# Echo client program
import socket
import sys
import time
import csv


################################################################

     ## Read points from file and space transformation ##

################################################################


#def readcsv(filename):	
    
    # Reading detected points
#    ifile = open(filename, "rU")
 #   reader = csv.reader(ifile, delimiter=";")

  #  rownum = 0	
   # a = []

    #for row in reader:
     #   a.append (row)
     #  rownum += 1
    
    #ifile.close()
        
    #return a


#################################################################

		    ## TCP/IP Communication ##

#################################################################


server_address = ('10.42.0.1', 30000)
print >>sys.stderr, 'Starting up on %s port %s' % server_address
count = 0
filen = "/home/charlie/workspace/Projects/simple_camera/genfiles/2Dpoints.txt"
 
while (count < 1000):
 s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
 s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
 s.bind(server_address) # Bind to the port 
 s.listen(5) # Now wait for client connection.
 c, addr = s.accept() # Establish connection with client.
 try:
   #msg = c.recv(1024)
   #print "Pose Position = ", msg
   #msg = c.recv(1024)
   #print "Joint Positions = ", msg
   msg = c.recv(1024)
   #print "Request = ", msg
   #time.sleep(1)
   if msg == "asking_for_data":
      print 'Message received:'
      print msg
      count = count + 1
      fil = open(filen, "r")
      for line in fil:	
         int_list = [int(i) for i in line.split()]
         print int_list
      #pots = fil.read()
      #int_list = pots.split('\n', 1)[0]
      x1 = int_list[0]
      y1 = int_list[1]
      x2 = int_list[2]
      y2 = int_list[3]
      #back_msg = "(", pts[0], ",", pts[1], ",", pts[2], ",", pts[3],")"
      back_msg = x1, y1, x2, y2
      back_m = str(back_msg)
      print 'Sending points:'
      print back_m
   #print "The count is:", count
   #time.sleep(0.5)
   #print ""
   #time.sleep(0.5)
      c.send(back_m);
   #print "Send 200, 50, 45"
 except socket.error as socketerror:
   print count
 
c.close()
s.close()
print "Program finish"
