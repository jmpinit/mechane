var express = require('express');
var app = express();
var net = require('net');
var sys = require('sys');

/*var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort("/dev/ttyUSB0", {
	  baudrate: 4800
});*/

var client_socket = null;

app.configure(function(){
	app.use(express.static(__dirname + '/public'));
});

mode = "velocity";

app.put("/dl", function(req, res) {
	var valid = false;

	req.on('data', function(chunk) {
		var data = JSON.parse(chunk);
		console.log(JSON.stringify(data));
		console.log("yers");
		res.end();

		if("velocity" in data) {
			if(mode == "position") {
				serialport.write("\v");
				mode = "velocity";
			}

			serialport.write(data[velocity]);
		} else if("position" in data) {
			if(mode == "velocity") {
				serialport.write("\p");
				mode = "position";
			}

			serialport.write(data[position]);
		}
		/*if(client_socket) {
			client_socket.write(JSON.stringify(data));
		}*/
	});
});

// Setup a tcp server
/*var server = net.createServer(function (socket) {

  // Every time someone connects, tell them hello and then close the connection.
  socket.addListener("connect", function () {
    sys.puts("Connection from " + socket.remoteAddress);
    // socket.end("Hello World\n");
    client_socket = socket;
  });

});*/

app.listen(9000);
console.log('Listening on port 9000');

// Fire up the server bound to port 7000 on localhost
//server.listen(7000);

// Put a friendly message on the terminal
console.log("TCP server listening on port 7000");
