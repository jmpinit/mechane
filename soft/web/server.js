var express = require('express');
var app = express();
var net = require('net');
var sys = require('sys');

var client_socket = null;

app.configure(function(){
	app.use(express.static(__dirname + '/public'));
});

app.put("/dl", function(req, res) {
	var valid = false;

	req.on('data', function(chunk) {
		var data = JSON.parse(chunk);
		//console.log('data: ' + JSON.stringify(data, null, 4));
		console.log(JSON.stringify(data));
		res.end();

		if(client_socket) {
			client_socket.write(JSON.stringify(data, null, 0));
		}
	});
});

// Setup a tcp server
var server = net.createServer(function (socket) {

  // Every time someone connects, tell them hello and then close the connection.
  socket.addListener("connect", function () {
    sys.puts("Connection from " + socket.remoteAddress);
    //socket.end("Hello World\n");
    client_socket = socket;
  });

});

app.listen(9000);
console.log('Listening on port 9000');

// Fire up the server bound to port 7000 on localhost
server.listen(7000);

// Put a friendly message on the terminal
console.log("TCP server listening on port 7000");