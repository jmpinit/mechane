// by Chtiwi Malek on CODICODE.COM

var mousePressed = false; 
var lastX, lastY;
var ctx;
var points = new Array();
var data = new Object();

function InitThis() {
    ctx = document.getElementById('myCanvas').getContext("2d");

    $('#myCanvas').mousedown(function (e) { 
        mousePressed = true;
        points = [];

        Draw(e.pageX - $(this).offset().left, e.pageY - $(this).offset().top, false);
    });

    $('#myCanvas').mousemove(function (e) {
        if (mousePressed) {
            var x = Math.round(e.pageX - $(this).offset().left);
            var y = Math.round(e.pageY - $(this).offset().top);
            console.log(x);
            Draw(x, y, true);
            console.log(e.timeStamp);
            points.push({"x":x,"y":y});
        }
    });

    $('#myCanvas').mouseup(function (e) {
        mousePressed = false;
        sendToSocket(points);
        console.log(JSON.stringify(points, null, 4)); 
    });

    $('#myCanvas').mouseleave(function (e) {
        mousePressed = false;
        data.points = points;
        data.timestamp = e.timeStamp;
        sendToSocket(data);
        console.log(JSON.stringify(points, null, 4)); 
    });
}

function Draw(x, y, isDown) {
    if (isDown) {
        ctx.beginPath();
        ctx.strokeStyle = "black";
        ctx.lineWidth = "3";
        ctx.lineJoin = "round";
        ctx.moveTo(lastX, lastY);
        ctx.lineTo(x, y);
        ctx.closePath();
        ctx.stroke();
    }
    lastX = x;
    lastY = y;
}

function clearArea() {
    // Use the identity matrix while clearing the canvas
    ctx.setTransform(1, 0, 0, 1, 0, 0);
    ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);
}

function sendToSocket(data) {
    $.post('socket.php', 
    {
        coords: data
    }, 
    function(data) 
    {
        $("#coordsResponse").html(data).fadeIn('80');

    }, 
    'text');   
}
