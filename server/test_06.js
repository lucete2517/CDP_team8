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
    database : 'test',
    dateStrings : 'date',
    multipleStatements: true
});

conn.connect();

var sql1 = 'SELECT * FROM Operation; ';
var sql2 = 'SELECT * FROM State; ';
var sql3 = 'SELECT * FROM Sensor; '

test.use(express.static(path.join(__dirname, 'public')));
test.engine('html', require('ejs').renderFile);
test.set('view engine', 'ejs');
test.set('views', './views');

test.get('/', function(request, response) {
    // 대표님 페이지 통계
    /*
    conn.query(sql1 + sql2, function(err, result, fields) {
        if(err) throw err;
        response.render("index.ejs", {data : result});
    });
    */
   // 현장 관리자 페이지 통계
   
    conn.query(sql3, function(err, result, fields) {
        if(err) throw err;
        response.render("admin.ejs", {data : result});
    });
    
});

test.listen(port, function() {
    console.log('Connecting');
}); 