const SerialPort = require('serialport');
const port = new SerialPort('COM5', {
    baudRate: 250000,
});
// const port = new SerialPort('/dev/ttyS0', {
//     baudRate: 250000,
// });
const Readline = require('@serialport/parser-readline')
const parser = port.pipe(new Readline({ delimiter: '\r\n' }))

const controller = {
    index: function(req,res){
        let data;
        port.on("readable",()=>{
            data = port.read();
        });
        if(data){
            res.render('index',{
                data: data
            });
        }else{
            res.render('index',{
                data: "Sin datos nuevos"
            });
        }
        
    },
    on: function(req,res){
        port.write("on",function(err){
            if(err){
                return res.send("Error!: "+err.message)
            }
            console.log("---   ---   El led ha sido encendido   ---   ---");
        });
        res.redirect("/");
    },
    off: function(req,res){
        port.write("off",function(err){
            if(err){
                return res.send("Error!: "+err.message)
            }
            console.log("---   ---   El led ha sido apagao   ---   ---");
        });
        res.redirect("/");
    },
    listen: function(req,res){
        port.on("open", function(){
            console.log("abieeeeerto");
        });
        parser.on("data",data=>{
            console.log("Arcuino dice: "+data.toString());
        });
        res.send("Lisen!");
    },

    
};

module.exports = controller;