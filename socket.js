/*************************************************************************
 * File Name :  socket.js
 * Author  :      unasm
 * Mail :         unasm@sina.cn
 * Last_Modified: 2015-03-23 16:52:22
 ************************************************************************/

console.log("Server started");
var connects = new Array();
var WebSocketServer = require('ws').Server
, wss = new WebSocketServer({port: 8010});
wss.on('connection', function(ws) {
	//console.log(ws);
	ws.on('message', function(msg) {
		for(var i = 0,len = connects.length; i < len;i++){
			console.log("checking\n");
			console.log(connects[i].OPEN);
			console.log(connects[i].readyState);
			if(connects[i].readyState == connects[i].OPEN){
				if(connects[i] !== ws){
					connects[i].send(msg);
				}
			} else {
				console.log("not ready");
			}
		}
	});
	console.log("connection");
	connects.push(ws);
});
