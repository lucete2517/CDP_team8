// 클라우드 VM에 구축한 서버에서 작동시킬 수 있도록 수정함
const express = require('express');
const mysql = require('mysql');
const ejs = require('ejs');
const path = require('path');
const test = express();
const port = 3000;

const conn = mysql.createConnection({
    host : 'localhost',
    user : 'user0',
    password : '1234',
    database : 'database0',
    dateStrings : 'date',
    multipleStatements: true
});

conn.connect();

var sql1 = 'SELECT * FROM state; ';
var sql2 = 'SELECT * FROM module; ';

test.use(express.static(path.join(__dirname, 'public')));
test.engine('html', require('ejs').renderFile);
test.set('view engine', 'ejs');
test.set('views', './views');

test.get('/', function(request, response) {
    conn.query(sql1 + sql2, function(err, result, fields) {
        if(err) throw err;

        response.render("index.ejs", {data : result});
    });
});

test.listen(port, function() {
    console.log('Connecting');
});