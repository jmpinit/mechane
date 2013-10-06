var fs = require('fs');
var express = require('express');
var app = express();

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
