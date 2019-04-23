var express = require('express'),
app = express();
const port = 8000


var bodyParser = require('body-parser')
app.use(bodyParser.urlencoded())


app.get('/', function (req, res) {
	res.sendFile('index.html' , { root : __dirname});
});


app.post('/mode', function (req, res) {
    	var mode = req.body.choose;
    	var red = req.body.red;
    	var green = req.body.green;
    	var blue = req.body.blue;
    	var weather = req.body.weather
	console.log(mode);
	console.log(red);
	console.log(green);
	console.log(blue);
	res.sendFile('index.html' , { root : __dirname});
});


app.listen(port, () => console.log(`Example app listening on port ${port}!`))

