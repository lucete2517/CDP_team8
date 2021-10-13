const express = require('express');
const mysql = require('mysql');
const ejs = require('ejs');
const test = express()
const port = 3000

const conn = mysql.createConnection({
    host : 'localhost',
    user : 'root',
    password : '456258',
    database : 'test'
});

conn.connect(function(err) {
    if(err) throw err;
    console.log('Connected');
});

test.set('vuew engine', 'ejs');

test.get('/', (request, response) => {
    conn.query('SELECT * FROM test', function(err, result, fields) {
        if(err) throw err;
        response.send(result)
        //response.render('index', {users : result});
    });
});

test.listen(port, () => console.log('Connecting'))