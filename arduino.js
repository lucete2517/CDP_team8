var SerialPort = require('serialport');

const parsers = SerialPort.parsers;
const parser = parsers.Readline({
    delimiter: '\r\n'
});

var port = SerialPort('/dev/cu.wchusbserialfa1410', {
    baudRate: 9600, 
    dataBits: 8, 
    parity: 'none', 
    stopBits: 1, 
    flowBits: false
});

port.pipe(parser);

parser.on('data', function(data) {
    console.log(data);
});