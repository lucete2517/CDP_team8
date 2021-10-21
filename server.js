const express = require('express');
const http = require('http');
const mysql = require('mysql');

const app = express();
app.use(express.static(__dirname));

var client = mysql.createConnection({
    host : 'localhost',
    user : 'user0',
    password : '1234',
    database : 'database0',
});
client.connect();

function insert_person() {
    var Pid = document.getElementById('Pid');
    var Pname = document.getElementById('Pname');
    var Rrn = document.getElementById('Rrn');
    var Position = document.getElementById('Position');
    var Email = document.getElementById('Email');
    var Password = document.getElementById('Password');
    var Blood_type = document.getElementById('Blood_type');
    var Phone = document.getElementById('Phone');
    console.log('insert into PERSON values(\'' + Pid.value + '\', \'' + Pname.value + '\', \'' + Rrn.value + '\', \'' + Position.value + '\', \'' + Email.value + '\', \'' + Password.value + '\', \'' + Blood_type.value + '\', \'' + Phone.value + '\');');
    //client.query('insert into PERSON values(\'' + Pid.value + '\', \'' + Pname.value + '\', \'' + Rrn.value + '\', \'' + Position.value + '\', \'' + Email.value + '\', \'' + Password.value + '\', \'' + Blood_type.value + '\', \'' + Phone.value + '\');');
}

app.listen(3000, function(){
    console.log('Server opened.\n');
});

app.get('/', function(req, res){
    res.sendFile(__dirname + '/input.html');
});