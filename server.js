const express = require("express");
const bodyParser = require("body-parser");
const app = express();
const fs = require("fs");
app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.static('public'));
app.get("/",(req,res)=>{
  console.log("data");
  res.send("Hello");
});

app.get('/getData', (req, res) => {
  fs.readFile('write_data.txt', 'utf8', (err, data) => {
    if (err) {
      console.error('Error reading file:', err);
      res.status(500).send('Error reading file');
    } else {

      console.log('Data read from file:', data);
      res.send(data);
    }
  });
});

app.post("/", (req,res)=>{
    var azimuth = body.req.azimuth;
    var elevation = body.req.elevation;

    const data = azimuth+" "+elevation;
    fs.appendFile("E:\SolarTracker\azimuth_elevation_writefile.txt", data, (err) => {
    if (err) {
      console.error('Error writing to file:', err);
      res.status(500).send('Error writing to file');
    } else {
      console.log('Angles written to file:', data);
      res.send('Angles received and written to file. azimuth_elevation_writefile');
    }
  });
});

app.listen(3000, ()=>{
  console.log("server is listening using port 3000");
});
