const SerialPort = require('serialport');
const port = new SerialPort('COM5', {
    baudRate: 9600,
});

let elPuerto= function(){
    port.on("open", function(){
        console.log("abieeeeerto");
    });
    port.on("data",data=>{
        console.log("Conteo: "+data.toString());
    });
}

module.exports = elPuerto;
