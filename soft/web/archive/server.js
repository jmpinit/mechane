var fs = require('fs');
var express = require('express');
var app = express();
// var sh = require('sh');

app.configure(function(){
	app.use(express.static(__dirname + '/public'));
});

app.put("/dl", function(req, res) {
	var valid = false;

	req.on('data', function(chunk) {
		var data = JSON.parse(chunk);
		console.log('downloading ' + data.url);

		if(grabber.recognize(data.url)) {
			//grabber.grab(data.url);

			res.writeHead(200, "OK", {'Content-Type': 'text/html'});
			console.log("OK");
		} else {
			res.writeHead(400, "Bad Request", {'Content-Type': 'text/html'});
			console.log("Bad Request");
		}

		res.end();
	});
});

app.listen(9000);
console.log('Listening on port 9000');


// var net = require('net');

// // Setup a tcp server
// var server = net.createServer(function (socket) {

//   // Every time someone connects, tell them hello and then close the connection.
//   socket.addListener("connect", function () {
//     sys.puts("Connection from " + socket.remoteAddress);
//     socket.end("Hello World\n");
//   });

// });

// // Fire up the server bound to port 7000 on localhost
// server.listen(7000);

// // Put a friendly message on the terminal
// console.log("TCP server listening on port 7000");
