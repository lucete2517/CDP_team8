const express = require('express');
const http = require('http');
const mysql = require('mysql');

const app = express();
app.use(express.static(__dirname));

const client = mysql.createConnection({
    host : 'localhost',
    user : 'user0',
    password : '1234',
    database : 'database0'
});
client.connect();

function insert_person() {
    var Pid = document.getElementById('Pid');
    var Pname = document.getElementById('Pname');
    var Btype = document.getElementById('Btype');
    var Rrn = document.getElementById('Rrn');
    var Email = document.getElementById('Email');
    var Phone = document.getElementById('Phone');

    console.log('insert into PERSON values(\'' + 
    Pid.value + '\', \'' + Pname.value + '\', \'' + Btype.value + '\', \'' + Rrn.value + '\', \'' + Email.value + '\', \'' + Phone.value + '\');');
    client.query('insert into PERSON values(\'' + 
    Pid.value + '\', \'' + Pname.value + '\', \'' + Btype.value + '\', \'' + Rrn.value + '\', \'' + Email.value + '\', \'' + Phone.value + '\');');
}

function insert_equip() {
    var Eid = document.getElementById('Eid');
    var Ename = document.getElementById('Ename');
    
    console.log('insert into EQUIP values(\'' + Eid.value + '\', \'' + Ename.value + '\'):');
    client.query('insert into EQUIP values(\'' + Eid.value + '\', \'' + Ename.value + '\'):');
}

app.listen(3000, function(){
    console.log('Server opened.\n');
});

app.get('/', function(req, res){
    res.sendFile(__dirname + '/input.html');
});