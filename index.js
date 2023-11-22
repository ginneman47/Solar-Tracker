const express = require('express');
const axios = require('axios');
const bodyParser = require("body-parser");
const app = express();
const port = 4000;

app.use(express.static('public'));
app.use(bodyParser.urlencoded({extend:true}));
app.use(bodyParser.json());
app.get('/', (req, res) => {
  res.sendFile(__dirname + '/sample.html');
});

app.get('/rotate', async (req, res) => {
  try {
    // Fetch rotation angles from the server running on port 3000
    const response = await axios.get('http://localhost:3000/getRotationMovements');
    const { xAngle, yAngle } = response.data;
    res.json({ xAngle, yAngle });
  } catch (error) {
    console.error('Error fetching rotation angles:', error);
    res.status(500).json({ error: 'Internal Server Error' });
  }
});

app.listen(port, () => {
  console.log(`Server is running at 4000`);
});
