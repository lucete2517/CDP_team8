const express = require('express');
const mysql = require('mysql');
const ejs = require('ejs');
const path = require('path')
const test = express()
const port = 3000

// database에 연결
const conn = mysql.createConnection({
    host : 'localhost',
    user : 'root',
    password : '456258',
    database : 'test02',
    multipleStatements: true
});

conn.connect();

var sql1 = 'SELECT * FROM state; ';
var sql2 = 'SELECT * FROM module; ';

test.use(express.static(path.join(__dirname, 'public')));

test.get('/', (request, response) => {
    conn.query(sql1 + sql2, function(err, result, fields) {
        if(err) throw err;

        var sql1_list = result[0] // state
        var sql2_list = result[1] // module

        //response.json(result[0]);
        //conn.release();

        //response.send(sql1_list)
        response.render("index.html");
    });
});
test.listen(port, () => console.log('Connecting'))