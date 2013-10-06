var express = require('express');
var app = express();
var net = require('net');
var sys = require('sys');

app.configure(function(){
	app.use(express.static(__dirname + '/public'));
});

// Setup a tcp server
var server = net.createServer(function (socket) {

  // Every time someone connects, tell them hello and then close the connection.
  socket.addListener("connect", function () {
    sys.puts("Connection from " + socket.remoteAddress);
    socket.end("Hello World\n");
  });

});

app.listen(9000);
console.log('Listening on port 9000');

// Fire up the server bound to port 7000 on localhost
server.listen(7000);

// Put a friendly message on the terminal
console.log("TCP server listening on port 7000");