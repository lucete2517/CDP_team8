var express = require('express');
var http = require('http');
var mysql = require('mysql');
var path = require('path');

var app = express();
app.use(express.static(path.join(__dirname)));

app.use(express.static(path.join(__dirname, 'functions')));

app.listen(3000, function(){
    console.log('Server opened.\n');
});

app.get('/', function(req, res){
    res.sendFile(__dirname + '/input.html');
});